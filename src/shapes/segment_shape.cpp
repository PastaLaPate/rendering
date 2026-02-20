#include "shapes/segment_shape.h"
#include "camera.h"
#include "scene.h"
#include "rendering/mat3.h"
#include "raylib.h"

SegmentShape::SegmentShape(Vector2 position, ShapeID p1, ShapeID p2, Color color)
    : Shape(position), p1(p1), p2(p2)
{
    this->color = color;
    setDraggingEnabled(false);
}

void SegmentShape::render(const Scene &scene)
{
    Mat3 cameraMatrix = scene.getCamera().getCameraMatrix();
    Vector2 p1V = scene.getShapeByID(p1)->getPosition();
    Vector2 p2V = scene.getShapeByID(p2)->getPosition();
    Vector2 transformedP1 = cameraMatrix.multiply(p1V);
    Vector2 transformedP2 = cameraMatrix.multiply(p2V);
    DrawLine(transformedP1.x, transformedP1.y, transformedP2.x, transformedP2.y, color);
}

Rectangle SegmentShape::getBounds() const
{
    return {0, 0, 0, 0};
}

bool SegmentShape::contains(Vector2 point) const
{
    return false;
}


// Clickable interface
void SegmentShape::onMouseDown() {}
void SegmentShape::onMouseUp() {}
void SegmentShape::onClick() {}

// Draggable interface
void SegmentShape::onDrag(float x, float y) {}
