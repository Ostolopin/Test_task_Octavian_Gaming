#ifndef SPINNINGSTATE_H
#define SPINNINGSTATE_H

#include "State.h"
#include "../SlotMachine.h"

// Состояние вращения барабанов
class SpinningState : public State {
public:
    SpinningState(SlotMachine* machine);
    void handleMouse(int button, int state, int x, int y) override;
    void update(float dt) override;
    void render() override;
private:
    SlotMachine* machine;
    float elapsedTime;
    float autoStopTime;
    bool stopInitiated;
    void initiateStop();
};

#endif // SPINNINGSTATE_H
