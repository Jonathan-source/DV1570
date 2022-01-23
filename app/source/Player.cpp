#include "Player.h"

Player::Player()
	:Entity(),
	m_health(100),
	m_attackDmg(1),
	m_runSpeed(1),
	m_velocity({0.f,0.f,0.f})
{
	
}

Player::Player(int health, int attdmg, float runSpeed, Vector3 position)
	: Entity(position),
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

void Player::PlayerInput()
{
	if (IsKeyDown(KEY_A))
		m_velocity.x = 1.0f;

	if (IsKeyDown(KEY_W))
		m_velocity.z = 1.0f;

	if (IsKeyDown(KEY_D))
		m_velocity.x = -1.0f;

	if (IsKeyDown(KEY_S))
		m_velocity.z = -1.0f;

	if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
		m_velocity.x = 0;

	if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
		m_velocity.z = 0;
}

Vector3 Player::GetVelocity() const
{
	return m_velocity;
}

void Player::SetVelocity(const Vector3& velocity)
{
	this->m_velocity = velocity;
}