#include "InimigoTipo1.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera.h"

#define SCALE 1.5
#define ATTACKING 0
#define DYING 1
#define WALKING 2
#define IDLE 3
#define HIT 4

InimigoTipo1::InimigoTipo1() {
	sprite = { 0, 0, 64, 64 };
	flip = false;

	addComponente<ComponenteColisao>();
	addComponente<ComponenteSaude>();
	addComponente<ComponenteTransform>();
	addComponente<ComponenteSprite>();
	getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Skeleton.png");

	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 0;
	transform->velocidade.y = 0;
	transform->posicao.x = 0;
	transform->posicao.y = 0;

	getComponente<ComponenteColisao>()->set(transform->posicao.x, transform->posicao.y, sprite.w * SCALE, sprite.h * SCALE);
}

InimigoTipo1::~InimigoTipo1() {}

void InimigoTipo1::atualizar() {
	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	getComponente<ComponenteColisao>()->setPos(transform->posicao.x, transform->posicao.y);

	// if (collide || end platform) { side = false; switch direction;}

}

void InimigoTipo1::render() {
	SDL_Rect posRect = { 0, 0, sprite.w * SCALE, sprite.h * SCALE };
	posRect.x = (int)getComponente<ComponenteTransform>()->posicao.x - GerenciadorDeCamera::camera.x;
	posRect.y = (int)getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::camera.y;
	flip = true;
	getComponente<ComponenteSprite>()->render(posRect, sprite, flip);
}