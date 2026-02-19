#pragma once

#include "shape.h"

// Concrete Rectangle shape implementation
class RectangleShape : public Shape {
public:
    RectangleShape(Vector2 position = {0, 0}, float width = 100, float height = 100, Color color = WHITE)
        : Shape(position), width(width), height(height) {
        this->color = color;
    }
    
    void render() override {
        DrawRectangle(position.x, position.y, width, height, color);
    }
    
    Rectangle getBounds() const override {
        return {position.x, position.y, width, height};
    }
    
    bool contains(Vector2 point) const override {
        return point.x >= position.x && point.x <= position.x + width &&
               point.y >= position.y && point.y <= position.y + height;
    }
    
    void setDimensions(float w, float h) {
        width = w;
        height = h;
    }
    
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    
private:
    float width;
    float height;
};
