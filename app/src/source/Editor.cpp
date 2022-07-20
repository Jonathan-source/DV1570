#include "pch.h"
#include "Editor.h"
#include "ResourceManager.h"
#include "LevelManager.h"

#define CAMERASPEED 5.f;
#define GRID_X 50
#define GRID_Y 50

Editor::Editor()
	: m_cameraVelocity({ 0.f,0.f,0.f })
	, m_cameraSpeedModifier(1.f)
	, m_saveMessageCounter(0)
	, m_showSaveMessage(false)
{
	m_items.push_back({
		ResourceManager::Get().GetTexture("tree_1_icon.png"),
		"tree_1.obj" }
	);

	m_items.push_back({
		ResourceManager::Get().GetTexture("tree_2_icon.png"),
		"tree_2.obj" }
	);

	m_items.push_back({
		ResourceManager::Get().GetTexture("rock_1_icon.png"),
		"rock_1.obj" }
	);

	m_items.push_back({
		ResourceManager::Get().GetTexture("spawner_1_icon.png"),
		"cube.obj" }
	);

	m_items.push_back({
		ResourceManager::Get().GetTexture("zombie_1_icon.png"),
		"zombie.obj" }
	);

	LoadLevel();
}

void Editor::OnEnter()
{
	m_camera.position = { 0.0f, 10.0f, 10.0f };
	m_camera.target = { 0.0f, 0.0f, 0.0f };	
	m_camera.up = { 0.0f, 1.0f, 0.0f };	
	m_camera.fovy = 45.0f;  
	m_camera.projection = CAMERA_PERSPECTIVE;
	
	SetupPanel();
}

void Editor::OnInput()
{
	m_cameraRay = GetMouseRay(GetMousePosition(), m_camera);

	HandleCameraInput();

	HandleItemSelectionInput();

	HandleItemPlacementInput();

	if (IsKeyPressed(KEY_ESCAPE))
	{
		GetStateMachine()->Change("MainMenu");
	}
}

bool Editor::OnUpdate(float frameDelta)
{
	UpdateCamera(frameDelta);

	UpdateSaveMsgTimer(frameDelta);

	return true;
}

void Editor::OnRender()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	BeginMode3D(m_camera);

	DrawTileGrid();

	DrawObjects();

	EndMode3D();

	DrawPanel();

	EndDrawing();
}

void Editor::OnExit()
{

}

void Editor::UpdateCamera(float frameDelta)
{
	const float velocity = frameDelta * m_cameraSpeedModifier * CAMERASPEED;
	m_camera.position = Vector3Add(Vector3Scale(m_cameraVelocity, velocity), m_camera.position);
	m_camera.target = Vector3Add(Vector3Scale(m_cameraVelocity, velocity), m_camera.target);
}

void Editor::HandleCameraInput()
{
	// Movement directions
	if (IsKeyDown(KEY_A))
		m_cameraVelocity.x = -1.0f;

	if (IsKeyDown(KEY_W))
		m_cameraVelocity.z = -1.0f;

	if (IsKeyDown(KEY_D))
		m_cameraVelocity.x = 1.0f;

	if (IsKeyDown(KEY_S))
		m_cameraVelocity.z = 1.0f;

	if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
		m_cameraVelocity.x = 0;

	if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
		m_cameraVelocity.z = 0;

	// Increase speed
	if (IsKeyDown(KEY_LEFT_SHIFT))
		m_cameraSpeedModifier = 3.f;
	else 
		m_cameraSpeedModifier = 1.f;
}

void Editor::UpdateSaveMsgTimer(float frameDelta)
{
	if (m_showSaveMessage)
	{
		m_saveMessageCounter++; 
		if (m_saveMessageCounter > 120) // 60 frames per sec: 2s = 120.
		{
			m_showSaveMessage = false;
			m_saveMessageCounter = 0;
		}
	}
}

void Editor::DrawObjects()
{
	for (const auto& obj : m_objects)
	{
		DrawModel(ResourceManager::Get().GetModel(obj.modelName),
			obj.position, 1.f, WHITE);
		//DrawBoundingBox(obj.boundingBox, RED);
	}
}

void Editor::SetupPanel()
{
	for (int i = 0; i < m_items.size(); i++)
	{
		m_itemRects[i].x = 20 + 64.0f * i + 4 * i;
		m_itemRects[i].y = 20;
		m_itemRects[i].width = 64;
		m_itemRects[i].height = 64;
	}

	m_btnClearRec = { GetScreenWidth() / 1.5f - 10, 20, 85, 60 };
	m_btnSaveRec = { GetScreenWidth() / 1.2f - 10, 20, 85, 60 };
}

void Editor::HandleItemSelectionInput()
{
	Vector2 mousePos = GetMousePosition();

	if (m_itemSelected >= 10) m_itemSelected = 10 - 1;
	else if (m_itemSelected < 0) m_itemSelected = 0;

	m_isMouseOnPanel = false;
	m_btnSaveMouseHover = false;
	m_btnClearMouseHover = false;

	// Check if mouse hover panel
	if (mousePos.y <= 100.f)
	{
		m_isMouseOnPanel = true;

		// Choose item with mouse
		for (int i = 0; i < 10; i++)
		{
			if (CheckCollisionPointRec(mousePos, m_itemRects[i]))
			{
				m_itemMouseHover = i;
					break;
			}
			else 
				m_itemMouseHover = -1;
		}

		if ((m_itemMouseHover >= 0) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			m_itemSelected = m_itemMouseHover;
			m_itemSelectedPrev = m_itemMouseHover;
		}

		// Check mouse hover save button
		if (CheckCollisionPointRec(mousePos, m_btnSaveRec))
		{
			m_btnSaveMouseHover = true;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				m_showSaveMessage = true;

				if (m_objects.empty())
				{
					std::filesystem::remove("level.eff");
				}
				else
				{
					SaveLevel();
				}
			}
		}

		// Check mouse hover clear button
		if (CheckCollisionPointRec(mousePos, m_btnClearRec))
		{
			m_btnClearMouseHover = true;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				m_objects.clear();	
			}
		}
	}
}

