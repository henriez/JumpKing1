#pragma once
#include <SDL.h>
#include "../../../Componentes/SubComponentes/ComponenteTransform.h"

class Jogador;

class ControladorDeEventos {
public:
	ControladorDeEventos();
	~ControladorDeEventos();

	void atualizar();
	void setTransform(Jogador* pl);
private:
	Jogador* jogador;
};