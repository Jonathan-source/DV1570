#pragma once
#include "IScene.h"

class MainMenu : public IScene
{
public:
	MainMenu() = default;
	virtual ~MainMenu() = default;

	void OnUserCreate() override
	{
		std::cout << __FUNCTION__ << std::endl;
	}
	void OnUserInput() override
	{
		std::cout << __FUNCTION__ << std::endl;
	}
	GameState OnUserUpdate() override
	{
		std::cout << __FUNCTION__ << std::endl;
		return GameState::NO_CHANGE;
	}

};
