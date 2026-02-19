#pragma once

#include <vector>
#include "raylib.h"
#include "shapes/shape.h"

// Abstract base class for rendering strategies
class Renderer {
public:
    virtual ~Renderer() = default;
    
    // Render a single shape
    virtual void renderShape(Shape* shape) = 0;
    virtual void renderShape(Shape* shape, Vector2* cameraPosition) = 0;
    
    // Render multiple shapes
    virtual void renderShapes(const std::vector<Shape*>& shapes, Vector2* cameraPosition = new Vector2{0, 0}) {
        for (Shape* shape : shapes) {
            renderShape(shape, cameraPosition);
        }
    }
};
