#pragma once

#include "shapes/shape.h"
#include "interfaces/draggable.h"
#include "camera.h"

// Concrete Rectangle shape implementation
class RectangleShape : public Shape, public Draggable
{
public:
    RectangleShape(Vector2 position = {0, 0}, float width = 100, float height = 100, Color color = WHITE);
    void render(const Camera2 &camera) override;
    Rectangle getBounds() const override;
    bool contains(Vector2 point) const override;
    void setDimensions(float w, float h);
    float getWidth() const;
    float getHeight() const;

    // Clickable interface
    void onMouseDown() override;
    void onMouseUp() override;
    void onClick() override;

    // Draggable interface
    void onDrag(float x, float y) override;

private:
    float width;
    float height;
};
