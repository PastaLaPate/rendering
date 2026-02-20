#include "shapes/rectangle_shape.h"
#include "camera.h"
#include "scene.h"
#include "rendering/mat3.h"
#include "raylib.h"
#include <iostream>

RectangleShape::RectangleShape(Vector2 position, float width, float height, Color color)
    : Shape(position), width(width), height(height)
{
    this->color = color;
    setDraggingEnabled(true);
}

void RectangleShape::render(const Scene &scene)
{
    Mat3 cameraMatrix = scene.getCamera().getCameraMatrix();
    Vector2 p2 = {position.x + width, position.y};
    Vector2 p3 = {position.x + width, position.y + height};
    Vector2 p4 = {position.x, position.y + height};
    Vector2 transformedPosition = cameraMatrix.multiply(position);
    Vector2 transformedP2 = cameraMatrix.multiply(p2);
    Vector2 transformedP3 = cameraMatrix.multiply(p3);
    Vector2 transformedP4 = cameraMatrix.multiply(p4);
    DrawTriangle(transformedPosition, transformedP3, transformedP2, color);
    DrawTriangle(transformedPosition, transformedP4, transformedP3, color);
}

Rectangle RectangleShape::getBounds() const
{
    return {position.x, position.y, width, height};
}

bool RectangleShape::contains(Vector2 point) const
{
    return point.x >= position.x && point.x <= position.x + width &&
           point.y >= position.y && point.y <= position.y + height;
}

void RectangleShape::setDimensions(float w, float h)
{
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
