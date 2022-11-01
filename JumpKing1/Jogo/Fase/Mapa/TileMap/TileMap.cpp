#include "TileMap.h"
#include "../../../Jogo.h"
#include "../../../../ECS/Gerenciador/GerenciadorGrafico.h"
#include "../../../../ECS/Gerenciador/GerenciadorDeColisao.h"
#include "../../../../ECS/Gerenciador/GerenciadorDeCamera.h"
#include "../Mapa.h"

#include <fstream>
#include <SDL_image.h>

const char* mapa1_camada1 = "Assets/TileMap/Mapa1/mapa1_camada_tiles_1.csv";
const char* mapa1_camada2 = "Assets/TileMap/Mapa1/mapa1_camada_tiles_2.csv";
const char* mapa1_camada_espinhos = "Assets/TileMap/Mapa1/mapa1_camada_espinhos.csv";
const char* mapa1_camada_colisao = "Assets/TileMap/Mapa1/mapa1_camada_colisao.csv";

const int largura = 11;
const int altura = 12;
const int tamanhoTile = 32;

TileMap::TileMap() {
	nTiles.x = 80;
	nTiles.y = 200;
	algarismos[0] = algarismos[1] = algarismos[2] = 0;
	GerenciadorDeColisao::setTileMap(this);
	GerenciadorGrafico::init_tileMap();
}

TileMap::~TileMap() {
	clear();
}

void TileMap::inicializa() {
	

	char c = 0;
	std::fstream mapFile;

	int srcX, srcY, alg, id; //diferentes algarismos
	srcX = srcY = alg = id = 0;

	mapFile.open(mapa1_camada1);
	for (int i = 0; i < nTiles.y; i++) {
		for (int j = 0; j < nTiles.x; j++) {
			algarismos[0] = algarismos[1] = algarismos[2] = alg = 0;
			mapFile.get(c);

			if (c == '-') {
				mapFile.ignore();
				mapFile.ignore();
				continue;
			}
			if (j == nTiles.x - 1)
				while (c != '\n') {
					algarismos[alg++] = atoi(&c);
					mapFile.get(c);
				}
			else {
				while (c != ',') {
					algarismos[alg++] = atoi(&c);
					mapFile.get(c);
				}
			}
			// ao final do loop alg será 2 3 (depende do n de algarismos do id)
			if (alg == 3)
				id = algarismos[0] * 100 + algarismos[1] * 10 + algarismos[2];
			else if (alg == 2)
				id = algarismos[0] * 10 + algarismos[1];
			else //alg == 1
				id = algarismos[0];

			srcY = (id / largura) * tamanhoTile;
			srcX = (id % largura) * tamanhoTile;

			Tile* tile = new Tile;
			tile->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
			camada1.push_back(tile);
		}
	}
	mapFile.close();


	mapFile.open(mapa1_camada2);
	for (int i = 0; i < nTiles.y; i++) {
		for (int j = 0; j < nTiles.x; j++) {
			algarismos[0] = algarismos[1] = algarismos[2] = alg = 0;
			mapFile.get(c);

			if (c == '-') {
				mapFile.ignore();
				mapFile.ignore();
				continue;
			}
			if (j == nTiles.x - 1)
				while (c != '\n') {
					algarismos[alg++] = atoi(&c);
					mapFile.get(c);
				}
			else {
				while (c != ',') {
					algarismos[alg++] = atoi(&c);
					mapFile.get(c);
				}
			}
			// ao final do loop alg será 2 3 (depende do n de algarismos do id)
			if (alg == 3)
				id = algarismos[0] * 100 + algarismos[1] * 10 + algarismos[2];
			else if (alg == 2)
				id = algarismos[0] * 10 + algarismos[1];
			else //alg == 1
				id = algarismos[0];

			srcY = (id / largura) * tamanhoTile;
			srcX = (id % largura) * tamanhoTile;

			Tile* tile = new Tile;
			tile->setPosition(j*tamanhoTile, i*tamanhoTile, srcX, srcY);
			camada2.push_back(tile);
		}
	}
	mapFile.close();


	mapFile.open(mapa1_camada_espinhos);
	for (int i = 0; i < nTiles.y; i++) {
		for (int j = 0; j < nTiles.x; j++) {
			algarismos[0] = algarismos[1] = algarismos[2] = alg = 0;
			mapFile.get(c);

			if (c == '-') {
				mapFile.ignore();
				mapFile.ignore();
				continue;
			}
			if (j == nTiles.x - 1)
				while (c != '\n') {
					algarismos[alg++] = atoi(&c);
					mapFile.get(c);
				}
			else {
				while (c != ',') {
					algarismos[alg++] = atoi(&c);
					mapFile.get(c);
				}
			}
			// ao final do loop alg será 2 3 (depende do n de algarismos do id)
			if (alg == 3)
				id = algarismos[0] * 100 + algarismos[1] * 10 + algarismos[2];
			else if (alg == 2)
				id = algarismos[0] * 10 + algarismos[1];
			else //alg == 1
				id = algarismos[0];

			srcY = (id / largura) * tamanhoTile;
			srcX = (id % largura) * tamanhoTile;

			Espinhos* espinhos = new Espinhos;
			espinhos->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
			camada_espinhos.push_back(espinhos);
		}
	}
	mapFile.close();

	mapFile.open(mapa1_camada_colisao);
	for (int i = 0; i < nTiles.y; i++) {
		for (int j = 0; j < nTiles.x; j++) {
			id = 0;
			mapFile.get(c);

			if (c == '-') {
				mapFile.ignore();
				mapFile.ignore();
				continue;
			}
			id = atoi(&c);
			mapFile.ignore();

			srcY = 0;
			srcX = id * tamanhoTile;

			Tile* tile = new Tile;
			tile->setPosition(j * tamanhoTile, i * tamanhoTile, srcX, srcY);
			if (id == 1)
				hitbox_plataformas.push_back(tile);
			else if (id == 2)
				hitbox_espinhos.push_back(tile);
		}
	}
	mapFile.close();
}

