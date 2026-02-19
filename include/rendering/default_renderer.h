#pragma once

#include "raylib.h"
#include "rendering/renderer.h"

// Default renderer implementation
class DefaultRenderer : public Renderer {
public:
    void renderShape(Shape* shape) override {
        if (shape != nullptr) {
            shape->render();
        }
    }

    void renderShape(Shape* shape, Vector2* cameraPosition) override {
        if (shape != nullptr) {
            Vector2 originalPos = shape->getPosition();
            shape->setPosition({originalPos.x - cameraPosition->x, originalPos.y - cameraPosition->y});
            shape->render();
            shape->setPosition(originalPos);
        }
    }
    
    void renderShapes(const std::vector<Shape*>& shapes, Vector2* cameraPosition = new Vector2{0, 0}) override {
        for (Shape* shape : shapes) {
            renderShape(shape, cameraPosition);
        }
    }
};
