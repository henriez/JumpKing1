#pragma once
#include "../Entidade.h"

class Personagem : public Entidade {
public:
	Personagem() {}
	virtual ~Personagem() {}

	virtual void atualizar() = 0;
	virtual void render() = 0;
};