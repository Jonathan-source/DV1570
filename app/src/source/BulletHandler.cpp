#include "BulletHandler.h"

BulletHandler::BulletHandler()
{
	m_bulletModel = LoadModel("../resources/meshes/bullet.obj");
	//m_bulletTexture = LoadTexture("../resources/textures/Steve.png");
	//m_bulletModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_bulletTexture;
}

void BulletHandler::SpawnBullet(Bullet bulletType, Vector3 direction, Vector3 spawnPosition, float angle)
{
	switch (bulletType)
	{
	case Bullet::DEFAULT: 
	{
		auto projectile = new Projectile(spawnPosition, direction, true, 10.f);
		projectile->SetBulletSpeed(10.f);
		m_bulletModel.transform = m_bulletModel.transform = MatrixRotateXYZ({ 0, angle, 0 });
		
		projectile->SetModel(m_bulletModel);
		m_bullets.emplace_back(projectile);
	}
		break;
	case Bullet::TYPE1:
		break;
	case Bullet::TYPE2:
		break;
	default:
		break;
	}
}

void BulletHandler::UpdateBullets()
{
	// Move Bullets
	for (auto bullet : m_bullets)
	{
		bullet->Move(bullet->GetVelocity(), GetFrameTime(), bullet->GetBulletSpeed());
		bullet->SetLifeSpawn(bullet->GetLifeSpawn() - GetFrameTime());
	}
	// Erase dead bullets
	bool hasDeadBullets = true;
	while(hasDeadBullets && !m_bullets.empty())
	{
		if (m_bullets.back()->GetLifeSpawn() <= 0.01f)
		{
			m_bullets.pop_back();
		}
		else
			hasDeadBullets = false;
	}

}

void BulletHandler::RenderBullets() const
{
	for (auto bullet : m_bullets)
	{
		DrawModel(bullet->GetModel(),bullet->GetPosition(),1, WHITE);
	}
}
