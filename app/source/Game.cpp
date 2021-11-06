#include "Game.h"

Game::Game(irr::IrrlichtDevice* device)
	:device(device)
{	
}

void Game::OnEnter()
{
	std::cout << __FUNCTION__ << std::endl;
	
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	
	//Player
	m_player.SetMesh(sceneManager->getMesh("../resources/mesh/Cube.obj"));
	
	//Camera
	irr::scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNode();
	camera->setPosition(irr::core::vector3df(0, 0, 5));
	camera->setTarget(irr::core::vector3df(0, 0, 0));

	//add player to the nodes
	m_meshSceneNodes.emplace_back(sceneManager->addMeshSceneNode(m_player.GetMesh()));
	
	m_currentState = GameState::NO_CHANGE;
}

void Game::OnUserInput(const EventHandler& eventHandler)
{
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
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();

	for (auto& meshNode : m_meshSceneNodes)
	{
		meshNode->remove();
	}

	m_meshSceneNodes.clear();
}
