#pragma once
#include <raylib.h>
#include <string>

class Entity
{
public:
	Entity() = default;
	Entity(Vector3 position);
	virtual ~Entity() = default;
	Entity(const Entity& other) = default; // copy constructor
	Entity(Entity&& other) noexcept = default; // move constructor
	Entity& operator=(const Entity& other) = default; //copy assignment
	Entity& operator = (Entity&& other) noexcept = default; //Move assignment

	//Getters
	[[nodiscard]] Vector3 GetPosition() const;

	//Setters
	void SetPosition(Vector3 position);

	//Functions
	//virtual void Move(Vector3 velocity, float delta, float baseSpeed = 1);
private:
	Vector3 m_position;
};