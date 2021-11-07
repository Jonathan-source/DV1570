#pragma once
#include <irrlicht.h>
#include <string>

class Entity
{
public:
	Entity();
	Entity(irr::IrrlichtDevice* device, irr::scene::IMesh* mesh, irr::video::ITexture* texture = nullptr, irr::core::vector3d<float> position = {0.f,0.f,0.f});
	virtual ~Entity() = default;
	Entity(const Entity& other) = default; // copy constructor
	Entity(Entity&& other) noexcept = default; // move constructor
	Entity& operator=(const Entity& other) = default; //copy assignment
	Entity& operator = (Entity && other) noexcept = default; //Move assignment

	//Getters
	[[nodiscard]] irr::core::vector3d<float> GetPosition() const;
	[[nodiscard]] irr::scene::IMesh* GetMesh() const;
	[[nodiscard]] irr::video::ITexture* GetTexture() const;
	[[nodiscard]] irr::scene::IMeshSceneNode* GetMeshSceneNode() const;
	
	//Setters
	void SetPosition(irr::core::vector3d<float> position);
	void SetMesh(irr::scene::IMesh* mesh);
	void setTexture(irr::video::ITexture* texture);
	void SetMeshSceneNode(irr::scene::IMeshSceneNode* const mesh_scene_node);
	
	//Functions
	virtual void Move(irr::core::vector3d<float> velocity, float delta, float baseSpeed = 1);
private:
	irr::scene::IMesh* m_mesh;
	irr::video::ITexture* m_texture;
	irr::scene::IMeshSceneNode* m_meshSceneNode;
};

