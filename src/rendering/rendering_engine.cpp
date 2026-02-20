#include "rendering/rendering_engine.h"
#include "scene.h"
#include "rendering/default_renderer.h"

RenderingEngine::RenderingEngine() : renderer(std::make_unique<DefaultRenderer>()) {}

RenderingEngine::RenderingEngine(std::unique_ptr<Renderer> customRenderer)
    : renderer(std::move(customRenderer)) {}

void RenderingEngine::renderShapes(const Scene &scene) {
    if (renderer)
        renderer->renderShapes(scene);
}

void RenderingEngine::setRenderer(std::unique_ptr<Renderer> customRenderer) {
    renderer = std::move(customRenderer);
}

Renderer *RenderingEngine::getRenderer() const {
    return renderer.get();
}

Vector2 RenderingEngine::toWorldPosition(Vector2 screenPos) const {
    return camera.toWorldPosition(screenPos);
}
