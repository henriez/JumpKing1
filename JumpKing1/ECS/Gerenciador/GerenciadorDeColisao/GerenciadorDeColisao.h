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
class Inimigo;
class Fase;
class Jogo;
class Inimigo;

class GerenciadorDeColisao
{
public:
	GerenciadorDeColisao();
	~GerenciadorDeColisao();

	static Jogador* getJogador1();
	static Jogador* getJogador2();
	static void ataqueJ1();
	static void ataqueJ2();

	static void saveObstaculos(const char* path);
	static void saveProjeteis(const char* path);
	static void saveInimigos(const char* path);

	static void addInimigo(Inimigo* in);
	static void atualizaInimigos();

	static void addObstaculo(Obstaculo* obst);
	static void atualizaObstaculos();
	static void renderObstaculos();
	static void addProjetil(Projetil* proj);
	static void atualizaProjeteis();
	static void renderProjeteis();
	static void iniciaInimigo(Inimigo* in);
	static void clear();

	static void setJogador(Jogador* jg);
	static void setJogador2(Jogador* jg);
	static void setFase(Fase* fs);
	static void setTileMap(TileMap* tmap);

	static void colisao_jogador1();
	static void colisao_esqueleto(Esqueleto* in1);

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

