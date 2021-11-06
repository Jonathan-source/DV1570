#pragma once

#include <iostream>

#include "GameStates.h"
#include "StateMachine.h"
#include "Player.h"

class Game : public IState
{
public:
	Game() = default;
	virtual ~Game() = default;

	void OnEnter() override;
	void OnUserInput(const EventHandler& eventHandler) override;	
	GameState OnUserUpdate() override;
	void OnExit() override;

private:
	GameState m_currentState;
	Player player;
	irr::scene::ICameraSceneNode* camera;

};
