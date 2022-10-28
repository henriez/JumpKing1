#include "Jogo.h"
#include <iostream>
#include "Fase/Fase.h"

#define FPS 60

SDL_Renderer* Jogo::renderer;
SDL_Event Jogo::evento;
Vector2D Jogo::dimensoesJanela;

Jogo::Jogo(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	rodando = true;
	fase = new Fase;
	inicializar(nomeJanela, largJanela, alturaJanela, telaCheia);
}

Jogo::~Jogo() {
	fase->clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(janela);
	SDL_Quit();
	delete fase;
}

void Jogo::inicializar(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_DisplayMode dm;

	if (telaCheia) {
		SDL_GetCurrentDisplayMode(0, &dm);
		largJanela = dm.w;
		alturaJanela = dm.h;
	}
	janela = SDL_CreateWindow("Jump King", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largJanela, alturaJanela, NULL);
	if (janela) { std::cout << "Janela Criada!\n"; }

	renderer = SDL_CreateRenderer(janela, -1, 0);
	if (renderer) { std::cout << "Renderer Criado!\n"; }

	dimensoesJanela.x = largJanela;
	dimensoesJanela.y = alturaJanela;

	menu.start.init();
	menu.leaderboard.init();
	menu.level.init();
	menu.pause.init();
	menu.settings.init();
	mainMenu();
}

void Jogo::mainMenu() {

	// algum loop while enquanto nao houver nenhum clique
	menu.start.reset();
	int click = menu.start.update();
	
	while (click == NO_BUTTON_CLICKED) {
		SDL_RenderClear(renderer);
		SDL_PollEvent(&evento);
		menu.start.render();
		SDL_RenderPresent(renderer);
		click = menu.start.update();
	}

	switch (click) { //apos algum clique
	case BUTTON_START:
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

	// algum loop while enquanto nao houver nenhum clique
	menu.pause.reset();
	int click = menu.pause.update();

	while (click == NO_BUTTON_CLICKED) {
		SDL_RenderClear(renderer);
		SDL_PollEvent(&evento);
		menu.pause.render();
		SDL_RenderPresent(renderer);
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
		SDL_RenderClear(renderer);
		SDL_PollEvent(&evento);
		menu.settings.render();
		SDL_RenderPresent(renderer);
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
		SDL_RenderClear(renderer);
		SDL_PollEvent(&evento);
		menu.leaderboard.render();
		SDL_RenderPresent(renderer);
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

	// algum loop while enquanto nao houver nenhum clique
	menu.level.reset();
	int click = menu.level.update();

	while (click == NO_BUTTON_CLICKED) {
		SDL_RenderClear(renderer);
		SDL_PollEvent(&evento);
		menu.level.render();
		SDL_RenderPresent(renderer);
		click = menu.level.update();
	}

	switch (click) { //apos algum clique
	case BUTTON_START:
		fase->inicializar();
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
	SDL_RenderClear(renderer);

	fase->render();

	SDL_RenderPresent(renderer);
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

Vector2D Jogo::getDimensoesJanela() {
	return dimensoesJanela;
}

