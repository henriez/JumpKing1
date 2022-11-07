#pragma once

#include "../Ente.h"
#include "MainMenu/MainMenu.h"
#include "PauseMenu/PauseMenu.h"
#include "GameOverMenu/GameOverMenu.h"
#include "SettingsMenu/SettingsMenu.h"
#include "LeaderboardMenu/LeaderboardMenu.h"
#include "LevelMenu/LevelMenu.h"
#include "SaveMenu/SaveMenu.h"
#include "LoadMenu/LoadMenu.h"

class Menu : public Ente{
public:
	Menu() {}
	~Menu() {}

	void init() {
		start.init();
		pause.init();
		settings.init();
		leaderboard.init();
		level.init();
		gameOver.init();
		save.init();
		load.init();
	}

	void atualizar() {}
	void render() {}

	MainMenu start;
	PauseMenu pause;
	SettingsMenu settings;
	LeaderboardMenu leaderboard;
	LevelMenu level;
	GameOverMenu gameOver;
	SaveMenu save;
	LoadMenu load;
};