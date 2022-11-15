#pragma once

#include "../MenuEnte.h"
#include "../Botao/Botao.h"
#include <SDL.h>

class LeaderboardMenu : public MenuEnte
{
public:
	LeaderboardMenu();
	~LeaderboardMenu();

	void init();

	void reset();

	int update();
	int updateRanking(SDL_Texture* textTex, SDL_Rect ranking);
	void render();

private:
	Button quit;
	Button level1;
	Button level2;
};

