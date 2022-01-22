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
	GameState OnUserUpdate(float frameDelta) override;
	void OnExit() override;

private:
	GameState m_currentState;
	//Player m_player;
};