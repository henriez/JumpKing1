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

			if (id) {
				Tile* tile = new Tile;
				tile->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
				camada1.push_back(tile);
			}
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

			if (id) {
				Tile* tile = new Tile;
				tile->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
				camada2.push_back(tile);
			}
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

			if (id) {
				Tile* tile = new Tile;
				tile->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
				if (id == 1) {
					hitbox_plataformas.push_back(tile);
					tile->setColide(true);
					//GerenciadorDeColisao::getInstance()->addObstaculo(tile);

				}
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
