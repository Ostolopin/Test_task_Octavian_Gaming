#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <string>
#include <vector>

// Функция для измерения ширины строки в пикселях с использованием GLUT_BITMAP_HELVETICA_18
int getTextWidth(const std::string& text);

// Функция разбивки текста на строки с учетом максимальной ширины (maxWidth)
std::vector<std::string> wrapText(const std::string& text, float maxWidth);

// Функция для отрисовки обёрнутого текста, начиная с координат (x, y) с заданным максимальным разрешением по ширине.
void drawWrappedText(float x, float y, float maxWidth, const std::string& text);

#endif // TEXT_UTILS_H
