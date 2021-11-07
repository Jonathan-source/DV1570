#include "MainMenu.h"

MainMenu::MainMenu(irr::IrrlichtDevice* device)
	:device(device)

{
	m_windowWidth = device->getVideoDriver()->getScreenSize().Width;
	m_windowHeight = device->getVideoDriver()->getScreenSize().Height;
	
}

void MainMenu::OnEnter()
{
	InitButtons();
	m_currentState = GameState::NO_CHANGE;
}

void MainMenu::OnUserInput(const EventHandler& eventHandler)
{
	if(m_playButton->isPressed())
		m_currentState = GameState::GAME;
	else if (m_editorButton->isPressed())
		m_currentState = GameState::EDITOR;
	else if (m_highScoreButton->isPressed())
		m_currentState = GameState::HIGHSCORE;
	else if(m_exitButton->isPressed())
		m_currentState = GameState::EXIT;
}

GameState MainMenu::OnUserUpdate(float frameDelta)
{
	return m_currentState;
}

void MainMenu::OnExit()
{
	m_playButton->remove();
	m_editorButton->remove();
	m_highScoreButton->remove();
	m_exitButton->remove();
}

void MainMenu::InitButtons()
{
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	int offsetX = (m_windowWidth / 4);
	int offsetY = (m_windowHeight / 8);
	int centerX = (m_windowWidth / 2);
	int currentYPos = offsetY;
	int padding = 10;

	wchar_t textPlay[] = L"Play";
	wchar_t textEditor[] = L"Editor";
	wchar_t textHighScore[] = L"High Score";
	wchar_t textExit[] = L"Exit";

	//Play button
	m_playButton = guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textPlay);
	currentYPos += offsetY;
	//Editor button
	m_editorButton = guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textEditor);
	currentYPos += offsetY;
	//High score button
	m_highScoreButton = guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textHighScore);
	currentYPos += offsetY;
	//Exit button
	m_exitButton = guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textExit);
}