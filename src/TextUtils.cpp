#include "TextUtils.h"
#include <sstream>
#include <GL/glut.h>

// ������� ��� ��������� ������ ������ � ��������
int getTextWidth(const std::string& text) {
    return glutBitmapLength(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(text.c_str()));
}

// ������� �������� ������ �� ������ � ������ ������������ ������
std::vector<std::string> wrapText(const std::string& text, float maxWidth) {
    std::istringstream iss(text);
    std::string word;
    std::vector<std::string> lines;
    std::string currentLine;

    while (iss >> word) {
        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
        if (getTextWidth(testLine) > maxWidth) {
            if (!currentLine.empty()) {
                lines.push_back(currentLine);
                currentLine = word;
            }
            else {
                lines.push_back(word);
                currentLine = "";
            }
        }
        else {
            currentLine = testLine;
        }
    }
    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }
    return lines;
}

// ������� ��� ��������� ��������� ������, ������� � ��������� (x, y)
void drawWrappedText(float x, float y, float maxWidth, const std::string& text) {
    std::vector<std::string> lines = wrapText(text, maxWidth);
    float lineHeight = 18.f; 
    for (const auto& line : lines) {
        glRasterPos2f(x, y);
        for (char c : line) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
        y -= lineHeight;
    }
}
