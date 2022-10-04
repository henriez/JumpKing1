#pragma once
#include "../Personagem.h"

class Inimigo : public Personagem {
public:
	Inimigo() {}
	~Inimigo() {}

	virtual void atualizar() = 0;
	virtual void render() = 0;
};