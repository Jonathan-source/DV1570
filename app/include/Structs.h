#pragma once
#include <vector3d.h>

struct Projectile
{
	Entity entity;
	irr::core::vector3d<float> direction;
	float timer = 0;
	bool isActive = false;
};


struct PlayerConfig
{
	int health;
	int attackDmg;

	float runSpeed;
	float projectileSpeed;
	float attackSpeed;
	float projectileLifeTime;

	irr::core::vector3d<float> startPosition;
};
