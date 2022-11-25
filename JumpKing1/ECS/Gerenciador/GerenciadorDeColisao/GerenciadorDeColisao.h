#pragma once
#include <SDL.h>
#include <vector>
#include <list>
#include <fstream>

class Jogador;
class TileMap;
class Obstaculo;
class Projetil;
class Esqueleto;
class Goblin;
class Inimigo;
class Fase;
class Jogo;
class Inimigo;

class GerenciadorDeColisao
{
public:
	~GerenciadorDeColisao();

	static GerenciadorDeColisao* getInstance();
	static void deleteInstance();
	void colidir();

	void addObstaculo(Obstaculo* obst);
	void addProjetil(Projetil* proj);
	void addInimigo(Inimigo* in);

	void iniciaInimigo(Inimigo* in);

	void atualizaInimigos();
	void atualizaObstaculos();
	void atualizaProjeteis();

	bool allEnemiesDead();
	
	void clear();
	
	void setFase(Fase* fs);
	void setTileMap(TileMap* tmap);
	void setJogador(Jogador* jg);
	void setJogador2(Jogador* jg);
	Jogador* getJogador1();
	Jogador* getJogador2();

	void colisao_jogadores();
	void colisao_jogadores_obstaculos();
	void colisao_jogadores_inimigos();
	void colisao_jogadores_projeteis();
	void colisao_inimigo_obstaculos(Inimigo* in1);
	void colisao_projeteis_obstaculos();

	void ataqueInimigo(Inimigo* in, SDL_Rect hitbox);
	void ataqueJ1();
	void ataqueJ2();

	bool AABB(SDL_Rect A, SDL_Rect B);
private:
	GerenciadorDeColisao();
	static GerenciadorDeColisao* manager;

	Jogador* jogador1;
	Jogador* jogador2;
	TileMap* tilemap;
	Fase* fase;
	std::vector<Obstaculo*> obstaculos;
	std::vector<Projetil*> projeteis;
	std::vector<Inimigo*> inimigos;
};

