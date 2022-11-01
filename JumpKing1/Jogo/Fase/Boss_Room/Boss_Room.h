#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "../../../ECS/Componentes/Vector2D/Vector2D.h"
#include "../Mapa/TileMap/TileMap.h"

class Boss_Room {
public:
	Boss_Room();
	~Boss_Room();
	void inicializar();

	void atualizar();
	void render();
	static int tamanhoTile();
	static Vector2D getDimensoes();
	
	void clear();

private:
	SDL_Texture* backgroundTex; //background
	static Vector2D nTiles;
	static int tamanhoDoTile;
	TileMap tileMap;
};