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
}

TileMap::~TileMap() {}

void TileMap::inicializa() {
	std::ifstream mapFile;
	mapFile.open(mapa1_camada1);
	mapFile.close();


	mapFile.open(mapa1_camada2);
	mapFile.close();


	mapFile.open(mapa1_camada_espinhos);
	mapFile.close();
}

void TileMap::atualiza() {}

void TileMap::render() {}

Vector2D TileMap::getNTiles() {
	return nTiles;
}

void TileMap::adicionaTile() {} //coloca novo tile no vetor