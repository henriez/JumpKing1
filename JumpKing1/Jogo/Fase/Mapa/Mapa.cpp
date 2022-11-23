#include "Mapa.h"
#include "../../Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include "../Fase.h"
#include <iostream>

SDL_Point Mapa::nTiles;
int Mapa::tamanhoDoTile;

const char* mapa1_camada1 = "Assets/TileMap/Mapa1/mapa1_camada_tiles_1.csv";
const char* mapa1_camada2 = "Assets/TileMap/Mapa1/mapa1_camada_tiles_2.csv";
const char* mapa1_camada_colisao = "Assets/TileMap/Mapa1/mapa1_camada_colisao.csv";
const char* mapa1_posicoes_lava = "Assets/TileMap/Mapa1/mapa1_posicoes_lava.csv";
const char* mapa1_posicoes_espinhos = "Assets/TileMap/Mapa1/mapa1_posicoes_espinhos.csv";

const char* mapa2_camada1 = "Assets/TileMap/Mapa2/mapa2_Camada_0.csv";
const char* mapa2_camada2 = "Assets/TileMap/Mapa2/mapa2_Camada_1.csv";
const char* mapa2_camada_colisao = "Assets/TileMap/Mapa2/mapa2_Camada_colisao.csv"; 
const char* mapa2_posicoes_lava = "Assets/TileMap/Mapa2/mapa2_posicoes_lava.csv";
const char* mapa2_posicoes_espinhos = "Assets/TileMap/Mapa2/mapa2_posicoes_espinhos.csv";

Mapa::Mapa() {
	backgroundTex = nullptr;
	fase = nullptr;
	tamanhoDoTile = 32;
	fim = { 0,0,0,0 };
	onBossRoom = false;
	id = 0;
	graphics = GerenciadorGrafico::getInstance();
}

Mapa::~Mapa() {
	clear();
	SDL_DestroyTexture(backgroundTex);
}

void Mapa::inicializar(int id, Fase* fs){
	this->id = id;
	fase = fs;

	criaObstaculos(id);
	switch (id) {
	case 1:
		backgroundTex = graphics->LoadTexture("Assets/TileMap/Mapa1/mapa1background.png"); //65mb de textura??????
		fim = { 0,64,32,96 };
		tileMap.inicializa(mapa1_camada1, mapa1_camada2, mapa1_camada_colisao, 80, 200); 
		break;
	case 2:
		backgroundTex = graphics->LoadTexture("Assets/TileMap/Mapa2/mapa2.png");
		fim = { 0,96,32,288 };
		tileMap.inicializa(mapa2_camada1, mapa2_camada2, mapa2_camada_colisao, 65, 250);
	default:
		break;
	}

	nTiles = tileMap.getNTiles();
	GerenciadorDeCamera::getInstance()->init();
}

