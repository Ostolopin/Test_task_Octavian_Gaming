#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "State.h"
#include "../SlotMachine.h"

// Состояние ожидания действия игрока
class IdleState : public State {
public:
    IdleState(SlotMachine* machine);
    void handleMouse(int button, int state, int x, int y) override;
    void update(float dt) override;
    void render() override;
private:
    SlotMachine* machine;
};

#endif // IDLESTATE_H
