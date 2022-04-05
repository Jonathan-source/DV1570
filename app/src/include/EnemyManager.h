#pragma once
#include "Enemy.h"
#include <vector>
enum class EnemyType {DEFAULT, TYPE1, TYPE2};

class EnemyManager
{
public:
	// Constructor
	EnemyManager(Player* playerTarget, const std::vector<std::vector<Node*>>& grid);
	// Deconstructor
	~EnemyManager();
	// Getters
	[[nodiscard]] std::vector<Enemy*>& GetEnemies();
	[[nodiscard]] std::vector<Vector3>& GetSpawnPoints();

	// Setters 

	// Functions
	void AddSpawnPoint(Vector3 spawnPoint);
	void SpawnEnemy(EnemyType enemyType);
	void SpawnWave(int numOfEnemies);
	void UpdateEnemies();
	void RenderEnemies() const;


private:
	std::vector<Enemy*> m_enemies;
	std::vector<Vector3> m_spawnPoints;
	Player* m_playerTarget;
	const std::vector<std::vector<Node*>> m_grid;
	int m_waveCount;
	int currentSpawnIndex;
};

