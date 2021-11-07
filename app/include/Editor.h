#pragma once

#include "Entity.h"
#include "GameStates.h"
#include "StateMachine.h"

class Editor : public IState
{
public:
	Editor(irr::IrrlichtDevice* device);
	virtual ~Editor() = default;

	void OnEnter() override;

	void OnUserInput(const EventReceiver& eventHandler) override;

	GameState OnUserUpdate(float frameDelta) override;

	void OnExit() override;


private:
	irr::IrrlichtDevice* device;
	GameState m_currentState;

	irr::scene::ICameraSceneNode* m_camera;
	float m_cameraSpeed;
	irr::core::vector3d<float> m_cameraDirection;

	Entity m_test;


	void UpdateCamera(float frameDelta);
	void HandleCameraInput(const EventReceiver& eventHandler);
	void ZoomIn();
	void ZoomOut();
};
