#include "Projetil.h"
#include "../../Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"

Projetil::Projetil() {
	addComponente<ComponenteTransform>();

	Vector2D pos = getComponente<ComponenteTransform>()->posicao;
	addComponente<ComponenteColisao>();
	getComponente<ComponenteColisao>()->set(pos.x, pos.y, 32, 32);

	addComponente<ComponenteSprite>();
	getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/projetil.png");
	onScreen = false;
	speed = 4;
}

Projetil::~Projetil() {}

void Projetil::init() {
}

void Projetil::atualizar() {
	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->posicao.x += transform->velocidade.x*speed;
	transform->posicao.y += transform->velocidade.y*speed;

	Vector2D pos = getComponente<ComponenteTransform>()->posicao;
	getComponente<ComponenteColisao>()->setPos(pos.x, pos.y);
}

void Projetil::render() {
	SDL_Rect pos = getComponente<ComponenteColisao>()->getColisor();

	pos.x -= GerenciadorDeCamera::camera.x;
	pos.y -= GerenciadorDeCamera::camera.y;
	getComponente<ComponenteSprite>()->render(pos);
}

