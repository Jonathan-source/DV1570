#include "MainMenu.h"

MainMenu::MainMenu(irr::IrrlichtDevice* device, int width, int height)
{
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	int offsetX = (width / 4);
	int offsetY = (height / 8);
	int centerX = (width / 2);
	int currentYPos = offsetY;
	int padding = 10;
	
	wchar_t textPlay[] = L"Play";
	wchar_t textEditor[] = L"Editor";
	wchar_t textHighScore[] = L"High Score";
	wchar_t textExit[] = L"Exit";

	//Play button
	m_playButton =      guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textPlay);
	currentYPos += offsetY;
	//Editor button
	m_EditorButton =    guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textEditor);
	currentYPos += offsetY;
	//High score button
	m_HighScoreButton = guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textHighScore);
	currentYPos += offsetY;
	//Exit button
	m_exitButton =      guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textExit);

}

void MainMenu::OnEnter()
{
	m_currentState = GameState::NO_CHANGE;
}

void MainMenu::OnUserInput(const EventHandler& eventHandler)
{
	if (eventHandler.IsKeyDown(irr::KEY_KEY_G))
		m_currentState = GameState::GAME;

	else if (eventHandler.IsKeyDown(irr::KEY_KEY_H))
		m_currentState = GameState::HIGHSCORE;

	else if (eventHandler.IsKeyDown(irr::KEY_KEY_E))
		m_currentState = GameState::EDITOR;

	else if (eventHandler.IsKeyDown(irr::KEY_KEY_Q))
		m_currentState = GameState::EXIT;
}

GameState MainMenu::OnUserUpdate()
{
	return m_currentState;
}

void MainMenu::OnExit()
{
}
