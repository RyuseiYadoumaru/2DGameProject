#include "Object.h"

unsigned int mySystem::Object::_objectCouter = 0;

mySystem::Object::Object(string name, bool active)
	: _name(name), isActive(active)
{
	_id = _objectCouter;
	_objectCouter++;
}
