#include "Fase.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include <fstream>
#include <string>
using namespace std;

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
	
	

	Zumbi* zumbi = new Zumbi;
	Chefe* boss = new Chefe;


	listaEntidades.addEntidade(static_cast<Entidade*>(jogador));
	listaEntidades.addEntidade(static_cast<Entidade*>(zumbi));
	listaEntidades.addEntidade(static_cast<Entidade*>(boss));

	mapa->inicializar(id);
	if (id == 1) {
		Esqueleto* en1T1 = new Esqueleto(456, 6240);
		listaEntidades.addEntidade(static_cast<Entidade*>(en1T1));

		Esqueleto* en2T1 = new Esqueleto(160, 5632.8);
		listaEntidades.addEntidade(static_cast<Entidade*>(en2T1));

		Esqueleto* en3T1 = new Esqueleto(1064, 5358);
		listaEntidades.addEntidade(static_cast<Entidade*>(en3T1));

		Esqueleto* en4T1 = new Esqueleto(1500, 5984);
		listaEntidades.addEntidade(static_cast<Entidade*>(en4T1));

	}
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
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteTransform>()->velocidade.y << " "
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteSaude>()->getHealth() << std::endl;
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
		if (out) {
			for (int i = 0; i < listaEntidades.listaEntidades.size(); i++) {
				out << typeid(*listaEntidades.listaEntidades[i]).name() << " "
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteTransform>()->posicao.x << " "
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteTransform>()->posicao.y << " "
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteTransform>()->velocidade.x << " "
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteTransform>()->velocidade.y << " "
					<< listaEntidades.listaEntidades[i]->getComponente<ComponenteSaude>()->getHealth() << std::endl;
			}
		}
		else {
			std::cout << "Failed saving!\n";
			return;
		}
		out.close();

		GerenciadorDeColisao::saveProjeteis("Saves/Fase2/projeteis.dat");
		GerenciadorDeColisao::saveObstaculos("Saves/Fase2/obstaculos.dat");
	}
}

