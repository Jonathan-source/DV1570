#pragma once
#include <IGUIButton.h>
#include <iostream>

#include "EventHandler.h"
#include "GameStates.h"
#include "StateMachine.h"

class MainMenu : public IState
{
public:
	MainMenu() = default;
	virtual ~MainMenu() = default;

	void OnEnter() override
	{
		std::cout << __FUNCTION__ << std::endl;
		m_currentState = GameState::NO_CHANGE;
	}
	void OnUserInput(const EventHandler &eventHandler) override
	{
		std::cout << __FUNCTION__ << std::endl;

		if (eventHandler.IsKeyDown(irr::KEY_KEY_G))
			m_currentState = GameState::GAME;

		else if (eventHandler.IsKeyDown(irr::KEY_KEY_H))
			m_currentState = GameState::HIGHSCORE;

		else if (eventHandler.IsKeyDown(irr::KEY_KEY_E))
			m_currentState = GameState::EDITOR;

		else if (eventHandler.IsKeyDown(irr::KEY_KEY_Q))
			m_currentState = GameState::EXIT;

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
