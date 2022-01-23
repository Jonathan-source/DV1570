#include "Game.h"

Game::Game()
{
}

void Game::OnEnter()
{
	InitCamera();
	m_currentState = GameState::NO_CHANGE;
}

void Game::OnUserInput()
{
	m_player.PlayerInput();
}

void Game::UpdateCamera()
{
	m_camera.position = Vector3Add(m_player.GetPosition(), {0,10,-5});
	m_camera.target = m_player.GetPosition();
}

GameState Game::OnUserUpdate(float frameDelta)
{
	// Update Player.
	m_player.Move(m_player.GetVelocity(), frameDelta, m_player.GetRunSpeed());
	// Update Camera.
	UpdateCamera();

	if (IsKeyReleased(KEY_B))
		m_currentState = GameState::MENU;

	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(RAYWHITE);
	BeginMode3D(m_camera);
		DrawCube(m_player.GetPosition(), 2.0f, 2.0f, 2.0f, RED);
		DrawCubeWires({0,0,0}, 2.0f, 2.0f, 2.0f, MAROON);
		DrawGrid(10, 1.0f);
	EndMode3D();



	DrawText("GAME!", ((float)GetScreenWidth() - 100.f), 10, 32, BLACK);
	DrawFPS(10, 10);


	EndDrawing();
	//----------------------------------------------------------------------------------

	return m_currentState;
}

void Game::OnExit()
{
}

void Game::InitCamera()
{
	// Define the camera to look into our 3d world
	m_camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
	m_camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	m_camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	m_camera.fovy = 45.0f;                                // Camera field-of-view Y
	m_camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
}
