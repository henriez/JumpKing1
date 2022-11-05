#include "Espinhos.h"
#include "../../../Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../../Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"

Espinhos::Espinhos() {
	addComponente<ComponenteColisao>();
	fonte = { 0,0,32,32 };
	destino = { 0,0,32,32 };
	onScreen = false;
}

Espinhos::~Espinhos() {}

void Espinhos::render() {
	SDL_Rect colisor = getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect destino = { colisor.x, colisor.y -16,32,32 };//tamanho da textura
	//REDEFINIR RENDER PARA ESPINHO E LAVA
	SDL_Rect dest = {0,0,32,32};
	dest.x = destino.x - GerenciadorDeCamera::camera.x;
	dest.y = destino.y - GerenciadorDeCamera::camera.y;
	GerenciadorGrafico::renderEspinho(fonte, dest);
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

void Espinhos::atualizar() {}