#include "Entity.h"

Entity::Entity()
	:m_position({0.f,0.f,0.f})
{
}

Entity::Entity(Vector3 position)
	:m_position(position)
{
}

Vector3 Entity::GetPosition() const
{
	return m_position;
}

void Entity::Move(Vector3 velocity, float delta, float baseSpeed)
{
	this->m_position = Vector3Add(Vector3Scale(velocity,delta*baseSpeed), this->m_position);
}
