#pragma once

#include <iostream>
#include "Player.h"
#include "StateMachine.h"


class Game : public IState
{
public:
	Game() = default;
	virtual ~Game() = default;

	void OnEnter() override;
	void OnInput() override;
	void UpdateCamera();
	bool OnUpdate(float frameDelta) override;
	void OnRender() override;
	void OnExit() override;
	void InitCamera();

private:
	Camera m_camera;
	Player m_player;
};