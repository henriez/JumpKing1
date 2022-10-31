#include "GerenciadorDeColisao.h"

#include "../../Jogo/Fase/Mapa/TileMap/TileMap.h"
#include "../Entidade/Personagem/Jogador/Jogador.h"

TileMap* GerenciadorDeColisao::tilemap = nullptr;
Jogador* GerenciadorDeColisao::jogador1 = nullptr;

GerenciadorDeColisao::GerenciadorDeColisao() {
	tilemap = nullptr;
	jogador1 = nullptr;
}

GerenciadorDeColisao::~GerenciadorDeColisao() {}

void GerenciadorDeColisao::setJogador(Jogador* jg) {
	jogador1 = jg;
}

void GerenciadorDeColisao::setTileMap(TileMap* tmap) {
	tilemap = tmap;
}

void GerenciadorDeColisao::colisao_jogador1() {
	tilemap->colisao_jogador1();
}

bool GerenciadorDeColisao::AABB(SDL_Rect A, SDL_Rect B) {
	if (A.x + A.w > B.x &&
		B.x + B.w > A.x &&
		A.y + A.h > B.y &&
		B.y + B.h > A.y)
		return true;
	return false;	
}

Jogador* GerenciadorDeColisao::getJogador1(){
	return jogador1;
}

