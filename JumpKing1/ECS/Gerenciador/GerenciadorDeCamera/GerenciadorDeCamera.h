#pragma once 
#include <SDL.h>

class Jogador;
class Fase;

class GerenciadorDeCamera
{
private:
	GerenciadorDeCamera();
	Jogador* jogador;
	Jogador* jogador2;
	static GerenciadorDeCamera* manager;
public:
	
	~GerenciadorDeCamera();

	static GerenciadorDeCamera* getInstance();
	static void deleteInstance();
	void init();
	void Atualiza();
	void AtualizaJogador();

	void setJogador(Jogador* jg);
	void setJogador2(Jogador* jg);
	SDL_Rect camera;
};
