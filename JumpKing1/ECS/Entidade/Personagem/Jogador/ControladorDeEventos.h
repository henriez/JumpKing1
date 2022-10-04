#pragma once
#include <SDL.h>
#include "../../../Componentes/SubComponentes/ComponenteTransform.h"

class Jogador;

class ControladorDeEventos {
public:
	ControladorDeEventos();
	~ControladorDeEventos();

	void atualizar();
	void setJogador(Jogador* pl);
private:
	Jogador* jogador;
	ComponenteTransform* transform;
};