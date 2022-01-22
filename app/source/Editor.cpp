#include "Editor.h"

Editor::Editor()
{
}

void Editor::OnEnter()
{
	m_currentState = GameState::NO_CHANGE;
}
void Editor::OnUserInput()
{
	HandleCameraInput();

	if (IsKeyDown(KEY_ESCAPE))
		m_currentState = GameState::MENU;
}
GameState Editor::OnUserUpdate(float frameDelta)
{
	// Update Camera.
	UpdateCamera(frameDelta);

	// Update MouseOnGrid.
	//UpdateMouseOnGrid();

	return m_currentState;
}
void Editor::OnExit()
{
}

void Editor::UpdateCamera(float frameDelta)
{
}

void Editor::HandleCameraInput()
{
	// Camera Zoom.


	// Camera Movement.

}

void Editor::ZoomIn()
{

}

void Editor::ZoomOut()
{

}