void Editor::DrawPanel()
{
	// Draw top panel
	DrawRectangle(0, 0, GetScreenWidth(), 100, DARKGRAY);
	DrawLine(0, 100, GetScreenWidth(), 100, LIGHTGRAY);

	// Draw item selection rectangles
	auto& rm = ResourceManager::Get();

	for (int i = 0; i < m_items.size(); i++) {
		DrawTexture(m_items[i].texture, (int)m_itemRects[i].x, (int)m_itemRects[i].y, WHITE);
	}

	// Draw faded rectangle on item hover
	if (m_itemMouseHover >= 0) 
		DrawRectangleRec(m_itemRects[m_itemMouseHover], Fade(WHITE, 0.6f));

	// Draw rectangle boarder around current selected item
	Rectangle rect = { m_itemRects[m_itemSelected].x - 4, m_itemRects[m_itemSelected].y - 4,
		m_itemRects[m_itemSelected].width + 8, m_itemRects[m_itemSelected].height + 8 };
	DrawRectangleLinesEx(rect, 2, RED);

	// Drawn clear button
	DrawRectangleLinesEx(m_btnClearRec, 2, m_btnClearMouseHover ? RED : BLACK);
	DrawText("CLEAR", GetScreenWidth() / 1.5f, 40, 20, m_btnClearMouseHover ? RED : BLACK);

	// Draw save button
	DrawRectangleLinesEx(m_btnSaveRec, 2, m_btnSaveMouseHover ? RED : BLACK);
	DrawText("SAVE!", GetScreenWidth() / 1.2f, 40, 20, m_btnSaveMouseHover ? RED : BLACK);

	// Draw save image message
	if (m_showSaveMessage)
	{
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
		DrawRectangle(0, 150, GetScreenWidth(), 80, BLACK);
		std::string name = "default_level";
		std::string text = "LEVEL SAVED: '" + name + "'";
		DrawText(text.c_str(), GetScreenWidth() / 3, 180, 20, RAYWHITE);
	}
}

void Editor::DrawTileGrid()
{

}

void Editor::SaveLevel()
{
	std::fstream writer;
	writer.open("level.eff", std::ios::out | std::ios::binary);
	if (writer.is_open())
	{
		size_t num_elements = m_objects.size();
		writer.write(reinterpret_cast<char*>(&num_elements), sizeof(size_t));
		writer.write(reinterpret_cast<char*>(&m_objects[0]), num_elements * sizeof(SceneObject));
		writer.close();
	}
	else
	{
		std::cout << "\nAn error occured when writing data to file.\n\n";
		writer.clear();
	}
}

void Editor::LoadLevel()
{
	std::fstream reader;
	reader.open("level.eff", std::ios::in | std::ios::binary);
	if (reader.is_open())
	{
		size_t num_elements = 0;
		reader.read(reinterpret_cast<char*>(&num_elements), sizeof(size_t));
		m_objects.clear();
		m_objects.resize(num_elements);
		reader.read(reinterpret_cast<char*>(&m_objects[0]), num_elements * sizeof(SceneObject));
		reader.close();
	}
	else
	{
		std::cout << "\nAn error occured when reading data from file.\n\n";
		reader.clear();
	}
}

void Editor::HandleItemPlacementInput()
{
	if (m_isMouseOnPanel) return;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Ray ray = GetMouseRay(GetMousePosition(), m_camera);
		RayCollision collision = { 0 };
		for (int i = 0; i < m_objects.size() && !collision.hit; ++i)
		{
			Vector3 position = m_objects[i].position;
			BoundingBox boundingBox = m_objects[i].boundingBox;

			collision = GetRayCollisionBox(ray, BoundingBox{ Vector3{
					position.x + boundingBox.min.x,
					position.y + boundingBox.min.y,
					position.z + boundingBox.min.z,
			},Vector3{
					position.x + boundingBox.max.x,
					position.y + boundingBox.max.y,
					position.z + boundingBox.max.z,
				}
			});	
		}

		if (!collision.hit)
		{
			collision = GetRayCollisionQuad(ray, { 0, 0, 50 }, { 50, 0, 50 }, { 50, 0, -50 }, { 0, 0, -50 });
			std::string modelName = m_items[m_itemSelected].modelName;
			Model model = ResourceManager::Get().GetModel(modelName);

			Vector3 position = collision.point;
			position.x = floorf(position.x) + 0.5f;
			position.z = floorf(position.z) + 0.5f;
	
			SceneObject object;
			object.position = position;
			object.boundingBox = GetMeshBoundingBox(model.meshes[0]);
			strcpy_s(object.modelName, modelName.c_str());
			m_objects.emplace_back(object);
		}
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		Ray ray = GetMouseRay(GetMousePosition(), m_camera);
		RayCollision collision = { 0 };
		for (int i = 0; i < m_objects.size() && !collision.hit; ++i)
		{
			Vector3 position = m_objects[i].position;
			BoundingBox boundingBox = m_objects[i].boundingBox;

			collision = GetRayCollisionBox(ray, BoundingBox{ Vector3{
					position.x + boundingBox.min.x,
					position.y + boundingBox.min.y,
					position.z + boundingBox.min.z,
			},Vector3{
					position.x + boundingBox.max.x,
					position.y + boundingBox.max.y,
					position.z + boundingBox.max.z,
				}
			});

			if (collision.hit)
			{
				m_objects.erase(m_objects.begin() + i);
			}
		}
	}
}

