#include "shapes/rectangle_shape.h"
#include "raylib.h"

RectangleShape::RectangleShape(Vector2 position, float width, float height, Color color)
    : Shape(position), width(width), height(height) {
    this->color = color;
}

void RectangleShape::render() {
    DrawRectangle(position.x, position.y, width, height, color);
}

Rectangle RectangleShape::getBounds() const {
    return {position.x, position.y, width, height};
}

bool RectangleShape::contains(Vector2 point) const {
    return point.x >= position.x && point.x <= position.x + width &&
           point.y >= position.y && point.y <= position.y + height;
}

void RectangleShape::setDimensions(float w, float h) {
    width = w;
    height = h;
}

float RectangleShape::getWidth() const { return width; }
float RectangleShape::getHeight() const { return height; }

// Clickable interface
void RectangleShape::onMouseDown() {}
void RectangleShape::onMouseUp() {}
void RectangleShape::onClick() {}

// Draggable interface
void RectangleShape::onDrag(float x, float y) { setPosition({x, y}); }
