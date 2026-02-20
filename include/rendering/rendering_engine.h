#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "raylib.h"
#include "shapes/shape.h"
#include "rendering/renderer.h"
#include "rendering/default_renderer.h"
#include "rendering/mat3.h"

// Rendering engine to manage and render shapes
class RenderingEngine
{
public:
    Mat3 cameraMatrix;
    Vector2 cameraPosition = {0, 0};
    float cameraRotation = 0.0f; // In radians
    Vector2 cameraScale = {1.0f, 1.0f};

    bool cameraMatrixDirty = true; // Flag to track if camera matrix needs recalculation

    RenderingEngine() : renderer(std::make_unique<DefaultRenderer>()) {}

    explicit RenderingEngine(std::unique_ptr<Renderer> customRenderer)
        : renderer(std::move(customRenderer)) {}

    // Add a shape to the rendering engine
    void addShape(Shape *shape)
    {
        if (shape != nullptr)
        {
            shapes.push_back(shape);
        }
    }

    // Remove a shape from the rendering engine
    void removeShape(Shape *shape)
    {
        auto it = std::find(shapes.begin(), shapes.end(), shape);
        if (it != shapes.end())
        {
            shapes.erase(it);
        }
    }

    // Clear all shapes
    void clear()
    {
        shapes.clear();
    }

    // Render all shapes
    void render()
    {
        // Only recalculate camera matrix if it changed
        if (cameraMatrixDirty)
        {
            Mat3 view = Mat3::translation(-cameraPosition.x, -cameraPosition.y);
            Mat3 rotation = Mat3::rotation(cameraRotation);
            Mat3 scale = Mat3::scale(cameraScale.x, cameraScale.y);
            cameraMatrix = scale * rotation * view;
            cameraMatrixDirty = false;
        }
        renderer->renderShapes(shapes, cameraMatrix);
    }

    // Get all shapes
    const std::vector<Shape *> &getShapes() const
    {
        return shapes;
    }

    Vector2 toWorldPosition(Vector2 screenPos) const
    {
        // Invert the camera transformations to convert screen position to world position
        Mat3 invCameraMatrix = Mat3::translation(cameraPosition.x, cameraPosition.y) *
                               Mat3::rotation(-cameraRotation) *
                               Mat3::scale(1.0f / cameraScale.x, 1.0f / cameraScale.y);
        return invCameraMatrix.multiply(screenPos);
    }

    // Find shape at position
    Shape *findShapeAt(Vector2 position)
    {
        // Search in reverse order (last added = topmost)
        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it)
        {
            if ((*it)->contains(position))
            {
                return *it;
            }
        }
        return nullptr;
    }

    // Set custom renderer
    void setRenderer(std::unique_ptr<Renderer> customRenderer)
    {
        renderer = std::move(customRenderer);
    }

    // Get renderer
    Renderer *getRenderer() const
    {
        return renderer.get();
    }

    void setCameraPosition(const Vector2 &position)
    {
        cameraPosition = position;
        cameraMatrixDirty = true;
    }

    void setCameraRotation(const float &rotation)
    {
        cameraRotation = rotation;
        cameraMatrixDirty = true;
    }

    void setCameraScale(const Vector2 &scale)
    {
        cameraScale = scale;
        cameraMatrixDirty = true;
    }

    // Get number of shapes
    size_t getShapeCount() const
    {
        return shapes.size();
    }

private:
    std::vector<Shape *> shapes;
    std::unique_ptr<Renderer> renderer;
};
