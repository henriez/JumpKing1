#pragma once 
#include <SDL.h>

class GerenciadorGrafico
{
public:
	GerenciadorGrafico();
	~GerenciadorGrafico();

	static void init_tileMap();
	static void setRenderer(SDL_Renderer* rend);

	static SDL_Texture* CarregaTextura(const char* fileName);
	static void Desenhe(SDL_Texture* tex, SDL_Rect fonte, SDL_Rect destino);

	static void renderTile(SDL_Rect fonte, SDL_Rect destino);
	static void renderHitbox(SDL_Rect fonte, SDL_Rect destino);
private:
	static SDL_Texture* tileset;
	static SDL_Texture* tilesetHitbox;
	static SDL_Renderer* renderer
		;
};
