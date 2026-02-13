/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
using namespace std;

#include <iostream>
#include <vector>
#include "raylib.h"

#include "point.cpp"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	float accumulator = 0.0f;
	float fixedDt = 1.0f / 60.0f;
	Point* point = new Point(100, 100);
	vector<Renderable*> objects;
	objects.push_back(point);
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{

		float frameDt = GetFrameTime();
		accumulator += frameDt;

		while (accumulator >= fixedDt)
		{
			accumulator -= fixedDt;

		}
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Hello Raylib", 200,200,20,WHITE);
		for (Renderable* obj : objects)
		{
			Vector2 mousePos = GetMousePosition();
			if (Hoverable* hoverable = dynamic_cast< Hoverable* >( obj )) {
				hoverable->Collides(mousePos);
			}
			obj->render();
		}
		EndDrawing();
		DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GREEN);
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
