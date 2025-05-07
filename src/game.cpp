#include "game.h"

Game::Game(void)
{
	this->is_running = Graphic::instance() -> initialize();
	this->is_running = Graphic::instance() -> initialize_window();
	this->is_running = Graphic::instance() -> initialize_renderer();
	this->is_running = Graphic::instance() -> initialize_textures();

	this->is_running = Sound::instance() -> initialize();
}

void Game::setup(void)
{
	/*
	* Game Setup Here
	*/
		//Textures
		Texture::instance() -> load_textures(this->texture_files);

		//Sounds
		Sound::instance()->load_sounds(this->sound_efx_files, efx);
}

void Game::process_input(void) /*TODO: Extract game logic from here */
{
	//SDL CHECK
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			//printf("sdl event quit \n");

			this->is_running = false;
			break;

		case SDL_KEYDOWN:
			//printf("sdl event keydown \n");

			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					this->is_running = false;
					break;

				case SDLK_LEFT:
					break;

				case SDLK_RIGHT:
					break;

				case SDLK_UP:
					break;

				case SDLK_DOWN:
					break;
				}
			break;

		case SDL_KEYUP:
			//printf("sdl event keyup \n");

			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
					break;

				case SDLK_RIGHT:
					break;

				case SDLK_UP:
					break;

				case SDLK_DOWN:
					break;
				}
			break;

		case SDL_MOUSEMOTION:
			//printf("sdl event mouse motion \n");

			mouseX = event.motion.x;
			mouseY = event.motion.y;

			if (mouseX > 0 && mouseX < WINDOW_WIDTH)
			{
				if (mouseY > 52 && mouseY < WINDOW_HEIGHT)
				{
					int my = floor(mouseX / TILE_SIZE);
					int mx = floor(mouseY / TILE_SIZE);

					int local_index_x;
					int local_index_y;

					//over iten mouse over
					if ( (mx >= 0 && mx <= 10) && (my >= 0 && my <= 10) )
					{
						if (canva[mx-1][my] == 0)
						{
							local_index_x = mx-1;
							local_index_y = my;

							canva[local_index_x][local_index_y] = 1;
						}						
					}

					//clear others overs
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							if (i != local_index_x && j != local_index_y && canva[i][j] == 1)
							{
								canva[i][j] = 0;
							}
						}
					}
				}
			}

			break;

		case SDL_MOUSEBUTTONDOWN:
			//printf("sdl event mouse button down \n");

			int m_value;
			if (mouseX > 0 && mouseX < WINDOW_WIDTH)
			{
				if (mouseY > 52 && mouseY < WINDOW_HEIGHT)
				{
					int my = floor(mouseX / TILE_SIZE );
					int mx = floor(mouseY / TILE_SIZE );

					if ( (mx >= 0 && mx <= 10) && (my >= 0 && my <= 10) )
					{
						m_value = canva[mx-1][my];
					}
				}
			}

			switch (event.button.button)
			{
				case SDL_BUTTON_LEFT:
					if (atual_game_status == game_status::game)
					{
						Sound::instance()->play_efx(1, 1, 0, 255);

						if (m_value != 0 || m_value != 1)
						{
							//gren
							if (m_value == 2)
							{
								//std::cout << m_value << std::endl;
								dots_values.push_back(2);
							}
							else
							{
								atual_game_status = game_status::game_over;
								global_time = 0;
							}
						}
					}
					break;

				case SDL_BUTTON_RIGHT:
					if (atual_game_status == game_status::game)
					{
						Sound::instance()->play_efx(1, 1, 0, 255);
						
						if (m_value != 0 || m_value != 1)
						{
							//red
							if (m_value == 3)
							{
								//std::cout << m_value << std::endl;
								dots_values.push_back(3);
							}
							else
							{
								atual_game_status = game_status::game_over;
								global_time = 0;
							}
						}
					}
					break;

				default:
					break;
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					canva[i][j] = 0;
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			//printf("sdl event mouse button up \n");

			switch (event.button.button)
			{
				case SDL_BUTTON_LEFT:
					break;

				case SDL_BUTTON_RIGHT:
					break;

				default:
					break;
			}
			break;
		}
	}
}

void Game::fix_update(void)
{
	/*
	* Todo: calc FixDeltaTime for Physics
	*/
}

