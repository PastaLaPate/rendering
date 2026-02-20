#pragma once

#include <vector>
#include "shapes/shape.h"
#include "camera.h"


class Scene;

// Abstract base class for rendering strategies
class Renderer
{
public:
    virtual ~Renderer() = default;

    // Render a single shape
    virtual void renderShape(Shape *shape, const Scene &scene) = 0;

    // Render all shapes in the scene
    virtual void renderShapes(const Scene &scene) = 0;
};
