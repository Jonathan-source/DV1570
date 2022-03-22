#pragma once
#include <raylib.h>
#include <raymath.h>
#include <string>

// include Lua, assumes it is local to this file
extern "C"
{
#include "../libs/lua542/include/lua.h"
#include "../libs/lua542/include/lauxlib.h"
#include "../libs/lua542/include/lualib.h"
}

// Link to lua library
#ifdef _WIN32
#pragma comment(lib, "../libs/lua542/liblua54.a")
#endif

class Entity
{
public:
	Entity();
	Entity(Vector3 position);
	virtual ~Entity() = default;
	Entity(const Entity& other) = default; // copy constructor
	Entity(Entity&& other) noexcept = default; // move constructor
	Entity& operator=(const Entity& other) = default; //copy assignment
	Entity& operator = (Entity&& other) noexcept = default; //Move assignment

	//Getters
	[[nodiscard]] Vector3 GetPosition() const;
	[[nodiscard]] Model GetModel() const;
	//Setters
	void SetPosition(Vector3 position);
	void SetModel(Model model);
	//Functions
	virtual void Move(Vector3 velocity, float delta, float baseSpeed = 1);
private:
	Vector3 m_position;
protected:
	Model m_model;
};