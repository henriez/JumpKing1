#include "TileMap.h"
#include "../../../Jogo.h"
#include "../../../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include "../../../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../Mapa.h"

#include <fstream>
#include <SDL_image.h>

const int largura = 11; //dados tileset
const int altura = 12;
const int tamanhoTile = 32;

TileMap::TileMap() {
	nTiles.x = 80;
	nTiles.y = 200;
	GerenciadorDeColisao::getInstance()->setTileMap(this);
	graphics = GerenciadorGrafico::getInstance(); 
}

TileMap::~TileMap() {
	clear();
}

void TileMap::carregaPosicoesValidas(const char* posicoes_lava, const char* posicoes_espinhos) {
	char c;
	int a1, a2, a3, a4, nPosicoes;
	SDL_Point pos = { 0,0 };

	std::fstream mapFile;

	/* ============================================= */
	/* Posicoes validas para lavas */

	mapFile.open(posicoes_lava);

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
		this->posicoes_lava.push_back(pos);
	}

	mapFile.close();

	/* ============================================= */
	/* Posicoes validas para espinhos */

	mapFile.open(posicoes_espinhos);

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
		this->posicoes_espinhos.push_back(pos);
	}

	mapFile.close();

	Lava* lava = nullptr;
	Espinhos* espinhos = nullptr;
	SDL_Point random_pos = { 0,0 };

	//geracao aleatoria
	if (this->posicoes_espinhos.size() > 2) {
		int nEspinhos = rand() % (this->posicoes_espinhos.size() / 2) + 3;

		for (int i = 0; i < nEspinhos; i++) {
			random_pos = this->posicoes_espinhos[rand() % this->posicoes_espinhos.size()]; //posicao aleatoria do vetor retorna uma posicao valida definida
			espinhos = new Espinhos;
			espinhos->getComponente<ComponenteColisao>()->set(random_pos.x, random_pos.y + 16, 32, 16);
			GerenciadorDeColisao::getInstance()->addObstaculo(static_cast<Obstaculo*>(espinhos));
			//adiciona espinhos ao manager
		}
	}

	if (this->posicoes_lava.size() > 2) {
		int nLavas = rand() % (this->posicoes_lava.size() / 2) + 3;
		for (int i = 0; i < nLavas; i++) {
			random_pos = this->posicoes_lava[rand() % this->posicoes_lava.size()]; //posicao aleatoria do vetor retorna uma posicao valida definida
			lava = new Lava;
			lava->getComponente<ComponenteColisao>()->set(random_pos.x, random_pos.y, 32, 32);
			GerenciadorDeColisao::getInstance()->addObstaculo(static_cast<Obstaculo*>(lava));
			//adiciona lava ao manager
		}
	}
}