void TileMap::atualiza() {
	for (auto& t : camada1) {
		t->setScreen(false);
		if (GerenciadorDeColisao::AABB(t->getPos(), GerenciadorDeCamera::camera))
			t->setScreen(true);
	}

	for (auto& t : camada2) {
		t->setScreen(false);
		if (GerenciadorDeColisao::AABB(t->getPos(), GerenciadorDeCamera::camera))
			t->setScreen(true);
	}

	for (auto& t : camada_espinhos) {
		t->setScreen(false);
		if (GerenciadorDeColisao::AABB(t->getPos(), GerenciadorDeCamera::camera))
			t->setScreen(true);
	}

	for (auto& t : hitbox_plataformas) {
		t->setScreen(false);
		if (GerenciadorDeColisao::AABB(t->getPos(), GerenciadorDeCamera::camera))
			t->setScreen(true);
	}

	for (auto& t : hitbox_espinhos) {
		t->setScreen(false);
		if (GerenciadorDeColisao::AABB(t->getPos(), GerenciadorDeCamera::camera))
			t->setScreen(true);
	}

	colisao_jogador1();
}

void TileMap::render() {
	for (auto& t : camada1)
		if (t->isOnScreen())
			t->render();

	for (auto& t : camada2) 
		if (t->isOnScreen())
			t->render();

	for (auto& t : camada_espinhos)
		if (t->isOnScreen())
			t->render();

	for (auto& t : hitbox_plataformas)
		if (t->isOnScreen())
			t->renderHitbox();

	for (auto& t : hitbox_espinhos)
		if (t->isOnScreen())
			t->renderHitbox();
}

void TileMap::clear() {
	for (auto& t : camada1)
		delete t;
	camada1.clear();

	for (auto& t : camada2)
		delete t;
	camada2.clear();

	for (auto& t : camada_espinhos)
		delete t;
	camada_espinhos.clear();

	for (auto& t : hitbox_plataformas)
		delete t;
	hitbox_plataformas.clear();

	for (auto& t : hitbox_espinhos)
		delete t;
	hitbox_espinhos.clear();
}

Vector2D TileMap::getNTiles() {
	return nTiles;
}

void TileMap::colisao_jogador1() {
	Jogador* jg = GerenciadorDeColisao::getJogador1();
	bool collided = true;

	SDL_Rect initialhitbox = jg->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect hitbox = initialhitbox;

	ComponenteTransform* transform = jg->getComponente<ComponenteTransform>();
	
	Vector2D velocity = transform->velocidade;

	if (!jg->inGround())
		transform->velocidade.y += 0.05; // simula gravidade 

	for (auto& t : hitbox_plataformas) {
		if (t->isOnScreen()) {
			hitbox = initialhitbox;
			hitbox.y += velocity.y * jg->getSpeed();
			if (GerenciadorDeColisao::AABB(t->getPos(), hitbox)) {
				if (velocity.y > 0) { //colidiu por cima
					jg->setGround(true); 
					transform->posicao.y = t->getPos().y - hitbox.h;
				}
				else if (velocity.y < 0) //colidiu por baixo
					transform->posicao.y = t->getPos().y + hitbox.h;
				transform->velocidade.y = 0;
				
			}
			hitbox = initialhitbox;
			hitbox.x += velocity.x * jg->getSpeed();
			if (GerenciadorDeColisao::AABB(t->getPos(), hitbox)) {
				if (velocity.x > 0) { //colidiu pela esquerda
					transform->posicao.x = t->getPos().x - hitbox.w;
				}
				else if (velocity.x < 0) //colidiu pela direita
					transform->posicao.x = t->getPos().x + hitbox.w;
				transform->velocidade.x = 0;
			}
		}
	}

	SDL_Rect hitbox_espinho = {0,0,0,0};
	
	for (auto& t : hitbox_espinhos) {
		if (t->isOnScreen()) {
			//hitbox na parte inferior do tile
			hitbox_espinho.x = t->getPos().x;
			hitbox_espinho.y = t->getPos().y + tamanhoTile / 2;
			hitbox_espinho.w = t->getPos().w;
			hitbox_espinho.h = t->getPos().h - tamanhoTile / 2;

			//mesma checagem usada para as plataformas
			hitbox = initialhitbox;
			hitbox.y += velocity.y * jg->getSpeed();
			if (GerenciadorDeColisao::AABB(hitbox_espinho, hitbox)) {
				if (velocity.y > 0) { //colidiu por cima
					jg->setGround(true);
					transform->posicao.y = hitbox_espinho.y - hitbox.h;
				}
				else if (velocity.y < 0) //colidiu por baixo // em teoria, pela montagem da fase, nunca deve acontecer
					transform->posicao.y = hitbox_espinho.y + hitbox_espinho.h;
				transform->velocidade.y = 0;
				collided = true;
			}
			hitbox = initialhitbox;
			hitbox.x += velocity.x * jg->getSpeed();
			if (GerenciadorDeColisao::AABB(hitbox_espinho, hitbox)) {
				if (velocity.x > 0) { //colidiu pela esquerda
					transform->posicao.x = t->getPos().x - hitbox.w;
				}
				else if (velocity.x < 0) //colidiu pela direita
					transform->posicao.x = t->getPos().x + hitbox.w;
				transform->velocidade.x = 0;
			}
		}
	}
}