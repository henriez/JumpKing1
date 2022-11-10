#include "GerenciadorDeCamera.h"
#include "../../Entidade/Personagem/Jogador/Jogador.h"
#include "../../../Jogo/Fase/Mapa/Mapa.h"
#include "../../../Jogo/Jogo.h"
#include "../../../Jogo/Fase/Fase.h"

Jogador* GerenciadorDeCamera::jogador = nullptr;
Jogador* GerenciadorDeCamera::jogador2 = nullptr;
SDL_Rect GerenciadorDeCamera::camera;

GerenciadorDeCamera::GerenciadorDeCamera() {
}

GerenciadorDeCamera::~GerenciadorDeCamera() {}

void GerenciadorDeCamera::setJogador(Jogador* jg) {
	jogador = jg;
}

void GerenciadorDeCamera::setJogador2(Jogador* jg) {
	jogador2 = jg;
}

void GerenciadorDeCamera::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	GerenciadorDeCamera::camera.x = GerenciadorDeCamera::camera.y = 0;
	GerenciadorDeCamera::camera.w = dm.w;
	GerenciadorDeCamera::camera.h = dm.h;
}

void GerenciadorDeCamera::Atualiza() {
	AtualizaJogador();
}

void GerenciadorDeCamera::AtualizaJogador() {

	ComponenteTransform* transform = jogador->getComponente<ComponenteTransform>();
	ComponenteTransform* transform2 = jogador2->getComponente<ComponenteTransform>();
	SDL_Point dimMapa = Mapa::getDimensoes();

	camera.x = (transform->posicao.x + transform2->posicao.x) / 2 - camera.w / 2.0;
	camera.y = (transform->posicao.y + transform2->posicao.y) / 2 - camera.h / 2.0;
	
	//jogadores colidem com a GerenciadorDeCamera::camera
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
	if (transform2->posicao.y < GerenciadorDeCamera::camera.y)
		camera.y = transform2->posicao.y;
	else if (transform2->posicao.y + Mapa::tamanhoTile() > camera.y + camera.h)
		camera.y = transform2->posicao.y - camera.h + Mapa::tamanhoTile();
	

	// Checa bordas do mapa para a camera em X
	if (GerenciadorDeCamera::camera.x <= 0)
		GerenciadorDeCamera::camera.x = 0;
	else if (GerenciadorDeCamera::camera.x + GerenciadorDeCamera::camera.w >= dimMapa.x)
		GerenciadorDeCamera::camera.x = dimMapa.x - GerenciadorDeCamera::camera.w;

	// Checa bordas do mapa para a camera em Y
	if (GerenciadorDeCamera::camera.y <= 0)
		GerenciadorDeCamera::camera.y = 0;
	else if (GerenciadorDeCamera::camera.y + GerenciadorDeCamera::camera.h >= dimMapa.y)
		GerenciadorDeCamera::camera.y = dimMapa.y - GerenciadorDeCamera::camera.h;
}