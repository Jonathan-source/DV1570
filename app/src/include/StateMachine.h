#pragma once

#define SafeDelete(x) if(x) { delete x; x = nullptr; }

#include <string>
#include <unordered_map>
#include "raylib.h"

class StateMachine;

class IState
{
public:
	virtual ~IState() = default;
	virtual void OnEnter() = 0;
	virtual void OnInput() = 0;
	virtual bool OnUpdate(float frameDelta) = 0;
	virtual void OnRender() = 0;
	virtual void OnExit() = 0;

	void SetStateMachine(StateMachine* sm) { if (!m_stateMachine) { m_stateMachine = sm; } }

protected:
	StateMachine* GetStateMachine() { return m_stateMachine; }

private:
	StateMachine * m_stateMachine = nullptr;
};


/**
* Todo: add security and error management.
*/
class StateMachine
{
public:
	StateMachine() = default;
	virtual ~StateMachine();

	IState* Current() const;
	void Add(const std::string& id, IState* state);
	void Change(const std::string& id);
	
private:
	std::unordered_map<std::string, IState*> m_states;
	IState* m_current;
};

inline IState* StateMachine::Current() const
{
	return m_current;
}

inline void StateMachine::Add(const std::string& id, IState* state)
{
	m_states.emplace(id, state);
	state->SetStateMachine(this);
}

inline void StateMachine::Change(const std::string& id)
{
	if (m_current) {
		m_current->OnExit();
	}
	IState* next = m_states[id];
	next->OnEnter();
	m_current = next;
}

inline StateMachine::~StateMachine()
{
	for (auto it = m_states.begin(); it != m_states.end(); it++) {
		SafeDelete(it->second);
	}
}