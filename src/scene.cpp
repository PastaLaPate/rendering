#include "scene.h"
#include <algorithm>

Scene::Scene() : renderingEngine() {}

Scene::~Scene() {
    clearShapes();
}

void Scene::addShape(std::unique_ptr<Shape> shape) {
    if (shape) {
        shapes.push_back(std::move(shape));
    }
}

void Scene::removeShape(Shape* shape) {
    auto it = std::remove_if(shapes.begin(), shapes.end(), [shape](const std::unique_ptr<Shape>& ptr) {
        return ptr.get() == shape;
    });
    shapes.erase(it, shapes.end());
}

void Scene::clearShapes() {
    shapes.clear();
}

void Scene::render() {
    renderingEngine.renderShapes(*this);
}

Shape* Scene::findShapeAt(Vector2 worldPos) {
    // Search in reverse order (topmost first)
    for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
        if ((*it)->contains(worldPos)) {
            return it->get();
        }
    }
    return nullptr;
}

size_t Scene::getShapeCount() const {
    return shapes.size();
}

Camera2& Scene::getCamera() {
    return renderingEngine.camera;
}

const Camera2& Scene::getCamera() const {
    return renderingEngine.camera;
}

RenderingEngine& Scene::getRenderingEngine() {
    return renderingEngine;
}

const RenderingEngine& Scene::getRenderingEngine() const {
    return renderingEngine;
}

Vector2 Scene::toWorldPosition(Vector2 screenPos) const {
    return renderingEngine.toWorldPosition(screenPos);
}

const std::vector<std::unique_ptr<Shape>>& Scene::getShapes() const {
    return shapes;
}
