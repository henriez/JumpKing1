#pragma once

#include <vector>

#include "../Personagem/Jogador/Jogador.h"
#include "../Personagem/Inimigo/Esqueleto/Esqueleto.h"
#include "../Personagem/Inimigo/Zumbi/Zumbi.h"
#include "../Personagem/Inimigo/Chefe/Chefe.h"
#include "../Projetil/Projetil.h"
#include "../../Lista/Lista.h"

class ListaDeEntidades {
public:
	ListaDeEntidades();
	~ListaDeEntidades();

	void addEntidade(Entidade* en);
	void clear();

	void atualizar();
	void render();
private:
	Lista<Entidade*> listaEntidades;

};