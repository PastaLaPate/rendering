
#pragma once

#include <vector>
#include <memory>
#include "shapes/shape.h"
#include "rendering/rendering_engine.h"
#include "camera.h"

using ShapeID = uint32_t;

struct ShapeEntry {
    ShapeID id;
    std::unique_ptr<Shape> shape;
    uint32_t generation; // for stale ID detection
};

class Scene {
public:
	Scene();
	~Scene();

	// Add a shape (Scene takes ownership)
	ShapeID addShape(std::unique_ptr<Shape> shape);

	// Remove a shape (by ID)
	void removeShape(ShapeID id);

	// Clear all shapes
	void clearShapes();

    Shape* getShapeByID(ShapeID id) const;

	// Render all shapes in the scene
	void render();

	// Get shape at world position
	Shape* findShapeAt(Vector2 worldPos);

	// Get number of shapes
	size_t getShapeCount() const;

	// Access camera
	Camera2& getCamera();
	const Camera2& getCamera() const;

	// Access rendering engine
	RenderingEngine& getRenderingEngine();
	const RenderingEngine& getRenderingEngine() const;

	// Convert screen to world position
	Vector2 toWorldPosition(Vector2 screenPos) const;

	// Get all shapes (const)
	const std::vector<ShapeEntry>& getShapes() const;

private:
    std::vector<ShapeEntry> shapes;
    std::vector<size_t> freeIndices; // indices of holes
    uint32_t nextID = 1;
	RenderingEngine renderingEngine;
};