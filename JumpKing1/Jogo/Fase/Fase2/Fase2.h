#pragma once

#include "../Fase.h"

class Fase2 : public Fase
{
private:
	int nGoblins;
	int nChefes;
public:
	Fase2();
	~Fase2();

	void inicializar();
	void atualizar();
	
	void criaGoblins();
	
	void save();
	void saveRank();
	void load();

};