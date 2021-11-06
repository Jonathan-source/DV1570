#include "Entity.h"

Entity::Entity()
	: m_position(0.0f, 0.0f, 0.0f),
	  m_mesh(nullptr),
	  m_texture(nullptr),
	  m_meshSceneNode(nullptr)
{
}

Entity::Entity(irr::core::vector3d<float>& position, irr::scene::IMesh* mesh, irr::video::ITexture* texture)
	: m_position(position),
	  m_mesh(mesh),
	  m_texture(texture),
	  m_meshSceneNode(nullptr)
{
}

irr::core::vector3d<float> Entity::GetPosition() const
{
	return this->m_position;
}

irr::scene::IMesh* Entity::GetMesh() const
{
	return this->m_mesh;
}

irr::video::ITexture* Entity::GetTexture() const
{
	return this->m_texture;
}

void Entity::SetPosition(const irr::core::vector3d<float> position)
{
	this->m_position = position;
}

void Entity::SetMesh(irr::scene::IMesh* mesh)
{
	this->m_mesh = mesh;
}

void Entity::setTexture(irr::video::ITexture* texture)
{
	this->m_texture = texture;
}

void Entity::SetMeshSceneNode(irr::scene::IMeshSceneNode* const mesh_scene_node)
{
	this->m_meshSceneNode = mesh_scene_node;
}

void Entity::Move(const irr::core::vector3d<float> velocity, float delta, float baseSpeed)
{
	this->m_position = this->m_position + (velocity * delta * baseSpeed);
	
	if(m_meshSceneNode != nullptr)
		m_meshSceneNode->setPosition(m_position);
}

irr::scene::IMeshSceneNode* Entity::GetMeshSceneNode() const
{
	return m_meshSceneNode;
}
