#include "Game.h"

Game::Game(irr::IrrlichtDevice* device)
	: device(device), m_currentState(), m_camera(nullptr)
{
}

void Game::OnEnter()
{
	std::cout << __FUNCTION__ << std::endl;
	
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	
	//Camera
	m_camera = sceneManager->addCameraSceneNode();
	m_camera->setPosition(irr::core::vector3df(m_player.GetPosition().X, m_player.GetPosition().Y + 8, m_player.GetPosition().Z + 8));
	m_camera->setTarget(irr::core::vector3df(m_player.GetPosition().X, m_player.GetPosition().Y, m_player.GetPosition().Z));

	m_player = Player(device, sceneManager->getMesh("../resources/meshes/Cube.obj"));
	entities.emplace_back(Entity(device, sceneManager->getMesh("../resources/meshes/Sphere.obj")));
	
	m_currentState = GameState::NO_CHANGE;
}

void Game::OnUserInput(const EventHandler& eventHandler)
{
	m_player.PlayerInput(eventHandler);
	
	if (eventHandler.IsKeyDown(irr::KEY_ESCAPE))
		m_currentState = GameState::MENU;
}

GameState Game::OnUserUpdate(float frameDelta)
{


	// Update Player.
	m_player.Move(m_player.GetVelocity(), frameDelta, m_player.GetRunSpeed());
	
	// Update Camera.
	//m_camera->setPosition(irr::core::vector3df(m_player.GetPosition().X, m_player.GetPosition().Y + 8, m_player.GetPosition().Z + 8));
	//m_camera->setTarget(irr::core::vector3df(m_player.GetPosition().X, m_player.GetPosition().Y, m_player.GetPosition().Z));

	return m_currentState;
}

void Game::OnExit()
{
	std::cout << __FUNCTION__ << std::endl;
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	m_player.SetMeshSceneNode(nullptr);
	m_camera->remove();
	entities.clear();
	sceneManager->clear();

}