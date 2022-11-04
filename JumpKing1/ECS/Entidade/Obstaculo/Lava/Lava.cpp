#include "Lava.h"
#include "../../../Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../../Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"

Lava::Lava() {
	fonte = { 0,0,32,32 };
	destino = { 0,0,32,32 };
	onScreen = false;
}

Lava::~Lava() {}

void Lava::render() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - GerenciadorDeCamera::camera.x;
	tempDest.y = destino.y - GerenciadorDeCamera::camera.y;
	GerenciadorGrafico::renderTile(fonte, tempDest);
}

void Lava::renderHitbox() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - GerenciadorDeCamera::camera.x;
	tempDest.y = destino.y - GerenciadorDeCamera::camera.y;
	GerenciadorGrafico::renderHitbox(fonte, tempDest);
}


void Lava::setPosition(int x, int y, int srcX, int srcY) {
	destino.x = x;
	destino.y = y;
	fonte.x = srcX;
	fonte.y = srcY;
}

SDL_Rect Lava::getPos() const {
	return destino;
}

void Lava::setScreen(const bool inScreen) {
	onScreen = inScreen;
}

bool Lava::isOnScreen() const {
	return onScreen;
}

void Lava::atualizar() {}