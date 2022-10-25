#include "Mapa.h"
#include "../../Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorDeTexturas.h"
#include "../../../ECS/Gerenciador/GerenciadorDeCamera.h"
#include <iostream>


Vector2D Mapa::camera;
Vector2D Mapa::dimensoesCamera;
Vector2D Mapa::nTiles;
int Mapa::tamanhoDoTile;

Mapa::Mapa() {
	backgroundTex = nullptr;
	jogo = nullptr;
	camera.x = camera.y = 0;
	tamanhoDoTile = 32;
}

Mapa::~Mapa() {
	clear();
}

void Mapa::inicializar(Jogo* jg) {
	jogo = jg;
	backgroundTex = GerenciadorDeTexturas::CarregaTextura("Assets/TileMap/mapa1background.png");

	SDL_DisplayMode dm;

	SDL_GetCurrentDisplayMode(0, &dm);
	dimensoesCamera.x = dm.w;
	dimensoesCamera.y = dm.h;

	tileMap.inicializa(); //passar id de mapa
	nTiles = tileMap.getNTiles();
}

void Mapa::atualizar() {
	GerenciadorDeCamera::Atualiza();
	tileMap.atualiza();
}

void Mapa::render() {
	SDL_Rect tela = { 0,0,(int)Jogo::getDimensoesJanela().x,(int)Jogo::getDimensoesJanela().y };
	SDL_Rect cam = { camera.x, camera.y, dimensoesCamera.x, dimensoesCamera.y };
	GerenciadorDeTexturas::Desenhe(backgroundTex, cam, tela);

	tileMap.render();
}

int Mapa::tamanhoTile() {
	return tamanhoDoTile;
}

Vector2D Mapa::getDimensoes() {
	return nTiles*tamanhoDoTile;
}

void Mapa::clear() {
	if(backgroundTex != NULL)
		SDL_DestroyTexture(backgroundTex);
}