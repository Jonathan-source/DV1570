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

	bool OnUpdate(float frameDelta) override;

	void OnRender() override;

	void OnExit() override;


private:
	Camera m_camera;
	Ray m_cameraRay;
	Vector3 m_cameraVelocity;
	const float m_cameraSpeed = 5.f;
	float m_cameraSpeedModifier = 1.0f;

	struct Object 
	{
		Vector3 position;
		Model model;
		Color color;
	};

	Vector3 m_boxPosition;
	Color m_boxColor;
	bool m_isBoxPositionValid;

	std::vector<Object> m_objects;

	Rectangle m_itemRects[10];
	int m_itemSelected ;
	int m_itemSelectedPrev;
	int m_itemMouseHover;
	bool m_mouseWasPressed;
	bool m_isMouseOnPanel;

	Rectangle m_btnSaveRec;
	bool m_btnSaveMouseHover;
	bool m_showSaveMessage;
	int m_saveMessageCounter;

	void UpdateCamera(float frameDelta);
	void HandleCameraInput();
	void ZoomIn();
	void ZoomOut();
	void DrawObjects();

	void SetupPanel();
	void HandleItemSelectionInput();
	void HandleItemPlacementInput();
	void DrawPanel();
};