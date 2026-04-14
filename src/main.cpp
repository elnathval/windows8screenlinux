/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "engine/rendering.h"		// header for our rendering code
#include "opentasks.h"		// source file for our game logic code (for now just input handling and updating the state of the tiles)
#include "engine/initialize.h"	// source file for our initialization code (for now just loading the tile configuration from a file or setting up a default one if the file doesn't exist)
#include "systemsettings.h"

int main ()
{
	if(isAlreadyRunning()){
		return 0;
	}
	
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Start Menu");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	


	SetWindowState(FLAG_FULLSCREEN_MODE);
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	LoadResources();

	GetApplications();
	
	LoadTiles();

	InitialAnimation();

	
	// game loop
	while (!WindowShouldClose() && !openingTask)		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();
		
		Update();
		Render();
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);
	UnloadResources();

	FinalAnimation();

	// destroy the window and cleanup the OpenGL context
	CloseWindow();

	closeLockFile();
	return 0;
}