void TileMap::inicializa(const char* cam1, const char* cam2, const char* cam_colisao, int tilesW, int tilesH) {
	GerenciadorDeColisao::getInstance()->setTileMap(this);

	int algarismos[3];
	algarismos[0] = algarismos[1] = algarismos[2] = 0;

	nTiles.x = tilesW;
	nTiles.y = tilesH;

	Mapa::setDimMapa(tilesW, tilesH);
	char c = 0;
	std::fstream mapFile;

	int srcX, srcY, alg, id; //diferentes algarismos
	srcX = srcY = alg = id = 0;

	mapFile.open(cam1);
	for (int i = 0; i < nTiles.y; i++) {
		for (int j = 0; j < nTiles.x; j++) {
			algarismos[0] = algarismos[1] = algarismos[2] = alg = 0;
			mapFile.get(c);

			if (c == '-') {
				mapFile.ignore();
				mapFile.ignore();
				continue;
			}
			if (j == nTiles.x - 1)
				while (c != '\n') {
					algarismos[alg++] = atoi(&c);
					mapFile.get(c);
				}
			else {
				while (c != ',') {
					algarismos[alg++] = atoi(&c);
					mapFile.get(c);
				}
			}
			// ao final do loop alg será 2 3 (depende do n de algarismos do id)
			if (alg == 3)
				id = algarismos[0] * 100 + algarismos[1] * 10 + algarismos[2];
			else if (alg == 2)
				id = algarismos[0] * 10 + algarismos[1];
			else //alg == 1
				id = algarismos[0];

			srcY = (id / largura) * tamanhoTile;
			srcX = (id % largura) * tamanhoTile;

			Tile* tile = new Tile;
			tile->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
			camada1.push_back(tile);
		}
	}
	mapFile.close();


	mapFile.open(cam2);
	for (int i = 0; i < nTiles.y; i++) {
		for (int j = 0; j < nTiles.x; j++) {
			algarismos[0] = algarismos[1] = algarismos[2] = alg = 0;
			mapFile.get(c);

			if (c == '-') {
				mapFile.ignore();
				mapFile.ignore();
				continue;
			}
			if (j == nTiles.x - 1)
				while (c != '\n') {
					algarismos[alg++] = atoi(&c);
					mapFile.get(c);
				}
			else {
				while (c != ',') {
					algarismos[alg++] = atoi(&c);
					mapFile.get(c);
				}
			}
			// ao final do loop alg será 2 3 (depende do n de algarismos do id)
			if (alg == 3)
				id = algarismos[0] * 100 + algarismos[1] * 10 + algarismos[2];
			else if (alg == 2)
				id = algarismos[0] * 10 + algarismos[1];
			else //alg == 1
				id = algarismos[0];

			srcY = (id / largura) * tamanhoTile;
			srcX = (id % largura) * tamanhoTile;

			Tile* tile = new Tile;
			tile->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
			camada2.push_back(tile);
		}
	}
	mapFile.close();


	mapFile.open(cam_colisao);
	for (int i = 0; i < nTiles.y; i++) {
		for (int j = 0; j < nTiles.x; j++) {
			id = 0;
			mapFile.get(c);

			if (c == '-') {
				mapFile.ignore();
				mapFile.ignore();
				continue;
			}
			id = atoi(&c);
			mapFile.ignore();

			srcY = 0;
			srcX = id * tamanhoTile;

			Tile* tile = new Tile;
			tile->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
			if (id == 1)
				hitbox_plataformas.push_back(tile);
			else if (id == 2) {
				std::cout << j * Mapa::tamanhoTile() << ", " << i * Mapa::tamanhoTile() << std::endl;
			}

		}
	}
	mapFile.close();

	
}

void TileMap::atualiza() {
	for (auto& t : camada1) {
		t->setScreen(false);
		if (GerenciadorDeColisao::getInstance()->AABB(t->getPos(), GerenciadorDeCamera::getInstance()->camera))
			t->setScreen(true);
	}

	for (auto& t : camada2) {
		t->setScreen(false);
		if (GerenciadorDeColisao::getInstance()->AABB(t->getPos(), GerenciadorDeCamera::getInstance()->camera))
			t->setScreen(true);
	}

	for (auto& t : hitbox_plataformas) {
		t->setScreen(false);
		if (GerenciadorDeColisao::getInstance()->AABB(t->getPos(), GerenciadorDeCamera::getInstance()->camera))
			t->setScreen(true);
	}

	GerenciadorDeColisao::getInstance()->atualizaObstaculos();

	GerenciadorDeColisao::getInstance()->colisao_jogadores();
}

void TileMap::render() {
	for (auto& t : camada1)
		if (t->isOnScreen())
			t->render();

	for (auto& t : camada2) 
		if (t->isOnScreen())
			t->render();

	/*for (auto& t : hitbox_plataformas)
		if (t->isOnScreen())
			t->renderHitbox();	*/
}

void TileMap::clear() {
	for (auto& t : camada1)
		delete t;
	camada1.clear();

	for (auto& t : camada2)
		delete t;
	camada2.clear();

	for (auto& t : hitbox_plataformas)
		delete t;
	hitbox_plataformas.clear();

	posicoes_espinhos.clear();
	posicoes_lava.clear();
	GerenciadorDeColisao::getInstance()->clear();
}

SDL_Point TileMap::getNTiles() {
	return nTiles;
}
