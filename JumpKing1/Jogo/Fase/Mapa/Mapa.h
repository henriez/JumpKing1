#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "../../../ECS/Componentes/Vector2D/Vector2D.h"
#include "TileMap/TileMap.h"

class Jogo;

class Mapa {
public:
	Mapa();
	~Mapa();
	void inicializar(Jogo* jg);

	void atualizar();
	void render();
	static int tamanhoTile();
	static Vector2D getDimensoes();

	static Vector2D camera;
	static Vector2D dimensoesCamera;
	void clear();

private:
	SDL_Texture* backgroundTex; //background
	Jogo* jogo;
	static Vector2D nTiles;
	static int tamanhoDoTile;
	TileMap tileMap;
};