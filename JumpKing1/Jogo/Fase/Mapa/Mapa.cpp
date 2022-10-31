#include "Mapa.h"
#include "../../Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorDeTexturas.h"
#include "../../../ECS/Gerenciador/GerenciadorDeCamera.h"
#include <iostream>


SDL_Rect Mapa::camera;
Vector2D Mapa::nTiles;
int Mapa::tamanhoDoTile;

Mapa::Mapa() {
	backgroundTex = nullptr;
	camera.x = camera.y = 0;
	tamanhoDoTile = 32;
}

Mapa::~Mapa() {
	clear();

}

void Mapa::inicializar() {
	backgroundTex = GerenciadorDeTexturas::CarregaTextura("Assets/TileMap/mapa1background.png");

	SDL_DisplayMode dm;

	SDL_GetCurrentDisplayMode(0, &dm);
	camera.w = dm.w;
	camera.h = dm.h;

	tileMap.inicializa(); //passar id de mapa
	nTiles = tileMap.getNTiles();
}

void Mapa::atualizar() {
	GerenciadorDeCamera::Atualiza();
	tileMap.atualiza();
}

void Mapa::render() {;
	SDL_Rect destino = { 0, 0, camera.w, camera.h };
	GerenciadorDeTexturas::Desenhe(backgroundTex, camera, destino);

	tileMap.render();
}

int Mapa::tamanhoTile() {
	return tamanhoDoTile;
}

Vector2D Mapa::getDimensoes() {
	return nTiles*tamanhoDoTile;
}

void Mapa::clear() {
	SDL_DestroyTexture(backgroundTex);
}