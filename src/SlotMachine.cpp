#include "SlotMachine.h"
#include "States/IdleState.h"
#include <GL/glut.h>
#include <string>
#include <cstdlib>
#include <sstream> 
#include "TextUtils.h"

SlotMachine::SlotMachine()
{
    // Получаем размеры окна (в полноэкранном режиме)
    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Задаем позиции для барабанов по центру экрана
    reelsStartPos = { static_cast<float>(screenWidth) / 2.f - 100.f,
                      static_cast<float>(screenHeight) / 2.f - 50.f };
    reelSpacing = 70.f;
    reelSymbolHeight = 50.f;

    // Локальные переменные для отступов и размеров кнопок
    const int margin = 20;
    const int buttonWidth = 150;
    const int buttonHeight = 50;

    // Располагаем кнопки в левом верхнем углу (координаты преобразованы в float)
    startButton = Button(
        Vec2{ static_cast<float>(margin),
              static_cast<float>(screenHeight) - static_cast<float>(margin) - static_cast<float>(buttonHeight) },
        Vec2{ static_cast<float>(buttonWidth), static_cast<float>(buttonHeight) },
        "Start"
    );

    stopButton = Button(
        Vec2{ static_cast<float>(margin),
              static_cast<float>(screenHeight) - static_cast<float>(margin) - 2.f * static_cast<float>(buttonHeight) - 10.f },
        Vec2{ static_cast<float>(buttonWidth), static_cast<float>(buttonHeight) },
        "Stop"
    );

    creditButton = Button(
        Vec2{ static_cast<float>(margin),
              static_cast<float>(screenHeight) - static_cast<float>(margin) - 3.f * static_cast<float>(buttonHeight) - 20.f },
        Vec2{ static_cast<float>(buttonWidth), static_cast<float>(buttonHeight) },
        "Credit"
    );

    exitButton = Button(
        Vec2{ static_cast<float>(margin),
              static_cast<float>(screenHeight) - static_cast<float>(margin) - 4.f * static_cast<float>(buttonHeight) - 30.f },
        Vec2{ static_cast<float>(buttonWidth), static_cast<float>(buttonHeight) },
        "Exit"
    );

    // Начальный баланс
    balance = 5;
    creditTaken = false;
    creditDebt = 0;

    // Создаем барабаны
    for (int i = 0; i < 2; ++i) {
        reels.push_back(Reel(reelSymbolHeight));
    }

    const float reelWidth = 50.f;
    float totalWidth = (reels.size() > 0) ? reelWidth + (reels.size() - 1) * reelSpacing : 0.f;
    reelsStartPos.x = (screenWidth - totalWidth) / 2.0f;
    reelsStartPos.y = static_cast<float>(screenHeight) / 2.f - 50.f;

    // Начальное состояние – ожидание действия игрока
    stateMachine.changeState(std::make_unique<IdleState>(this));
}

void SlotMachine::update(float dt) {
    stateMachine.update(dt);
    // Обновляем барабаны (анимация вращения)
    for (auto& reel : reels) {
        reel.update(dt);
    }
}

void SlotMachine::render() {
    // Отрисовка барабанов
    for (size_t i = 0; i < reels.size(); ++i) {
        Vec2 pos = { reelsStartPos.x + i * reelSpacing, reelsStartPos.y };
        reels[i].render(pos);
    }

    // Отрисовка кнопок Start и Stop
    startButton.render();
    stopButton.render();

    stateMachine.render();

    exitButton.render();

    float panelX = 220.f;
    float panelY = static_cast<float>(screenHeight) - 20.f; // верхняя граница панели с отступом
    float panelWidth = 300.f;  // ширина панели сообщений
    float panelHeight = 100.f; // высота панели сообщений
    float padding = 10.f;      // внутренний отступ

    // Отрисовка фона панели
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(panelX, panelY - panelHeight);
    glVertex2f(panelX + panelWidth, panelY - panelHeight);
    glVertex2f(panelX + panelWidth, panelY);
    glVertex2f(panelX, panelY);
    glEnd();

    // Отрисовка рамки панели
    glColor3f(0, 0, 0);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(panelX, panelY - panelHeight);
    glVertex2f(panelX + panelWidth, panelY - panelHeight);
    glVertex2f(panelX + panelWidth, panelY);
    glVertex2f(panelX, panelY);
    glEnd();
    glPopAttrib();


    float textX = panelX + padding;
    float textY = panelY - padding - 18.f;
    std::string text = messagePanelText.empty() ? "No messages" : messagePanelText;


    glColor3f(0, 0, 0);
    drawWrappedText(textX, textY, panelWidth - 2 * padding, text);

    bool isIdle = false;
    State* curState = stateMachine.getCurrentState();
    if (curState != nullptr) {
        if (dynamic_cast<IdleState*>(curState) != nullptr)
            isIdle = true;
    }

    if (!(isIdle && (balance < 5 && !creditTaken))) {
        std::string infoText = "Balance: " + std::to_string(balance) + " Eurodollar";
        if (creditTaken) {
            infoText += " | Debt: " + std::to_string(creditDebt) + " Eurodollar";
        }

        // Позиция текста 
        float infoX = 25.f;
        float infoY = static_cast<float>(screenHeight) - 20.f - 2.f * 50.f - 50.f;

        // Отступ вокруг текста
        float padding = 5.f;

        // Вычисляем ширину текста с помощью GLUT
        int textWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(infoText.c_str()));
        float textHeight = 18.f;

        // Сохраняем текущий цвет
        glPushAttrib(GL_CURRENT_BIT);

        // Отрисовываем фон
        glColor3f(0.9f, 0.9f, 0.9f);
        glBegin(GL_QUADS);
        glVertex2f(infoX - padding, infoY - padding);
        glVertex2f(infoX + textWidth + padding, infoY - padding);
        glVertex2f(infoX + textWidth + padding, infoY + textHeight + padding);
        glVertex2f(infoX - padding, infoY + textHeight + padding);
        glEnd();

        // Отрисовываем рамку вокруг прямоугольника
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(infoX - padding, infoY - padding);
        glVertex2f(infoX + textWidth + padding, infoY - padding);
        glVertex2f(infoX + textWidth + padding, infoY + textHeight + padding);
        glVertex2f(infoX - padding, infoY + textHeight + padding);
        glEnd();

        // Восстанавливаем предыдущий цвет
        glPopAttrib();

        // Отрисовываем текст поверх фона
        glColor3f(0, 0, 0);
        glRasterPos2f(infoX, infoY);
        for (char c : infoText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }
}

void SlotMachine::handleMouse(int button, int state, int x, int y) {
    // Преобразуем координаты в Vec2
    Vec2 mousePos = { static_cast<float>(x), static_cast<float>(y) };
    // Если нажата кнопка Exit, завершаем программу
    if (exitButton.isClicked(mousePos)) {
        exit(0);
    }
    stateMachine.handleMouse(button, state, x, y);
}
