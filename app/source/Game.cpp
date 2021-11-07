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

	PlayerConfig playerConfig =
	{
		100,
		10,
		10.f,
		20.f,
		0.25f,
		5.f,
		{0.f, 0.f, 0.f},
	};
	
	m_player = Player(device, sceneManager->getMesh("../resources/meshes/Arrow.obj"), playerConfig);

	//Entities in scene
	entities.emplace_back(Entity(device, sceneManager->getMesh("../resources/meshes/Sphere.obj")));
	
	m_currentState = GameState::NO_CHANGE;
}

void Game::OnUserInput(const EventHandler& eventHandler)
{
	m_player.PlayerInput(eventHandler);
	
	if (eventHandler.IsKeyDown(irr::KEY_ESCAPE))
		m_currentState = GameState::MENU;
	
	if(eventHandler.IsKeyDown(irr::KEY_KEY_F))
	{
		m_player.Shoot();
	}
}

GameState Game::OnUserUpdate(float frameDelta)
{
	// Update Player.
	m_player.Update(frameDelta, device->getCursorControl());
	


	// Update Camera.
	m_camera->setPosition(irr::core::vector3df(m_player.GetPosition().X, m_player.GetPosition().Y + 8, m_player.GetPosition().Z + 8));
	m_camera->setTarget(irr::core::vector3df(m_player.GetPosition().X, m_player.GetPosition().Y, m_player.GetPosition().Z));

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