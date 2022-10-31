#include "GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"
#include <SDL_image.h>
#include <iostream>
#include "../../Menu/LeaderboardMenu/LeaderboardMenu.h"
#include "../../Menu/LevelMenu/LevelMenu.h"
#include "../../Menu/MainMenu/MainMenu.h"
#include "../../Menu/PauseMenu/PauseMenu.h"
#include "../../Menu/SettingsMenu/SettingsMenu.h"
#include "../../Jogo/Fase/Fase.h"

SDL_Texture* GerenciadorGrafico::tileset = nullptr;
SDL_Texture* GerenciadorGrafico::tilesetHitbox = nullptr;
SDL_Renderer* GerenciadorGrafico::renderer = nullptr;
SDL_Window* GerenciadorGrafico::window = nullptr;

GerenciadorGrafico::GerenciadorGrafico() {
}

GerenciadorGrafico::~GerenciadorGrafico() {
	SDL_DestroyTexture(tileset);
	SDL_DestroyTexture(tilesetHitbox);
}

void GerenciadorGrafico::init(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	SDL_DisplayMode dm;

	if (telaCheia) {
		SDL_GetCurrentDisplayMode(0, &dm);
		largJanela = dm.w;
		alturaJanela = dm.h;
	}
	window = SDL_CreateWindow("Jump King", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largJanela, alturaJanela, NULL);
	if (!window) std::cout << "Failed Creating Window! Error:" << SDL_GetError();

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) { std::cout << "Failed Creating Renderer! Error:" << SDL_GetError(); }
}

void GerenciadorGrafico::init_tileMap() {
	tilesetHitbox = IMG_LoadTexture(renderer, "Assets/TileMap/hitboxes colisao.png");
	tileset = IMG_LoadTexture(renderer, "Assets/TileMap/Tiles.png");
}

void GerenciadorGrafico::setRenderer(SDL_Renderer* rend) {
	renderer = rend;
}

SDL_Texture* GerenciadorGrafico::CarregaTextura(const char* fileName){
	SDL_Texture* tex = IMG_LoadTexture(renderer, fileName);
	if (!tex)
		std::cout << SDL_GetError() << std::endl;

	return tex;
}

void GerenciadorGrafico::Desenhe(SDL_Texture* tex, SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(renderer, tex, &fonte, &destino);
}

void GerenciadorGrafico::renderFase(Fase* fase) {
	SDL_RenderClear(renderer);

	fase->render();

	SDL_RenderPresent(renderer);
}

void GerenciadorGrafico::renderTile(SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(renderer, tileset, &fonte, &destino);
}

void GerenciadorGrafico::renderHitbox(SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(renderer, tilesetHitbox, &fonte, &destino);
}

void GerenciadorGrafico::renderMenu(LeaderboardMenu& leaderboard) {
	SDL_RenderClear(renderer);
	SDL_PollEvent(&Jogo::evento);
	leaderboard.render();
	SDL_RenderPresent(renderer);
}

void GerenciadorGrafico::renderMenu(LevelMenu& level) {
	SDL_RenderClear(renderer);
	SDL_PollEvent(&Jogo::evento);
	level.render();
	SDL_RenderPresent(renderer);
}

void GerenciadorGrafico::renderMenu(MainMenu& start) {
	SDL_RenderClear(renderer);
	SDL_PollEvent(&Jogo::evento);
	start.render();
	SDL_RenderPresent(renderer);
}

void GerenciadorGrafico::renderMenu(PauseMenu& pause) {
	SDL_RenderClear(renderer);
	SDL_PollEvent(&Jogo::evento);
	pause.render();
	SDL_RenderPresent(renderer);
}

void GerenciadorGrafico::renderMenu(SettingsMenu& settings) {
	SDL_RenderClear(renderer);
	SDL_PollEvent(&Jogo::evento);
	settings.render();
	SDL_RenderPresent(renderer);
}