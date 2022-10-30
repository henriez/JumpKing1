#pragma once
#include "../../../../ECS/Componentes/ListaDeComponentes/ListaDeComponentes.h"

class Tile {
public:
	Tile();
	~Tile();
	void render();

	static void setTex(const char* path);
	void setPosition(int x, int y, int srcX, int srcY);
private:
	ListaDeComponentes componentes;
	static SDL_Texture* tileset;
	SDL_Rect fonte;
	SDL_Rect destino;
};