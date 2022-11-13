#pragma once

#include "../MenuEnte.h"
#include "../Botao/Botao.h"
#include <SDL_image.h>

class MainMenu: public MenuEnte
{
public:
	MainMenu();
	~MainMenu();

	void init();

	void reset();
	
	int update();
	void render();
	

private:
	Button start;
	Button settings;
	Button leaderboard;
	Button load;
	Button quit;
};

