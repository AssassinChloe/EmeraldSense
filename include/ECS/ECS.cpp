#include "ECS.hpp"

void Entity::addGroup(Group group)
{
	this->groupBitset[group] = true;
	this->manager.addToGroup(this, group);
}