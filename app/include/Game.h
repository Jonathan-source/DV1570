#pragma once

#include <iostream>
#include "GameState.h"
#include "Player.h"
#include "StateMachine.h"


class Game : public IState
{
public:
	Game();
	virtual ~Game() = default;

	void OnEnter() override;
	void OnUserInput() override;
	void UpdateCamera();
	GameState OnUserUpdate(float frameDelta) override;
	void OnExit() override;
	void InitCamera();
private:
	GameState m_currentState;
	Camera m_camera;
	Player m_player;
};