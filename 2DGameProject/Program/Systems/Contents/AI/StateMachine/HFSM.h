#pragma once
#include "../../../Typedef/Typedef.h"
#include "IStateMachine.h"

namespace myGame::AI
{
	template<class T>
	class State : public IState
	{
		using StatePtr = shared_ptr<State<T>>;
		using ChildStateList = unordered_map<int, StatePtr>;
		using TransitionMap = unordered_map<int, int>;

		const TypeID StateTypeNULL = 999;

	public: 
		State(T* context, State<T>* parent) :
			_context(context), _parentState(parent){ }
		~State() = default;

	public:
		T& GetContext() const noexcept { return *_context; }
		
		State<T>& GetParent() const noexcept{ return _parentState; }

		template<class S>
		const bool HasChildState() noexcept
		{
			TypeID childID = typeid(S);
			return _childStateMap.contains(childID);
		}

		const bool HasChildState(int childID) const noexcept { return _childStateMap.contains(childID); }

	public:

		void OnEnable()
		{
			enable = true;
			if (_childStateMap.empty()) return;

			for (const auto& child : _childStateMap)
			{
				child.second->OnEnable();
			}

			_currentChildState = _startChildState;
		}

		void OnDisable()
		{
			enable = false;
			if (_childStateMap.empty()) return;

			for (const auto& child : _childStateMap)
			{
				child.second->OnDisable();
			}

			_currentChildState = nullptr;
		}


	public:
		void SendEnter()
		{
			if (enable == false) return;

			OnEnter();

			_currentChildState = _startChildState;
			if (_currentChildState != nullptr)
			{
				_currentChildState->SendEnter();
			}
			
		}

		void SendUpdate()
		{
			if (enable == false) return;

			OnUpdate();

			if (_currentChildState != nullptr)
			{
				_currentChildState->SendUpdate();
			}
		}

		void SendExit()
		{
			if (enable == false) return;

			OnExit();

			if (_currentChildState != nullptr)
			{
				_currentChildState->SendExit();
			}
		}

		void SendTrigger(int eventId)
		{
			auto* state = this;
			while (state->_parentState != nullptr)
			{
				// Rootから探索する
				state = state->_parentState;
			}

			while (state != nullptr)
			{
				TypeID nextStateID = state->GetTransitionState(eventId);
				if (nextStateID != StateTypeNULL)
				{
					state->_parentState->ChangeState(nextStateID);
					break;
				}

				state = state->_currentChildState.get();
			}
		}

	public:

		template<class S>
		void RegisterStartState()
		{
			TypeID typeId = typeid(S).hash_code();
			bool hasState = HasChildState(typeId);
			if (hasState == false)
			{
				printf("ステートがありません\n");
				return;
			}
			_startChildState = _childStateMap[typeId];
		}


		template<class S>
		void AddTransition(int eventId)
		{
			TypeID stateID = typeid(S);
			AddTransition(eventId, stateID);
		}

		void AddTransition(int eventId, int stateId)
		{
			bool hasEvent = _transitionMap.contains(eventId);
			if (hasEvent == true)
			{
				printf("すでにイベントが登録されています\n");
				return;
			}

			_transitionMap[eventId] = stateId;
		}

		template<class S>
		void AddChildState()
		{
			TypeID id = typeid(S).hash_code();
			if (_childStateMap.contains(id)) return;

			auto newState = make_shared<S>(_context, this);
			_childStateMap[id] = newState;
			nameList.push_back(typeid(S).name());
		}


		template<class From, class To>
		void AddChildTransition(int eventID)
		{
			TypeID fromID = typeid(From).hash_code();
			TypeID toID = typeid(To).hash_code();

			bool hasChild = (HasChildState(fromID) && HasChildState(toID));
			if (hasChild == false)
			{
				printf("ステートが存在しません\n");
				return;
			}

			_childStateMap[fromID]->AddTransition(eventID, toID);
		}

	private:
		bool enable = false;
		T* _context = nullptr;
		State<T>* _parentState = nullptr;
		ChildStateList _childStateMap;
		TransitionMap _transitionMap;
		vector<string> nameList;

		StatePtr _startChildState;
		StatePtr _currentChildState;

	private:

		TypeID GetTransitionState(int eventId)
		{
			bool hasEvent = _transitionMap.contains(eventId);
			if (hasEvent == false) return StateTypeNULL;

			return _transitionMap[eventId];
		}

		void ChangeState(int stateId)
		{
			_currentChildState->SendExit();
			_currentChildState = _childStateMap[stateId];
			_currentChildState->SendEnter();
		}

	};

	template<class T>
	class HFSM : public IStateMachine
	{
	public:
		HFSM(T* context) : _context(context) {}
		~HFSM()
		{
			_context = nullptr;
		}

	public:
		const T& GetContext() const noexcept { return _context; }
		const bool Enable() const noexcept { return enable; }

	public:
		template <class S >
		void RegisterRootState()
		{
			_rootState = make_shared<S>(_context, nullptr);
		}

		void OnEnable()
		{
			if (_rootState == nullptr)
			{
				printf("RootStateが設定されていません\n");
				return;
			}

			enable = true;

			_rootState->OnEnable();
			_rootState->SendEnter();
		}

		void OnUpdate()
		{
			if (enable == false) return;

			_rootState->SendUpdate();
		}

		void OnDisable()
		{
			_rootState->SendExit();
			_rootState->OnDisable();

			enable = false;
		}

	private:
		shared_ptr<State<T>> _rootState;
		T* _context;

		bool enable = false;

	};

}