#pragma once
#include "Entity.h"
#include "GameState.h"
#include "StateMachine.h"

class Editor : public IState
{
public:
	Editor();
	virtual ~Editor() = default;

	void OnEnter() override;

	void OnUserInput() override;

	GameState OnUserUpdate(float frameDelta) override;

	void OnExit() override;


private:
	GameState m_currentState;
	Camera m_camera;

	Entity m_test;

	void UpdateCamera(float frameDelta);
	void HandleCameraInput();
	void ZoomIn();
	void ZoomOut();
};