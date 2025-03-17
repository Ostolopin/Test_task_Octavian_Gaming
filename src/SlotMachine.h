#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H

#include <vector>
#include <string>
#include "Button.h"
#include "Reel.h"
#include "StateMachine.h"
#include "Vec2.h"

// ����� SlotMachine ���������� ����������� �������� (�������� � ������)
// � �������� ������ ���������
class SlotMachine {
public:
    SlotMachine();
    void update(float dt);
    void render();
    void handleMouse(int button, int state, int x, int y);

    // ��� ��������� ���� ������������ �����������
    std::vector<Reel> reels;
    Button startButton;
    Button stopButton;
    Button creditButton;
    Button exitButton;
    StateMachine stateMachine;

    int balance;

    // ��������� �������
    bool creditTaken;   // ������ ���� ��� ���
    int creditDebt;     // ����� �����

    // ��������� ����������������
    Vec2 reelsStartPos;
    float reelSpacing;
    float reelSymbolHeight;

    int screenWidth;
    int screenHeight;

    std::string messagePanelText;
};

#endif // SLOTMACHINE_H
