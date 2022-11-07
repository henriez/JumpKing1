#pragma once

#include "../Botao/Botao.h"
#include <SDL_image.h>

class LoadMenu
{
public:
	LoadMenu();
	~LoadMenu();

	void init();

	void reset();

	int update();
	void render();
private:
	Button save1;
	Button save2;
	Button back;

	SDL_Texture* background;
};

