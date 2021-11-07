#pragma once
#include <IGUIButton.h>
#include <iostream>

#include "EventHandler.h"
#include "GameStates.h"
#include "StateMachine.h"

class MainMenu : public IState
{
public:
	MainMenu(irr::IrrlichtDevice* device);
	virtual ~MainMenu() = default;

	void OnEnter() override;
	void OnUserInput(const EventHandler& eventHandler) override;
	GameState OnUserUpdate(float frameDelta) override;
	void OnExit() override;

	//Initialize all buttons for menu
	void InitButtons();
	
private:
	GameState m_currentState;
	
	int m_windowWidth;
	int m_windowHeight;
	
	irr::IrrlichtDevice* device;
	
	//Menu buttons
	irr::gui::IGUIButton* m_playButton;
	irr::gui::IGUIButton* m_editorButton;
	irr::gui::IGUIButton* m_highScoreButton;
	irr::gui::IGUIButton* m_exitButton;
};
