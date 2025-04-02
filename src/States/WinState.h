#ifndef WINSTATE_H
#define WINSTATE_H

#include "State.h"
#include "../SlotMachine.h"

// Состояние показа результата выигрыша
class WinState : public State {
public:
    WinState(SlotMachine* machine);
    void handleMouse(int button, int state, int x, int y) override;
    void update(float dt) override;
    void render() override;
private:
    SlotMachine* machine;
    float displayTime;
    float elapsedTime;
    std::string resultMessage;
};

#endif // WINSTATE_H
