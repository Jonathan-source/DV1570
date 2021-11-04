#pragma once

enum class GameState
{
	NO_CHANGE,
	MAIN_MENU,
	PLAY_GAME,
	PAUSE_GAME,
	VIEW_HIGHSCORE,
	RUN_EDITOR,
	EXIT_GAME,
};


class IScene
{
public:
	virtual ~IScene() = default;
	virtual void OnUserCreate() = 0;
	virtual GameState OnUserUpdate() = 0;
	virtual void OnUserInput() = 0;
};