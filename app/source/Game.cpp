#include "Game.h"

void Game::OnEnter()
{
	std::cout << __FUNCTION__ << std::endl;
	
	m_currentState = GameState::NO_CHANGE;
}

void Game::OnUserInput(const EventHandler& eventHandler)
{
	std::cout << __FUNCTION__ << std::endl;

	if (eventHandler.IsKeyDown(irr::KEY_ESCAPE))
		m_currentState = GameState::MENU;
}

GameState Game::OnUserUpdate()
{
	return m_currentState;
}

void Game::OnExit()
{
	std::cout << __FUNCTION__ << std::endl;
}
