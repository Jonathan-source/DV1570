#pragma once
#include <raylib.h>

#include "Entity.h"
class Potion : public Entity
{
public:
	// Constructors
	Potion(int _healthScore);

	// Getters
	int GetHealthScore();
	bool GetIsActive();
	// Setters
	void SetHealthScore(int _healthScore);
	void SetIsActive(bool _isActive);

private:
	int m_healthScore;
	bool m_isActive;
};

