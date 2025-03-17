#ifndef STATE_H
#define STATE_H

// Абстрактный класс состояния с общим интерфейсом
class State {
public:
    virtual void handleMouse(int button, int state, int x, int y) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual ~State() {}
};

#endif // STATE_H
