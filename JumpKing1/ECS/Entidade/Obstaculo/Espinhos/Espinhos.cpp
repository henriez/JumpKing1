#include "Espinhos.h"
#include "../../../Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../../Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"

Espinhos::Espinhos() {
	addComponente<ComponenteColisao>();
	fonte = { 0,0,32,32 };
	destino = { 0,0,32,32 };
	onScreen = false;
	corte = rand()%2 + 1;
}

Espinhos::Espinhos(int x, int y, int w, int h, int tam) {
	addComponente<ComponenteColisao>();
	getComponente<ComponenteColisao>()->set(x, y, w, h);
	corte = tam;

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
	dest.x = destino.x - GerenciadorDeCamera::getInstance()->camera.x;
	dest.y = destino.y - GerenciadorDeCamera::getInstance()->camera.y;
	graphics->renderEspinho(fonte, dest);
}

void Espinhos::renderHitbox() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - GerenciadorDeCamera::getInstance()->camera.x;
	tempDest.y = destino.y - GerenciadorDeCamera::getInstance()->camera.y;
	graphics->renderHitbox(fonte, tempDest);
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

void Espinhos::impedir(Jogador* jogador) {
	if (isOnScreen()) {
		SDL_Rect initialhitbox = jogador->getComponente<ComponenteColisao>()->getColisor();
		SDL_Rect hitbox = initialhitbox;

		ComponenteTransform* transform = jogador->getComponente<ComponenteTransform>();
		Vector2D velocity = transform->velocidade;

		hitbox = initialhitbox;
		hitbox.x += velocity.x * jogador->getSpeed();
		SDL_Rect colisor = getComponente<ComponenteColisao>()->getColisor();

		if (GerenciadorDeColisao::getInstance()->AABB(colisor, hitbox)) {
			if (velocity.y > 0) { //colidiu por cima
				transform->posicao.y = colisor.y - hitbox.h;
				transform->velocidade.y = -1.4;
			}
			jogador->damage(corte);
			return;
		}
		hitbox = initialhitbox;
		hitbox.x += velocity.x * jogador->getSpeed();
		if (GerenciadorDeColisao::getInstance()->AABB(colisor, hitbox)) {
			if (velocity.x > 0) { //colidiu pela esquerda
				transform->posicao.x = colisor.x - hitbox.w;
				transform->velocidade.x = -1;
			}
			else if (velocity.x < 0) { //colidiu pela direita
				transform->posicao.x = colisor.x + colisor.w;
				transform->velocidade.x = 1;
			}
			jogador->damage(corte);
		}


	}
}