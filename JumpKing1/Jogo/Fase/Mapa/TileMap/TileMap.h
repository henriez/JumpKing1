#pragma once
#include "Tile.h"
#include <vector>

class Jogador;

class TileMap {
public:
	TileMap();
	~TileMap();
	void inicializa();
	void atualiza();
	void render();

	void clear();

	Vector2D getNTiles();

	void colisao_jogador1();
private:
	std::vector<Tile*> camada1;
	std::vector<Tile*> camada2;
	std::vector<Tile*> camada_espinhos;
	std::vector<Tile*> hitbox_plataformas;
	std::vector<Tile*> hitbox_espinhos;

	Vector2D nTiles;
	int algarismos[3];

	friend class GerenciadorDeColisao;
};