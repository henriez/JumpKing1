#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "../../../ECS/Componentes/Vector2D/Vector2D.h"
#include "TileMap/TileMap.h"
#include "../Boss_Room/Boss_Room.h"

class Jogo;

class Mapa {
public:
	Mapa();
	~Mapa();
	void inicializar(int id);
	void reload(int id);

	void atualizar();
	void render();
	static int tamanhoTile();
	static SDL_Point getDimensoes();
	static void setDimMapa(int w, int h);

	void setBossRoom(const bool inBossRoom) { onBossRoom = inBossRoom; }
	bool isOnBossRoom() const { return onBossRoom; }
	
	void clear();

private:
	SDL_Texture* backgroundTex; //background
	static SDL_Point nTiles;
	static int tamanhoDoTile;
	TileMap tileMap;
	Boss_Room boss_room;
	bool onBossRoom;
	SDL_Rect fim; //retangulo que indica fim da fase (entrada da sala do boss)
	int id; //relativo à fase
	GerenciadorGrafico* graphics;
};