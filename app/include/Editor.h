#pragma once

#pragma once

#include <iostream>

#include "Entity.h"
#include "GameStates.h"
#include "StateMachine.h"

class Editor : public IState
{
public:
	Editor(irr::IrrlichtDevice* device);
	virtual ~Editor() = default;

	void OnEnter() override;

	void OnUserInput(const EventHandler& eventHandler) override;

	GameState OnUserUpdate() override;

	void OnExit() override;


private:
	irr::IrrlichtDevice* device;
	GameState m_currentState;

	irr::scene::ICameraSceneNode* m_camera;
	irr::core::vector3d<float> m_cameraDirection;

	Entity m_test;


	void UpdateCamera();
	void HandleCameraInput(const EventHandler& eventHandler);
	void ZoomIn();
	void ZoomOut();
};
