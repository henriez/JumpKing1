#pragma once

#include "../MenuEnte.h"
#include "../Botao/Botao.h"
#include <SDL_image.h>

class LoadMenu : public MenuEnte
{
public:
	LoadMenu();
	~LoadMenu();

	void init();

	void reset();

	int update();
	void render();
private:
	Button save1;
	Button save2;
	Button back;
};

