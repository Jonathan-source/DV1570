#include "pch.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
	:currentSpawnIndex(0)
{

}

void EnemyManager::AddSpawnPoint(Vector3 spawnPoint)
{
	m_spawnPoints.push_back(spawnPoint);
}

void EnemyManager::SpawnEnemy(EnemyType enemyType, Player* playerTarget)
{

	switch (enemyType)
	{
	case EnemyType::DEFAULT:
		{
			Enemy* enemy = new Enemy;
			currentSpawnIndex = ++currentSpawnIndex % m_spawnPoints.size();
			enemy->SetPosition(m_spawnPoints[currentSpawnIndex]);
			enemy->SetPlayerTarget(playerTarget);
			m_enemies.push_back(enemy);
		}
		break;
	default:
		break;
	}
}

void EnemyManager::UpdateEnemies() const
{
	for (const auto enemy : m_enemies)
	{
		enemy->Update();
		enemy->Move(enemy->GetVelocity(), GetFrameTime(), enemy->GetRunSpeed());
	}
}

void EnemyManager::RenderEnemies() const
{
	for (const auto enemy : m_enemies)
	{
		DrawModel(enemy->GetModel(), enemy->GetPosition(), 1, WHITE);
	}
}
