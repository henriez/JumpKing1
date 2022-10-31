#include "GerenciadorDeCamera.h"
#include "../Entidade/Personagem/Jogador/Jogador.h"
#include "../../Jogo/Fase/Mapa/Mapa.h"
#include "../../Jogo/Jogo.h"

Jogador* GerenciadorDeCamera::jogador;
SDL_Rect GerenciadorDeCamera::camera;

GerenciadorDeCamera::GerenciadorDeCamera() {
	jogador = nullptr;
}

GerenciadorDeCamera::~GerenciadorDeCamera() {}

void GerenciadorDeCamera::setJogador(Jogador* jg) {
	jogador = jg;
}

void GerenciadorDeCamera::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	GerenciadorDeCamera::camera.x = GerenciadorDeCamera::camera.y = 0;
	GerenciadorDeCamera::camera.w = dm.w;
	GerenciadorDeCamera::camera.h = dm.h;
}

void GerenciadorDeCamera::Atualiza() {

}

void GerenciadorDeCamera::AtualizaJogador() {

	ComponenteTransform* transform = jogador->getComponente<ComponenteTransform>();
	Vector2D dimMapa = Mapa::getDimensoes();

	// Checa bordas do mapa em X
	if (transform->posicao.x < 0 && transform->velocidade.x < 0)
		transform->posicao.x = transform->velocidade.x = 0;
	else if (transform->posicao.x + Mapa::tamanhoTile() > dimMapa.x && transform->velocidade.x > 0) {
		transform->posicao.x = dimMapa.x - Mapa::tamanhoTile();
		transform->velocidade.x = 0;
	}

	// Checa bordas do mapa em Y
	if (transform->posicao.y < 0 && transform->velocidade.y < 0)
		transform->posicao.y = transform->velocidade.y = 0;
	else if (transform->posicao.y + Mapa::tamanhoTile() > dimMapa.y && transform->velocidade.y > 0) {
		transform->posicao.y = dimMapa.y - Mapa::tamanhoTile();
		transform->velocidade.y = 0;
	}

	
	// Posicao da camera centralizando o player
	GerenciadorDeCamera::camera.x = transform->posicao.x - GerenciadorDeCamera::camera.w / 2;
	GerenciadorDeCamera::camera.y = transform->posicao.y - GerenciadorDeCamera::camera.h / 2;

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