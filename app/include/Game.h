#pragma once

#include <iostream>

#include "GameStates.h"
#include "StateMachine.h"

class Game : public IState
{
public:
	Game() = default;
	virtual ~Game() = default;

	void OnEnter() override
	{
		std::cout << __FUNCTION__ << std::endl;
		m_currentState = GameState::NO_CHANGE;
	}
	void OnUserInput(const EventHandler& eventHandler) override
	{
		std::cout << __FUNCTION__ << std::endl;

		if (eventHandler.IsKeyDown(irr::KEY_KEY_S))
			m_currentState = GameState::EXIT;
	}
	void OnUserUpdate() override
	{
		std::cout << __FUNCTION__ << std::endl;

	}
	void OnExit() override
	{
		
	}

private:
	GameState m_currentState;

};
