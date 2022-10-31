#include "Tile.h"
#include "../../../Gerenciador/GerenciadorGrafico.h"
#include "../../../Gerenciador/GerenciadorDeCamera.h"

#include <SDL_image.h>
#include <SDL.h>

Tile::Tile() {
	fonte = { 0,0,32,32 };
	destino = { 0,0,32,32 };
	onScreen = false;
}

Tile::~Tile() {}

void Tile::render() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - GerenciadorDeCamera::camera.x;
	tempDest.y = destino.y - GerenciadorDeCamera::camera.y;
	GerenciadorGrafico::renderTile(fonte, tempDest);
}

void Tile::renderHitbox() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - GerenciadorDeCamera::camera.x;
	tempDest.y = destino.y - GerenciadorDeCamera::camera.y;
	GerenciadorGrafico::renderHitbox(fonte, tempDest);
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