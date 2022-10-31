#pragma once

#include "../../Ente.h"
#include "Mapa/Mapa.h"
#include "../../ECS/Entidade/ListaDeEntidades/ListaDeEntidades.h"
#include "../Jogo.h"

class Fase : public Ente{
public:
	Fase();
	~Fase();

	void inicializar();
	void atualizar();
	void render();
	void clear();
private:
	ListaDeEntidades listaEntidades;
	const char* arquivoSave;
	Mapa* mapa;
};