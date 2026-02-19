#pragma once

#include "raylib.h"
#include "interfaces/renderable.h"

// Abstract base class for all shapes
class Shape : public Renderable {
public:
    Shape(Vector2 position = {0, 0}) : position(position) {}
    
    virtual ~Shape() = default;
    
    // Core rendering method - must be implemented by subclasses
    void render() override = 0;
    
    // Get the bounds of the shape
    virtual Rectangle getBounds() const = 0;
    
    // Check if a point is inside the shape
    virtual bool contains(Vector2 point) const = 0;
    
    // Setters and getters
    virtual void setPosition(Vector2 newPosition) { position = newPosition; }
    Vector2 getPosition() const { return position; }
    
    void setColor(Color newColor) { color = newColor; }
    Color getColor() const { return color; }
    
protected:
    Vector2 position;
    Color color = WHITE;
};
