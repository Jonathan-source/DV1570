#include "pch.h"

#include "Enemy.h"

#include "PathFinderManager.h"

#include "ResourceManager.h"

Enemy::Enemy()
	: Entity()
	, m_health(100)
	, m_attackDmg(5)
	, m_runSpeed(3.f + static_cast<float>((rand() % 5) / 10.f))
	, m_updateFreqAStar(static_cast<float>((rand() % 100 + 1) / 100.f))
	, m_updateTimer(m_updateFreqAStar)
	, m_velocity({0.f, 0.f, 0.f})
	, m_direction({ 0.f, 0.f, })
	, m_attackRange(1.f)
	, m_attackTimer(0.f)
	, m_attackCooldown(1.f)
{
	auto& rm = ResourceManager::Get();
	SetModel(rm.GetModel("zombie.obj"));
	this->m_texture = rm.GetTexture("zombie.png");

	m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_texture;
	m_boundingBox = GetMeshBoundingBox(m_model.meshes[0]);
}

Enemy::Enemy(Player* playerTarget)
	: Entity()
	, m_health(100)
	, m_attackDmg(5)
	, m_runSpeed(5)
	, m_updateFreqAStar(static_cast<float>((rand() % 100 + 1) / 100.f))
	, m_updateTimer(m_updateFreqAStar)
	, m_velocity({ 0.f, 0.f, 0.f })
	, m_direction({ 0.f, 0.f, })
	, m_playerTarget(playerTarget)
	, m_attackRange(1.f)
	, m_attackTimer(0.f)
	, m_attackCooldown(1.f)
{
	auto& rm = ResourceManager::Get();
	SetModel(rm.GetModel("zombie.obj"));
	this->m_texture = rm.GetTexture("zombie.png");

	m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_texture;
	m_boundingBox = GetMeshBoundingBox(m_model.meshes[0]);
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

void Enemy::SetBoundingBox(BoundingBox boundingBox)
{
	m_boundingBox = boundingBox;
}

void Enemy::SetGrid(const std::vector<std::vector<Node*>>& grid)
{
	m_grid = grid;
}

void Enemy::MoveOnPath()
{
	Node* closestNode = PathFinderManager::GetClosestNode(GetPosition(), m_grid);

	// Generate path with A-star
	if (m_updateTimer < 0.001f)
	{
		path = PathFinderManager::AStar(closestNode, PathFinderManager::GetClosestNode(m_playerTarget->GetPosition(), m_grid));
		m_updateTimer = m_updateFreqAStar;
	}
	else
		m_updateTimer -= GetFrameTime();

	// Move on path
	if (!path.empty())
	{
		if (Vector2Distance( {path.back()->position.x, path.back()->position.z}, {this->GetPosition().x, this->GetPosition().z} ) < 0.5f)
		{
			path.pop_back();
		}

		if(!path.empty())
			m_direction = { path.back()->position.z - GetPosition().z,  path.back()->position.x - GetPosition().x };
	}
	else
	{
		// Stop on empty path
		m_direction = { 0,0 };
		m_velocity = { 0, 0.0, 0};
		return;
	}

	// Give velocity depending on the direction for the next node
	m_direction = Vector2Normalize(m_direction);
	m_velocity = { m_direction.y, 0.0, m_direction.x };

	// Rotate towards target
	const float angle = atan2f(m_direction.x, m_direction.y);
	m_model.transform = MatrixRotateXYZ({ 0, angle, 0 });
}

void Enemy::Update()
{
	// Generate path and move
	MoveOnPath();

	AttackPlayer();

	m_attackTimer -= GetFrameTime();
}

void Enemy::AttackPlayer()
{
	if (Vector3Distance(m_playerTarget->GetPosition(), this->GetPosition()) < m_attackRange && m_attackTimer < 0.01f)
	{
		m_playerTarget->TakeDamage(m_attackDmg);
		m_playerTarget->SetVelocity({ this->GetDirection().x * 2, 0.0f, this->GetDirection().y * 2 });
		m_attackTimer = m_attackCooldown;
	}
}

void Enemy::TakeDamage(int damage)
{
	m_health -= damage;
}


Vector3 Enemy::GetVelocity() const
{
	return m_velocity;
}

Texture2D Enemy::GetTexture() const
{
	return m_texture;
}

BoundingBox Enemy::GetBoundingBox() const
{
	return m_boundingBox;
}
