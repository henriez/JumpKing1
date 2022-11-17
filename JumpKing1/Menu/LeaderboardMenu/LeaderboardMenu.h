#pragma once

#include "../MenuEnte.h"
#include "../Botao/Botao.h"
#include <SDL.h>

#include <map>

class LeaderboardMenu : public MenuEnte
{
public:
	LeaderboardMenu();
	~LeaderboardMenu();

	void init();

	void reset();

	int update();
	int updateRanking();
	void render();

private:
	Button quit;
	Button level1;
	Button level2;
};

