#include "pch.h"
#include "Potion.h"
#include "Potion.h"

Potion::Potion(int _healthScore)
	:m_healthScore(_healthScore)
	, m_isActive(false)
{}

int Potion::GetHealthScore()
{
	return m_healthScore;
}

bool Potion::GetIsActive()
{
	return m_isActive;
}

void Potion::SetHealthScore(int _healthScore)
{
	m_healthScore = _healthScore;
}

void Potion::SetIsActive(bool _isActive)
{
	m_isActive = _isActive;
}
