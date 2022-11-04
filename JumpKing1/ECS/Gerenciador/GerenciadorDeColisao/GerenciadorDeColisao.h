#pragma once
#include <SDL.h>

class Jogador;
class TileMap;
class Esqueleto;
class Fase;
class Jogo;

class GerenciadorDeColisao
{
public:
	GerenciadorDeColisao();
	~GerenciadorDeColisao();

	static Jogador* getJogador1();
	static void setJogador(Jogador* jg);
	static void setJogo(Jogo* jg);
	static void setFase(Fase* fs);
	static void setTileMap(TileMap* tmap);

	static void colisao_jogador1();
	static void colisao_inimigo1(Esqueleto* in1);

	static bool AABB(SDL_Rect A, SDL_Rect B);
private:

	static Jogador* jogador1;
	static TileMap* tilemap;
	static Jogo* jogo;
	static Fase* fase;
};

