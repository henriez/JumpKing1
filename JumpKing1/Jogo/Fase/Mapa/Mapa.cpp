#include "Mapa.h"
#include "../../Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include <iostream>

Vector2D Mapa::nTiles;
int Mapa::tamanhoDoTile;

const char* mapa1_camada1 = "Assets/TileMap/Mapa1/mapa1_camada_tiles_1.csv";
const char* mapa1_camada2 = "Assets/TileMap/Mapa1/mapa1_camada_tiles_2.csv";
const char* mapa1_camada_espinhos = "Assets/TileMap/Mapa1/mapa1_camada_espinhos.csv";
const char* mapa1_camada_lava = "Assets/TileMap/Mapa1/mapa1_camada_lava.csv";
const char* mapa1_camada_colisao = "Assets/TileMap/Mapa1/mapa1_camada_colisao.csv";
const char* mapa1_posicoes_lava = "Assets/TileMap/Mapa1/mapa1_posicoes_lava.csv";
const char* mapa1_posicoes_espinhos = "Assets/TileMap/Mapa1/mapa1_posicoes_espinhos.csv";

const char* mapa2_camada1 = "Assets/TileMap/Mapa2/mapa2_Camada_0.csv";
const char* mapa2_camada2 = "Assets/TileMap/Mapa2/mapa2_Camada_1.csv";
const char* mapa2_camada_espinhos = "Assets/TileMap/Mapa2/mapa2_Camada_espinhos.csv";
const char* mapa2_camada_lava = "Assets/TileMap/Mapa2/mapa2_Camada_lava.csv";
const char* mapa2_camada_colisao = "Assets/TileMap/Mapa2/mapa2_Camada_colisao.csv"; 
const char* mapa2_posicoes_lava = "Assets/TileMap/Mapa2/mapa2_posicoes_lava.csv";
const char* mapa2_posicoes_espinhos = "Assets/TileMap/Mapa2/mapa2_posicoes_espinhos.csv";

Mapa::Mapa() {
	backgroundTex = nullptr;
	tamanhoDoTile = 32;
	fim = { 0,0,0,0 };
	onBossRoom = false;
	id = 0;
}

Mapa::~Mapa() {
	clear();
	SDL_DestroyTexture(backgroundTex);

}

void Mapa::inicializar(int id) {
	this->id = id;

	switch (id) {
	case 1:
		backgroundTex = GerenciadorGrafico::LoadTexture("Assets/TileMap/Mapa1/mapa1background.png");
		fim = { 0,64,32,96 };
		tileMap.carregaPosicoesValidas(mapa1_posicoes_lava, mapa1_posicoes_espinhos);
		tileMap.inicializa(mapa1_camada1, mapa1_camada2, mapa1_camada_colisao, 80, 200); 
		break;
	case 2:
		backgroundTex = GerenciadorGrafico::LoadTexture("Assets/TileMap/Mapa2/mapa2.png");
		fim = { 0,96,32,288 };
		tileMap.inicializa(mapa2_camada1, mapa2_camada2, mapa2_camada_colisao, 65, 250);
	default:
		break;
	}

	nTiles = tileMap.getNTiles();
	GerenciadorDeCamera::init();
}

void Mapa::atualizar() {
	if (!onBossRoom) {
		tileMap.atualiza();
		SDL_Rect hitbox = GerenciadorDeColisao::getJogador1()->getComponente<ComponenteColisao>()->getColisor();
		if (GerenciadorDeColisao::AABB(fim, hitbox)) {
			clear();
			onBossRoom = true;
			boss_room.inicializar(id);
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
		GerenciadorGrafico::render(backgroundTex, GerenciadorDeCamera::camera, destino);

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
	tileMap.clear();
	boss_room.clear();
}