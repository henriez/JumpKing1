#include "GerenciadorDeCamera.h"
#include "../../Entidade/Personagem/Jogador/Jogador.h"
#include "../../../Jogo/Fase/Mapa/Mapa.h"
#include "../../../Jogo/Jogo.h"
#include "../../../Jogo/Fase/Fase.h"

GerenciadorDeCamera* GerenciadorDeCamera::manager = nullptr;

GerenciadorDeCamera::GerenciadorDeCamera() {
	jogador = jogador2 = nullptr;
	camera = { 0,0,0,0 };
}

GerenciadorDeCamera::~GerenciadorDeCamera() {}

GerenciadorDeCamera* GerenciadorDeCamera::getInstance() {
	if (manager == nullptr) {
		manager = new GerenciadorDeCamera;
	}
	return manager;
}

void GerenciadorDeCamera::deleteInstance() {
	if (manager != nullptr) {
		delete manager;
		manager = nullptr;
	}
}

void GerenciadorDeCamera::setJogador(Jogador* jg) {
	jogador = jg;
}

void GerenciadorDeCamera::setJogador2(Jogador* jg) {
	jogador2 = jg;
}

void GerenciadorDeCamera::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	GerenciadorDeCamera::getInstance()->camera.x = GerenciadorDeCamera::getInstance()->camera.y = 0;
	GerenciadorDeCamera::getInstance()->camera.w = dm.w;
	GerenciadorDeCamera::getInstance()->camera.h = dm.h;
}

void GerenciadorDeCamera::Atualiza() {
	ComponenteTransform* transform = jogador->getComponente<ComponenteTransform>();
	ComponenteTransform* transform2 = jogador2->getComponente<ComponenteTransform>();
	SDL_Point dimMapa = Mapa::getDimensoes();

	camera.x = (transform->posicao.x + transform2->posicao.x) / 2 - camera.w / 2.0;
	camera.y = (transform->posicao.y + transform2->posicao.y) / 2 - camera.h / 2.0;

	//jogadores colidem com a GerenciadorDeCamera::getInstance()->camera
	//jogador1
	if (transform->posicao.x < camera.x)
		camera.x = transform->posicao.x;
	else if (transform->posicao.x + Mapa::tamanhoTile() > camera.x + camera.w)
		camera.x = transform->posicao.x - camera.w + Mapa::tamanhoTile();
	if (transform->posicao.y < camera.y)
		camera.y = transform->posicao.y;
	else if (transform->posicao.y + Mapa::tamanhoTile() > camera.y + camera.h)
		camera.y = transform->posicao.y - camera.h + Mapa::tamanhoTile();

	//jogador2
	if (transform2->posicao.x < camera.x)
		camera.x = transform2->posicao.x;
	else if (transform2->posicao.x + Mapa::tamanhoTile() > camera.x + camera.w)
		camera.x = transform2->posicao.x - camera.w + Mapa::tamanhoTile();
	if (transform2->posicao.y < GerenciadorDeCamera::getInstance()->camera.y)
		camera.y = transform2->posicao.y;
	else if (transform2->posicao.y + Mapa::tamanhoTile() > camera.y + camera.h)
		camera.y = transform2->posicao.y - camera.h + Mapa::tamanhoTile();


	// Checa bordas do mapa para a camera em X
	if (GerenciadorDeCamera::getInstance()->camera.x <= 0)
		GerenciadorDeCamera::getInstance()->camera.x = 0;
	else if (GerenciadorDeCamera::getInstance()->camera.x + GerenciadorDeCamera::getInstance()->camera.w >= dimMapa.x)
		GerenciadorDeCamera::getInstance()->camera.x = dimMapa.x - GerenciadorDeCamera::getInstance()->camera.w;

	// Checa bordas do mapa para a camera em Y
	if (GerenciadorDeCamera::getInstance()->camera.y <= 0)
		GerenciadorDeCamera::getInstance()->camera.y = 0;
	else if (GerenciadorDeCamera::getInstance()->camera.y + GerenciadorDeCamera::getInstance()->camera.h >= dimMapa.y)
		GerenciadorDeCamera::getInstance()->camera.y = dimMapa.y - GerenciadorDeCamera::getInstance()->camera.h;
}
