#include "Jogo.h"
#include <iostream>
#include "Fase/Fase.h"
#include "../ECS/Gerenciador/GerenciadorGrafico.h"

#define FPS 60

SDL_Event Jogo::evento;

Jogo::Jogo(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	rodando = true;
	fase = new Fase;
	inicializar(nomeJanela, largJanela, alturaJanela, telaCheia);
}

Jogo::~Jogo() {
	fase->clear();
	SDL_Quit();
	delete fase;
}

void Jogo::inicializar(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	SDL_Init(SDL_INIT_EVERYTHING);

	GerenciadorGrafico::init(nomeJanela, largJanela, alturaJanela, telaCheia);

	menu.start.init();
	menu.leaderboard.init();
	menu.level.init();
	menu.pause.init();
	menu.settings.init();
	mainMenu();
	srand(time(NULL));
}

void Jogo::mainMenu() {

	menu.start.reset();
	int click = menu.start.update();
	
	while (click == NO_BUTTON_CLICKED) {
		GerenciadorGrafico::renderMenu(menu.start);
		click = menu.start.update();
	}

	switch (click) { //apos algum clique
	case BUTTON_START1:
		levelMenu();
		break;
	case BUTTON_LEADERBOARD:
		leaderboardMenu();
		break;		
	case BUTTON_SETTINGS:
		settingsMenu();
		break;
	case BUTTON_QUIT:
		rodando = false;
		break;
	default:
		break;
	}

}

void Jogo::pauseMenu() {

	menu.pause.reset();
	int click = menu.pause.update();

	while (click == NO_BUTTON_CLICKED) {
		GerenciadorGrafico::renderMenu(menu.pause);
		click = menu.pause.update();
	}

	switch (click) { //apos algum clique
	case BUTTON_RESUME:
		atualizar();
		break;
	case BUTTON_QUIT:
		fase->clear();
		mainMenu();
		break;
	default:
		break;
	}
}

void Jogo::settingsMenu() {

	//fazer o menu de settings
	//por enquanto redireciona para mainMenu()
	menu.settings.reset();
	int click = menu.settings.update();

	while (click == NO_BUTTON_CLICKED) {
		GerenciadorGrafico::renderMenu(menu.settings);
		click = menu.settings.update();
	}	
	
	switch (click) { //apos algum clique
	case BUTTON_QUIT:
		SDL_Delay(100);
		mainMenu();
		break;
	default:
		break;
	}

}

void Jogo::leaderboardMenu() {

	// fazer o menu de leaderboard
	menu.leaderboard.reset();
	int click = menu.leaderboard.update();

	while (click == NO_BUTTON_CLICKED) {
		GerenciadorGrafico::renderMenu(menu.leaderboard);
		click = menu.leaderboard.update();
	}

	switch (click) { //apos algum clique
	case BUTTON_QUIT:
		mainMenu();
		break;
	default:
		break;
	}

}

void Jogo::levelMenu() {

	menu.level.reset();
	int click = menu.level.update();

	while (click == NO_BUTTON_CLICKED) {
		GerenciadorGrafico::renderMenu(menu.level);
		click = menu.level.update();
	}

	switch (click) { //apos algum clique
	case BUTTON_START1:
		fase->inicializar(1);
		atualizar();
		break;
	case BUTTON_START2:
		fase->inicializar(2);
		atualizar();
		break;
	case BUTTON_QUIT:
		mainMenu();
		break;
	default:
		break;
	}

}

void Jogo::atualizar() {
	Uint32 ticks0 = SDL_GetTicks();
	Uint32 finalTicks;
	Uint32 framedelay = 1000 / FPS;
	analisaEventos();

	if (!rodando) return;
	fase->atualizar();

	render();

	finalTicks = SDL_GetTicks();
	if (finalTicks - ticks0 < framedelay)
		SDL_Delay(framedelay - (finalTicks - ticks0));
}

void Jogo::render() {
	GerenciadorGrafico::renderFase(fase);
}

void Jogo::analisaEventos() {
	SDL_PollEvent(&evento);

	if (evento.type == SDL_QUIT)
		rodando = false;

	else if (evento.type == SDL_KEYDOWN)
		if (evento.key.keysym.sym == SDLK_ESCAPE) //pause
			pauseMenu();
												  //rodando = false;
}

bool Jogo::executando() {
	return rodando;
}


