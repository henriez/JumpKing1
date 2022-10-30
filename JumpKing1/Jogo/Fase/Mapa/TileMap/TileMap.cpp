#include "TileMap.h"
#include "../../../Jogo.h"
#include "../../../../ECS/Gerenciador/GerenciadorDeTexturas.h"

#include <fstream>
#include <SDL_image.h>

const char* mapa1_camada1 = "Assets/TileMap/mapa1_camada_tiles_1.csv";
const char* mapa1_camada2 = "Assets/TileMap/mapa1_camada_tiles_2.csv";
const char* mapa1_camada_espinhos = "Assets/TileMap/mapa1_camada_espinhos.csv";

const char* tiles_png = "Assets/TileMap/Tiles.png";
const int largura = 11;
const int altura = 12;
const int tamanhoTile = 32;

TileMap::TileMap() {
	nTiles.x = 80;
	nTiles.y = 200;
	algarismos[0] = algarismos[1] = algarismos[2] = 0;

	Tile::setTex(tiles_png);
}

TileMap::~TileMap() {}

void TileMap::inicializa() {
	char c = 0;
	std::fstream mapFile;

	int srcX, srcY, alg, id; //diferentes algarismos
	srcX = srcY = alg = id = 0;

	mapFile.open(mapa1_camada1);
	for (int i = 0; i < nTiles.y; i++) {
		for (int j = 0; j < nTiles.x; j++) {
			algarismos[0] = algarismos[1] = algarismos[2] = alg = 0;
			mapFile.get(c);
			if (c == '-') {
				mapFile.get(c);
				mapFile.get(c);
				continue;
			}
			while (c != ',') {
				algarismos[alg++] = atoi(&c);
				mapFile.get(c);
			}
			// ao final do loop alg será 2 3 (depende do n de algarismos do id)
			if (alg == 3)
				id = algarismos[0] * 100 + algarismos[1] * 10 + algarismos[2];
			else if (alg == 2)
				id = algarismos[0] * 10 + algarismos[1];

			srcY = (id / largura) * tamanhoTile;
			srcX = (id % largura) * tamanhoTile;

			Tile* tile = new Tile;
			tile->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
			camada1.push_back(tile);
		}
	}
	mapFile.close();


	mapFile.open(mapa1_camada2);

	for (int i = 0; i < nTiles.y; i++) {
		for (int j = 0; j < nTiles.x; j++) {
			algarismos[0] = algarismos[1] = algarismos[2] = alg = 0;
			mapFile.get(c);

			if (c == '-') {
				mapFile.get(c);
				mapFile.get(c);
				continue;
			}
			while (c != ',') {
				algarismos[alg++] = atoi(&c);
				mapFile.get(c);
			}
			// ao final do loop alg será 2 3 (depende do n de algarismos do id)
			if (alg == 3)
				id = algarismos[0] * 100 + algarismos[1] * 10 + algarismos[2];
			else if(alg == 2)
				id = algarismos[0] * 10 + algarismos[1];

			srcY = (id / largura) * tamanhoTile;
			srcX = (id % largura) * tamanhoTile;

			Tile* tile = new Tile;
			tile->setPosition(j*tamanhoTile, i*tamanhoTile, srcX, srcY);
			camada2.push_back(tile);
		}
	}

	mapFile.close();


	mapFile.open(mapa1_camada_espinhos);
	for (int i = 0; i < nTiles.y; i++) {
		for (int j = 0; j < nTiles.x; j++) {
			algarismos[0] = algarismos[1] = algarismos[2] = alg = 0;
			mapFile.get(c);
			if (c == '-') {
				mapFile.get(c);
				mapFile.get(c);
				continue;
			}
			while (c != ',') {
				algarismos[alg++] = atoi(&c);
				mapFile.get(c);
			}
			// ao final do loop alg será 2 3 (depende do n de algarismos do id)
			if (alg == 3)
				id = algarismos[0] * 100 + algarismos[1] * 10 + algarismos[2];
			else if (alg == 2)
				id = algarismos[0] * 10 + algarismos[1];

			srcY = (id / largura) * tamanhoTile;
			srcX = (id % largura) * tamanhoTile;

			Tile* tile = new Tile;
			tile->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
			camada_espinhos.push_back(tile);
		}
	}
	mapFile.close();
}

void TileMap::atualiza() {}

void TileMap::render() {
	for (auto& t : camada1)
		t->render();

	for (auto& t : camada2)
		t->render();

	for (auto& t : camada_espinhos)
		t->render();
}

void TileMap::clear() {
	for (auto& t : camada1)
		delete t;

	camada1.clear();

	for (auto& t : camada2)
		delete t;

	camada2.clear();

	for (auto& t : camada_espinhos)
		delete t;

	camada_espinhos.clear();
}

Vector2D TileMap::getNTiles() {
	return nTiles;
}