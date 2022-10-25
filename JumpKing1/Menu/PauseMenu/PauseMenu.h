#pragma once

#include "../Botao/Botao.h"
#include <SDL_image.h>

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	void init();

	void reset();

	int update();
	void render();


private:
	Button resume;
	Button quit;
	SDL_Texture* background;
};