void Game::update(void)
{
	//FPS Control (Fix FPS)
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - this->last_frame_time);
	if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(time_to_wait);
	}

	this->frame_time = (SDL_GetTicks() - this->last_frame_time) / 1000.0f;
	float frame_rate = (1.0f / this->frame_time);

	string new_title = (string) GAME_NAME + " - " + to_string(frame_rate);
	const char* title = new_title.c_str();
	Graphic::instance() -> update_window_title(title);

	//Deltatime
	this->delta_time = (SDL_GetTicks() - this->last_frame_time) / 1000.0f;
	this->last_frame_time = SDL_GetTicks();

	EventSystem::instance() -> process_events();

	/*
	* Game Logig Here
	*/
		switch (atual_game_status)
		{
			case game_status::intro:
				if (global_time < SDL_GetTicks())
				{
					if (global_time == 0)
					{
						if ((int)dots_values.size() > 0){dots_values.clear();}
						std::cout << "“Jason Piloti presents the Dot game”" << std::endl;
						Sound::instance()->play_efx(0, 1, 0, 255);

						global_time = SDL_GetTicks() + 5000;
					}
					else
					{
						atual_game_status = game_status::game;
						global_time = 0;
					}
				}
				break;

			case game_status::game:
				

				if (global_time < SDL_GetTicks())
				{
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							canva[i][j] = 0;
						}
					}

					int mx = get_random_num(0,9);
					int my = get_random_num(0, 9);

					canva[mx][my] = get_random_num(2,3);

					global_time = SDL_GetTicks() + 2000;
				}

				if ((int)dots_values.size() >= 10)
				{
					atual_game_status = game_status::game_over;
					global_time = 0;
				}
				break;

			case game_status::game_over:
				if (global_time < SDL_GetTicks())
				{
					if (global_time == 0)
					{
						std::cout << "Game Over!" << std::endl;
						std::cout << "Your Final Score: " << (int)dots_values.size() << std::endl;
						Sound::instance()->play_efx(2, 1, 0, 255);

						global_time = SDL_GetTicks() + 5000;

						//dots_values.clear();
					}
					else
					{
						atual_game_status = game_status::intro;
						global_time = 0;
					}
				}
				break;
		}

	/* END Game Logig */
}


void Game::render(void)
{
	Graphic::instance() -> clear_color_buffer(0xFF000000);

	/*
	* Game Render Here
	*/
		switch (atual_game_status)
		{
			case game_status::intro:
				Graphic::instance()->drawn_rect_in_color_buffer(0, 0, Texture::instance()->print_texture(6).width, Texture::instance()->print_texture(6).height, 6);
				break;

			case game_status::game:
				//RENDER CANVA
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						int tileX = j * TILE_SIZE;
						int tileY = i * TILE_SIZE;

						//uint32_t tileColor;
						int tileColor;
						switch (canva[i][j])
						{
							case 0:
								//tileColor = 0xFFFFFFFF;
								tileColor = 0;
								break;
							case 1:
								//tileColor = 0xFFFF0000;
								tileColor = 1;
								break;
							case 2:
								//tileColor = 0xFF00FF00;
								tileColor = 2;
								break;
							case 3:
								//tileColor = 0xFF0000FF;
								tileColor = 3;
								break;
						}

						Graphic::instance()->drawn_rect_in_color_buffer(tileX, tileY+52, TILE_SIZE, TILE_SIZE, tileColor);
					}
				}

				//RENDER SCORE
				Graphic::instance()->drawn_rect_in_color_buffer(0, 0, WINDOW_WIDTH, 52, (uint32_t)0x4872D3);

				for (int i = 0; i < (int)dots_values.size(); i++)
				{
					int tileX = i * TILE_SIZE;

					//uint32_t tileColor;
					int tileColor;
					switch (dots_values[i])
					{
						case 2:
							//tileColor = 0xFF00FF00;
							tileColor = 4;
							break;
						case 3:
							//tileColor = 0xFF0000FF;
							tileColor = 5;
							break;
					}

					Graphic::instance()->drawn_rect_in_color_buffer(tileX, 0, TILE_SIZE, TILE_SIZE, tileColor);
				}
				break;
			
			case game_status::game_over:
				Graphic::instance()->drawn_rect_in_color_buffer(0, (WINDOW_HEIGHT / 2) - (Texture::instance()->print_texture(7).height / 2), Texture::instance()->print_texture(7).width, Texture::instance()->print_texture(7).height, 7);
				int num_img = (int)dots_values.size() > 0 ? ((int)dots_values.size() * 52)-11 : 0;
				Graphic::instance()->drawn_rect_in_color_buffer((WINDOW_WIDTH / 2) - 26, (WINDOW_HEIGHT / 2) + 25, 52, 52, 8, 1, -267 + num_img, 0);
				break;
		}

	/* END Render Here */

	Graphic::instance()->render_color_buffer();
}

void Game::release_resources(void)
{
	EventSystem::instance() -> shut_down();
	Texture::instance() -> free_textures();
	Sound::instance() -> free_sounds();
	Graphic::instance() -> destroy_window();
}