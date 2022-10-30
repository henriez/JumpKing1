#include "Tile.h"
#include "../../../Jogo.h"
#include "../../../../ECS/Gerenciador/GerenciadorDeTexturas.h"
#include "../Mapa.h"

#include <SDL_image.h>
#include <SDL.h>

SDL_Texture* Tile::tileset;

Tile::Tile() {
	componentes.addComponente<ComponenteColisao>();
	fonte = { 0,0,32,32 };
	destino = { 0,0,32,32 };}

Tile::~Tile() {}


void Tile::render() {
	SDL_Rect tempDest = { 0,0,32,32 };

	tempDest.x = destino.x - Mapa::camera.x;
	tempDest.y = destino.y - Mapa::camera.y;
	GerenciadorDeTexturas::Desenhe(Tile::tileset, fonte, tempDest);
}

void Tile::setTex(const char* path) {
	tileset = GerenciadorDeTexturas::CarregaTextura(path);
}

void Tile::setPosition(int x, int y, int srcX, int srcY) {
	destino.x = x;
	destino.y = y;
	fonte.x = srcX;
	fonte.y = srcY;
	//componentes.getComponente<ComponenteColisao>().set
}