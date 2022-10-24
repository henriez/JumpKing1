#include "Jogo.h"
#include <iostream>
#include "Fase/Fase.h"

SDL_Renderer* Jogo::renderer;
SDL_Event Jogo::evento;
SDL_Window* Jogo::janela;
Vector2D Jogo::dimensoesJanela;

Jogo::Jogo(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	rodando = true;
	fase = new Fase;
	inicializar(nomeJanela, largJanela, alturaJanela, telaCheia);
}

Jogo::~Jogo() {
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
	SDL_SetWindowResizable(janela, SDL_TRUE);
	if (janela) { std::cout << "Janela Criada!\n"; }

	renderer = SDL_CreateRenderer(janela, -1, 0);
	if (renderer) { std::cout << "Renderer Criado!\n"; }

	dimensoesJanela.x = largJanela;
	dimensoesJanela.y = alturaJanela;

	mMenu.init();
	menu();
}

void Jogo::menu() {

	// algum loop while enquanto nao houver nenhum clique
	int click = mMenu.click();
	
	while (click == 0) {
		SDL_RenderClear(renderer);
		analisaEventos();
		mMenu.update();
		mMenu.render();
		SDL_RenderPresent(renderer);
		click = mMenu.click();
	}

	switch (click) { //apos algum clique
	case BUTTON_START:
		fase->inicializar(this);
		break;
	case BUTTON_RESUME:
		fase->atualizar();
		break;
	case BUTTON_SETTINGS:
		//SETTINGS
		break;
	case BUTTON_QUIT:
		rodando = false;
		break;
	default:
		break;
	}

}

void Jogo::atualizar() {
	analisaEventos();

	fase->atualizar();

	render();
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
			menu();
												  //rodando = false;
}

bool Jogo::executando() {
	return rodando;
}

Vector2D Jogo::getDimensoesJanela() {
	return dimensoesJanela;
}