void Fase::load(const int id) {
	string esqueleto = "Esqueleto";
	string zumbi = "Zumbi";
	string chefe = "Chefe";
	string jogador = "Jogador";
	string lava = "Lava";
	string espinhos = "Espinhos";
	string projetil = "Projetil";
	std::ifstream in;

	GerenciadorDeColisao::setFase(this);
	mapa = new Mapa;
	player_is_alive = true;
	mapa->reload(id);

	this->id = id;

	if (id == 1) {
		in.open("Saves/Fase1/entidades.dat", std::ios::in);
		if (in) {
			string classe, nomeClasse;
			int saude;
			float x, y, vx, vy;

			while (in >> classe >> nomeClasse >> x >> y >> vx >> vy >> saude) {
				if (nomeClasse == jogador) {
					Jogador* jog = new Jogador;
					jog->getComponente<ComponenteTransform>()->posicao.x = x;
					jog->getComponente<ComponenteTransform>()->posicao.y = y;
					jog->getComponente<ComponenteTransform>()->velocidade.x = vx;
					jog->getComponente<ComponenteTransform>()->velocidade.y = vy;
					jog->getComponente<ComponenteSaude>()->init(saude);
					listaEntidades.addEntidade(static_cast<Entidade*>(jog));

					GerenciadorDeCamera::setJogador(jog);
					GerenciadorDeColisao::setJogador(jog);
				}
				else if (nomeClasse == esqueleto) {
					Esqueleto* esq = new Esqueleto(x, y);
					esq->getComponente<ComponenteTransform>()->velocidade.x = vx;
					esq->getComponente<ComponenteTransform>()->velocidade.y = vy;
					esq->getComponente<ComponenteSaude>()->init(saude);
					listaEntidades.addEntidade(static_cast<Entidade*>(esq));
				}
				else if (nomeClasse == zumbi) {
					Zumbi* zum = new Zumbi;
					zum->getComponente<ComponenteTransform>()->posicao.x = x;
					zum->getComponente<ComponenteTransform>()->posicao.y = y;
					zum->getComponente<ComponenteTransform>()->velocidade.x = vx;
					zum->getComponente<ComponenteTransform>()->velocidade.y = vy;
					zum->getComponente<ComponenteSaude>()->init(saude);
					listaEntidades.addEntidade(static_cast<Entidade*>(zum));
				}
				else if (nomeClasse == chefe) {
					Chefe* che = new Chefe;
					che->getComponente<ComponenteTransform>()->posicao.x = x;
					che->getComponente<ComponenteTransform>()->posicao.y = y;
					che->getComponente<ComponenteTransform>()->velocidade.x = vx;
					che->getComponente<ComponenteTransform>()->velocidade.y = vy;
					che->getComponente<ComponenteSaude>()->init(saude);
					listaEntidades.addEntidade(static_cast<Entidade*>(che));
				}
			}

		}
		else {
			jogo->mainMenu();
			std::cerr << " Arquivo nao pode ser aberto " << endl;
			return;
		}
		
		in.close();

		in.open("Saves/Fase1/obstaculos.dat", std::ios::in);
		if (in) {
			string classe, nomeClasse;
			int x, y, w, h;

			while (in >> classe >> nomeClasse >> x >> y >> w >> h) {
				if (nomeClasse == espinhos) {
					Espinhos* esp = new Espinhos;
					esp->getComponente<ComponenteColisao>()->set(x, y, w, h);
					GerenciadorDeColisao::addObstaculo(esp);

				}
				else if (nomeClasse == lava) {
					Lava* lav = new Lava;
					lav->getComponente<ComponenteColisao>()->set(x, y, w, h);
					GerenciadorDeColisao::addObstaculo(lav);
				}
			}

		}
		else {
			jogo->mainMenu();
			std::cerr << " Arquivo nao pode ser aberto " << endl;
			return;
		}
		
		in.close();

		in.open("Saves/Fase1/projeteis.dat", std::ios::in);
		if (in) {
			string classe, nomeClasse;
			float x, y, vx, vy;

			while (in >> classe >> nomeClasse >> x >> y >> vx >> vy) {
				Projetil* pro = new Projetil;
				pro->getComponente<ComponenteTransform>()->posicao.x = x;
				pro->getComponente<ComponenteTransform>()->posicao.y = y;
				pro->getComponente<ComponenteTransform>()->velocidade.x = vx;
				pro->getComponente<ComponenteTransform>()->velocidade.y = vy;
				GerenciadorDeColisao::addProjetil(pro);
			}

		}
		else {
			jogo->mainMenu();
			std::cerr << " Arquivo nao pode ser aberto " << endl;
			return;
		}

		in.close();
	}

	else if (id == 2) {
		in.open("Saves/Fase2/entidades.dat", std::ios::in);
		if (in) {
			string classe, nomeClasse;
			int saude;
			float x, y, vx, vy;

			while (in >> classe >> nomeClasse >> x >> y >> vx >> vy >> saude) {
				if (nomeClasse == jogador) {
					Jogador* jog = new Jogador;
					jog->getComponente<ComponenteTransform>()->posicao.x = x;
					jog->getComponente<ComponenteTransform>()->posicao.y = y;
					jog->getComponente<ComponenteTransform>()->velocidade.x = vx;
					jog->getComponente<ComponenteTransform>()->velocidade.y = vy;
					jog->getComponente<ComponenteSaude>()->init(saude);
					listaEntidades.addEntidade(static_cast<Entidade*>(jog));

					GerenciadorDeCamera::setJogador(jog);
					GerenciadorDeColisao::setJogador(jog);
				}
				else if (nomeClasse == esqueleto) {
					Esqueleto* esq = new Esqueleto(x, y);
					esq->getComponente<ComponenteTransform>()->velocidade.x = vx;
					esq->getComponente<ComponenteTransform>()->velocidade.y = vy;
					esq->getComponente<ComponenteSaude>()->init(saude);
					listaEntidades.addEntidade(static_cast<Entidade*>(esq));
				}
				else if (nomeClasse == zumbi) {
					Zumbi* zum = new Zumbi;
					zum->getComponente<ComponenteTransform>()->posicao.x = x;
					zum->getComponente<ComponenteTransform>()->posicao.y = y;
					zum->getComponente<ComponenteTransform>()->velocidade.x = vx;
					zum->getComponente<ComponenteTransform>()->velocidade.y = vy;
					zum->getComponente<ComponenteSaude>()->init(saude);
					listaEntidades.addEntidade(static_cast<Entidade*>(zum));
				}
				else if (nomeClasse == chefe) {
					Chefe* che = new Chefe;
					che->getComponente<ComponenteTransform>()->posicao.x = x;
					che->getComponente<ComponenteTransform>()->posicao.y = y;
					che->getComponente<ComponenteTransform>()->velocidade.x = vx;
					che->getComponente<ComponenteTransform>()->velocidade.y = vy;
					che->getComponente<ComponenteSaude>()->init(saude);
					listaEntidades.addEntidade(static_cast<Entidade*>(che));
				}
			}

		}
		else {
			jogo->mainMenu();
			std::cerr << " Arquivo nao pode ser aberto " << endl;
			return;
		}

		in.close();

		in.open("Saves/Fase2/obstaculos.dat", std::ios::in);
		if (in) {
			string classe, nomeClasse;
			int x, y, w, h;

			while (in >> classe >> nomeClasse >> x >> y >> w >> h) {
				if (nomeClasse == espinhos) {
					Espinhos* esp = new Espinhos;
					esp->getComponente<ComponenteColisao>()->set(x, y, w, h);
					GerenciadorDeColisao::addObstaculo(esp);

				}
				else if (nomeClasse == lava) {
					Lava* lav = new Lava;
					lav->getComponente<ComponenteColisao>()->set(x, y, w, h);
					GerenciadorDeColisao::addObstaculo(lav);
				}
			}

		}
		else {
			jogo->mainMenu();
			std::cerr << " Arquivo nao pode ser aberto " << endl;
			return;
		}

		in.close();

		in.open("Saves/Fase2/projeteis.dat", std::ios::in);
		if (in) {
			string classe, nomeClasse;
			float x, y, vx, vy;

			while (in >> classe >> nomeClasse >> x >> y >> vx >> vy) {
				Projetil* pro = new Projetil;
				pro->getComponente<ComponenteTransform>()->posicao.x = x;
				pro->getComponente<ComponenteTransform>()->posicao.y = y;
				pro->getComponente<ComponenteTransform>()->velocidade.x = vx;
				pro->getComponente<ComponenteTransform>()->velocidade.y = vy;
				GerenciadorDeColisao::addProjetil(pro);
			}

		}
		else {
			jogo->mainMenu();
			std::cerr << " Arquivo nao pode ser aberto " << endl;
			return;
		}

		in.close();
	}
	
}