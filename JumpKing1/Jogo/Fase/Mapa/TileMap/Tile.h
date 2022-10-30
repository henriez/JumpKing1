#pragma once
#include "../../../../ECS/Componentes/ListaDeComponentes/ListaDeComponentes.h"

class Tile {
public:
	Tile();
	~Tile();
	void render();
	void renderHitbox();

	static void setTex(const char* path, const char* hitboxPath);
	void setPosition(int x, int y, int srcX, int srcY);
private:
	static SDL_Texture* tileset;
	static SDL_Texture* tilesetHitbox;
	SDL_Rect fonte;
	SDL_Rect destino;
};