#include "Game.h"

Game::Game()
{
}

void Game::OnEnter()
{

	m_currentState = GameState::NO_CHANGE;
}

void Game::OnUserInput()
{
	//m_player.PlayerInput();
	if(IsKeyReleased(KEY_ESCAPE))
		m_currentState = GameState::MENU;

}

GameState Game::OnUserUpdate(float frameDelta)
{
	// Update Player.
	//m_player.Move(m_player.GetVelocity(), frameDelta, m_player.GetRunSpeed());

	// Update Camera.
	//m_camera->setPosition(irr::core::vector3df(m_player.GetPosition().X, m_player.GetPosition().Y + 8, m_player.GetPosition().Z + 8));
	//m_camera->setTarget(irr::core::vector3df(m_player.GetPosition().X, m_player.GetPosition().Y, m_player.GetPosition().Z));

	return m_currentState;
}

void Game::OnExit()
{
}