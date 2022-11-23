#pragma once

#include "../Inimigo.h"

class Esqueleto : public Inimigo {
public:
	Esqueleto(float x, float y, int agress = 0);
	~Esqueleto();

	const int getSpeed() const { return speed; }
	const bool facingLeft() const { return flip; }
	void setState(unsigned char val) { state = val; }

	void atualizar();
	void render();
	int attack();

	void salvar(int faseID) {
		ofstream file;
		if (faseID == 1) file.open("Saves/Fase1/esqueletos.dat", ios::app);
		else if (faseID == 2) file.open("Saves/Fase2/esqueletos.dat", ios::app);

		ComponenteTransform* transform = getComponente<ComponenteTransform>();
		std::string str = std::to_string(transform->posicao.x) + " " + std::to_string(transform->posicao.y) + " "
			+ std::to_string(transform->velocidade.x) + " " + std::to_string(transform->velocidade.y) + " "
			+ std::to_string(agressividade) + "\n";

		file << str;

		file.close();
	}

private:
	int agressividade;
};