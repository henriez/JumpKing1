#include "Mapa.h"
#include "../../Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico.h"
#include "../../../ECS/Gerenciador/GerenciadorDeCamera.h"
#include "../../../ECS/Gerenciador/GerenciadorDeColisao.h"
#include <iostream>

Vector2D Mapa::nTiles;
int Mapa::tamanhoDoTile;

const char* mapa1_camada1 = "Assets/TileMap/Mapa1/mapa1_camada_tiles_1.csv";
const char* mapa1_camada2 = "Assets/TileMap/Mapa1/mapa1_camada_tiles_2.csv";
const char* mapa1_camada_espinhos = "Assets/TileMap/Mapa1/mapa1_camada_espinhos.csv";
const char* mapa1_camada_colisao = "Assets/TileMap/Mapa1/mapa1_camada_colisao.csv";

Mapa::Mapa() {
	backgroundTex = nullptr;
	tamanhoDoTile = 32;
	fim.x = 0;
	fim.y = 64;
	fim.w = 32;
	fim.h = 96;
	onBossRoom = false;
}

Mapa::~Mapa() {
	clear();

}

void Mapa::inicializar() {
	backgroundTex = GerenciadorGrafico::CarregaTextura("Assets/TileMap/Mapa1/mapa1background.png");

	tileMap.inicializa(mapa1_camada1, mapa1_camada2, mapa1_camada_colisao, mapa1_camada_espinhos, 80, 200); //passar id de mapa
	tileMap.setFim(fim);
	nTiles = tileMap.getNTiles();
	GerenciadorDeCamera::init();
}

void Mapa::atualizar() {
	if (!onBossRoom) {
		GerenciadorDeCamera::Atualiza();
		tileMap.atualiza();
		SDL_Rect hitbox = GerenciadorDeColisao::getJogador1()->getComponente<ComponenteColisao>()->getColisor();
		if (GerenciadorDeColisao::AABB(fim, hitbox)) {
			clear();
			onBossRoom = true;
			boss_room.inicializar();
		}
	}
	else
		boss_room.atualizar();
}

void Mapa::render() {

	if (onBossRoom)
		boss_room.render();
	else {
		SDL_Rect destino = { 0, 0, GerenciadorDeCamera::camera.w, GerenciadorDeCamera::camera.h };
		GerenciadorGrafico::Desenhe(backgroundTex, GerenciadorDeCamera::camera, destino);

		tileMap.render();
	}
}

int Mapa::tamanhoTile() {
	return tamanhoDoTile;
}

void Mapa::setDimMapa(int w, int h) {
	nTiles.x = w;
	nTiles.y = h;
}

Vector2D Mapa::getDimensoes() {
	return nTiles*tamanhoDoTile;
}

void Mapa::clear() {
	SDL_DestroyTexture(backgroundTex);
	tileMap.clear();
	boss_room.clear();
}