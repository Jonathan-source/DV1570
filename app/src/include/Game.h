#pragma once

#include "Player.h"
#include "StateMachine.h"
#include "BulletHandler.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "PathFinderManager.h"

class Game : public IState
{
public:
	Game(lua_State* L);
	virtual ~Game();

	void OnEnter() override;
	void OnInput() override;
	void UpdateCamera();
	bool OnUpdate(float frameDelta) override;
	void RenderGrid();
	void OnRender() override;
	void OnExit() override;
	void InitCamera();

private:
	lua_State* L;
	Camera m_camera;
	Player m_player;
	Enemy m_enemy;
	EnemyManager* m_enemyManager;
	BulletHandler m_bulletHandler;
	std::vector<std::vector<Node*>> m_grid;
};
