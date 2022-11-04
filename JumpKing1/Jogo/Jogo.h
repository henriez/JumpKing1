#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "../ECS/Entidade/ListaDeEntidades/ListaDeEntidades.h"
#include "../ECS/Componentes/Vector2D/Vector2D.h"
#include "../Menu/Menu.h"

class Fase;

class Jogo {
public:
	Jogo(const char* nomeJanela = "Jump King", int largJanela = 1920, int alturaJanela = 1080, bool telaCheia = true);
	~Jogo();

	void atualizar();
	void render();
	void analisaEventos();
	bool executando();

	void mainMenu();
	void gameOverMenu();
	void pauseMenu();
	void settingsMenu();
	void leaderboardMenu();
	void levelMenu();

	static SDL_Event evento;

private:
	void inicializar(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia);
	bool rodando;
	
	Menu menu;

	Fase* fase;
};