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
	agressividade = rand() % 2 + 1;
	sprite = { 0, 64 * WALKING, 64, 64 }; // w = 42 h = 49
	flip = false;
	speed = 1;
	state = WALKING;

	addComponente<ComponenteColisao>();
	getComponente<ComponenteSaude>()->init(3);
	addComponente<ComponenteTransform>();
	addComponente<ComponenteSprite>();
	getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Skeleton.png");

	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 2 * (rand() & 0x01) - 1;
	transform->velocidade.y = 0;
	transform->posicao.x = x;
	transform->posicao.y = y;

	getComponente<ComponenteColisao>()->set(transform->posicao.x, transform->posicao.y, 21 * SCALE, 31 * SCALE);
	GerenciadorDeColisao::iniciaInimigo(this);
}

Esqueleto::~Esqueleto() {}

void Esqueleto::atualizar() {
	if (isAlive()) {
		ComponenteTransform* transform = getComponente<ComponenteTransform>();
		transform->posicao.x += transform->velocidade.x * speed;
		getComponente<ComponenteColisao>()->setPos(transform->posicao.x, transform->posicao.y);
		GerenciadorDeColisao::colisao_inimigo_obstaculos(this);
		GerenciadorDeColisao::colisao_inimigo_projeteis(this);

		if (!vulnerable) {
			transform->velocidade.x = 0;
			setState(HIT);
			if (SDL_GetTicks() - vulnerable_timer > 1000) { //dano a cada 1 segundo
				vulnerable = true;
			}
		}

		if (state == WALKING) {
			if (haveTarget()) {
				if (abs(getDistance()) > Mapa::tamanhoTile()) {
					setState(WALKING);
					transform->velocidade.x = 1;
					if ((getDistance() < 0 && transform->velocidade.x > 0) || getDistance() > 0 && transform->velocidade.x < 0) {
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
	}
}

void Esqueleto::render() {
	int frames;
	unsigned int fSpeed;
	static int frameNumber = 0;

	if (getComponente<ComponenteTransform>()->velocidade.x < 0) { flip = true; }
	else if (getComponente<ComponenteTransform>()->velocidade.x > 0) { flip = false; }
	SDL_Rect posRect = { 0, 0, sprite.w * SCALE, sprite.h * SCALE };
	posRect.x = (int)getComponente<ComponenteTransform>()->posicao.x - GerenciadorDeCamera::camera.x - (19 * SCALE);
	posRect.y = (int)getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::camera.y - (17 * SCALE);
	if (flip) { posRect.x -= 4 * SCALE; }

	if (isAlive()) {
		sprite.y = 64 * state;
		frames = 12;
		fSpeed = 90;

		if (state == ATTACKING) {
			frames = 13;
			fSpeed = 10;
			int frameVal = static_cast<int>((frameNumber / fSpeed) % frames);
			sprite.x = 64 * frameVal;
			frameNumber++;
			if (frameVal == 4 || frameVal == 8) { GerenciadorDeColisao::ataqueEsqueleto(this); }
			if (frameNumber >= frames * static_cast<int>(fSpeed)) { setState(WALKING); frameNumber = 0; }
		}
		else if (state == HIT) {
			frames = 3;
			fSpeed = 25;
			int frameVal = static_cast<int>((frameNumber / fSpeed) % frames);
			sprite.x = 64 * frameVal;
			frameNumber++;
			if ((frameNumber > frames * fSpeed) && vulnerable == true) { setState(WALKING); frameNumber = 0; }
		}
		else {
			sprite.x = 64 * static_cast<int>((SDL_GetTicks() / fSpeed) % frames);
		}

		getComponente<ComponenteSprite>()->render(posRect, sprite, flip);
	}
	else {
		if (state != DYING) {
			sprite.y = 64 * DYING;
			frames = 13;
			fSpeed = 9;
			int frameVal = static_cast<int>((frameNumber / fSpeed) % frames);
			sprite.x = 64 * frameVal;
			frameNumber++;
			if (frameNumber >= frames * fSpeed) { setState(DYING); }
			getComponente<ComponenteSprite>()->render(posRect, sprite, flip);
		}
	}
}

int Esqueleto::attack() {
	return agressividade;
}