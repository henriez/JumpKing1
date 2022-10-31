#pragma once
#include "../../../../ECS/Componentes/ListaDeComponentes/ListaDeComponentes.h"
#include "../../ECS/Entidade/Obstaculo/Obstaculo.h"

class Tile : public Obstaculo{
public:
	Tile();
	~Tile();
	void render();
	void renderHitbox();

	void atualizar();

	SDL_Rect getPos() const;
	bool isOnScreen() const;
	void setScreen(const bool inScreen);

	static void setTex(const char* path, const char* hitboxPath);
	void setPosition(int x, int y, int srcX, int srcY);
private:
	static SDL_Texture* tileset;
	static SDL_Texture* tilesetHitbox;
	SDL_Rect fonte;
	SDL_Rect destino;
	bool onScreen;
};