#include "pch.h"
#include "Game.h"
#include "Utility.h"
#include "CollisionHandler.h"


Game::Game()
	: m_enemyManager(nullptr)
{
	L = luaL_newstate();
	luaL_openlibs(L);
	RegisterLuaFunctions();
}

Game::~Game()
{
	for (const auto& nodeVec : m_grid)
	{
		for (auto node : nodeVec)
		{
			if(node) delete node;
		}
	}

	delete m_enemyManager;

	DumpStack(L);
	lua_close(L);
}

void Game::OnEnter()
{
	InitCamera();

	// init grid
	m_grid = PathFinderManager::InitializeGrid(50,1);

	m_enemyManager = new EnemyManager(&m_player, m_grid);

	m_enemyManager->AddSpawnPoint({ 10,0,10 });
	m_enemyManager->AddSpawnPoint({ 40,0,10 });
	m_enemyManager->AddSpawnPoint({ 40,0,40 });
	m_enemyManager->AddSpawnPoint({ 10,0,40 });

	m_grid[3][3]->reachable = false;
	m_grid[3][4]->reachable = false;
	m_grid[3][5]->reachable = false;
	m_grid[2][3]->reachable = false;
	m_grid[2][4]->reachable = false;
	m_grid[2][5]->reachable = false;

	PathFinderManager::UpdateConnections(m_grid);
}

void Game::OnInput()
{
	// Get ray and test against objects
	Ray ray = GetMouseRay(GetMousePosition(), m_camera);
	m_player.PlayerInput(ray);
	m_player.Shoot(m_bulletHandler);

	// Toggle menu.
	if (IsKeyPressed(KEY_ESCAPE))
	{
		GetStateMachine()->Change("MainMenu");
	}
}

void Game::UpdateCamera()
{
	luaL_dofile(L, "../resources/scripts/GameConfig.lua");
	lua_getglobal(L, "Camera");

	if (lua_istable(L, -1))
	{
		lua_pushstring(L, "Fov");
		lua_gettable(L, -2);
		m_camera.fovy = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}

	m_camera.position = Vector3Add(m_player.GetPosition(), {0,10,-5});
	m_camera.target = m_player.GetPosition();
}

bool Game::OnUpdate(float frameDelta)
{
	// Update Player.
	m_player.Move(m_player.GetVelocity(), frameDelta, m_player.GetRunSpeed());
	m_player.Update();
	// Update enemies
	m_enemyManager->UpdateEnemies();
	// Update Camera.
	UpdateCamera();
	//Update Bullets
	m_bulletHandler.UpdateBullets();

	CollisionHandler::CheckBulletEnemy(m_enemyManager->GetEnemies(), m_bulletHandler.GetBullets());

	return true;
}

void Game::RenderGrid()
{
	for(int i = 0; i < m_grid.size(); i++)
	{
		for(int j = 0;j<m_grid.size(); j++)
		{
			if(m_grid.at(i).at(j)->reachable)
				DrawCube(m_grid.at(i).at(j)->position, 0.2f, 0.2f, 0.2f, RED);
			else
				DrawCube(m_grid.at(i).at(j)->position, 0.2f, 0.2f, 0.2f, BLUE);
		}
	}
}

void Game::OnRender()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	BeginMode3D(m_camera);
	DrawModel(m_player.GetModel(), m_player.GetPosition(), 1.0f, WHITE);
	m_bulletHandler.RenderBullets();
	m_enemyManager->RenderEnemies();
	RenderGrid();
	DrawCubeWires({ 0,0,0 }, 2.0f, 2.0f, 2.0f, MAROON);
	DrawGrid(50, 1.0f);
	EndMode3D();
	DrawRectangleRec(m_player.GetHealthBar(), Fade(RED, 0.5f));
	EndDrawing();
}

void Game::OnExit()
{
	
}

void Game::InitCamera()
{
	// Define the camera to look into our 3d world
	m_camera.position = { 0.0f, 10.0f, 10.0f };				// Camera position
	m_camera.target = { 0.0f, 0.0f, 0.0f };					// Camera looking at point
	m_camera.up = { 0.0f, 1.0f, 0.0f };						// Camera up vector (rotation towards target)
	m_camera.fovy = 45.0f;									// Camera field-of-view Y
	m_camera.projection = CAMERA_PERSPECTIVE;				// Camera mode type
}

void Game::RegisterLuaFunctions()
{

}


