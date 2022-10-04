#pragma once
#include "Tile.h"
#include <vector>

class TileMap {
public:
	TileMap();
	~TileMap();
	void inicializa();
	void atualiza();
	void render();

	Vector2D getNTiles();
private:
	void adicionaTile();
	std::vector<Tile*> camada1;
	std::vector<Tile*> camada2;
	std::vector<Tile*> camada_espinhos;

	Vector2D nTiles;
};