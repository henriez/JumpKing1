#pragma once
#include "Mapa/Mapa.h"
#include "../../ECS/Entidade/ListaDeEntidades/ListaDeEntidades.h"
#include "../Jogo.h"

class Fase {
public:
	Fase();
	~Fase();

	void inicializar(Jogo* jg);
	void atualizar();
	void render();
private:
	ListaDeEntidades listaEntidades;
	const char* arquivoSave;
	Mapa* mapa;
	Jogo* jogo;
};