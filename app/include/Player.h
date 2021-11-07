#pragma once
#include "Entity.h"
#include "Structs.h"
#include <vector>
class EventHandler;

class Player : public Entity
{
public:
	Player();
	Player(irr::IrrlichtDevice* device, irr::scene::IMesh* mesh, PlayerConfig& playerConfig, irr::video::ITexture* texture = nullptr);
	~Player() = default;
	Player(const Player& other) = default; // copy constructor
	Player(Player&& other) noexcept = default; // move constructor
	Player& operator=(const Player& other) = default; //copy assignment
	Player& operator = (Player&& other) noexcept = default; //Move assignment
	
	//Gets health of the player
	[[nodiscard]] int GetHealth() const;
	//Gets attack damage player projectiles does
	[[nodiscard]] int GetAttackDamage() const;
	//Gets moving speed of the player
	[[nodiscard]] float GetRunSpeed() const;
	//Gets all the projectiles player have
	[[nodiscard]] std::vector<Projectile>& GetProjectiles();
	//Gets projectiles moving speed
	[[nodiscard]] float GetProjectileSpeed() const;
	//Gets players current velocity
	[[nodiscard]] irr::core::vector3d<float> GetVelocity() const;
	//Gets player time cooldown between attacks
	[[nodiscard]] float GetAttackCooldown() const;
	//Gets life time in seconds on the projectiles 
	[[nodiscard]] float GetProjectileLifeTime() const;
	
	//Sets the health on player.
	void SetHealth(int health);
	//Sets the attack damage of the projectiles from player
	void SetAttackDamage(int attackDamage);
	//Sets how fast player moves
	void SetRunSpeed(float runSpeed);
	//Sets the speed on the projectiles
	void SetProjectileSpeed(const float projectile_speed);
	//Sets the velocity player node moves in
	void SetVelocity(const irr::core::vector3d<float>& velocity);
	//Sets how long time projectiles will move after they been shoot.
	void SetProjectileLifeTime(const float projectile_life_time);
	//Sets the time on how long cooldown between each attack will be in seconds.
	void SetAttackCooldown(const float attackCooldown);
	
	//Takes the users input and adjust the player velocity
	void PlayerInput(const EventHandler& eventHandler);
	//Shoots a projectile on the players forward direction.
	void Shoot();

	//addition on timers and Move player
	void Update(float frameDelta, irr::gui::ICursorControl* cursor);
	
private:
	//Rotate player towards mouse pos
	void UpdateRotation(irr::gui::ICursorControl* cursor);
	//Moves projectiles with assigned direction
	void UpdateProjectiles(float frameDelta);
	
	//Data
	int m_health;
	int m_attackDmg;
	
	float m_runSpeed;
	float m_projectileSpeed;
	float m_attackCooldown;
	float m_attackTimer;
	float m_projectileLifeTime;

	std::vector<Projectile> m_projectiles;
	irr::core::vector3d<float> m_velocity;
	irr::core::vector3d<float> m_forwardDirection;
};

