#pragma once

#include "../MenuEnte.h"
#include "../Botao/Botao.h"
#include <SDL_image.h>

class GameOverMenu : public MenuEnte
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
};

