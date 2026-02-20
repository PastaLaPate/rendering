#include "rendering/default_renderer.h"
#include "scene.h"

void DefaultRenderer::renderShape(Shape *shape, const Scene &scene)
{
    if (shape)
        shape->render(scene);
}

void DefaultRenderer::renderShapes(const Scene &scene)
{
    for (const auto &shapePtr : scene.getShapes())
    {
        renderShape(shapePtr.shape.get(), scene);
    }
}
