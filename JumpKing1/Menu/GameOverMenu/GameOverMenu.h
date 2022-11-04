#pragma once

#include "../Botao/Botao.h"
#include <SDL_image.h>

class GameOverMenu
{
public:
	GameOverMenu();
	~GameOverMenu();

	void init();

	void reset();

	int update();
	void render();


private:
	Button quit;
	SDL_Texture* background;
};

