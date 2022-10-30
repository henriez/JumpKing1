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
	//BUG APROXIMANDO DAS BORDAS DO MAPA

	ComponenteTransform* transform = jogador->getComponente<ComponenteTransform>();
	Vector2D dimMapa = Mapa::getDimensoes();

	transform->velocidade.y += 0.035; // simula gravidade - // possivel perda de dados em casting

	transform->posicao.x += transform->velocidade.x * jogador->speed;
	transform->posicao.y += transform->velocidade.y * jogador->speed;

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


	if (transform->posicao.x + Mapa::tamanhoTile()/2.0 > Mapa::dimensoesCamera.x / 2.0 &&
		transform->posicao.x < dimMapa.x - Mapa::dimensoesCamera.x / 2.0)
		Mapa::camera.x += transform->velocidade.x * jogador->speed;
	if (transform->posicao.y + Mapa::tamanhoTile()/2.0 > Mapa::dimensoesCamera.y / 2.0 &&
		transform->posicao.y < dimMapa.y - Mapa::dimensoesCamera.y/ 2.0)
		Mapa::camera.y += transform->velocidade.y * jogador->speed; // cast para int mata camera - trocar para vector2D

}