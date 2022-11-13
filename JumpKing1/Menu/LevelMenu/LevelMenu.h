#pragma once

#include "../MenuEnte.h"
#include "../Botao/Botao.h"
#include <SDL_image.h>

class LevelMenu : public MenuEnte
{
public:
	LevelMenu();
	~LevelMenu();

	void init();

	void reset();

	int update();
	void render();
private:
	Button level1;
	Button level2;
	Button back;
};

