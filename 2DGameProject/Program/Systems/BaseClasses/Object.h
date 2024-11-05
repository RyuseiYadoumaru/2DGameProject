#pragma once
#include "../Typedef/Typedef.h"

#define OBJECT_CLASS using mySystem::Object::Object;

using Order = unsigned int;
using ID = unsigned int;
namespace mySystem
{
	class Object
	{
		static unsigned int _objectCouter;

	public:
		Object(string name, bool active = true);

		~Object() = default;

	public:
		const string& GetName() const noexcept { return _name; }
		void SetName(const string& name) noexcept { _name = name; }

		const bool IsActive() const noexcept { return isActive; }
		void SetActive(bool active) noexcept { isActive = active; }

		const unsigned int GetID() const noexcept { return _id; }

	protected:
		string _name;
		ID _id;
		bool isActive;

	};
}