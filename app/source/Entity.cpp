#include "Entity.h"

Entity::Entity()
	: m_mesh(nullptr),
	  m_texture(nullptr),
	  m_meshSceneNode(nullptr)
{
}

Entity::Entity(irr::IrrlichtDevice* device, irr::scene::IMesh* mesh, irr::video::ITexture* texture, irr::core::vector3d<float> position)
	: m_mesh(mesh),
	  m_texture(texture),
	  m_meshSceneNode(device->getSceneManager()->addMeshSceneNode(mesh))
{
	m_meshSceneNode->setPosition(position);
}

irr::core::vector3d<float> Entity::GetPosition() const
{
	if (m_meshSceneNode != nullptr)
		return m_meshSceneNode->getPosition();
	
	return {0.f,0.f,0.f,};
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
	if(m_meshSceneNode != nullptr)
		m_meshSceneNode->setPosition(position);
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
	if(m_meshSceneNode != nullptr)
	{
		const irr::core::vector3d<float> newPosition = this->m_meshSceneNode->getPosition() + (velocity * delta * baseSpeed);
		m_meshSceneNode->setPosition(newPosition);
	}
}

irr::scene::IMeshSceneNode* Entity::GetMeshSceneNode() const
{
	return m_meshSceneNode;
}
