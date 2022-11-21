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
	GerenciadorDeColisao();
	~GerenciadorDeColisao();

	static void colidir();

	static void addObstaculo(Obstaculo* obst);
	static void addProjetil(Projetil* proj);
	static void addInimigo(Inimigo* in);

	static void iniciaInimigo(Inimigo* in);

	static void atualizaInimigos();
	static void atualizaObstaculos();
	static void atualizaProjeteis();

	static bool allEnemiesDead();

	static void renderObstaculos();
	static void renderProjeteis();
	
	static void clear();
	
	static void setFase(Fase* fs);
	static void setTileMap(TileMap* tmap);
	static void setJogador(Jogador* jg);
	static void setJogador2(Jogador* jg);
	static Jogador* getJogador1();
	static Jogador* getJogador2();

	static void colisao_jogadores();
	static void colisao_jogadores_obstaculos();
	static void colisao_jogadores_inimigos();
	static void colisao_jogadores_projeteis();
	static void colisao_inimigo_obstaculos(Inimigo* in1);
	static void colisao_projeteis_obstaculos();

	static void ataqueInimigo(Inimigo* in1, SDL_Rect hitbox) {}
	static void ataqueEsqueleto(Esqueleto* in1);
	static void ataqueGoblin(Goblin* in1);
	static void ataqueJ1();
	static void ataqueJ2();

	static bool AABB(SDL_Rect A, SDL_Rect B);
private:

	static Jogador* jogador1;
	static Jogador* jogador2;
	static TileMap* tilemap;
	static Fase* fase;
	static std::vector<Obstaculo*> obstaculos;
	static std::vector<Projetil*> projeteis;
	static std::vector<Inimigo*> inimigos;
};

