#pragma once
#include "Enemy.h"
#include <vector>
enum class EnemyType {DEFAULT, TYPE1, TYPE2};

class EnemyManager
{
public:
	// Constructor
	EnemyManager();
	// Deconstructor
	~EnemyManager() = default;
	// Getters
	std::vector<Enemy>& GetEnemies() const;
	std::vector<Vector3>& GetSpawnPoints() const;

	// Setters 

	// Functions
	void AddSpawnPoint(Vector3 spawnPoint);
	void SpawnEnemy(EnemyType enemyType, Player* playerTarget);
	void UpdateEnemies() const;
	void RenderEnemies() const;


private:
	std::vector<Enemy*> m_enemies;
	std::vector<Vector3> m_spawnPoints;
	int currentSpawnIndex;
};

