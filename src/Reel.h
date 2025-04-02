#ifndef REEL_H
#define REEL_H

#include <string>
#include <vector>

// Класс Reel реализует один барабан слот-машины
class Reel {
public:
    Reel(float symbolHeight);
    void startSpin(float initialSpeed);
    void stopSpin();
    void update(float dt);
    void render(const struct Vec2& position);
    std::string getCenterSymbol() const;
    bool isSpinning() const;
private:
    std::vector<std::string> symbols; // Набор символов
    float offset;       // Текущее смещение для анимации
    float speed;        // Текущая скорость вращения
    bool spinning;      // Флаг вращения
    bool stopping;      // Флаг замедления
    float deceleration; // Коэффициент замедления (пикселей/сек^2)
    float symbolHeight; // Высота одного символа (для выравнивания)
};

#endif // REEL_H
