#pragma once

#include "../Inimigo.h"

class Mago : public Inimigo {
public:
	Mago(float x = 0, float y = 0, int sab = 0);
	~Mago();

	const int getSpeed() const { return speed; }
	const bool facingLeft() const { return flip; }
	void setState(unsigned char val);

	void shoot();
	void atualizar();
	void render();
	int attack();

	void salvar(int faseID) {
		ofstream file;
		if (faseID == 1) file.open("Saves/Fase1/magos.dat", ios::app);
		else if (faseID == 2) file.open("Saves/Fase2/magos.dat", ios::app);

		ComponenteTransform* transform = getComponente<ComponenteTransform>();
		std::string str = std::to_string(transform->posicao.x) + " " + std::to_string(transform->posicao.y) + " "
			+ std::to_string(transform->velocidade.x) + " " + std::to_string(transform->velocidade.y) + " "
			+ std::to_string(sabedoria) + "\n";

		file << str;

		file.close();
	}
private:
	int sabedoria;
};