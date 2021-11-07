#pragma once
#include "Entity.h"

class EventReceiver;

class Player : public Entity
{
public:
	Player();
	Player(irr::IrrlichtDevice* device, irr::scene::IMesh* mesh, irr::video::ITexture* texture = nullptr, int health = 100, int attdmg = 10, float runSpeed = 10.f, irr::core::vector3d<float> position = {0.f,0.f,0.f});
	~Player() = default;
	Player(const Player& other) = default; // copy constructor
	Player(Player&& other) noexcept = default; // move constructor
	Player& operator=(const Player& other) = default; //copy assignment
	Player& operator = (Player&& other) noexcept = default; //Move assignment

	//Getters
	[[nodiscard]] int GetHealth() const;
	[[nodiscard]] int GetAttackDamage() const;
	[[nodiscard]] float GetRunSpeed() const;

	//Setters
	void SetHealth(int health);
	void SetAttackDamage(int attdmg);
	void SetRunSpeed(float runSpeed);
	
	//Functions
	void PlayerInput(const EventReceiver& eventHandler);
	void Shoot();
	
private:
	int m_health;
	int m_attackDmg;
	float m_runSpeed;
	irr::core::vector3d<float> m_velocity;
public:
	irr::core::vector3d<float> GetVelocity() const;
	void SetVelocity(const irr::core::vector3d<float>& velocity);
};

