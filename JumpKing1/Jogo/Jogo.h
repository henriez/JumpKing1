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
	void pauseMenu();
	void settingsMenu();
	void leaderboardMenu();
	void levelMenu();

	static SDL_Renderer* renderer;
	static SDL_Event evento;
	static Vector2D getDimensoesJanela();

private:
	void inicializar(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia);
	static SDL_Window* janela;
	bool rodando;
	static Vector2D dimensoesJanela;
	
	Menu menu;

	Fase* fase;
};