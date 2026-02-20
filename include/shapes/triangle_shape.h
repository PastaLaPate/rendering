#pragma once

#include <cmath>
#include "camera.h"
#include "shapes/shape.h"
#include "interfaces/draggable.h"
#include "camera.h"

// Concrete Triangle shape implementation
class TriangleShape : public Shape, public Draggable
{
public:
    TriangleShape(Vector2 position = {0, 0}, Vector2 point2 = {50, 100}, Vector2 point3 = {100, 0}, Color color = WHITE);
    void render(const Scene &scene) override;
    Rectangle getBounds() const override;
    bool contains(Vector2 point) const override;
    void setVertices(Vector2 p1, Vector2 p2, Vector2 p3);
    void setPosition(Vector2 newPosition) override;
    static void EnsureCCW(Vector2 &a, Vector2 &b, Vector2 &c);
    Vector2 getVertex2() const;
    Vector2 getVertex3() const;

    // Clickable interface
    void onMouseDown() override;
    void onMouseUp() override;
    void onClick() override;

    // Draggable interface
    void onDrag(float x, float y) override;

private:
    Vector2 p2;
    Vector2 p3;
};
