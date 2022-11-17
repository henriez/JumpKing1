#include <cstdlib>
#include "Goblin.h"
#include "../../Jogo/Fase/Mapa/Mapa.h"
#include "../../Jogo/Fase/Mapa/TileMap/TileMap.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"

#define SCALE 1.3
#define ATTACKING 0
#define DYING 1
#define WALKING 2
#define IDLE 3
#define HIT 4

Goblin::Goblin(float x, float y) {
	sprite = { 0, 150 * WALKING, 150, 150 }; // w = 42 h = 49
	flip = false;
	speed = 1;
	state = WALKING;

	addComponente<ComponenteColisao>();
	getComponente<ComponenteSaude>()->init(3);
	addComponente<ComponenteTransform>();
	addComponente<ComponenteSprite>();
	getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Goblin.png");

	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 2 * (rand() & 0x01) - 1;
	transform->velocidade.y = 0;
	transform->posicao.x = x;
	transform->posicao.y = y;

	getComponente<ComponenteColisao>()->set(transform->posicao.x, transform->posicao.y, 24 * SCALE, 35 * SCALE);
	GerenciadorDeColisao::iniciaInimigo(this);
}

Goblin::~Goblin() {}

void Goblin::atualizar() {
	if (isAlive()) {
		ComponenteTransform* transform = getComponente<ComponenteTransform>();
		transform->posicao.x += transform->velocidade.x * speed;
		getComponente<ComponenteColisao>()->setPos(transform->posicao.x, transform->posicao.y);
		GerenciadorDeColisao::colisao_inimigo(this);

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

void Goblin::render() {
	int frames;
	unsigned int fSpeed;
	static int frameNumber = 0;

	if (getComponente<ComponenteTransform>()->velocidade.x < 0) { flip = true; }
	else if (getComponente<ComponenteTransform>()->velocidade.x > 0) { flip = false; }
	SDL_Rect posRect = { 0, 0, sprite.w * SCALE, sprite.h * SCALE };
	posRect.x = (int)getComponente<ComponenteTransform>()->posicao.x - GerenciadorDeCamera::camera.x - (66 * SCALE);
	posRect.y = (int)getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::camera.y - (64 * SCALE);
	//if (flip) { posRect.x -= 4 * SCALE; }

	if (isAlive()) {
		sprite.y = 150 * state;
		frames = 8;
		fSpeed = 120;

		if (state == ATTACKING) {
			frames = 8;
			fSpeed = 10;
			int frameVal = static_cast<int>((frameNumber / fSpeed) % frames);
			sprite.x = 150 * frameVal;
			frameNumber++;
			if (frameVal == 7) { GerenciadorDeColisao::ataqueGoblin(this); }
			if (frameNumber >= frames * static_cast<int>(fSpeed)) { setState(WALKING); frameNumber = 0; }
		}
		else if (state == HIT) {
			frames = 4;
			fSpeed = 15;
			int frameVal = static_cast<int>((frameNumber / fSpeed) % frames);
			sprite.x = 150 * frameVal;
			frameNumber++;
			if ((frameNumber > frames * fSpeed) && vulnerable == true) { setState(WALKING); frameNumber = 0; }
		}
		else {
			sprite.x = 150 * static_cast<int>((SDL_GetTicks() / fSpeed) % frames);
		}

		getComponente<ComponenteSprite>()->render(posRect, sprite, flip);
		//SDL_Rect tst = getComponente<ComponenteColisao>()->getColisor();
		//tst.x -= GerenciadorDeCamera::camera.x;
		//tst.y -= GerenciadorDeCamera::camera.y;
		//graphics->renderInimigoHitbox(tst);
	}
	else {
		if (state != DYING && state != IDLE) {
			sprite.y = 150 * DYING;
			frames = 4;
			fSpeed = 10;
			int frameVal = static_cast<int>((frameNumber / fSpeed) % frames);
			sprite.x = 150 * frameVal;
			frameNumber++;
			if (frameNumber >= frames * fSpeed) { setState(DYING); }
			getComponente<ComponenteSprite>()->render(posRect, sprite, flip);
		}
	}
}
