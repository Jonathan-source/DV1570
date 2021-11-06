#pragma once

#include <iostream>

#include "GameStates.h"
#include "StateMachine.h"
#include "Player.h"

class Game : public IState
{
public:
	Game(irr::IrrlichtDevice* device);
	virtual ~Game() = default;

	void OnEnter() override;
	void OnUserInput(const EventHandler& eventHandler) override;	
	GameState OnUserUpdate() override;
	void OnExit() override;

private:
	irr::IrrlichtDevice* device;
	GameState m_currentState;
	Player m_player;
	irr::scene::ICameraSceneNode* m_camera;

	//Timer
	u32 then;
	u32 now;
	f32 frameDeltaTime;
};
