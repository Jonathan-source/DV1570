#include "Projectile.h"

Projectile::Projectile()
	:Entity(),
	m_velocity({ 0, 0, 0 }),
	m_isActive(false),
	m_lifeSpawn(0),
	m_bulletSpeed(1),
	m_bulletType(Bullet::DEFAULT)
{
}

Projectile::Projectile(Vector3 position, Vector3 velocity, bool isActive, float lifeSpawn)
	:Entity(position),
	m_velocity(velocity),
	m_isActive(isActive),
	m_lifeSpawn(lifeSpawn),
	m_bulletSpeed(1),
	m_bulletType(Bullet::DEFAULT)

{
}

Vector3 Projectile::GetVelocity() const
{
	return m_velocity;
}

float Projectile::GetLifeSpawn() const
{
	return m_lifeSpawn;
}

bool Projectile::GetIsActive() const
{
	return m_isActive;
}

Bullet Projectile::GetBulletType() const
{
	return m_bulletType;
}

float Projectile::GetBulletDamage() const
{
	return m_dmg;
}

float Projectile::GetBulletSpeed() const
{
	return m_bulletSpeed;
}

void Projectile::SetVelocity(Vector3 velocity)
{
	m_velocity = velocity;
}

void Projectile::SetLifeSpawn(float lifeSpawn)
{
	m_lifeSpawn = lifeSpawn;
}

void Projectile::SetIsActive(bool condition)
{
	m_isActive = condition;
}

void Projectile::SetBulletType(Bullet bulletType)
{
	m_bulletType = bulletType;
	//change model?
	//this->SetModel();
}

void Projectile::SetBulletSpeed(float speed)
{
	m_bulletSpeed = speed;
}

void Projectile::SetBulletDamage(float dmg)
{
	m_dmg = dmg;
}
