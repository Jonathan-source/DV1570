#pragma once

#include "Player.h"
#include "StateMachine.h"
#include "BulletHandler.h"
#include "EnemyManager.h"
#include "Enemy.h"

class Game : public IState
{
public:
	Game() = default;
	virtual ~Game() = default;

	void OnEnter() override;
	void OnInput() override;
	void UpdateCamera();
	bool OnUpdate(float frameDelta) override;
	void OnRender() override;
	void OnExit() override;
	void InitCamera();

private:
	Camera m_camera;
	Player m_player;
	Enemy m_enemy;
	EnemyManager m_enemyManager;
	BulletHandler m_bulletHandler;
};
