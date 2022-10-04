#pragma once

#include "../Inimigo.h"

class InimigoTipo2 : public Inimigo {
public:
	InimigoTipo2();
	~InimigoTipo2();

	void atualizar();
	void render();
};