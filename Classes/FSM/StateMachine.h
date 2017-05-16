#pragma once
#ifndef _StateMachine_H_
#define _StateMachine_H_

#include"State.h"

template <class entity_type>
class StateMachine {
public:
	StateMachine(entity_type* owner) :
		m_pOwner(owner),
		m_pCurrentState(nullptr),
		m_pPreviousState(nullptr),
		m_pGlobalState(nullptr){}

	void setCurrentState(State<entity_type>* state) {
		//state->Enter(m_pOwner);
		m_pCurrentState = state;
	}
	void setPrevoiusState(State<entity_type>* state) {
		m_pPreviousState = state;
	}
	void setGlobalState(State<entity_type>* state) {
		m_pGlobalState = state;
	}
	State<entity_type>* getCurrentState()const {
		return m_pCurrentState;
	}
	State<entity_type>* getPrevoiusState()const {
		return m_pPreviousState;
	}
	State<entity_type>* getGlobalState()const {
		return m_pGlobalState;
	}

	bool IsInState(const State<entity_type>* state)const {
		//if (m_pCurrentState == state)
		//	return true;
		//return false;
		m_pCurrentState == state ? return true : return false;
	}


	void update(float delta)const {
		if (m_pGlobalState)
			m_pGlobalState->Execute(m_pOwner);
		if (m_pCurrentState)
			m_pCurrentState->Execute(m_pOwner);
	}
	void changeState(State<entity_type>* pnewState) {
		//assert(pnewState && "<StateMachine::changeState>: trying to change to a null state");
		m_pPreviousState = m_pCurrentState;
		m_pCurrentState->Exit(m_pOwner);
		m_pCurrentState = pnewState;
		m_pCurrentState->Enter(m_pOwner);
	}
	void ReverToPreviousState() {
		changeState(m_pPreviousState);
	}
private:
	//指向拥有这个实例的智能体的指针
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;
	//记录上一个状态
	State<entity_type>* m_pPreviousState;
	//每次FSM更新，这个状态的逻辑被调用
	State<entity_type>* m_pGlobalState;


};

#endif // !_StateMachine_H_
