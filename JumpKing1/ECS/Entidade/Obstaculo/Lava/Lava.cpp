#include "Lava.h"
#include "../../../Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../../Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"

Lava::Lava() {
	addComponente<ComponenteColisao>();
	fonte = { 0,0,32,64 };
	destino = { 0,0,32,64 };
	onScreen = false;
	temperatura = 0;
}

Lava::Lava(int x, int y, int w, int h, int temp) {
	addComponente<ComponenteColisao>();
	getComponente<ComponenteColisao>()->set(x, y, w, h);
	temperatura = temp;

	fonte = { 0,0,32,64 };
	destino = { 0,0,32,64 };
	onScreen = false;
}

Lava::~Lava() {}

void Lava::render() {
	SDL_Rect colisor = getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect destino = { colisor.x, colisor.y - 32,32,64 };//tamanho da textura

	SDL_Rect dest = { 0,0,32,64 };
	dest.x = destino.x - GerenciadorDeCamera::getInstance()->camera.x;
	dest.y = destino.y - GerenciadorDeCamera::getInstance()->camera.y;
	graphics->renderLava(fonte, dest);

}

void Lava::renderHitbox() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - GerenciadorDeCamera::getInstance()->camera.x;
	tempDest.y = destino.y - GerenciadorDeCamera::getInstance()->camera.y;
	graphics->renderHitbox(fonte, tempDest);
}


SDL_Rect Lava::getPos() const {
	return destino;
}

void Lava::atualizar() {}

void Lava::impedir(Jogador* jogador) {
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
			jogador->damage(temperatura);
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
			jogador->damage(temperatura);
		}


	}
}