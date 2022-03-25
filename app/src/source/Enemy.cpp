#include "pch.h"

#include "Enemy.h"

Enemy::Enemy()
	: Entity()
	, m_health(100)
	, m_attackDmg(1)
	, m_velocity({ 0.f, 0.f, 0.f })
	, m_direction({ 0.f, 0.f, })
{
	SetModel(LoadModel("../resources/meshes/zombie.obj"));
	this->m_texture = LoadTexture("../resources/textures/zombie.png");
	m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_texture;

	m_runSpeed = (1.f + static_cast<float>((rand() % 5) / 10.f));
}

Enemy::Enemy(Player* playerTarget)
	: Entity()
	, m_health(100)
	, m_attackDmg(1)
	, m_runSpeed(5)
	, m_velocity({ 0.f, 0.f, 0.f })
	, m_direction({ 0.f, 0.f, })
	, m_playerTarget(playerTarget)
{
	SetModel(LoadModel("../resources/meshes/zombie.obj"));
	this->m_texture = LoadTexture("../resources/textures/zombie.png");
	m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_texture;
}


Enemy::~Enemy()
= default;

int Enemy::GetHealth() const
{
	return m_health;
}

int Enemy::GetAttackDamage() const
{
	return m_attackDmg;
}

float Enemy::GetRunSpeed() const
{
	return m_runSpeed;
}

Vector2 Enemy::GetDirection() const
{
	return m_direction;
}

void Enemy::SetHealth(int health)
{
	m_health = health;
}

void Enemy::SetAttackDamage(int attdmg)
{
	m_attackDmg = attdmg;
}

void Enemy::SetRunSpeed(float runSpeed)
{
	m_runSpeed = runSpeed;
}

void Enemy::SetTexture(Texture2D texture)
{
	m_texture = texture;
}

void Enemy::SetVelocity(const Vector3& velocity)
{
	m_velocity = velocity;
}

void Enemy::SetPlayerTarget(Player* playerTarget)
{
	m_playerTarget = playerTarget;
}

void Enemy::Update()
{
	// Set direction towards player target
	m_direction = {  m_playerTarget->GetPosition().z - GetPosition().z,  m_playerTarget->GetPosition().x - GetPosition().x};
	m_direction = Vector2Normalize(m_direction);
	m_velocity = { m_direction.y, 0.0, m_direction.x };

	// Rotate towards player target
	float angle = atan2f(m_direction.x, m_direction.y);
	m_model.transform = MatrixRotateXYZ({ 0, angle, 0 });
}


Vector3 Enemy::GetVelocity() const
{
	return m_velocity;
}

Texture2D Enemy::GetTexture() const
{
	return m_texture;
}
