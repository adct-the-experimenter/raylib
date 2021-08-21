/*******************************************************************************************
*
*   raylib [audio] example - Sound loading and playing
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdio.h>

//function is applied in a loop to each individual frame
//needs to have float pointer and count
void MyCustomEffect(float* frame, unsigned int count)
{
	//implementing low-pass filter with moving average
	//TO DO: Figure out stereo
	if(count % 2 == 0)
	{
		float* lastFrame = frame;
		float* prevFrame = frame -= 2;
		
		float coeff = (*lastFrame + *prevFrame) / 2;
		
		*lastFrame = coeff *  *lastFrame;
		*prevFrame = coeff * *prevFrame;
	}
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - applying sound effect");

    InitAudioDevice();      // Initialize audio device

    Sound fxWav = LoadSound("resources/sound.wav");         // Load WAV audio file
    
    
	AudioEffectParams effect_params;
	effect_params.usage = AUDIO_EFFECT_CUSTOM;
	effect_params.cutoff = 100;
	effect_params.custom_effect_func_ptr = &MyCustomEffect;
	
	AudioEffectParams effect_params_none;
	effect_params_none.usage = AUDIO_EFFECT_NONE;
	
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_SPACE))
        {
			SetEffectForSound(fxWav,effect_params_none); 
			PlaySound(fxWav);      // Play WAV sound without effect
		}
        if (IsKeyPressed(KEY_ENTER))
        {
			SetEffectForSound(fxWav,effect_params); 
			PlaySound(fxWav);      // Play WAV sound with effect
		} 
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Press SPACE to PLAY the WAV sound without effect!", 200, 180, 20, LIGHTGRAY);
            DrawText("Press ENTER to PLAY the WAV sound with effect!", 200, 220, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadSound(fxWav);     // Unload sound data

    CloseAudioDevice();     // Close audio device

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
