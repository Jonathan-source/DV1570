#include "Editor.h"

Editor::Editor(irr::IrrlichtDevice* device)
	: device(device)
	, m_cameraSpeed(10.f)
{
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	m_test.SetMesh(sceneManager->getMesh("../resources/meshes/Cube.obj"));
}

void Editor::OnEnter()
{
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	m_test.SetMeshSceneNode(sceneManager->addMeshSceneNode(m_test.GetMesh()));

	// Camera.
	m_camera = sceneManager->addCameraSceneNode();
	m_camera->setPosition(irr::core::vector3df(0, 8, 8));
	m_camera->setTarget(irr::core::vector3df(0, 0, 0));

	// Create a plane.

	m_currentState = GameState::NO_CHANGE;
}
void Editor::OnUserInput(const EventReceiver& eventHandler)
{
	HandleCameraInput(eventHandler);

	if (eventHandler.IsKeyDown(irr::KEY_ESCAPE))
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
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	m_test.SetMeshSceneNode(nullptr);
	m_camera->remove();
	sceneManager->clear();
}

void Editor::UpdateCamera(float frameDelta)
{
	// Update Camera position.
	auto position = m_camera->getPosition();
	position = position + m_cameraDirection * frameDelta * m_cameraSpeed;
	m_camera->setPosition(position);

	// Update Camera target.
	auto target = m_camera->getPosition();
	target.Y -= 8; target.Z -= 8;
	m_camera->setTarget(target);
}

void Editor::HandleCameraInput(const EventReceiver& eventHandler)
{
	// Camera Zoom.
	if (eventHandler.IsKeyDown(irr::KEY_KEY_Q))
		ZoomIn();
	else if (eventHandler.IsKeyDown(irr::KEY_KEY_E))
		ZoomOut();

	// Camera Movement.
	if (eventHandler.IsKeyDown(irr::KEY_KEY_A))
		m_cameraDirection.X = 1.0f;
	if (eventHandler.IsKeyDown(irr::KEY_KEY_W))
		m_cameraDirection.Z = -1.0f;
	if (eventHandler.IsKeyDown(irr::KEY_KEY_D))
		m_cameraDirection.X = -1.0f;
	if (eventHandler.IsKeyDown(irr::KEY_KEY_S))
		m_cameraDirection.Z = 1.0f;
	if (!eventHandler.IsKeyDown(irr::KEY_KEY_A) && !eventHandler.IsKeyDown(irr::KEY_KEY_D))
		m_cameraDirection.X = 0;
	if (!eventHandler.IsKeyDown(irr::KEY_KEY_W) && !eventHandler.IsKeyDown(irr::KEY_KEY_S))
		m_cameraDirection.Z = 0;
}

void Editor::ZoomIn()
{
	auto position = m_camera->getPosition();
	position.Y -= 0.25f;
	position.Z -= 0.25f;

	if (position.Y > 2.5f && position.Z > 2.5f)
		m_camera->setPosition(position);
}

void Editor::ZoomOut()
{
	auto position = m_camera->getPosition();
	position.Y += 0.25f;
	position.Z += 0.25f;

	if (position.Y < 50.f && position.Z < 50.f)
		m_camera->setPosition(position);
}
