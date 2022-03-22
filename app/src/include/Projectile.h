#pragma once
#include <raylib.h>

#include "Entity.h"
enum class Bullet{DEFAULT, TYPE1, TYPE2 };

class Projectile : public Entity
{
public:
	//Constructors
	Projectile();
	Projectile(Vector3 position, Vector3 velocity, bool isActive, float lifeSpawn);
	//Getters
	[[nodiscard]] Vector3 GetVelocity() const;
	[[nodiscard]] float GetLifeSpawn() const;
	[[nodiscard]] bool GetIsActive() const;
	[[nodiscard]] Bullet GetBulletType() const;
	float GetBulletSpeed() const;
	//Setters
	void SetVelocity(Vector3 velocity);
	void SetLifeSpawn(float lifeSpawn);
	void SetIsActive(bool condition);
	void SetBulletType(Bullet bulletType);
	void SetBulletSpeed(float speed);
private:
	//Data
	Vector3 m_velocity;
	bool m_isActive;
	float m_lifeSpawn;
	float m_bulletSpeed;
	Bullet m_bulletType;
};

