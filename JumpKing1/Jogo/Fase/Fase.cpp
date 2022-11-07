#include "Fase.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include <fstream>

Fase::Fase() {
	mapa = nullptr;
	player_is_alive = true;
	jogo = nullptr;
	id = 0;
}

Fase::~Fase() {
	if (mapa != nullptr) {
		delete mapa;
	}
}

void Fase::inicializar(const int id) {
	this->id = id;
	GerenciadorDeColisao::setFase(this);
	mapa = new Mapa;
	Jogador* jogador = new Jogador;
	player_is_alive = true;
	GerenciadorDeCamera::setJogador(jogador);
	GerenciadorDeColisao::setJogador(jogador);
	switch (id) {
	case 1:
		jogador->getComponente<ComponenteTransform>()->posicao.x = 100;
		jogador->getComponente<ComponenteTransform>()->posicao.y = 6240;
		break;
	case 2:
		jogador->getComponente<ComponenteTransform>()->posicao.x = 300;
		jogador->getComponente<ComponenteTransform>()->posicao.y = 7648;
		break;
	default:
		break;
	}
	GerenciadorDeCamera::setJogador(jogador);
	
	if (id == 1) {
		Esqueleto* en1T1 = new Esqueleto;
		en1T1->getComponente<ComponenteTransform>()->posicao.x = 456;
		en1T1->getComponente<ComponenteTransform>()->posicao.y = 6240;
		listaEntidades.addEntidade(static_cast<Entidade*>(en1T1));

		Esqueleto* en2T1 = new Esqueleto;
		en2T1->getComponente<ComponenteTransform>()->posicao.x = 160;
		en2T1->getComponente<ComponenteTransform>()->posicao.y = 5632.8;
		listaEntidades.addEntidade(static_cast<Entidade*>(en2T1));

		Esqueleto* en3T1 = new Esqueleto;
		en3T1->getComponente<ComponenteTransform>()->posicao.x = 1064;
		en3T1->getComponente<ComponenteTransform>()->posicao.y = 5358;
		listaEntidades.addEntidade(static_cast<Entidade*>(en3T1));

		Esqueleto* en4T1 = new Esqueleto;
		en4T1->getComponente<ComponenteTransform>()->posicao.x = 1500;
		en4T1->getComponente<ComponenteTransform>()->posicao.y = 5984;
		listaEntidades.addEntidade(static_cast<Entidade*>(en4T1));

	}

	Zumbi* zumbi = new Zumbi;
	Chefe* boss = new Chefe;


	listaEntidades.addEntidade(static_cast<Entidade*>(jogador));
	listaEntidades.addEntidade(static_cast<Entidade*>(zumbi));
	listaEntidades.addEntidade(static_cast<Entidade*>(boss));

	mapa->inicializar(id);
}

void Fase::setJogo(Jogo* jg) {
	jogo = jg;
}

void Fase::atualizar() {
	if (player_is_alive) {
		listaEntidades.atualizar();
		if (mapa != nullptr) {
			mapa->atualizar();
		}
		GerenciadorDeColisao::atualizaProjeteis();
		GerenciadorDeColisao::atualizaObstaculos();
		GerenciadorDeColisao::colisao_jogador1();
		GerenciadorDeCamera::Atualiza();
		
	}
	else {
		clear();
		jogo->gameOverMenu();
	}
	//else Jogo::evento.key.keysym.sym = SDLK_ESCAPE; //simula menu de pause

}

void Fase::render() {
	mapa->render();
	GerenciadorDeColisao::renderObstaculos();
	GerenciadorDeColisao::renderProjeteis();
	listaEntidades.render();
}

void Fase::clear() {

	mapa->clear();
	listaEntidades.clear();
}

void Fase::gameOver() {
	//clear();
	player_is_alive = false;
}

void Fase::save() {
	std::ofstream out;
	if (id == 1) {
		out.open("Saves/Fase1/entidades.dat", std::ios::out);
		if (out) {
			for (int i = 0; i < listaEntidades.listaEntidades.size(); i++) {
				out << typeid(*listaEntidades.listaEntidades[i]).name() << " "
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteTransform>()->posicao.x << " "
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteTransform>()->posicao.y << " "
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteTransform>()->velocidade.x << " "
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteTransform>()->velocidade.y << std::endl; //retorna apenas Entidade*
			}
		} //aqui salva os dados
		else {
				std::cout << "Failed saving!\n";
				return;
			}
		out.close();
		
		GerenciadorDeColisao::saveProjeteis("Saves/Fase1/projeteis.dat");
		GerenciadorDeColisao::saveObstaculos("Saves/Fase1/obstaculos.dat");
	}
	else if (id == 2) {
		out.open("Saves/Fase2/entidades.dat", std::ios::out);
		if (out) {} //aqui salva os dados
		else {
			std::cout << "Failed saving!\n";
			return;
		}
		out.close();

		out.open("Saves/Fase2/obstaculos.dat", std::ios::out);
		if (out) {} //aqui salva os dados
		else {
			std::cout << "Failed saving!\n";
			return;
		}
		out.close();

		out.open("Saves/Fase2/projeteis.dat", std::ios::out);
		if (out) {} //aqui salva os dados
		else {
			std::cout << "Failed saving!\n";
			return;
		}
		out.close();
	}
}