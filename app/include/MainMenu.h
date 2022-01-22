#pragma once
#include <iostream>
#include "GameState.h"
#include "StateMachine.h"

class MainMenu : public IState
{
public:
	MainMenu();
	virtual ~MainMenu() = default;

	void OnEnter() override;
	void OnUserInput() override;
	GameState OnUserUpdate(float frameDelta) override;
	void OnExit() override;

	//Initialize all buttons for menu
	void InitButtons();

private:
	GameState m_currentState;

	//Mouse
	Vector2 mousePoint;

	//Menu buttons
	int m_Numframes; //Number of frames for button sprite texture
	float frameHeight; //Define frame rectangle height for button
	Rectangle sourceRec;
	Rectangle btnBounds;
	int btnState; // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
	bool btnAction;
	Sound fxButton;
	Texture2D button;

};