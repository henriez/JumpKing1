#include "GerenciadorDeCamera.h"
#include "../Entidade/Personagem/Jogador/Jogador.h"
#include "../../Jogo/Fase/Mapa/Mapa.h"
#include "../../Jogo/Jogo.h"

Jogador* GerenciadorDeCamera::jogador;

GerenciadorDeCamera::GerenciadorDeCamera() {
	jogador = nullptr;
}

GerenciadorDeCamera::~GerenciadorDeCamera() {}

void GerenciadorDeCamera::setJogador(Jogador* jg) {
	jogador = jg;
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
	Mapa::camera.x = transform->posicao.x - Mapa::camera.w / 2;
	Mapa::camera.y = transform->posicao.y - Mapa::camera.h / 2;

	// Checa bordas do mapa para a camera em X
	if (Mapa::camera.x <= 0)
		Mapa::camera.x = 0;
	else if (Mapa::camera.x + Mapa::camera.w >= dimMapa.x)
		Mapa::camera.x = dimMapa.x - Mapa::camera.w;

	// Checa bordas do mapa para a camera em Y
	if (Mapa::camera.y <= 0)
		Mapa::camera.y = 0;
	else if (Mapa::camera.y + Mapa::camera.h >= dimMapa.y)
		Mapa::camera.y = dimMapa.y - Mapa::camera.h;
}