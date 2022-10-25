#include "../../Jogo/Jogo.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* GerenciadorDeTexturas::CarregaTextura(const char* fileName){
	SDL_Texture* tex = IMG_LoadTexture(Jogo::renderer, fileName);
	if (tex == NULL)
		std::cout << SDL_GetError() << std::endl;

	return tex;
}

void GerenciadorDeTexturas::Desenhe(SDL_Texture* tex, SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(Jogo::renderer, tex, &fonte, &destino);
}