#pragma once 
#include <SDL.h>

class GerenciadorDeTexturas
{
public:
	static SDL_Texture* CarregaTextura(const char* fileName);
	static void Desenhe(SDL_Texture* tex, SDL_Rect fonte, SDL_Rect destino);
};
