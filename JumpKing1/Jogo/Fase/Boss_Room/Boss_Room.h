#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "../../../ECS/Componentes/Vector2D/Vector2D.h"
#include "../Mapa/TileMap/TileMap.h"

class Boss_Room {
public:
	Boss_Room();
	~Boss_Room();
	void inicializar(int id);
	void reload(int id);

	void atualizar();
	void render();
	static int tamanhoTile();
	static SDL_Point getDimensoes();
	
	void clear();

private:
	SDL_Texture* backgroundTex; //background
	static SDL_Point nTiles;
	static int tamanhoDoTile;
	TileMap tileMap;
	GerenciadorGrafico* graphics;
};