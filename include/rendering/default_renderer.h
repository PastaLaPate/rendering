#pragma once

#include "raylib.h"
#include "rendering/renderer.h"

// Default renderer implementation
class DefaultRenderer : public Renderer
{
public:
    void renderShape(Shape *shape) override
    {
        if (shape != nullptr)
        {
            shape->render(Mat3());
        }
    }

    void renderShape(Shape *shape, const Mat3 &cameraMatrix) override
    {
        if (shape != nullptr)
        {
            shape->render(cameraMatrix);
        }
    }

    void renderShapes(const std::vector<Shape *> &shapes, const Mat3 &cameraMatrix) override
    {
        for (Shape *shape : shapes)
        {
            renderShape(shape, cameraMatrix);
        }
    }
};
