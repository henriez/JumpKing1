#pragma once 
#include <SDL.h>

class Jogador;

class GerenciadorDeCamera
{
private:
	static Jogador* jogador;
public:
	GerenciadorDeCamera();
	~GerenciadorDeCamera();
	static void init();
	static void Atualiza();
	static void AtualizaJogador();

	static void setJogador(Jogador* jg);
	static SDL_Rect camera;
};
