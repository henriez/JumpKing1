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
	void render();


private:
	Button quit;
};

