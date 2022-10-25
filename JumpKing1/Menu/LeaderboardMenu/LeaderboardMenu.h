#pragma once

#include "../Botao/Botao.h"
#include <SDL.h>

class LeaderboardMenu
{
public:
	LeaderboardMenu();
	~LeaderboardMenu();

	void init();

	void reset();

	int update();
	void render();


private:
	Button quit;
	SDL_Texture* background;
};

