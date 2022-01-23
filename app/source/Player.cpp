#include "Player.h"

Player::Player()
	:Entity(),
	m_health(100),
	m_attackDmg(1),
	m_runSpeed(1),
	m_velocity({0.f,0.f,0.f})
{
	SetModel(LoadModel("../resources/meshes/steve.obj"));
	this->m_texture = LoadTexture("../resources/textures/Steve.png");
	m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_texture;
	m_model.transform = MatrixRotateXYZ({ 0, DEG2RAD * 90, 0 });
}

Player::Player(int health, int attdmg, float runSpeed, Vector3 position)
	: Entity(position),
	m_health(health),
	m_attackDmg(attdmg),
	m_runSpeed(runSpeed)
{
	SetModel(LoadModel("../resources/meshes/steve.obj"));
	// Tranformation matrix for rotations
	m_model.transform = MatrixRotateXYZ( { 0, DEG2RAD* 90, 0 });
	this->m_texture = LoadTexture("../resources/textures/Steve.png");
	m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_texture;
}

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

void Player::SetTexture(Texture2D texture)
{
	m_texture = texture;
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

Texture2D Player::GetTexture() const
{
	return m_texture;
}

void Player::SetVelocity(const Vector3& velocity)
{
	this->m_velocity = velocity;
}
