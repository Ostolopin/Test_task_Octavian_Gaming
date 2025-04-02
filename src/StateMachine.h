#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <memory>
#include "States/State.h"

// Класс StateMachine для управления текущим состоянием игры
class StateMachine {
public:
    void changeState(std::unique_ptr<State> newState);
    void handleMouse(int button, int state, int x, int y);
    void update(float dt);
    void render();
    State* getCurrentState() const { return currentState.get(); }
private:
    std::unique_ptr<State> currentState;
};

#endif // STATEMACHINE_H
