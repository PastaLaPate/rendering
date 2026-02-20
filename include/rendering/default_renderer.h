#pragma once

#include "rendering/renderer.h"


class Scene;

// Default renderer implementation
class DefaultRenderer : public Renderer
{
public:
    void renderShape(Shape *shape, const Scene &scene) override;
    void renderShapes(const Scene &scene) override;
};
