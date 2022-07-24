#pragma once
#include "Potion.h"

#include <raylib.h>

class PotionManager
{
public:
	// Constructor
	PotionManager() = default;
	
	// Functions
	void SpawnPotion(int _healthScore);

private:
	// Data
	std::vector<Potion> m_potions;
};

