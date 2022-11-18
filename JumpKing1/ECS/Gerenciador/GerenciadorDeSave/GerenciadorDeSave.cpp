#include "GerenciadorDeSave.h"
#include <fstream>
#include "../../Entidade/Personagem/Inimigo/Inimigo.h"
#include "../..//Entidade/Obstaculo/Obstaculo.h"
#include "../..//Entidade/Projetil/Projetil.h"

GerenciadorDeSave* GerenciadorDeSave::manager = nullptr;

GerenciadorDeSave::GerenciadorDeSave() {}

GerenciadorDeSave::~GerenciadorDeSave() {
	if (manager != nullptr) {
		delete manager;
	}
}

GerenciadorDeSave* GerenciadorDeSave::getInstance() {
	if (manager == nullptr) {
		manager = new GerenciadorDeSave;
	}
	return manager;
}

void GerenciadorDeSave::deleteInstance() {
	if (manager != nullptr) {
		delete manager;
		manager = nullptr;
	}
}

void GerenciadorDeSave::save(int id) {
	std::ofstream out;

	//obstaculos
	if (id == 1) out.open("Saves/Fase1/obstaculos.dat", std::ios::out);
	else if (id == 2) out.open("Saves/Fase2/obstaculos.dat", std::ios::out);

	if (out) {
		for (int i = 0; i < obstaculos.size(); i++) {
			out << typeid(*obstaculos[i]).name() << " "
				<< obstaculos[i]->getComponente<ComponenteColisao>()->getColisor().x << " "
				<< obstaculos[i]->getComponente<ComponenteColisao>()->getColisor().y << " "
				<< obstaculos[i]->getComponente<ComponenteColisao>()->getColisor().w << " "
				<< obstaculos[i]->getComponente<ComponenteColisao>()->getColisor().h << std::endl;
		}
	}
	else {
		std::cout << "Failed saving!\n";
		return;
	}
	out.close();

	//projeteis
	if (id == 1) out.open("Saves/Fase1/projeteis.dat", std::ios::out);
	else if (id == 2) out.open("Saves/Fase2/projeteis.dat", std::ios::out);

	if (out) {
		for (int i = 0; i < projeteis.size(); i++) {
			out << typeid(*projeteis[i]).name() << " "
				<< projeteis[i]->getComponente<ComponenteColisao>()->getColisor().x << " "
				<< projeteis[i]->getComponente<ComponenteColisao>()->getColisor().y << " "
				<< projeteis[i]->getComponente<ComponenteTransform>()->velocidade.x << " "
				<< projeteis[i]->getComponente<ComponenteTransform>()->velocidade.y << std::endl;
		}
	}
	else {
		std::cout << "Failed saving!\n";
		return;
	}
	out.close();

	//inimigos
	if (id == 1) out.open("Saves/Fase1/inimigos.dat", std::ios::out);
	else if (id == 2) out.open("Saves/Fase2/inimigos.dat", std::ios::out);

	if (out) {
		for (int i = 0; i < inimigos.size(); i++) {
			if (inimigos[i]->isAlive()) {
				out << typeid(*inimigos[i]).name() << " "
					<< inimigos[i]->getComponente<ComponenteTransform>()->posicao.x << " "
					<< inimigos[i]->getComponente<ComponenteTransform>()->posicao.y << " "
					<< inimigos[i]->getComponente<ComponenteTransform>()->velocidade.x << " "
					<< inimigos[i]->getComponente<ComponenteTransform>()->velocidade.y << std::endl;
			}
		}
	}
	else {
		std::cout << "Failed saving!\n";
		return;
	}
	out.close();
}

void GerenciadorDeSave::addInimigo(Inimigo* in) {
	inimigos.push_back(in);
}

void GerenciadorDeSave::addProjetil(Projetil* proj) {
	projeteis.push_back(proj);
}

void GerenciadorDeSave::addObstaculo(Obstaculo* obst) {
	obstaculos.push_back(obst);
}

void GerenciadorDeSave::clear() {
	inimigos.clear();
	obstaculos.clear();
	projeteis.clear();
}