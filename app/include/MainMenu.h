#pragma once
#include <IGUIButton.h>
#include <iostream>

#include "EventHandler.h"
#include "GameStates.h"
#include "StateMachine.h"

class MainMenu : public IState
{
public:
	MainMenu(irr::IrrlichtDevice* device, int width, int height);
	virtual ~MainMenu() = default;

	void OnEnter() override;
	void OnUserInput(const EventHandler& eventHandler) override;
	GameState OnUserUpdate() override;
	void OnExit() override;


private:
	GameState m_currentState;
	
	//Menu buttons
	irr::gui::IGUIButton* m_playButton;
	irr::gui::IGUIButton* m_EditorButton;
	irr::gui::IGUIButton* m_HighScoreButton;
	irr::gui::IGUIButton* m_exitButton;
};
