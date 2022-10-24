#pragma once

#include "Botao/Botao.h"

#define BUTTON_QUIT 1
#define BUTTON_START 2
#define BUTTON_SETTINGS 3
#define BUTTON_RESUME 4

class Menu {
private:
	SettingsButton settings;
	StartButton start;
	StartButton resume;
	QuitButton quit;
public:
	Menu();
	~Menu();
	void init();

	int click();

	void update();
	void render();
};