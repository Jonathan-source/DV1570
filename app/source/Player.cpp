#include "Player.h"
#include "EventHandler.h"

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

void Player::PlayerInput(const EventHandler& eventHandler)
{
	if (eventHandler.IsKeyDown(irr::KEY_KEY_A))
		m_velocity.X = 1.0f;

	if (eventHandler.IsKeyDown(irr::KEY_KEY_W))
		m_velocity.Z = -1.0f;

	if (eventHandler.IsKeyDown(irr::KEY_KEY_D))
		m_velocity.X = -1.0f;

	if (eventHandler.IsKeyDown(irr::KEY_KEY_S))
		m_velocity.Z = 1.0f;

	if (!eventHandler.IsKeyDown(irr::KEY_KEY_A) && !eventHandler.IsKeyDown(irr::KEY_KEY_D))
		m_velocity.X = 0;

	if (!eventHandler.IsKeyDown(irr::KEY_KEY_W) && !eventHandler.IsKeyDown(irr::KEY_KEY_S))
		m_velocity.Z = 0;
}

irr::core::vector3d<float> Player::GetVelocity() const
{
	return m_velocity;
}

void Player::SetVelocity(const irr::core::vector3d<float>& velocity)
{
	this->m_velocity = velocity;
}
