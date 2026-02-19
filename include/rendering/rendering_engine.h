#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "raylib.h"
#include "shapes/shape.h"
#include "rendering/renderer.h"
#include "rendering/default_renderer.h"

// Rendering engine to manage and render shapes
class RenderingEngine {
public:
    RenderingEngine() : renderer(std::make_unique<DefaultRenderer>()) {}
    
    explicit RenderingEngine(std::unique_ptr<Renderer> customRenderer)
        : renderer(std::move(customRenderer)) {}
    
    // Add a shape to the rendering engine
    void addShape(Shape* shape) {
        if (shape != nullptr) {
            shapes.push_back(shape);
        }
    }
    
    // Remove a shape from the rendering engine
    void removeShape(Shape* shape) {
        auto it = std::find(shapes.begin(), shapes.end(), shape);
        if (it != shapes.end()) {
            shapes.erase(it);
        }
    }
    
    // Clear all shapes
    void clear() {
        shapes.clear();
    }
    
    // Render all shapes
    void render() {
        renderer->renderShapes(shapes);
    }

    void render(Vector2* cameraPosition) {
        renderer->renderShapes(shapes, cameraPosition);
    }
    
    // Get all shapes
    const std::vector<Shape*>& getShapes() const {
        return shapes;
    }
    
    // Find shape at position
    Shape* findShapeAt(Vector2 position) {
        // Search in reverse order (last added = topmost)
        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
            if ((*it)->contains(position)) {
                return *it;
            }
        }
        return nullptr;
    }
    
    // Set custom renderer
    void setRenderer(std::unique_ptr<Renderer> customRenderer) {
        renderer = std::move(customRenderer);
    }
    
    // Get renderer
    Renderer* getRenderer() const {
        return renderer.get();
    }
    
    // Get number of shapes
    size_t getShapeCount() const {
        return shapes.size();
    }
    
private:
    std::vector<Shape*> shapes;
    std::unique_ptr<Renderer> renderer;
};
