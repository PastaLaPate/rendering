#include "shapes/triangle_shape.h"
#include "camera.h"
#include "scene.h"
#include "rendering/mat3.h"
#include <algorithm>
#include <cmath>
#include "raylib.h"

TriangleShape::TriangleShape(Vector2 position, Vector2 point2, Vector2 point3, Color color)
    : Shape(position), p2(point2), p3(point3)
{
    this->color = color;
}

void TriangleShape::render(const Scene &scene)
{
    Mat3 cameraMatrix = scene.getCamera().getCameraMatrix();
    EnsureCCW(position, p2, p3);
    Vector2 transformedPosition = cameraMatrix.multiply(position);
    Vector2 transformedP2 = cameraMatrix.multiply(p2);
    Vector2 transformedP3 = cameraMatrix.multiply(p3);
    DrawTriangle(transformedPosition, transformedP3, transformedP2, color);
}

Rectangle TriangleShape::getBounds() const
{
    float minX = fmin(fmin(position.x, p2.x), p3.x);
    float maxX = fmax(fmax(position.x, p2.x), p3.x);
    float minY = fmin(fmin(position.y, p2.y), p3.y);
    float maxY = fmax(fmax(position.y, p2.y), p3.y);
    return {minX, minY, maxX - minX, maxY - minY};
}

bool TriangleShape::contains(Vector2 point) const
{
    auto sign = [](Vector2 p1, Vector2 p2, Vector2 p3)
    {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    };
    float d1 = sign(point, position, p2);
    float d2 = sign(point, p2, p3);
    float d3 = sign(point, p3, position);
    bool allNonNegative = (d1 >= 0) && (d2 >= 0) && (d3 >= 0);
    bool allNonPositive = (d1 <= 0) && (d2 <= 0) && (d3 <= 0);
    return allNonNegative || allNonPositive;
}

void TriangleShape::setVertices(Vector2 p1, Vector2 p2, Vector2 p3)
{
    position = p1;
    this->p2 = p2;
    this->p3 = p3;
}

void TriangleShape::setPosition(Vector2 newPosition)
{
    Vector2 offset = {newPosition.x - position.x, newPosition.y - position.y};
    position = newPosition;
    p2.x += offset.x;
    p2.y += offset.y;
    p3.x += offset.x;
    p3.y += offset.y;
}

void TriangleShape::EnsureCCW(Vector2 &a, Vector2 &b, Vector2 &c)
{
    float area = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    if (area < 0.0f)
        std::swap(b, c);
}

Vector2 TriangleShape::getVertex2() const { return p2; }
Vector2 TriangleShape::getVertex3() const { return p3; }

// Clickable interface
void TriangleShape::onMouseDown() {}
void TriangleShape::onMouseUp() {}
void TriangleShape::onClick() {}

// Draggable interface
void TriangleShape::onDrag(float x, float y) { setPosition({x, y}); }
