#include "Player.h"
#include "EventHandler.h"
#include <iostream>

Player::Player()
	: m_health(100),
	  m_attackDmg(1),
	  m_runSpeed(1),
	  m_projectileSpeed(1),
	  m_attackCooldown(1.f),
	  m_attackTimer(1),
	  m_projectileLifeTime(1),
	  m_forwardDirection({0.0f, 0.0f, 1.0f})
{
}

Player::Player(irr::IrrlichtDevice* device, irr::scene::IMesh* mesh, PlayerConfig& playerConfig, irr::video::ITexture* texture)
	: Entity(device, mesh, texture, playerConfig.startPosition),
	  m_health(playerConfig.health),
	  m_attackDmg(playerConfig.attackDmg),
	  m_runSpeed(playerConfig.runSpeed),
	  m_projectileSpeed(playerConfig.projectileSpeed),
	  m_attackCooldown(playerConfig.attackSpeed),
	  m_attackTimer(1),
	  m_projectileLifeTime(playerConfig.projectileLifeTime),
	  m_forwardDirection({0.0f, 0.0f, 1.0f})

{
	for (int i = 0; i < 25; i++)
	{
		m_projectiles.emplace_back(Projectile{
			Entity(device, device->getSceneManager()->getMesh("../resources/meshes/rock_smallI.obj"), nullptr,
			       {999.f, 999.f, 999.f}),
			{0.f, 0.f, 0.f}
		});
	}
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

std::vector<Projectile>& Player::GetProjectiles()
{
	return m_projectiles;
}

void Player::SetHealth(int health)
{
	this->m_health = health;
}

void Player::SetAttackDamage(int attackDamage)
{
	this->m_attackDmg = attackDamage;
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

void Player::Shoot()
{
	//Cooldown on shoot
	if(m_attackTimer >= m_attackCooldown)
	{
		for (auto& projectile : m_projectiles)
		{
			if (!projectile.isActive)
			{
				projectile.entity.SetPosition(this->GetPosition());
				projectile.isActive = true;
				projectile.direction = m_forwardDirection;
				break;
			}
		}
		m_attackTimer = 0;
	}
}

void Player::UpdateRotation(irr::gui::ICursorControl* cursor)
{
	const irr::core::vector2d<float> mousePos = { cursor->getRelativePosition().X , cursor->getRelativePosition().Y };
	const irr::core::vector2d<float> centerPos = { 0.5f, 0.5f };
	const irr::core::vector2d<float> centerToMouse2d = mousePos - centerPos;
	const irr::core::vector3d<float> centerToMouse = { centerToMouse2d.X, 0.0f, centerToMouse2d.Y};

	const irr::core::vector3d<float> requiredRotation = -centerToMouse.getHorizontalAngle();
	
	m_meshSceneNode->setRotation(requiredRotation);
	m_forwardDirection = requiredRotation.rotationToDirection();
}

float Player::GetProjectileLifeTime() const
{
	return m_projectileLifeTime;
}

void Player::SetProjectileLifeTime(const float projectile_life_time)
{
	m_projectileLifeTime = projectile_life_time;
}

void Player::UpdateProjectiles(float frameDelta)
{
	for (auto& projectile : m_projectiles)
	{
		if (projectile.isActive)
		{
			if (projectile.timer >= m_projectileLifeTime)
			{
				projectile.entity.SetPosition({ 999.f,999.f,999.f });
				projectile.isActive = false;
				projectile.timer = 0.f;
			}
			else
			{
				projectile.entity.Move(projectile.direction, frameDelta, m_projectileSpeed);
				projectile.timer += frameDelta;
			}
		}
	}
}

void Player::Update(float frameDelta, irr::gui::ICursorControl* cursor)
{
	this->UpdateRotation(cursor);

	this->Move(m_velocity, frameDelta, m_runSpeed);

	this->UpdateProjectiles(frameDelta);
	
	//Add on timers
	m_attackTimer += frameDelta;
}

float Player::GetAttackCooldown() const
{
	return m_attackCooldown;
}

void Player::SetAttackCooldown(const float attackCooldown)
{
	m_attackCooldown = attackCooldown;
}

float Player::GetProjectileSpeed() const
{
	return m_projectileSpeed;
}

void Player::SetProjectileSpeed(const float projectile_speed)
{
	m_projectileSpeed = projectile_speed;
}

irr::core::vector3d<float> Player::GetVelocity() const
{
	return m_velocity;
}

void Player::SetVelocity(const irr::core::vector3d<float>& velocity)
{
	this->m_velocity = velocity;
}
