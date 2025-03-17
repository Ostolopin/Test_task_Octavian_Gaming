#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "Vec2.h" 


class Button {
public:
    Button();
    Button(const Vec2& position, const Vec2& size, const std::string& label);

    void render();
    bool isClicked(const Vec2& mousePos) const;

    void setPosition(const Vec2& pos) { position = pos; }
    Vec2 getPosition() const { return position; }
private:
    Vec2 position;
    Vec2 size;
    std::string label;
};

#endif // BUTTON_H
