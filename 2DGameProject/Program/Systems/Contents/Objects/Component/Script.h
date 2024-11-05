#pragma once
#include "../../../../Systems/BaseClasses/Component.h"

#define  SCRIPT_CLASS using myGame::Object::Script::Script;

namespace myGame::Object
{
	class Transform;

	class Script : public mySystem::IComponent
	{
	public:
		COMPONENT_CLASS;

		virtual void Setup()				 { /* empty */ }
		virtual void Start()		override { /* empty */ }
		virtual void Update()		override { /* empty */ }
		virtual void LateUpdate()	override { /* empty */ }
		virtual void End()			override { /* empty */ }

	public:
		virtual void Initialize() override final;
		virtual void Finalize() override final;

	protected:
		Transform* _transform;
	};
}