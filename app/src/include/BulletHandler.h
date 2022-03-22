#pragma once
#include <vector>
#include <iostream>
#include "Projectile.h"

class BulletHandler
{
public:
	BulletHandler();
	void SpawnBullet(Bullet bulletType, Vector3 direction, Vector3 spawnPosition, float angle);
	void UpdateBullets();
	void RenderBullets() const;
private:
	std::vector<Projectile*> m_bullets;
	Model m_bulletModel;
	Texture2D m_bulletTexture;
};

