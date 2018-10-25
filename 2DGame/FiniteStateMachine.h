#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H
#include <vector>
#include "IBehaviour.h"
#include "State.h"
#include "Transition.h"


class State;
class Transition;
class Condition;

class FiniteStateMachine : public IBehaviour {
public:

	FiniteStateMachine() : m_currentState(nullptr) {}

	virtual ~FiniteStateMachine() {
		for (auto state : m_states)
			delete state;
		for (auto t : m_transitions)
			delete t;
		for (auto c : m_conditions)
			delete c;
	}

	// add components, takes ownership
	State* addState(State* state) { m_states.push_back(state); return state; }

	Transition* addTransition(Transition* transition) {	m_transitions.push_back(transition); return transition;	}

	Condition* addCondition(Condition* condition) {	m_conditions.push_back(condition); return condition;}

	void setCurrentState(State* state) { m_currentState = state; }

	eBehaviourResult update(Agent* agent, float deltaTime) override;

protected:

	std::vector<State*> m_states;
	std::vector<Transition*> m_transitions;
	std::vector<Condition*> m_conditions;

	State* m_currentState;
};

inline eBehaviourResult FiniteStateMachine::update(Agent* agent,float deltaTime) {

	if (m_currentState != nullptr) {

		Transition* transition = m_currentState->getTriggeredTransition(agent);

		if (transition != nullptr) {
			m_currentState->exit(agent);
			m_currentState = transition->getTargetState();
			m_currentState->init(agent);
		}

		m_currentState->update(agent, deltaTime);
		return eBehaviourResult::SUCCESS;
	}

	return eBehaviourResult::FAILURE;
}

#endif // FINITESTATEMACHINE_H
