#pragma once

#include <vector>
#include "raylib.h"
#include "shapes/shape.h"
#include "rendering/mat3.h"

// Abstract base class for rendering strategies
class Renderer
{
public:
    virtual ~Renderer() = default;

    // Render a single shape
    virtual void renderShape(Shape *shape) = 0;
    virtual void renderShape(Shape *shape, const Mat3 &cameraMatrix) = 0;

    // Render multiple shapes
    virtual void renderShapes(const std::vector<Shape *> &shapes, const Mat3 &cameraMatrix)
    {
        for (Shape *shape : shapes)
        {
            renderShape(shape, cameraMatrix);
        }
    }
};
