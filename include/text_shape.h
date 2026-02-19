#pragma once

#include "shape.h"
#include <string>

// Concrete Text shape implementation
class TextShape : public Shape {
public:
    TextShape(Vector2 position = {0, 0}, const std::string& text = "Text", int fontSize = 20, Color color = WHITE)
        : Shape(position), text(text), fontSize(fontSize) {
        this->color = color;
    }
    
    void render() override {
        DrawText(text.c_str(), position.x, position.y, fontSize, color);
    }
    
    Rectangle getBounds() const override {
        // Estimate bounds based on text length and font size
        float width = text.length() * (fontSize * 0.6f);
        float height = fontSize;
        return {position.x, position.y, width, height};
    }
    
    bool contains(Vector2 point) const override {
        auto bounds = getBounds();
        return point.x >= bounds.x && point.x <= bounds.x + bounds.width &&
               point.y >= bounds.y && point.y <= bounds.y + bounds.height;
    }
    
    void setText(const std::string& newText) {
        text = newText;
    }
    
    void setFontSize(int size) {
        fontSize = size;
    }
    
    std::string getText() const { return text; }
    int getFontSize() const { return fontSize; }
    
private:
    std::string text;
    int fontSize;
};
