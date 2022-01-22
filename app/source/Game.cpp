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

}

GameState Game::OnUserUpdate(float frameDelta)
{
	// Update Player.
	//m_player.Move(m_player.GetVelocity(), frameDelta, m_player.GetRunSpeed());

	// Update Camera.
	//m_camera->setPosition(irr::core::vector3df(m_player.GetPosition().X, m_player.GetPosition().Y + 8, m_player.GetPosition().Z + 8));
	//m_camera->setTarget(irr::core::vector3df(m_player.GetPosition().X, m_player.GetPosition().Y, m_player.GetPosition().Z));

	if (IsKeyReleased(KEY_B))
		m_currentState = GameState::MENU;


	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();
	DrawText("GAME!", ((float)GetScreenWidth() / 2.0f), float(GetScreenHeight()) / 2.0f, 32, BLACK);

	ClearBackground(RAYWHITE);

	EndDrawing();
	//----------------------------------------------------------------------------------

	return m_currentState;
}

void Game::OnExit()
{
}