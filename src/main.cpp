/*
Raylib example file with modular rendering engine.
Demonstrates object-based rendering with shapes, rendering engine, and abstract base classes.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
using namespace std;

#include <iostream>
#include <vector>
#include <memory>
#include "raylib.h"

#include "resource_dir.h"
#include "rendering_engine.h"
#include "rectangle_shape.h"
#include "triangle_shape.h"
#include "text_shape.h"

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags( FLAG_WINDOW_HIGHDPI); //FLAG_VSYNC_HINT |

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Modular Rendering Engine - Shapes Demo");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Create the rendering engine
	RenderingEngine renderingEngine;

	// Create shapes
	auto rectangle1 = new RectangleShape({100.0f, 100.0f}, 150.0f, 100.0f, BLUE);
	auto rectangle2 = new RectangleShape({400.0f, 150.0f}, 120.0f, 120.0f, GREEN);
	
	auto triangle1 = new TriangleShape(
		{700.0f, 100.0f},
		{750.0f, 200.0f},
		{650.0f, 200.0f},
		RED
	);
	
	auto triangle2 = new TriangleShape(
		{900.0f, 150.0f},
		{950.0f, 250.0f},
		{850.0f, 250.0f},
		YELLOW
	);
	
	auto text1 = new TextShape({100.0f, 300.0f}, "Rectangle Shape", 20, WHITE);
	auto text2 = new TextShape({400.0f, 350.0f}, "Another Rectangle", 20, WHITE);
	auto text3 = new TextShape({700.0f, 300.0f}, "Triangle Shapes", 20, WHITE);
	auto text4 = new TextShape({900.0f, 300.0f}, "More Triangles", 20, WHITE);

	// Add shapes to rendering engine
	renderingEngine.addShape(rectangle1);
	renderingEngine.addShape(rectangle2);
	renderingEngine.addShape(triangle1);
	renderingEngine.addShape(triangle2);
	renderingEngine.addShape(text1);
	renderingEngine.addShape(text2);
	renderingEngine.addShape(text3);
	renderingEngine.addShape(text4);

	// Create a title text shape
	auto titleText = new TextShape({400.0f, 20.0f}, "Modular Rendering Engine Demo", 30, YELLOW);
	renderingEngine.addShape(titleText);

	// Create an info text shape
	auto infoText = new TextShape({10.0f, 700.0f}, "Click on shapes to interact. Total shapes: " , 20, LIGHTGRAY);
	renderingEngine.addShape(infoText);

	Shape* selectedShape = nullptr;

	while (!WindowShouldClose())
	{
		// Input handling
		Vector2 mousePos = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			selectedShape = renderingEngine.findShapeAt(mousePos);
			if (selectedShape != nullptr)
			{
				selectedShape->setColor(ORANGE);
			}
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			if (selectedShape != nullptr)
			{
				// Restore original color based on shape type
				if (selectedShape == rectangle1) selectedShape->setColor(BLUE);
				else if (selectedShape == rectangle2) selectedShape->setColor(GREEN);
				else if (selectedShape == triangle1) selectedShape->setColor(RED);
				else if (selectedShape == triangle2) selectedShape->setColor(YELLOW);
			}
			selectedShape = nullptr;
		}

		// Drag selected shape
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && selectedShape != nullptr)
		{
			selectedShape->setPosition(mousePos);
		}

		// Render
		BeginDrawing();
		ClearBackground(BLACK);

		// Render all shapes using the rendering engine
		renderingEngine.render();

		// Draw FPS
		DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GREEN);
		DrawText(TextFormat("Shapes: %zu", renderingEngine.getShapeCount()), 10, 40, 20, GREEN);

		EndDrawing();
	}

	// Cleanup
	delete rectangle1;
	delete rectangle2;
	delete triangle1;
	delete triangle2;
	delete text1;
	delete text2;
	delete text3;
	delete text4;
	delete titleText;
	delete infoText;

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
