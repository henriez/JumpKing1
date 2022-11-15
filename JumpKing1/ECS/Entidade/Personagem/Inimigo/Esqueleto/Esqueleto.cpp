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

Esqueleto::Esqueleto(float x, float y) {
	sprite = { 4, 64 * WALKING + 16, 39, 33 }; // w = 42 h = 49
	flip = false;
	speed = 1;
	fSpeed = 90;
	state = WALKING;
	distance = 0;
	haveTarget = false;

	addComponente<ComponenteColisao>();
	getComponente<ComponenteSaude>()->init(1);
	addComponente<ComponenteTransform>();
	addComponente<ComponenteSprite>();
	getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Skeleton.png");

	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 2 * (rand() & 0x01) - 1;
	transform->velocidade.y = 0;
	transform->posicao.x = x;
	transform->posicao.y = y;

	getComponente<ComponenteColisao>()->set(transform->posicao.x, transform->posicao.y, sprite.w * SCALE, (sprite.h - 1) * SCALE);
	GerenciadorDeColisao::iniciaInimigo(this);
	std::cout << getPlatform().x << " " << getPlatform().y << " " << getPlatform().w << " " << getPlatform().h << std::endl;
}

Esqueleto::~Esqueleto() {}

void Esqueleto::atualizar() {
	if (!vulnerable) {
		if (SDL_GetTicks() - vulnerable_timer > 1000) //dano a cada 1 segundo
			vulnerable = true;
	}
	ComponenteTransform* transform = getComponente<ComponenteTransform>();

	transform->posicao.x += transform->velocidade.x * speed;
	getComponente<ComponenteColisao>()->setPos(transform->posicao.x, transform->posicao.y);
	GerenciadorDeColisao::colisao_esqueleto(this);
	

	// TODO: Mudar hitboxes para encaixar na animacao
	if (haveTarget) {
		if (abs(distance) > Mapa::tamanhoTile()) {
			setState(WALKING);
			transform->velocidade.x = 1;
			if ((distance < 0 && transform->velocidade.x > 0) || distance > 0 && transform->velocidade.x < 0) {
				transform->velocidade.x = transform->velocidade.x * -1;
			}
		}
		else {
			// Ataca
			setState(ATTACKING);
			transform->velocidade.x = 0;
		}
	}
	else {
		setState(WALKING);
		if (!transform->velocidade.x) {
			if (flip) { transform->velocidade.x = -1; }
			else { transform->velocidade.x = 1; }
		}
	}

	SDL_Rect hitbox = getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect plat = getPlatform();
	if ((transform->posicao.x <= plat.x && transform->velocidade.x < 0) ||
		(transform->posicao.x + hitbox.w >= plat.x + plat.w && transform->velocidade.x > 0)) {
		transform->velocidade.x = transform->velocidade.x * -1;
	}

}

void Esqueleto::render() {
	if (isAlive()) {
		if (getComponente<ComponenteTransform>()->velocidade.x < 0) { flip = true; }
		else if (getComponente<ComponenteTransform>()->velocidade.x > 0) { flip = false; }


		// TODO:
		// Dar prioridade a animações de tomar dano e morrer
		// Bug ao usar SDL_GetTicks(), animação começa de ponto aleatório
		// Executar animação até o fim, podendo ser cancelada por outra animção

		unsigned char frames = 1;
		switch (state) {
		case ATTACKING:
			sprite.y = 0;
			frames = 13;
			fSpeed = 150;
			break;
		case WALKING:
			sprite.y = 64 * WALKING + 16;
			sprite.w = 39;
			sprite.h = 33;
			frames = 12;
			fSpeed = 90;
			break;
		default:
			break;
		}
		SDL_Rect posRect = { 0, 0, sprite.w * SCALE, sprite.h * SCALE };
		posRect.x = (int)getComponente<ComponenteTransform>()->posicao.x - GerenciadorDeCamera::camera.x;
		posRect.y = (int)getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::camera.y;
		sprite.x = 64 * static_cast<int>((SDL_GetTicks() / fSpeed) % frames);
		getComponente<ComponenteSprite>()->render(posRect, sprite, flip);
		//graphics->renderInimigoHitbox(posRect);
	}
}