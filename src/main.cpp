/*
Raylib example file with modular rendering engine.
Demonstrates object-based rendering with shapes, rendering engine, and abstract base classes.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "interfaces/hoverable.h"
#include "raylib.h"

#include "raymath.h"
#include "resource_dir.h"
#include "scene.h"
#include "shapes/rectangle_shape.h"
#include "shapes/triangle_shape.h"
#include "shapes/text_shape.h"

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE); // FLAG_VSYNC_HINT

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Modular Rendering Engine - Shapes Demo");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Create the scene
	Scene scene;

	auto rectangle1 = std::make_unique<RectangleShape>(Vector2{100.0f, 100.0f}, 150.0f, 100.0f, BLUE);
	auto rectangle2 = std::make_unique<RectangleShape>(Vector2{400.0f, 150.0f}, 120.0f, 120.0f, GREEN);
	auto triangle1 = std::make_unique<TriangleShape>(Vector2{700.0f, 100.0f}, Vector2{750.0f, 200.0f}, Vector2{650.0f, 200.0f}, RED);
	auto triangle2 = std::make_unique<TriangleShape>(Vector2{900.0f, 150.0f}, Vector2{950.0f, 250.0f}, Vector2{850.0f, 250.0f}, YELLOW);
	auto text1 = std::make_unique<TextShape>(Vector2{100.0f, 300.0f}, "Rectangle Shape", 20, WHITE);
	auto text2 = std::make_unique<TextShape>(Vector2{400.0f, 350.0f}, "Another Rectangle", 20, WHITE);
	auto text3 = std::make_unique<TextShape>(Vector2{700.0f, 300.0f}, "Triangle Shapes", 20, WHITE);
	auto text4 = std::make_unique<TextShape>(Vector2{900.0f, 300.0f}, "More Triangles", 20, WHITE);
	auto titleText = std::make_unique<TextShape>(Vector2{400.0f, 20.0f}, "Modular Rendering Engine Demo", 30, YELLOW);
	auto infoText = std::make_unique<TextShape>(Vector2{10.0f, 700.0f}, "Click on shapes to interact. Total shapes: ", 20, LIGHTGRAY);

	// Keep raw pointers for color restore logic
	Shape* rectangle1Ptr = rectangle1.get();
	Shape* rectangle2Ptr = rectangle2.get();
	Shape* triangle1Ptr = triangle1.get();
	Shape* triangle2Ptr = triangle2.get();

	scene.addShape(std::move(rectangle1));
	scene.addShape(std::move(rectangle2));
	scene.addShape(std::move(triangle1));
	scene.addShape(std::move(triangle2));
	scene.addShape(std::move(text1));
	scene.addShape(std::move(text2));
	scene.addShape(std::move(text3));
	scene.addShape(std::move(text4));
	scene.addShape(std::move(titleText));
	scene.addShape(std::move(infoText));

	Shape *selectedShape = nullptr;
	Shape *hoveredShape = nullptr;
	Hoverable *hoveredHoverable = nullptr;
	Draggable *selectedDraggable = nullptr;
	Clickable *selectedClickable = nullptr;
	Vector2 *dragOffset = nullptr;

	while (!WindowShouldClose())
	{
		// Input handling
		Vector2 mouseScreenPos = GetMousePosition();
		Vector2 mouseWorldPos = scene.toWorldPosition(mouseScreenPos);
		hoveredShape = scene.findShapeAt(mouseWorldPos);

		if (hoveredShape)
		{
			hoveredHoverable = dynamic_cast<Hoverable *>(hoveredShape);
			if (hoveredHoverable)
			{
				hoveredHoverable->onHoverStart();
			}
		}
		else if (hoveredHoverable)
		{
			hoveredHoverable->onHoverEnd();
			hoveredHoverable = nullptr;
		}

		scene.getCamera().setScale({scene.getCamera().getScale().x + (GetMouseWheelMove() * 0.1f), scene.getCamera().getScale().y + (GetMouseWheelMove() * 0.1f)});

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			selectedShape = hoveredShape;
			selectedDraggable = dynamic_cast<Draggable *>(selectedShape);
			selectedClickable = dynamic_cast<Clickable *>(selectedShape);
			if (selectedShape != nullptr)
			{
				selectedShape->setColor(BLUE);
				if (selectedClickable)
				{
					selectedClickable->onMouseDown();
					if (selectedDraggable)
					{
						// Calculate drag offset in world coordinates
						Vector2 shapePos = selectedShape->getPosition();
						if (dragOffset) delete dragOffset;
						dragOffset = new Vector2{mouseWorldPos.x - shapePos.x, mouseWorldPos.y - shapePos.y};
						selectedDraggable->onStartDrag();
					}
				};
			}
		}

		if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON))
		{
			scene.getCamera().setPosition({scene.getCamera().getPosition().x - GetMouseDelta().x, scene.getCamera().getPosition().y - GetMouseDelta().y});
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			if (selectedShape != nullptr)
			{
				// Restore original color based on shape type
				if (selectedShape == rectangle1Ptr)
					selectedShape->setColor(BLUE);
				else if (selectedShape == rectangle2Ptr)
					selectedShape->setColor(GREEN);
				else if (selectedShape == triangle1Ptr)
					selectedShape->setColor(RED);
				else if (selectedShape == triangle2Ptr)
					selectedShape->setColor(YELLOW);
				if (selectedClickable)
					selectedClickable->onMouseUp();
			}
			selectedShape = nullptr;
			selectedDraggable = nullptr;
			selectedClickable = nullptr;
			if (dragOffset) { delete dragOffset; dragOffset = nullptr; }
		}

		// Drag selected shape using world coordinates
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && selectedDraggable != nullptr)
		{
			float posX = mouseWorldPos.x - (dragOffset ? dragOffset->x : 0);
			float posY = mouseWorldPos.y - (dragOffset ? dragOffset->y : 0);
			selectedDraggable->onDrag(posX, posY);
		}

		// Render
		BeginDrawing();
		ClearBackground(BLACK);

		// Render all shapes using the scene
		scene.render();

		// Draw FPS
		DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GREEN);
		DrawText(TextFormat("Shapes: %zu", scene.getShapeCount()), 10, 40, 20, GREEN);

		EndDrawing();
	}

	// Cleanup handled by Scene (unique_ptr)

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
