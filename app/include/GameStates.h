#pragma once

// Also make change in StateMachine::Update().
enum class GameState
{
	NO_CHANGE,
	MENU,
	GAME,
	PAUSE,
	EXIT,
};