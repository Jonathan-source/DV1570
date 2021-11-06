#include "Player.h"

Player::Player()
	:m_health(100),
	m_attackDmg(1),
	m_runSpeed(1)
{}

Player::Player(irr::core::vector3d<float>& position, irr::scene::IMesh* mesh, irr::video::ITexture* texture, int health, int attdmg, float runSpeed)
	:Entity(position, mesh, texture),
	m_health(health),
	m_attackDmg(attdmg),
	m_runSpeed(runSpeed)
{}

int Player::GetHealth() const
{
	return this->m_health;
}

int Player::GetAttackDamage() const
{
	return this->m_attackDmg;
}

float Player::GetRunSpeed() const
{
	return this->m_runSpeed;
}

void Player::SetHealth(int health)
{
	this->m_health = health;
}

void Player::SetAttackDamage(int attdmg)
{
	this->m_attackDmg = attdmg;
}

void Player::SetRunSpeed(float runSpeed)
{
	this->m_runSpeed = runSpeed;
}

irr::core::vector3d<float> Player::GetVelocity() const
{
	return velocity;
}

void Player::SetVelocity(const irr::core::vector3d<float>& velocity)
{
	this->velocity = velocity;
}
