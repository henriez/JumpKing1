#pragma once

#include "../MenuEnte.h"
#include "../Botao/Botao.h"
#include <SDL_image.h>

class PauseMenu : public MenuEnte
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
	Button save;
};

