#include "MainMenu.h"

MainMenu::MainMenu()
	:m_Numframes(3),
	mousePoint({ 0.0f,0.0f }),
	buttonPadding(100.f)
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

	// Check t_startButton state
	if (CheckCollisionPointRec(mousePoint, startBtnBounds))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			startBtnState = 2;
		else
			startBtnState = 1;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			startBtnAction = true;
		}
		
	}
	else startBtnState = 0;

	// Check t_editorButton state
	if (CheckCollisionPointRec(mousePoint, editorBtnBounds))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) editorBtnState = 2;
		else editorBtnState = 1;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) editorBtnAction = true;
	}
	else editorBtnState = 0;

	// Check t_highscoreButton state
	if (CheckCollisionPointRec(mousePoint, highscoreBtnBounds))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) highscoreBtnState = 2;
		else highscoreBtnState = 1;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) highscoreBtnAction = true;
	}
	else highscoreBtnState = 0;

	// Check t_exitButton state
	if (CheckCollisionPointRec(mousePoint, exitBtnBounds))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) exitBtnState = 2;
		else exitBtnState = 1;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) exitBtnAction = true;
	}
	else exitBtnState = 0;

	//Activate action of the button
	if(startBtnAction)
	{
		PlaySound(fxButton);
		m_currentState = GameState::GAME;
	}
	else if(editorBtnAction)
	{
		PlaySound(fxButton);
		m_currentState = GameState::EDITOR;
	}
	else if (highscoreBtnAction)
	{
		PlaySound(fxButton);
		m_currentState = GameState::HIGHSCORE;
	}
	else if(exitBtnAction)
	{
		PlaySound(fxButton);
		m_currentState = GameState::EXIT;
	}

	// Calculate t_startButton frame rectangle to draw depending on t_startButton state
	srcRecStartButton.y = startBtnState * frameHeight;
	srcRecEditorButton.y = editorBtnState * frameHeight;
	srcRecHighscoreButton.y = highscoreBtnState * frameHeight;
	srcRecExitButton.y = exitBtnState * frameHeight;
	//----------------------------------------------------------------------------------


	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();
	DrawText("Main Menu!", ((float)GetScreenWidth() / 2.0f) - 85.f, 80, 32, YELLOW);
	DrawTextureRec(t_startButton, srcRecStartButton, {startBtnBounds.x, startBtnBounds.y}, WHITE); // Draw t_startButton frame
	DrawTextureRec(t_editorButton, srcRecEditorButton, { editorBtnBounds.x, editorBtnBounds.y }, WHITE); // Draw t_startButton frame
	DrawTextureRec(t_highscoreButton, srcRecHighscoreButton, { highscoreBtnBounds.x, highscoreBtnBounds.y }, WHITE); // Draw t_startButton frame
	DrawTextureRec(t_exitButton, srcRecExitButton, { exitBtnBounds.x, exitBtnBounds.y }, WHITE); // Draw t_startButton frame
	ClearBackground(DARKGRAY);

	EndDrawing();
	//----------------------------------------------------------------------------------

	return m_currentState;
}

void MainMenu::OnExit()
{
	UnloadTexture(t_startButton);
	UnloadTexture(t_editorButton);
	UnloadTexture(t_highscoreButton);
	UnloadTexture(t_exitButton);
}

void MainMenu::InitButtons()
{

	fxButton = LoadSound("../resources/sounds/buttonfx.wav");
	t_startButton = LoadTexture("../resources/textures/startbutton.png");
	t_editorButton = LoadTexture("../resources/textures/editorbutton.png");
	t_highscoreButton = LoadTexture("../resources/textures/highscorebutton.png");
	t_exitButton = LoadTexture("../resources/textures/exitbutton.png");

	frameHeight = static_cast<float>(t_startButton.height) / static_cast<float>(m_Numframes);

	srcRecStartButton = { 0,0,static_cast<float>(t_startButton.width), frameHeight };
	srcRecEditorButton = srcRecStartButton;
	srcRecHighscoreButton = srcRecStartButton;
	srcRecExitButton = srcRecStartButton;

	startBtnBounds = { (float)GetScreenWidth() / 2.0f - (float)t_startButton.width / 2.0f, (float)GetScreenHeight() / 2.0f - (float)t_startButton.height / m_Numframes / 2.0f, (float)t_startButton.width, frameHeight };
	startBtnBounds.y = 200.f;
	editorBtnBounds = startBtnBounds;
	editorBtnBounds.y += buttonPadding;

	highscoreBtnBounds = editorBtnBounds;
	highscoreBtnBounds.y += buttonPadding;

	exitBtnBounds = highscoreBtnBounds;
	exitBtnBounds.y += buttonPadding;

	startBtnState = 0;
	editorBtnState = 0;
	highscoreBtnState = 0;
	exitBtnState = 0;

	startBtnAction = false;
	editorBtnAction = false;
	highscoreBtnAction = false;
	exitBtnAction = false;
}
