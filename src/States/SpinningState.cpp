#include "SpinningState.h"
#include "WinState.h"
#include <GL/glut.h>

SpinningState::SpinningState(SlotMachine* m)
    : machine(m), elapsedTime(0.f), autoStopTime(3.f), stopInitiated(false)
{}

void SpinningState::handleMouse(int button, int btnState, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && btnState == GLUT_DOWN) {
        Vec2 mousePos = { static_cast<float>(x), static_cast<float>(y) };
        if (machine->stopButton.isClicked(mousePos)) {
            initiateStop();
        }
    }
}

void SpinningState::initiateStop() {
    if (!stopInitiated) {
        for (auto& reel : machine->reels) {
            reel.stopSpin();
        }
        stopInitiated = true;
    }
}

void SpinningState::update(float dt) {
    elapsedTime += dt;
    bool allStopped = true;
    for (auto& reel : machine->reels) {
        if (reel.isSpinning())
            allStopped = false;
    }
    if (!stopInitiated && elapsedTime >= autoStopTime) {
        initiateStop();
    }
    if (allStopped && stopInitiated) {
        machine->stateMachine.changeState(std::make_unique<class WinState>(machine));
    }
}

void SpinningState::render() {
    machine->messagePanelText = "Spinning...";
}
