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
	jogo = nullptr;
	camera = { 0,0,0,0 };
	tamanhoDoTile = 32;
}

Mapa::~Mapa() {
	SDL_DestroyTexture(backgroundTex);
}

void Mapa::inicializar(Jogo* jg) {
	jogo = jg;
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

void Mapa::render() {
	SDL_Rect tela = { 0,0,(int)Jogo::getDimensoesJanela().x,(int)Jogo::getDimensoesJanela().y };
	GerenciadorDeTexturas::Desenhe(backgroundTex, camera, tela);

	tileMap.render();
}

int Mapa::tamanhoTile() {
	return tamanhoDoTile;
}

Vector2D Mapa::getDimensoes() {
	return nTiles*tamanhoDoTile;
}