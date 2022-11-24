#include "Tile.h"
#include "../../../Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../../Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"

#include <SDL_image.h>
#include <SDL.h>

Tile::Tile() {
	fonte = { 0,0,32,32 };
	destino = { 0,0,32,32 };
	onScreen = false;
	colide = false;
}

Tile::~Tile() {}

void Tile::render() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - GerenciadorDeCamera::getInstance()->camera.x;
	tempDest.y = destino.y - GerenciadorDeCamera::getInstance()->camera.y;
	graphics->renderTile(fonte, tempDest);
}

void Tile::renderHitbox() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - GerenciadorDeCamera::getInstance()->camera.x;
	tempDest.y = destino.y - GerenciadorDeCamera::getInstance()->camera.y;
	graphics->renderHitbox(fonte, tempDest);
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

void Tile::atualizar() {}

void Tile::impedir(Jogador* jogador) {
	if (colide) {
		SDL_Rect initialhitbox = jogador->getComponente<ComponenteColisao>()->getColisor();
		SDL_Rect hitbox = initialhitbox;

		ComponenteTransform* transform = jogador->getComponente<ComponenteTransform>();
		Vector2D velocity = transform->velocidade;

		hitbox = initialhitbox;
		hitbox.x += velocity.x * jogador->getSpeed();
		if (GerenciadorDeColisao::getInstance()->AABB(getPos(), hitbox)) {
			if (velocity.x > 0) { //colidiu pela esquerda
				transform->posicao.x = getPos().x - hitbox.w;
			}
			else if (velocity.x < 0) //colidiu pela direita
				transform->posicao.x = getPos().x + hitbox.w;
			transform->velocidade.x = 0;
		}

		hitbox = initialhitbox;
		hitbox.y += velocity.y * jogador->getSpeed();
		if (GerenciadorDeColisao::getInstance()->AABB(getPos(), hitbox)) {
			if (velocity.y > 0) { //colidiu por cima
				jogador->setGround(true);
				transform->posicao.y = getPos().y - hitbox.h;
			}
			else if (velocity.y < 0) //colidiu por baixo
				transform->posicao.y = getPos().y + hitbox.h;
			transform->velocidade.y = 0;
		}
	}


}