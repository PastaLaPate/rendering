#pragma once

#include <vector>
#include "shape.h"

// Abstract base class for rendering strategies
class Renderer {
public:
    virtual ~Renderer() = default;
    
    // Render a single shape
    virtual void renderShape(Shape* shape) = 0;
    
    // Render multiple shapes
    virtual void renderShapes(const std::vector<Shape*>& shapes) {
        for (Shape* shape : shapes) {
            renderShape(shape);
        }
    }
};
