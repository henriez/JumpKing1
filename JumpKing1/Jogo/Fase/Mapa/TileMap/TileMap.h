#pragma once
#include "../../ECS/Entidade/Obstaculo/Tile/Tile.h"
#include "../../ECS/Entidade/Obstaculo/Espinhos/Espinhos.h"
#include "../../ECS/Entidade/Obstaculo/Lava/Lava.h"
#include <vector>

class Jogador;

class TileMap {
public:
	TileMap();
	~TileMap();

	void carregaPosicoesValidas(const char* posicoes_lava, const char* posicoes_espinhos);
	void inicializa(const char* cam1, const char* cam2, const char* cam_colisao, int tilesW, int tilesH);
	void atualiza();
	void render();

	void clear();

	Vector2D getNTiles();
private:
	std::vector<Tile*> camada1;
	std::vector<Tile*> camada2;
	std::vector<Lava*> camada_lava;
	std::vector<Espinhos*> camada_espinhos;
	std::vector<Tile*> hitbox_plataformas;
	std::vector<Tile*> hitbox_espinhos;
	std::vector<Tile*> hitbox_lavas;


	Vector2D nTiles;

	std::vector<SDL_Point> posicoes_lava;
	std::vector<SDL_Point> posicoes_espinhos;

	friend class GerenciadorDeColisao;
};