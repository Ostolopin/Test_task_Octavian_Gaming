#include "IdleState.h"
#include "SpinningState.h"
#include <GL/glut.h>
#include <random>
#include <iostream>

IdleState::IdleState(SlotMachine* m) : machine(m) {}

void IdleState::handleMouse(int button, int btnState, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && btnState == GLUT_DOWN) {
        Vec2 mousePos = { static_cast<float>(x), static_cast<float>(y) };

        // ���� ������ ������ 5:
        if (machine->balance < 5) {
            // ���� ������ ��� �� ����, ��������� ������ �������
            if (!machine->creditTaken) {
                if (machine->creditButton.isClicked(mousePos)) {
                    // ���� ������: +20 � �������, ���� 50
                    machine->balance += 20;
                    machine->creditTaken = true;
                    machine->creditDebt = 50;
                }
            }
            // ���� ������ ��� ���� � �� ��� ����� ���
            return;
        }

        // ���� ������� ����������, ������������ ������� �� Start
        if (machine->startButton.isClicked(mousePos)) {
            if (machine->balance >= 5) {
                // ������� ��������� ����
                machine->balance -= 5;
                // ��������� �������� ������� �������� � ������ ��������� ���������
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<float> dist(250.f, 350.f);
                for (auto& reel : machine->reels) {
                    reel.startSpin(dist(gen));
                }
                machine->stateMachine.changeState(std::make_unique<SpinningState>(machine));
            }
        }
    }
}

void IdleState::update(float dt) {
    
}

void IdleState::render() {
    std::string message;

    // ���� ������ ������ ��������� ����
    if (machine->balance < 5) {
        if (!machine->creditTaken) {
            machine->messagePanelText = "Insufficient funds! Press Credit to get 20 Eurodollar (Debt=50 Eurodollar)";
            machine->creditButton.render();
        }
        else {
            machine->messagePanelText = "Insufficient funds! Please repay your credit.";
        }
    }
    else {
        machine->messagePanelText = "Press Start to Play";
    }
}
