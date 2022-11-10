#pragma once
#include <SDL.h>
#include "../../Entidade/Personagem/Jogador/Jogador.h"

class GerenciadorDeEventos {
public:
	~GerenciadorDeEventos();
	static GerenciadorDeEventos* getInstance();
	static void deleteInstance();

	void atualizar();
	void setJogador1(Jogador* pl);
	void setJogador2(Jogador* pl);
private:
	GerenciadorDeEventos();
	static GerenciadorDeEventos* manager;
	Jogador* jogador;
	Jogador* jogador2;
};