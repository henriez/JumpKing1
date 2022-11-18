#pragma once

#include "../Fase.h"

class Fase1 : public Fase
{
private:
	int nEsqueletos;
	int nChefes;
public:
	Fase1();
	~Fase1();

	void inicializar();
	void atualizar();
	
	void criaEsqueletos();
	
	void save();
	void saveRank();
	void load();

};