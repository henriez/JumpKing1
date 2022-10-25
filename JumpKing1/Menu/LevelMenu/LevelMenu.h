#pragma once

#include "../Botao/Botao.h"
#include <SDL_image.h>

class LevelMenu
{
public:
	LevelMenu();
	~LevelMenu();

	void init();

	void reset();

	int update();
	void render();
private:
	Button start;
	Button quit;

	SDL_Texture* background;
};

