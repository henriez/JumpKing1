#include "Tile.h"
#include "../../../Jogo.h"
#include "../../../../ECS/Gerenciador/GerenciadorDeTexturas.h"
#include "../Mapa.h"

#include <SDL_image.h>
#include <SDL.h>

SDL_Texture* Tile::tileset;
SDL_Texture* Tile::tilesetHitbox;

Tile::Tile() {
	fonte = { 0,0,32,32 };
	destino = { 0,0,32,32 };
	onScreen = false;
}

Tile::~Tile() {}

void Tile::render() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - Mapa::camera.x;
	tempDest.y = destino.y - Mapa::camera.y;
	GerenciadorDeTexturas::Desenhe(Tile::tileset, fonte, tempDest);
}

void Tile::renderHitbox() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - Mapa::camera.x;
	tempDest.y = destino.y - Mapa::camera.y;
	GerenciadorDeTexturas::Desenhe(Tile::tilesetHitbox, fonte, tempDest);
}

void Tile::setTex(const char* path, const char* hitboxPath) {
	tileset = GerenciadorDeTexturas::CarregaTextura(path);
	tilesetHitbox = GerenciadorDeTexturas::CarregaTextura(hitboxPath);
}

void Tile::setPosition(int x, int y, int srcX, int srcY) {
	destino.x = x;
	destino.y = y;
	fonte.x = srcX;
	fonte.y = srcY;
}

SDL_Rect Tile::getPos() const {
	return destino;
}

void Tile::setScreen(const bool inScreen) {
	onScreen = inScreen;
}

bool Tile::isOnScreen() const {
	return onScreen;
}

void Tile::atualizar() {}