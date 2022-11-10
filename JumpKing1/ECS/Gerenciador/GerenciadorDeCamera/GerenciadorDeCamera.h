#pragma once 
#include <SDL.h>

class Jogador;
class Fase;

class GerenciadorDeCamera
{
private:
	static Jogador* jogador;
	static Jogador* jogador2;
public:
	GerenciadorDeCamera();
	~GerenciadorDeCamera();
	static void init();
	static void Atualiza();
	static void AtualizaJogador();

	static void setJogador(Jogador* jg);
	static void setJogador2(Jogador* jg);
	static SDL_Rect camera;
};
