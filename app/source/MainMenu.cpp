#include "MainMenu.h"

MainMenu::MainMenu()
	:m_Numframes(3),
	mousePoint({0.0f,0.0f})
{
}

void MainMenu::OnEnter()
{
	InitButtons();


	m_currentState = GameState::NO_CHANGE;

}

void MainMenu::OnUserInput()
{
	//if (m_playButton->isPressed())
	//	m_currentState = GameState::GAME;
	//else if (m_editorButton->isPressed())
	//	m_currentState = GameState::EDITOR;
	//else if (m_highScoreButton->isPressed())
	//	m_currentState = GameState::HIGHSCORE;
	//else if (m_exitButton->isPressed())
	//	m_currentState = GameState::EXIT;
}

GameState MainMenu::OnUserUpdate(float frameDelta)
{

	// Update
	//----------------------------------------------------------------------------------
	mousePoint = GetMousePosition();
	btnAction = false;

	// Check button state
	if (CheckCollisionPointRec(mousePoint, btnBounds))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
		else btnState = 1;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
	}
	else btnState = 0;

	if (btnAction)
	{
		PlaySound(fxButton);

		// TODO: Any desired action
	}

	// Calculate button frame rectangle to draw depending on button state
	sourceRec.y = btnState * frameHeight;
	//----------------------------------------------------------------------------------


	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();
	DrawText("Congrats! You created your first window!", ((float)GetScreenWidth() / 2.0f) - 300.f, float(GetScreenHeight()) / 2.0f + 200, 32, LIGHTGRAY);
	DrawTextureRec(button, sourceRec, {btnBounds.x, btnBounds.y}, WHITE); // Draw button frame
	ClearBackground(RAYWHITE);

	EndDrawing();
	//----------------------------------------------------------------------------------

	return m_currentState;
}

void MainMenu::OnExit()
{
	//m_playButton->remove();
	//m_editorButton->remove();
	//m_highScoreButton->remove();
	//m_exitButton->remove();
}

void MainMenu::InitButtons()
{

	fxButton = LoadSound("../resources/sounds/buttonfx.wav");
	button = LoadTexture("../resources/textures/startbutton.png");

	frameHeight = static_cast<float>(button.height) / static_cast<float>(m_Numframes);

	sourceRec = { 0,0,static_cast<float>(button.width), frameHeight };
	btnBounds = { (float)GetScreenWidth() / 2.0f - (float)button.width / 2.0f, (float)GetScreenHeight() / 2.0f - (float)button.height / m_Numframes / 2.0f, (float)button.width, frameHeight};

	btnState = 0;
	btnAction = false;

	//int offsetX = (m_windowWidth / 4);
	//int offsetY = (m_windowHeight / 8);
	//int centerX = (m_windowWidth / 2);
	//int currentYPos = offsetY;
	//int padding = 10;

	//wchar_t textPlay[] = L"Play";
	//wchar_t textEditor[] = L"Editor";
	//wchar_t textHighScore[] = L"High Score";
	//wchar_t textExit[] = L"Exit";

	////Play button
	//m_playButton = guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textPlay);
	//currentYPos += offsetY;
	////Editor button
	//m_editorButton = guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textEditor);
	//currentYPos += offsetY;
	////High score button
	//m_highScoreButton = guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textHighScore);
	//currentYPos += offsetY;
	////Exit button
	//m_exitButton = guienv->addButton(irr::core::rect<irr::s32>((centerX - (offsetX / 2)), (currentYPos + padding), (centerX + (offsetX / 2)), (currentYPos + offsetY)), nullptr, 0, textExit);
}