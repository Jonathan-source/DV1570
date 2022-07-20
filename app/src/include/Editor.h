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
	// Camera settings
	Camera m_camera;
	Ray m_cameraRay;
	Vector3 m_cameraVelocity;
	float m_cameraSpeedModifier;

	struct SceneObject {
		Vector3 position;
		BoundingBox boundingBox;
		char modelName[20];
	};

	struct PanelItem {
		Texture texture;
		std::string modelName;
	};

	std::vector<SceneObject> m_objects;
	std::vector<PanelItem> m_items;

	Rectangle m_itemRects[10];
	int m_itemSelected;
	int m_itemSelectedPrev;
	int m_itemMouseHover;
	bool m_mouseWasPressed;
	bool m_isMouseOnPanel;

	Rectangle m_btnSaveRec;
	bool m_btnSaveMouseHover;
	bool m_showSaveMessage;
	int m_saveMessageCounter;

	Rectangle m_btnClearRec;
	bool m_btnClearMouseHover;

	void UpdateCamera(float frameDelta);
	void UpdateSaveMsgTimer(float frameDelta);
	void HandleCameraInput();
	void DrawObjects();
	void SetupPanel();
	void HandleItemSelectionInput();
	void HandleItemPlacementInput();
	void DrawPanel();
	void DrawTileGrid();

	void SaveLevel();
	void LoadLevel();
};