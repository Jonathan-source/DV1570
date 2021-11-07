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
		m_currentState = GameState::NO_CHANGE;
	}
	void OnUserInput(const EventHandler& eventHandler) override
	{
		if (eventHandler.IsKeyDown(irr::KEY_ESCAPE))
			m_currentState = GameState::MENU;
	}
	GameState OnUserUpdate(float frameDelta) override
	{
		return m_currentState;
	}
	void OnExit() override
	{
	}

private:
	GameState m_currentState;

};
