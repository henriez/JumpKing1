#pragma once

#include "../Inimigo.h"

class InimigoTipo3 : public Inimigo {
public:
	InimigoTipo3();
	~InimigoTipo3();
	
	void atualizar();
	void render();
};