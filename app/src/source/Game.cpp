#include "pch.h"
#include "Game.h"

void Game::OnEnter()
{
	InitCamera();
}

void Game::OnInput()
{
	// Get ray and test against objects
	Ray ray = GetMouseRay(GetMousePosition(), m_camera);
	m_player.PlayerInput(ray);


	// Toggle menu.
	if (IsKeyPressed(KEY_ESCAPE))
	{
		GetStateMachine()->Change("MainMenu");
	}
}

void Game::UpdateCamera()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L, "../resources/scripts/GameConfig.lua");
	lua_getglobal(L, "Camera");

	if (lua_istable(L, -1))
	{
		lua_pushstring(L, "Fov");
		lua_gettable(L, -2);
		m_camera.fovy = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}

	lua_close(L);

	m_camera.position = Vector3Add(m_player.GetPosition(), {0,10,-5});
	m_camera.target = m_player.GetPosition();
}

bool Game::OnUpdate(float frameDelta)
{
	// Update Player.
	m_player.Move(m_player.GetVelocity(), frameDelta, m_player.GetRunSpeed());

	// Update Camera.
	UpdateCamera();

	return true;
}

void Game::OnRender()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	BeginMode3D(m_camera);
	DrawModel(m_player.GetModel(), m_player.GetPosition(), 0.2f, WHITE);
	DrawGrid(100, 1.0f);
	EndMode3D();

	EndDrawing();
}

void Game::OnExit()
{

}

void Game::InitCamera()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L, "../resources/scripts/GameConfig.lua");
	lua_getglobal(L, "Camera");

	if(lua_istable(L, -1))
	{
		lua_pushstring(L, "Fov");
		lua_gettable(L, -2);
		m_camera.fovy = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}

	// Define the camera to look into our 3d world
	m_camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
	m_camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	m_camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	//m_camera.fovy = 45.0f;                                // Camera field-of-view Y
	m_camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	lua_close(L);
}


