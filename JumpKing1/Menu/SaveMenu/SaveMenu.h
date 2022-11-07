#pragma once

#include "../Botao/Botao.h"
#include <SDL_image.h>

class SaveMenu
{
public:
	SaveMenu();
	~SaveMenu();

	void init();

	void reset();

	int update();
	void render();
private:
	Button save;
	Button back;
	Button quit;

	SDL_Texture* background;
};

