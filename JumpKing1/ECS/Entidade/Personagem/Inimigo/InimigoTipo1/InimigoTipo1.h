#pragma once

#include "../Inimigo.h"

class InimigoTipo1 : public Inimigo {
public:
	InimigoTipo1();
	~InimigoTipo1();

	void atualizar();
	void render();
};