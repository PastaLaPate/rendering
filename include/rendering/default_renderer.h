#pragma once

#include "raylib.h"
#include "rendering/renderer.h"
#include "camera.h"


class Scene;

// Default renderer implementation
class DefaultRenderer : public Renderer
{
public:
    void renderShape(Shape *shape, const Scene &scene) override;
    void renderShapes(const Scene &scene) override;
};
