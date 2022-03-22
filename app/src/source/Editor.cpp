#include "pch.h"
#include "Editor.h"

Editor::Editor()
{
}

void Editor::OnEnter()
{

}

void Editor::OnInput()
{
	HandleCameraInput();
}

bool Editor::OnUpdate(float frameDelta)
{
	// Update Camera.
	UpdateCamera(frameDelta);

	// Update MouseOnGrid.
	//UpdateMouseOnGrid();

	return true;
}

void Editor::OnRender()
{

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