#include "pch.h"
#include "PotionManager.h"

void PotionManager::SpawnPotion(int _healthScore)
{
	m_potions.push_back(Potion(_healthScore));
}
