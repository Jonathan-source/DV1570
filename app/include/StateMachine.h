#pragma once

#define SafeDelete(x) if(x) { delete x; x = nullptr; }

#include <string>
#include <unordered_map>

#include "EventReceiver.h"
#include "GameStates.h"

class IState
{
public:
	virtual ~IState() = default;
	virtual void OnEnter() = 0;
	virtual GameState OnUserUpdate(float frameDelta) = 0;
	virtual void OnUserInput(const EventReceiver& eventHandler) = 0;
	virtual void OnExit() = 0;
};

class EmptyState : public IState
{
public:
	EmptyState() = default;
	virtual ~EmptyState() = default;
	void OnEnter() override {}
	GameState OnUserUpdate(float frameDelta) override { return GameState::NO_CHANGE; }
	void OnUserInput(const EventReceiver& eventHandler) override {}
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
	bool Update(const EventReceiver& eventHandler, float frameDelta);

private:
	std::unordered_map<std::string, IState*> m_states;
	std::unordered_map<std::string, IState*>::iterator m_it;
	IState * m_current;

};

inline StateMachine::StateMachine()
{
	Add("empty_state", new EmptyState());
	m_current = m_states["empty_state"];
	Current()->OnEnter();
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

inline bool StateMachine::Update(const EventReceiver& eventHandler, float frameDelta)
{
	bool status = true;
	m_current->OnUserInput(eventHandler);
	const GameState state = m_current->OnUserUpdate(frameDelta);
	if(state != GameState::NO_CHANGE)
	{
		switch(state)
		{
		case GameState::MENU:
			Change("main_menu");
			break;
		case GameState::GAME:
			Change("game");
			break;
		case GameState::PAUSE:
			Change("empty_state");
			break;
		case GameState::HIGHSCORE:
			Change("highscore");
			break;
		case GameState::EDITOR:
			Change("editor");
			break;
		case GameState::EXIT:
			status = false;
			break;
		default:
			break;
		}
	}

	return status;
}

inline StateMachine::~StateMachine()
{
	Clear();
}