void Mapa::criaObstaculos(int id) {
	char c;
	int a1, a2, a3, a4, nPosicoes;
	SDL_Point pos = { 0,0 };

	std::fstream mapFile;
	std::vector<SDL_Point> posicoes_lava;
	std::vector<SDL_Point> posicoes_espinhos;

	/* ============================================= */
	/* Posicoes validas para lavas */

	if (id == 1) mapFile.open(mapa1_posicoes_lava);
	else if (id == 2) mapFile.open(mapa2_posicoes_lava);

	mapFile.get(c);
	a1 = atoi(&c);
	mapFile.get(c);
	a2 = atoi(&c);
	mapFile.get(c);
	a3 = atoi(&c);
	mapFile.ignore();

	nPosicoes = a1 * 100 + a2 * 10 + a3;

	for (int i = 0; i < nPosicoes; i++) {

		mapFile.get(c);
		a1 = atoi(&c);
		mapFile.get(c);
		a2 = atoi(&c);
		mapFile.get(c);
		a3 = atoi(&c);
		mapFile.get(c);
		a4 = atoi(&c);
		mapFile.ignore();
		pos.x = a1 * 1000 + a2 * 100 + a3 * 10 + a4;

		mapFile.get(c);
		a1 = atoi(&c);
		mapFile.get(c);
		a2 = atoi(&c);
		mapFile.get(c);
		a3 = atoi(&c);
		mapFile.get(c);
		a4 = atoi(&c);
		mapFile.ignore();
		pos.y = a1 * 1000 + a2 * 100 + a3 * 10 + a4;
		posicoes_lava.push_back(pos);
	}

	mapFile.close();

	/* ============================================= */
	/* Posicoes validas para espinhos */

	if (id == 1) mapFile.open(mapa1_posicoes_espinhos);
	else if (id == 2)  mapFile.open(mapa2_posicoes_espinhos);

	mapFile.get(c);
	a1 = atoi(&c);
	mapFile.get(c);
	a2 = atoi(&c);
	mapFile.get(c);
	a3 = atoi(&c);
	mapFile.ignore();

	nPosicoes = a1 * 100 + a2 * 10 + a3;

	for (int i = 0; i < nPosicoes; i++) {

		mapFile.get(c);
		a1 = atoi(&c);
		mapFile.get(c);
		a2 = atoi(&c);
		mapFile.get(c);
		a3 = atoi(&c);
		mapFile.get(c);
		a4 = atoi(&c);
		mapFile.ignore();
		pos.x = a1 * 1000 + a2 * 100 + a3 * 10 + a4;

		mapFile.get(c);
		a1 = atoi(&c);
		mapFile.get(c);
		a2 = atoi(&c);
		mapFile.get(c);
		a3 = atoi(&c);
		mapFile.get(c);
		a4 = atoi(&c);
		mapFile.ignore();
		pos.y = a1 * 1000 + a2 * 100 + a3 * 10 + a4;
		posicoes_espinhos.push_back(pos);
	}

	mapFile.close();

	Lava* lava = nullptr;
	Espinhos* espinhos = nullptr;
	SDL_Point random_pos = { 0,0 };

	//geracao aleatoria
	if (posicoes_espinhos.size() > 2) {
		int nEspinhos = rand() % (posicoes_espinhos.size() / 2) + 3;

		for (int i = 0; i < nEspinhos; i++) {
			random_pos = posicoes_espinhos[rand() % posicoes_espinhos.size()]; //posicao aleatoria do vetor retorna uma posicao valida definida
			espinhos = new Espinhos;
			espinhos->getComponente<ComponenteColisao>()->set(random_pos.x, random_pos.y + 16, 32, 16);
			GerenciadorDeColisao::getInstance()->addObstaculo(static_cast<Obstaculo*>(espinhos));
			fase->addEntidade(static_cast<Entidade*>(espinhos));
			//adiciona espinhos ao manager
		}
	}

	if (posicoes_lava.size() > 2) {
		int nLavas = rand() % (posicoes_lava.size() / 2) + 3;
		for (int i = 0; i < nLavas; i++) {
			random_pos = posicoes_lava[rand() % posicoes_lava.size()]; //posicao aleatoria do vetor retorna uma posicao valida definida
			lava = new Lava;
			lava->getComponente<ComponenteColisao>()->set(random_pos.x, random_pos.y, 32, 32);
			GerenciadorDeColisao::getInstance()->addObstaculo(static_cast<Obstaculo*>(lava));
			fase->addEntidade(static_cast<Entidade*>(lava));
			//adiciona lava ao manager
		}
	}
}

void Mapa::reload(int id, Fase* fs) {
	this->id = id;
	fase = fs;

	switch (id) {
	case 1:
		backgroundTex = graphics->LoadTexture("Assets/TileMap/Mapa1/mapa1background.png");
		fim = { 0,64,32,96 };
		if (!onBossRoom) tileMap.inicializa(mapa1_camada1, mapa1_camada2, mapa1_camada_colisao, 80, 200);
		else boss_room.reload(id);
		break;
	case 2:
		backgroundTex = graphics->LoadTexture("Assets/TileMap/Mapa2/mapa2.png");
		fim = { 0,96,32,288 };
		if (!onBossRoom) tileMap.inicializa(mapa2_camada1, mapa2_camada2, mapa2_camada_colisao, 65, 250);
		else boss_room.reload(id);
		break;
	default:
		break;
	}

	GerenciadorDeCamera::getInstance()->init();
}

void Mapa::atualizar() {
	if (!onBossRoom) {
		tileMap.atualiza();
		SDL_Rect hitbox = GerenciadorDeColisao::getInstance()->getJogador1()->getComponente<ComponenteColisao>()->getColisor();
		if (GerenciadorDeColisao::getInstance()->AABB(fim, hitbox)) {
			clear();
			onBossRoom = true;
			boss_room.inicializar(id);
			fase->criaMagos();
			return;
		}
		hitbox = GerenciadorDeColisao::getInstance()->getJogador2()->getComponente<ComponenteColisao>()->getColisor();
		if (GerenciadorDeColisao::getInstance()->AABB(fim, hitbox)) {
			clear();
			onBossRoom = true;
			boss_room.inicializar(id);
			fase->criaMagos();
		}
	}
	else
		boss_room.atualizar();
}

void Mapa::render() {

	if (onBossRoom)
		boss_room.render();
	else {
		SDL_Rect destino = { 0, 0, GerenciadorDeCamera::getInstance()->camera.w, GerenciadorDeCamera::getInstance()->camera.h };
		graphics->render(backgroundTex, GerenciadorDeCamera::getInstance()->camera, destino);

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

SDL_Point Mapa::getDimensoes() {
	SDL_Point temp = nTiles;
	temp.x *= tamanhoDoTile;
	temp.y *= tamanhoDoTile;
	return temp;
}

void Mapa::clear() {
	tileMap.clear();
	boss_room.clear();
}