#include "StateMachine.h"

void StateMachine::changeState(std::unique_ptr<State> newState) {
    currentState = std::move(newState);
}

void StateMachine::handleMouse(int button, int state, int x, int y) {
    if (currentState)
        currentState->handleMouse(button, state, x, y);
}

void StateMachine::update(float dt) {
    if (currentState)
        currentState->update(dt);
}

void StateMachine::render() {
    if (currentState)
        currentState->render();
}
