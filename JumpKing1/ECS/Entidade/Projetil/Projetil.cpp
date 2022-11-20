#include "Projetil.h"
#include "../../Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"


Projetil::Projetil() {
	addComponente<ComponenteTransform>();

	Vector2D pos = getComponente<ComponenteTransform>()->posicao;
	addComponente<ComponenteColisao>();
	getComponente<ComponenteColisao>()->set(pos.x, pos.y, 46, 46);

	addComponente<ComponenteSprite>();
	getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/Enemies/Fire Ball/Move.png");
	onScreen = false;
	flip = false;
	active = true;
	speed = 3;
	sprite = { 0, 0, 46, 46 }; // w = 42 h = 49
	maxColisoes = 2;
	
}

Projetil::~Projetil() {}

void Projetil::init() {
}

void Projetil::atualizar() {
	if (maxColisoes <= 0) active = false;
	if (active) {
		ComponenteTransform* transform = getComponente<ComponenteTransform>();
		transform->posicao.x += transform->velocidade.x * speed;
		transform->posicao.y += transform->velocidade.y * speed;

		transform->velocidade.y += 0.03; //gravidade

		Vector2D pos = getComponente<ComponenteTransform>()->posicao;
		getComponente<ComponenteColisao>()->setPos(pos.x, pos.y);
	}
}

void Projetil::render() {
	SDL_Rect pos = getComponente<ComponenteColisao>()->getColisor();

	pos.x -= GerenciadorDeCamera::camera.x;
	pos.y -= GerenciadorDeCamera::camera.y;

	// animated

	int frames;
	unsigned int fSpeed;
	static int frameNumber = 0;

	if (getComponente<ComponenteTransform>()->velocidade.x < 0) { flip = true; }
	else if (getComponente<ComponenteTransform>()->velocidade.x > 0) { flip = false; }

	if (active) {
		frames = 6;
		fSpeed = 8;

		int frameVal = static_cast<int>((frameNumber / fSpeed) % frames);
		sprite.x = sprite.w * frameVal;
		frameNumber++;
		if (frameNumber >= frames * static_cast<int>(fSpeed)) { frameNumber = 0; }
		

		getComponente<ComponenteSprite>()->render(pos, sprite, flip);
	}
}

