#pragma once
#include "ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"

class Ente {
public:
	Ente();
	virtual ~Ente();

	virtual void atualizar() = 0;
	virtual void render() = 0;

	//static setGraphics();
protected:
	//static GerenciadorGrafico* graphics;
	static GerenciadorGrafico* graphics;
};