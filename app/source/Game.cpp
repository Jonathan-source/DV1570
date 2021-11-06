#include "Game.h"

Game::Game(irr::IrrlichtDevice* device)
	: device(device), m_currentState(), m_camera(nullptr), then(0), now(0)
{
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	//init player
	m_player.SetRunSpeed(10);
	m_player.SetHealth(100);
	m_player.SetRunSpeed(10.f);
	m_player.SetMesh(sceneManager->getMesh("../resources/mesh/Cube.obj"));
}

void Game::OnEnter()
{
	std::cout << __FUNCTION__ << std::endl;

	then = device->getTimer()->getTime();
	
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	
	//Camera
	irr::scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNode();
	camera->setPosition(irr::core::vector3df(0, 0, 5));
	camera->setTarget(irr::core::vector3df(0, 0, 0));

	//Set players mesh node
	m_player.SetMeshSceneNode(sceneManager->addMeshSceneNode(m_player.GetMesh()));
	
	m_currentState = GameState::NO_CHANGE;
}

void Game::OnUserInput(const EventHandler& eventHandler)
{
	m_player.PlayerInput(eventHandler);
	
	if (eventHandler.IsKeyDown(irr::KEY_ESCAPE))
		m_currentState = GameState::MENU;
}

GameState Game::OnUserUpdate()
{
	now = device->getTimer()->getTime();
	frameDeltaTime = static_cast<f32>(now - then) / 1000.f; //time in seconds

	m_player.Move(m_player.GetVelocity(), frameDeltaTime, m_player.GetRunSpeed());
	
	then = now;
	return m_currentState;
}

void Game::OnExit()
{
	std::cout << __FUNCTION__ << std::endl;
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	m_player.SetMeshSceneNode(nullptr);
	sceneManager->clear();

}