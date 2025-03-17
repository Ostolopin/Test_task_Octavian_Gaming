#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <string>
#include <vector>

// ������� ��� ��������� ������ ������ � �������� � �������������� GLUT_BITMAP_HELVETICA_18
int getTextWidth(const std::string& text);

// ������� �������� ������ �� ������ � ������ ������������ ������ (maxWidth)
std::vector<std::string> wrapText(const std::string& text, float maxWidth);

// ������� ��� ��������� ��������� ������, ������� � ��������� (x, y) � �������� ������������ ����������� �� ������.
void drawWrappedText(float x, float y, float maxWidth, const std::string& text);

#endif // TEXT_UTILS_H
