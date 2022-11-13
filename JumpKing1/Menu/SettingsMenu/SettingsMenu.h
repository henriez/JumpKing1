#pragma once

#include "../MenuEnte.h"
#include "../Botao/Botao.h"
#include <SDL_image.h>

class SettingsMenu : public MenuEnte
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
};

