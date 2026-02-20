#include "scene.h"
#include <algorithm>

Scene::Scene() : renderingEngine(), freeIndices(), nextID(1) {}

Scene::~Scene() {
    clearShapes();
}

ShapeID Scene::addShape(std::unique_ptr<Shape> shape) {
    if (shape) {        
        ShapeID id = nextID++;
        size_t idx;

        if (!freeIndices.empty()) {
            idx = freeIndices.back();
            freeIndices.pop_back();
            shapes[idx] = {id, std::move(shape), 0};
        } else {
            idx = shapes.size();
            shapes.push_back({id, std::move(shape), 0});
        }

        return id;
    }
}

Shape* Scene::getShapeByID(ShapeID id) const {
    for (auto& entry : shapes) {
        if (entry.id == id && entry.shape)
            return entry.shape.get();
    }
    return nullptr;
}

void Scene::removeShape(ShapeID id) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        if (shapes[i].id == id) {
            shapes[i].shape.reset();
            freeIndices.push_back(i);
            shapes[i].generation++; // invalidate old references
            break;
        }
    }
}

void Scene::clearShapes() {
    shapes.clear();
    freeIndices.clear();
    nextID = 1;
}

void Scene::render() {
    renderingEngine.renderShapes(*this);
}

Shape* Scene::findShapeAt(Vector2 worldPos) {
    // Search in reverse order (topmost first)
    for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
        if (it->shape && it->shape->contains(worldPos)) {
            return it->shape.get();
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

const std::vector<ShapeEntry>& Scene::getShapes() const {
    return shapes;
}
