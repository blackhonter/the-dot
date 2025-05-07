#ifndef GAME_H
	#define GAME_H

	#include <iostream>
	#include <stdio.h>
	#include <stdint.h>
	#include <stdbool.h>
	#include <bits/stdc++.h>
	#include <string>
	#include <vector>

	#include <SDL2/SDL.h>

	#include "definitions.h"
	#include "functions.h"
	#include "graphic.h"
	#include "texture.h"
	#include "sound.h"
	#include "eventSystem.h"

	using namespace std;

	class Game
	{
		public:
			Game(void);

			void setup(void);
			void process_input(void);
			void fix_update(void);
			void update(void);
			void render(void);
			void release_resources(void);

			bool is_running = false;
			
		protected:
			/*
			* Game Vars Here
			*/
			enum game_status
			{
				intro = 1,
				game = 2,
				game_over = 3
			};
			enum game_status atual_game_status = game_status::intro;

			vector<string> texture_files
			{
				"images/TileBackground.png",
				"images/TileBackgroundOver.png",
				"images/ClickableGreen.png",
				"images/ClickableRed.png",
				"images/DotGreen.png",
				"images/DotRed.png",
				"images/cover.png",
				"images/score.png",
				"images/numbers.png"
			};

			vector<string> sound_efx_files
			{
				"sounds/intro.wav",
				"sounds/click.wav",
				"sounds/game_over.wav"
			};

			int canva[10][10] =
			{
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
			};

			int mouseX, mouseY;

			float global_time = 0;
			vector<int> dots_values;

		private:
			float last_frame_time = 0.0f;
			float delta_time = 0.0f;
			float frame_time = 0.0f;
	};
	
#endif