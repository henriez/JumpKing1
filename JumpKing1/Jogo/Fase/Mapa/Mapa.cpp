#include "Mapa.h"
#include "../../Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico.h"
#include "../../../ECS/Gerenciador/GerenciadorDeCamera.h"
#include <iostream>

Vector2D Mapa::nTiles;
int Mapa::tamanhoDoTile;

Mapa::Mapa() {
	backgroundTex = nullptr;
	tamanhoDoTile = 32;
}

Mapa::~Mapa() {
	clear();

}

void Mapa::inicializar() {
	backgroundTex = GerenciadorGrafico::CarregaTextura("Assets/TileMap/mapa1background.png");

	tileMap.inicializa(); //passar id de mapa
	nTiles = tileMap.getNTiles();
	GerenciadorDeCamera::init();
}

void Mapa::atualizar() {
	GerenciadorDeCamera::Atualiza();
	tileMap.atualiza();
}

void Mapa::render() {;
	SDL_Rect destino = { 0, 0, GerenciadorDeCamera::camera.w, GerenciadorDeCamera::camera.h };
	GerenciadorGrafico::Desenhe(backgroundTex, GerenciadorDeCamera::camera, destino);

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