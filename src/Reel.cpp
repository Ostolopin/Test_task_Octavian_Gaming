#include "Reel.h"
#include <cmath>
#include <GL/glut.h>
#include "Vec2.h" 

Reel::Reel(float symHeight)
    : symbolHeight(symHeight), offset(0.f), speed(0.f),
    spinning(false), stopping(false), deceleration(200.f)
{
    // Инициализация набора символов
    symbols = { "A", "B", "C", "D", "E" };
}

void Reel::startSpin(float initialSpeed) {
    spinning = true;
    stopping = false;
    speed = initialSpeed;
}

void Reel::stopSpin() {
    stopping = true;
}

void Reel::update(float dt) {
    if (spinning) {
        if (stopping) {
            speed -= deceleration * dt;
            if (speed <= 0.f) {
                speed = 0.f;
                spinning = false;
                stopping = false;
                // Выравнивание смещения до ближайшей позиции (кратной symbolHeight)
                float remainder = std::fmod(offset, symbolHeight);
                if (remainder < symbolHeight / 2)
                    offset -= remainder;
                else
                    offset += (symbolHeight - remainder);
            }
        }
        offset += speed * dt;
        float totalHeight = symbolHeight * symbols.size();
        if (offset >= totalHeight) {
            offset = std::fmod(offset, totalHeight);
        }
    }
}

void Reel::render(const Vec2& position) {
    // Отрисовка фона барабана
    glColor3f(0.863f, 0.863f, 0.863f); // цвет (220,220,220)
    glBegin(GL_QUADS);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + 50, position.y);
    glVertex2f(position.x + 50, position.y + symbolHeight);
    glVertex2f(position.x, position.y + symbolHeight);
    glEnd();

    // Рисуем контур барабана
    glColor3f(0, 0, 0);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + 50, position.y);
    glVertex2f(position.x + 50, position.y + symbolHeight);
    glVertex2f(position.x, position.y + symbolHeight);
    glEnd();

    // Отрисовка символов
    int totalSymbols = symbols.size();
    int startIndex = static_cast<int>(offset / symbolHeight);
    float yOffset = -(std::fmod(offset, symbolHeight));

    for (int i = 0; i < totalSymbols + 1; ++i) {
        int symbolIndex = (startIndex + i) % totalSymbols;
        std::string sym = symbols[symbolIndex];

        glColor3f(0, 0, 0);
        float textX = position.x + 25 - (sym.size() * 4); // приблизительное центрирование
        float textY = position.y + symbolHeight / 2 + yOffset + i * symbolHeight - 5;
        glRasterPos2f(textX, textY);
        for (char c : sym) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }
}

std::string Reel::getCenterSymbol() const {
    int index = static_cast<int>((offset + symbolHeight / 2) / symbolHeight) % symbols.size();
    return symbols[index];
}

bool Reel::isSpinning() const {
    return spinning;
}
