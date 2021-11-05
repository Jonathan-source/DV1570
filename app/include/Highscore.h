#pragma once

#pragma once

#include <iostream>

#include "GameStates.h"
#include "StateMachine.h"

class Highscore : public IState
{
public:
	Highscore() = default;
	virtual ~Highscore() = default;

	void OnEnter() override
	{
		std::cout << __FUNCTION__ << std::endl;
		m_currentState = GameState::NO_CHANGE;
	}
	void OnUserInput(const EventHandler& eventHandler) override
	{
		std::cout << __FUNCTION__ << std::endl;

		if (eventHandler.IsKeyDown(irr::KEY_KEY_M))
			m_currentState = GameState::MENU;
	}
	GameState OnUserUpdate() override
	{
		std::cout << __FUNCTION__ << std::endl;

		return m_currentState;
	}
	void OnExit() override
	{
		std::cout << __FUNCTION__ << std::endl;
	}

private:
	GameState m_currentState;

};
