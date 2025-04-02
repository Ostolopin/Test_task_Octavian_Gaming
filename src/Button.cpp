#include "Button.h"
#include <GL/glut.h>

Button::Button() : position({ 0,0 }), size({ 0,0 }), label("") {}

Button::Button(const Vec2& pos, const Vec2& s, const std::string& lbl)
    : position(pos), size(s), label(lbl) {}

void Button::render() {
    glColor3f(0.392f, 0.392f, 0.784f);
    glBegin(GL_QUADS);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + size.x, position.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x, position.y + size.y);
    glEnd();

    glColor3f(0, 0, 0);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + size.x, position.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x, position.y + size.y);
    glEnd();

    float centerX = position.x + size.x / 2;
    float centerY = position.y + size.y / 2;
    glColor3f(1, 1, 1);

    glRasterPos2f(centerX - (label.size() * 4), centerY - 5);
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

bool Button::isClicked(const Vec2& mousePos) const {
    return (mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
        mousePos.y >= position.y && mousePos.y <= position.y + size.y);
}
