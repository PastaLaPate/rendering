#pragma once

#include "raylib.h"
#include "camera.h"
#include "interfaces/renderable.h"
#include "interfaces/collidable.h"

class Scene;

// Abstract base class for all shapes
class Shape : public Renderable, public virtual Collidable
{
public:
    Shape(Vector2 position);

    virtual ~Shape() = default;

    // Core rendering method - must be implemented by subclasses
    void render(const Scene &scene) override = 0;

    // Get the bounds of the shape
    virtual Rectangle getBounds() const = 0;

    // Check if a point is inside the shape (for Collidable)
    virtual bool contains(Vector2 point) const = 0;
    // Collidable interface
    bool Collides(Vector2 p) const override;

    // Setters and getters
    virtual void setPosition(Vector2 newPosition) { position = newPosition; }
    Vector2 getPosition() const { return position; }

    void setColor(Color newColor) { color = newColor; }
    Color getColor() const { return color; }

protected:
    Vector2 position;
    Color color = WHITE;
};
