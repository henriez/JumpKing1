#pragma once

#include "../Fase.h"

class Fase1 : public Fase
{
private:
	int nEsqueletos;
	int nMagos;
public:
	Fase1();
	~Fase1();

	void inicializar();
	void atualizar();
	
	void criaEsqueletos();
	void criaMagos();

	void save();
	void saveRank();
	void load();

};