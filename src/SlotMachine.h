#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H

#include <vector>
#include <string>
#include "Button.h"
#include "Reel.h"
#include "StateMachine.h"
#include "Vec2.h"

// Класс SlotMachine объединяет графические элементы (барабаны и кнопки)
// и содержит машину состояний
class SlotMachine {
public:
    SlotMachine();
    void update(float dt);
    void render();
    void handleMouse(int button, int state, int x, int y);

    // Эти публичные поля используются состояниями
    std::vector<Reel> reels;
    Button startButton;
    Button stopButton;
    Button creditButton;
    Button exitButton;
    StateMachine stateMachine;

    int balance;

    // Кредитная система
    bool creditTaken;   // кредит взят или нет
    int creditDebt;     // сумма долга

    // Параметры позиционирования
    Vec2 reelsStartPos;
    float reelSpacing;
    float reelSymbolHeight;

    int screenWidth;
    int screenHeight;

    std::string messagePanelText;
};

#endif // SLOTMACHINE_H
