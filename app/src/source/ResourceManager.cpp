#include "pch.h"
#include "ResourceManager.h"

void ResourceManager::SetResourcePath(const std::string& path)
{
    m_resourcePath = path;
}

Texture& ResourceManager::GetTexture(const std::string& name)
{
    TextureMap::iterator it = m_textures.find(name);
    if (it == m_textures.end())
    {
        Texture& texture = m_textures[name];
        texture = LoadTexture(std::string(m_resourcePath + "/textures/" + name).c_str());
        return texture;
    }
    return it->second;
}

Model& ResourceManager::GetModel(const std::string& name)
{
    ModelMap::iterator it = m_models.find(name);
    if (it == m_models.end())
    {
        Model& model = m_models[name];
        model = LoadModel(std::string(m_resourcePath + "/meshes/" + name).c_str());
        return model;
    }
    return it->second;
}

Sound& ResourceManager::GetSound(const std::string& name)
{
    SoundMap::iterator it = m_sounds.find(name);
    if (it == m_sounds.end())
    {
        Sound& sound = m_sounds[name];
        sound = LoadSound(std::string(m_resourcePath + "/sounds/" + name).c_str());
        return sound;
    }
    return it->second;
}

ResourceManager::~ResourceManager()
{
}
