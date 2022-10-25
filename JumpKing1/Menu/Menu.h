#pragma once

#include "MainMenu/MainMenu.h"
#include "PauseMenu/PauseMenu.h"
#include "SettingsMenu/SettingsMenu.h"
#include "LeaderboardMenu/LeaderboardMenu.h"
#include "LevelMenu/LevelMenu.h"

struct Menu {
	MainMenu start;
	PauseMenu pause;
	SettingsMenu settings;
	LeaderboardMenu leaderboard;
	LevelMenu level;
};