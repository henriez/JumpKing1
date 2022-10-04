#pragma once 
#include <SDL.h>

class Jogador;
class Mapa;

class GerenciadorDeCamera
{
private:
	static Jogador* jogador;
public:
	GerenciadorDeCamera();
	~GerenciadorDeCamera();
	static void Atualiza();
	static void AtualizaJogador();

	static void setJogador(Jogador* jg);
};
