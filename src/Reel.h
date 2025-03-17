#ifndef REEL_H
#define REEL_H

#include <string>
#include <vector>

// ����� Reel ��������� ���� ������� ����-������
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
    std::vector<std::string> symbols; // ����� ��������
    float offset;       // ������� �������� ��� ��������
    float speed;        // ������� �������� ��������
    bool spinning;      // ���� ��������
    bool stopping;      // ���� ����������
    float deceleration; // ����������� ���������� (��������/���^2)
    float symbolHeight; // ������ ������ ������� (��� ������������)
};

#endif // REEL_H
