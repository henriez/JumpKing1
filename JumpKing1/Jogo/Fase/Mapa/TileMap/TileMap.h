#pragma once
#include "../../ECS/Entidade/Obstaculo/Tile/Tile.h"
#include "../../ECS/Entidade/Obstaculo/Espinhos/Espinhos.h"
#include <vector>

class Jogador;

class TileMap {
public:
	TileMap();
	~TileMap();
	void inicializa(const char* cam1, const char* cam2, const char* cam_colisao, const char* cam_espinhos, int tilesW, int tilesH);
	void atualiza();
	void render();

	void clear();

	Vector2D getNTiles();
private:
	std::vector<Tile*> camada1;
	std::vector<Tile*> camada2;
	std::vector<Espinhos*> camada_espinhos;
	std::vector<Tile*> hitbox_plataformas;
	std::vector<Tile*> hitbox_espinhos;


	Vector2D nTiles;
	int algarismos[3];

	friend class GerenciadorDeColisao;
};