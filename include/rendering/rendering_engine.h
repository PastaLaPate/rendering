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
#include "camera.h"

// Forward declaration
class Scene;

// Rendering engine to manage rendering
class RenderingEngine
{
public:
    Camera2 camera;

    RenderingEngine();
    explicit RenderingEngine(std::unique_ptr<Renderer> customRenderer);

    // Render all shapes in the scene
    void renderShapes(const Scene &scene);

    // Set custom renderer
    void setRenderer(std::unique_ptr<Renderer> customRenderer);

    // Get renderer
    Renderer *getRenderer() const;

    Vector2 toWorldPosition(Vector2 screenPos) const;

private:
    std::unique_ptr<Renderer> renderer;
};
