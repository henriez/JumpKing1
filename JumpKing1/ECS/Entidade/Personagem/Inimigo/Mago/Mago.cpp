#include "Mago.h"
#include <cstdlib>
#include "../../Jogo/Fase/Mapa/Mapa.h"
#include "../../Jogo/Fase/Mapa/TileMap/TileMap.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include "../../../Projetil/Projetil.h"

#define SCALE 1.3
#define ATTACKING 0
#define DYING 1
#define WALKING 2
#define IDLE 3
#define HIT 4

Mago::Mago(float x, float y) {
	sabedoria = rand() % 2 + 1;
	sprite = { 0, 0, 150, 150 }; 
	flip = false;
	speed = 1;
	

	addComponente<ComponenteColisao>();
	getComponente<ComponenteSaude>()->init(3);
	addComponente<ComponenteTransform>();
	addComponente<ComponenteSprite>();
	setState(WALKING);

	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 2 * (rand() & 0x01) - 1;
	transform->velocidade.y = 0;
	transform->posicao.x = x;
	transform->posicao.y = y;

	getComponente<ComponenteColisao>()->set(transform->posicao.x + 40, transform->posicao.y, 70, 150);
	GerenciadorDeColisao::getInstance()->iniciaInimigo(this);
}

Mago::~Mago() {}

void Mago::atualizar() {
	if (isAlive()) {
		ComponenteTransform* transform = getComponente<ComponenteTransform>();
		transform->posicao.x += transform->velocidade.x * speed;
		getComponente<ComponenteColisao>()->setPos(transform->posicao.x + 40, transform->posicao.y);
		GerenciadorDeColisao::getInstance()->colisao_inimigo_obstaculos(this);

		if (!vulnerable) {
			transform->velocidade.x = 0;
			setState(HIT);
			if (SDL_GetTicks() - vulnerable_timer > 1000) { //dano a cada 1 segundo
				vulnerable = true;
			}
		}

		if (state == WALKING) {
			if (haveTarget()) {
				if (abs(getDistance()) > 20*Mapa::tamanhoTile()) {
					setState(WALKING);
					transform->velocidade.x = 1;
					if ((getDistance() < 0 && transform->velocidade.x > 0) || getDistance() > 0 && transform->velocidade.x < 0) {
						transform->velocidade.x *= -1;
					}
				}
				else {
					// Ataca
					setState(ATTACKING);
					transform->velocidade.x = 0;
					flip = (getDistance() < 0) ? true : false;
					
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
			if ((hitbox.x <= plat.x && transform->velocidade.x < 0) ||
				(hitbox.x + hitbox.w >= plat.x + plat.w && transform->velocidade.x > 0)) {
				transform->velocidade.x = transform->velocidade.x * -1;
			}
		}
	}
}

void Mago::render() {
	int frames;
	unsigned int fSpeed;
	static int frameNumber = 0;

	if (getComponente<ComponenteTransform>()->velocidade.x < 0) { flip = true; }
	else if (getComponente<ComponenteTransform>()->velocidade.x > 0) { flip = false; }
	SDL_Rect posRect = { 0, 0, sprite.w * SCALE, sprite.h * SCALE };
	posRect.x = (int)getComponente<ComponenteTransform>()->posicao.x - GerenciadorDeCamera::getInstance()->camera.x;
	posRect.y = (int)getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::getInstance()->camera.y;
	//if (flip) { posRect.x -= 4 * SCALE; }

	if (isAlive()) {
		frames = 8;
		fSpeed = 120;

		if (state == ATTACKING) {
			if (getDistance() < 0) flip = true;
			frames = 8;
			fSpeed = 10;
			int frameVal = static_cast<int>((frameNumber / fSpeed) % frames);
			sprite.x = 150 * frameVal;
			frameNumber++;
			if (frameVal == 7) { shoot(); }
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
	}
	else {
		if (state != DYING && state != IDLE) {
			setState(DYING);
			frames = 5;
			fSpeed = 10;
			int frameVal = static_cast<int>((frameNumber / fSpeed) % frames);
			sprite.x = 150 * frameVal;
			frameNumber++;
			if (frameNumber >= frames * fSpeed) { setState(DYING); }
			getComponente<ComponenteSprite>()->render(posRect, sprite, flip);
		}
	}
}

void Mago::shoot() {
	Projetil* proj = new Projetil;
	proj->getComponente<ComponenteTransform>()->posicao.x = getComponente<ComponenteTransform>()->posicao.x;
	proj->getComponente<ComponenteTransform>()->posicao.y = getComponente<ComponenteTransform>()->posicao.y + 50;
	if (flip) { proj->getComponente<ComponenteTransform>()->velocidade.x = -3; }
	else { proj->getComponente<ComponenteTransform>()->velocidade.x = 3; }

	GerenciadorDeColisao::getInstance()->addProjetil(proj);
}

int Mago::attack() {
	return sabedoria;
}

void Mago::setState(unsigned char val) {
	state = val; 
	switch (state) {
	case WALKING:
		delete getComponente<ComponenteSprite>();
		addComponente<ComponenteSprite>();
		getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Mago/Sprites/Move.png");
		break;
	case IDLE:
		delete getComponente<ComponenteSprite>();
		addComponente<ComponenteSprite>();
		getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Mago/Sprites/Idle.png");
		break;
	case HIT: 
		delete getComponente<ComponenteSprite>();
		addComponente<ComponenteSprite>();
		getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Mago/Sprites/Take Hit.png");
		break;
	case ATTACKING:
		delete getComponente<ComponenteSprite>();
		addComponente<ComponenteSprite>();
		getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Mago/Sprites/Attack.png");
		break;
	case DYING:
		delete getComponente<ComponenteSprite>();
		addComponente<ComponenteSprite>();
		getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Mago/Sprites/Death.png");
		break;
	default:
		break;
	}
}
