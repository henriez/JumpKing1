#include <cstdlib>
#include "Esqueleto.h"
#include "../../Jogo/Fase/Mapa/Mapa.h"
#include "../../Jogo/Fase/Mapa/TileMap/TileMap.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"

#define SCALE 1.5
#define ATTACKING 0
#define DYING 1
#define WALKING 2
#define IDLE 3
#define HIT 4

Esqueleto::Esqueleto() : speed(1), maxSpeed(4), fSpeed(90) {
	sprite = { 0, 64 * WALKING, 42, 49 };
	flip = false;
	onGround = false;

	addComponente<ComponenteColisao>();
	addComponente<ComponenteSaude>();
	addComponente<ComponenteTransform>();
	addComponente<ComponenteSprite>();
	getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Skeleton.png");

	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 2 * (rand() & 0x01) - 1;
	transform->velocidade.y = 0;
	transform->posicao.x = 0;
	transform->posicao.y = 0;

	getComponente<ComponenteColisao>()->set(transform->posicao.x, transform->posicao.y, sprite.w * SCALE, (sprite.h - 1) * SCALE);
	if (transform->velocidade.x == -1) { flip = true; }
}

Esqueleto::~Esqueleto() {}

void Esqueleto::setGround(const bool inGround) {
	onGround = inGround;
}

bool Esqueleto::inGround() const {
	return onGround;
}

void Esqueleto::atualizar() {
	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	getComponente<ComponenteColisao>()->setPos(transform->posicao.x, transform->posicao.y);

	transform->posicao.x += transform->velocidade.x * speed;
	transform->posicao.y += transform->velocidade.y * speed;
	if (transform->velocidade.y < -maxSpeed) transform->velocidade.y = -maxSpeed;
	else if (transform->velocidade.y > maxSpeed) transform->velocidade.y = maxSpeed;
	GerenciadorDeColisao::colisao_inimigo1(this);
	// if (collide || end platform) { side = false; switch direction;}

}

void Esqueleto::render() {
	if (getComponente<ComponenteTransform>()->velocidade.x == -1) { flip = true; }
	else { flip = false; }
	SDL_Rect posRect = { 0, 0, sprite.w * SCALE, sprite.h * SCALE };
	posRect.x = (int)getComponente<ComponenteTransform>()->posicao.x - GerenciadorDeCamera::camera.x;
	posRect.y = (int)getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::camera.y;
	sprite.x = 64 * static_cast<int>((SDL_GetTicks() / fSpeed) % 12);
	getComponente<ComponenteSprite>()->render(posRect, sprite, flip);
}