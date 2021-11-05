#pragma once

#define SafeDelete(x) if(x) { delete x; x = nullptr; }

#include <string>
#include <unordered_map>

#include "EventHandler.h"

class IState
{
public:
	virtual ~IState() = default;
	virtual void OnEnter() = 0;
	virtual void OnUserUpdate() = 0;
	virtual void OnUserInput(const EventHandler& eventHandler) = 0;
	virtual void OnExit() = 0;
};

class EmptyState : public IState
{
public:
	EmptyState() = default;
	virtual ~EmptyState() = default;
	void OnEnter() override {}
	void OnUserUpdate() override {}
	void OnUserInput(const EventHandler& eventHandler) override {}
	void OnExit() override {}
};

class StateMachine
{
public:
	StateMachine();
	virtual ~StateMachine();

	IState* Current() const;
	void Add(const std::string &id, IState * state);
	void Remove(const std::string &id);
	void Clear();

	void Change(const std::string &id);
	void Update(const EventHandler& eventHandler);

private:
	std::unordered_map<std::string, IState*> m_states;
	std::unordered_map<std::string, IState*>::iterator m_it;
	IState * m_current = new EmptyState();

};

inline StateMachine::StateMachine()
{

}

inline IState* StateMachine::Current() const
{
	return m_current;
}

inline void StateMachine::Add(const std::string& id, IState* state)
{
	m_states.emplace(id, state);
}

inline void StateMachine::Remove(const std::string& id)
{
	m_it = m_states.find(id);
	if (m_it != m_states.end())
		SafeDelete(m_it->second);
}

inline void StateMachine::Clear()
{
	m_it = m_states.begin();
	while(m_it != m_states.end())
		SafeDelete(m_it->second)
}

inline void StateMachine::Change(const std::string& id)
{
	m_current->OnExit();
	IState* next = m_states[id];
	next->OnEnter();
	m_current = next;
}

inline void StateMachine::Update(const EventHandler& eventHandler)
{
	m_current->OnUserInput(eventHandler);
	m_current->OnUserUpdate();
}

inline StateMachine::~StateMachine()
{
}
