#pragma once

#include "scene.h"
#include "shapes/shape.h"
#include "interfaces/draggable.h"

// Concrete Rectangle shape implementation
class SegmentShape : public Shape, public Draggable
{
public:
    SegmentShape(Vector2 position = {0, 0}, ShapeID p1 = 0, ShapeID p2 = 0, Color color = WHITE);
    void render(const Scene &scene) override;
    Rectangle getBounds() const override;
    bool contains(Vector2 point) const override;
    void setDimensions(float w, float h);

    // Clickable interface
    void onMouseDown() override;
    void onMouseUp() override;
    void onClick() override;

    // Draggable interface
    void onDrag(float x, float y) override;

private:
    ShapeID p1;
    ShapeID p2;
};
