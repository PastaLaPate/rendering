
#pragma once

#include <vector>
#include <memory>
#include "shapes/shape.h"
#include "rendering/rendering_engine.h"
#include "camera.h"

class Scene {
public:
	Scene();
	~Scene();

	// Add a shape (Scene takes ownership)
	void addShape(std::unique_ptr<Shape> shape);

	// Remove a shape (by pointer)
	void removeShape(Shape* shape);

	// Clear all shapes
	void clearShapes();

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
	const std::vector<std::unique_ptr<Shape>>& getShapes() const;

private:
	std::vector<std::unique_ptr<Shape>> shapes;
	RenderingEngine renderingEngine;
};