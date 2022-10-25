#pragma once

#include "../Botao/Botao.h"
#include <SDL_image.h>

class SettingsMenu
{
public:
	SettingsMenu();
	~SettingsMenu();

	void init();

	void reset();

	int update();
	void render();


private:
	Button quit;
	SDL_Texture* background;
};

