#pragma once

#include "../Ente.h"
#include "MainMenu/MainMenu.h"
#include "PauseMenu/PauseMenu.h"
#include "GameOverMenu/GameOverMenu.h"
#include "SettingsMenu/SettingsMenu.h"
#include "LeaderboardMenu/LeaderboardMenu.h"
#include "LevelMenu/LevelMenu.h"
#include "LoadMenu/LoadMenu.h"

#define MAIN 1
#define PAUSE 2
#define SETTINGS 3
#define LEADERBOARD 4
#define LEVEL 5
#define GAMEOVER 6
#define LOAD 7

class GerenciadorDeMenu{
public:
	GerenciadorDeMenu() {}
	~GerenciadorDeMenu() {}

	void init() {
		start.init();
		pause.init();
		settings.init();
		leaderboard.init();
		level.init();
		gameOver.init();
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
	LoadMenu load;
};