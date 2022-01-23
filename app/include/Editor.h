#pragma once
#include "Entity.h"
#include "StateMachine.h"

class Editor : public IState
{
public:
	Editor();
	virtual ~Editor() = default;

	void OnEnter() override;

	void OnInput() override;

	void OnUpdate(float frameDelta) override;

	void OnRender() override;

	void OnExit() override;


private:
	Camera m_camera;
	Entity m_test;

	void UpdateCamera(float frameDelta);
	void HandleCameraInput();
	void ZoomIn();
	void ZoomOut();
};