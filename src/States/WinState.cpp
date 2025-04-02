#include "WinState.h"
#include "IdleState.h"
#include <GL/glut.h>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

WinState::WinState(SlotMachine* m)
    : machine(m), displayTime(2.f), elapsedTime(0.f)
{
    // Определяем базовые значения для символов (от A до E)
    std::map<std::string, int> symbolValues{
        {"A", 1},
        {"B", 2},
        {"C", 3},
        {"D", 4},
        {"E", 5}
    };

    // Собираем частоты появления центральных символов со всех барабанов
    std::map<std::string, int> freq;
    for (const auto& reel : machine->reels) {
        std::string sym = reel.getCenterSymbol();
        freq[sym]++;
    }

    int winAmount = 0;
    // Рассчитываем выигрыш для каждого символа
    for (const auto& pair : freq) {
        int count = pair.second;
        int base = symbolValues[pair.first];
        if (count == 2) {
            // Для двух одинаковых: сумма = base + base
            winAmount += 2 * base;
        }
        else if (count >= 3) {
            if (base == 1) {
                // Для A: если выпало более двух, выигрыш = count * 1
                winAmount += count;
            }
            else {
                // Для остальных: выигрыш = base^count
                int contribution = 1;
                for (int i = 0; i < count; ++i) {
                    contribution *= base;
                }
                winAmount += contribution;
            }
        }
    }

    if (winAmount > 0) {
        int netWin = winAmount;
        std::ostringstream oss;
        // Если кредит взят, 50% выигрыша идет на погашение долга
        if (machine->creditTaken) {
            int repayment = winAmount / 2;
            int appliedRepayment = std::min(repayment, machine->creditDebt);
            netWin = winAmount - appliedRepayment;
            machine->creditDebt -= appliedRepayment;
            if (machine->creditDebt <= 0) {
                machine->creditDebt = 0;
                machine->creditTaken = false;
            }
            oss << "You Win: " << winAmount << " Eurodollar! (" << appliedRepayment
                << " repaid, net win: " << netWin << ")";
        }
        else {
            oss << "You Win: " << winAmount << " Eurodollar!";
        }
        resultMessage = oss.str();
        machine->balance += netWin;
        machine->messagePanelText = resultMessage;
    }
    else {
        resultMessage = "No Win!";
        machine->messagePanelText = resultMessage;
    }
}

void WinState::handleMouse(int button, int state, int x, int y) {
   
}

void WinState::update(float dt) {
    elapsedTime += dt;
    if (elapsedTime >= displayTime) {
        machine->stateMachine.changeState(std::make_unique<IdleState>(machine));
    }
}

void WinState::render() {
}
