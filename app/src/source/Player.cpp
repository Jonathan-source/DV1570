#include "Player.h"
#include <iostream>

Player::Player()
	: Entity()
	, m_health(100)
	, m_attackDmg(1)
	, m_runSpeed(5)
	, m_velocity({0.f,0.f,0.f})
	, m_direction({ 0.f, 0.f, })
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
	m_model.transform = MatrixRotateXYZ( { 0, DEG2RAD * 90, 0 });
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

Vector2 Player::GetDirection() const
{
	return Vector2Normalize(m_direction);
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

void Player::PlayerInput(const Ray &ray)
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

	RotateWithMouse(ray);
}

void Player::Shoot()
{
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

void Player::RotateWithMouse(const Ray& ray)
{
	// Ground quad
	const float SIZE = 1000.f;
	Vector3 g0 = { -SIZE, 0.0f, -SIZE };
	Vector3 g1 = { -SIZE, 0.0f, SIZE };
	Vector3 g2 = { SIZE, 0.0f, SIZE };
	Vector3 g3 = { SIZE, 0.0f, -SIZE };

	// Check ray collision against ground quad
	RayCollision groundHitInfo = GetRayCollisionQuad(ray, g0, g1, g2, g3);
	m_direction = { groundHitInfo.point.z - GetPosition().z, groundHitInfo.point.x - GetPosition().x };
	float angle = atan2f(m_direction.x, m_direction.y);
	m_model.transform = MatrixRotateXYZ({ 0, angle, 0 });
}
