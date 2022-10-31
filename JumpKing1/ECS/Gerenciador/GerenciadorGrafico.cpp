#include "../../Jogo/Jogo.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* GerenciadorGrafico::tileset = nullptr;
SDL_Texture* GerenciadorGrafico::tilesetHitbox = nullptr;
SDL_Renderer* GerenciadorGrafico::renderer = nullptr;

GerenciadorGrafico::GerenciadorGrafico() {
}

GerenciadorGrafico::~GerenciadorGrafico() {
	SDL_DestroyTexture(tileset);
	SDL_DestroyTexture(tilesetHitbox);
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

void GerenciadorGrafico::renderTile(SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(renderer, tileset, &fonte, &destino);
}

void GerenciadorGrafico::renderHitbox(SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(renderer, tilesetHitbox, &fonte, &destino);
}