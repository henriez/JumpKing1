#include "Espinhos.h"
#include "../../../Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../../Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"

Espinhos::Espinhos() {
	fonte = { 0,0,32,32 };
	destino = { 0,0,32,32 };
	onScreen = false;
}

Espinhos::~Espinhos() {}

void Espinhos::render() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - GerenciadorDeCamera::camera.x;
	tempDest.y = destino.y - GerenciadorDeCamera::camera.y;
	GerenciadorGrafico::renderTile(fonte, tempDest);
}

void Espinhos::renderHitbox() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - GerenciadorDeCamera::camera.x;
	tempDest.y = destino.y - GerenciadorDeCamera::camera.y;
	GerenciadorGrafico::renderHitbox(fonte, tempDest);
}


void Espinhos::setPosition(int x, int y, int srcX, int srcY) {
	destino.x = x;
	destino.y = y;
	fonte.x = srcX;
	fonte.y = srcY;
}

SDL_Rect Espinhos::getPos() const {
	return destino;
}

void Espinhos::setScreen(const bool inScreen) {
	onScreen = inScreen;
}

bool Espinhos::isOnScreen() const {
	return onScreen;
}

void Espinhos::atualizar() {}