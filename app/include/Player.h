#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	Player(int health, int attdmg, float runSpeed, Vector3 position);
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
	void PlayerInput();
	void Shoot();

	Vector3 GetVelocity() const;
	void SetVelocity(const Vector3& velocity);
private:
	int m_health;
	int m_attackDmg;
	float m_runSpeed;
	Vector3 m_velocity;

};