#pragma once

#include "renderer.h"
#include <iostream>

// Default renderer implementation
class DefaultRenderer : public Renderer {
public:
    void renderShape(Shape* shape) override {
        if (shape != nullptr) {
            shape->render();
        }
    }
    
    void renderShapes(const std::vector<Shape*>& shapes) override {
        Renderer::renderShapes(shapes);
    }
};
