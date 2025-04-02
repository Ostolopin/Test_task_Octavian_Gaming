#include <GL/glut.h>
#include "SlotMachine.h"
#include <chrono>

// Глобальный указатель на слот-машину
SlotMachine* slotMachine = nullptr;
std::chrono::steady_clock::time_point previousTime;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (slotMachine) {
        slotMachine->render();
    }
    glutSwapBuffers();
}

void idle() {
    // Расчёт dt (в секундах)
    auto currentTime = std::chrono::steady_clock::now();
    float dt = std::chrono::duration<float>(currentTime - previousTime).count();
    previousTime = currentTime;

    if (slotMachine) {
        slotMachine->update(dt);
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int newY = windowHeight - y;
    if (slotMachine) {
        slotMachine->handleMouse(button, state, x, newY);
    }
}

void init() {
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1, 1, 1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Slot Machine");
    glutFullScreen(); // переключаем в полноэкранный режим

    init();

    slotMachine = new SlotMachine();
    previousTime = std::chrono::steady_clock::now();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);

    glutMainLoop();

    delete slotMachine;
    return 0;
}
