#include "Fase.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include "../../ECS/Gerenciador/GerenciadorDeEventos/GerenciadorDeEventos.h"
#include <fstream>
#include <string>
using namespace std;


Fase::Fase() {
	mapa = nullptr;
	player_is_alive = true;
	jogo = nullptr;
	id = 0;
	event_manager = GerenciadorDeEventos::getInstance();
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
	mapa->inicializar(id);

	Jogador* jogador = new Jogador;
	jogador->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/HenriqueIsFallingx32.png");
	player_is_alive = true;
	event_manager->setJogador1(jogador);
	GerenciadorDeCamera::setJogador(jogador);
	GerenciadorDeColisao::setJogador(jogador);

	Jogador* jogador2 = new Jogador;
	jogador2->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/player2.png");
	event_manager->setJogador2(jogador2);
	GerenciadorDeCamera::setJogador2(jogador2);
	GerenciadorDeColisao::setJogador2(jogador2);
	switch (id) {
	case 1:
		jogador->getComponente<ComponenteTransform>()->posicao.x = 100;
		jogador->getComponente<ComponenteTransform>()->posicao.y = 6240;
		jogador2->getComponente<ComponenteTransform>()->posicao.x = 200;
		jogador2->getComponente<ComponenteTransform>()->posicao.y = 6240;
		break;
	case 2:
		jogador->getComponente<ComponenteTransform>()->posicao.x = 300;
		jogador->getComponente<ComponenteTransform>()->posicao.y = 7648;
		jogador2->getComponente<ComponenteTransform>()->posicao.x = 400;
		jogador2->getComponente<ComponenteTransform>()->posicao.y = 7648;
		break;
	default:
		break;
	}
	
	if (id == 1) {
		Esqueleto* en1T1 = new Esqueleto(456, 6240);
		listaEntidades.addEntidade(static_cast<Entidade*>(en1T1));
		GerenciadorDeColisao::addInimigo(static_cast<Inimigo*>(en1T1));

		Esqueleto* en2T1 = new Esqueleto(160, 5632.8);
		listaEntidades.addEntidade(static_cast<Entidade*>(en2T1));
		GerenciadorDeColisao::addInimigo(static_cast<Inimigo*>(en2T1));

		Esqueleto* en3T1 = new Esqueleto(1064, 5358);
		listaEntidades.addEntidade(static_cast<Entidade*>(en3T1));
		GerenciadorDeColisao::addInimigo(static_cast<Inimigo*>(en3T1));

		Esqueleto* en4T1 = new Esqueleto(1500, 5984);
		listaEntidades.addEntidade(static_cast<Entidade*>(en4T1));
		GerenciadorDeColisao::addInimigo(static_cast<Inimigo*>(en4T1));

		Esqueleto* en5T1 = new Esqueleto(2368, 5248);
		listaEntidades.addEntidade(static_cast<Entidade*>(en5T1));
		GerenciadorDeColisao::addInimigo(static_cast<Inimigo*>(en5T1));

		Esqueleto* en6T1 = new Esqueleto(2368, 3648);
		listaEntidades.addEntidade(static_cast<Entidade*>(en6T1));
		GerenciadorDeColisao::addInimigo(static_cast<Inimigo*>(en6T1));

		Esqueleto* en7T1 = new Esqueleto(944, 4512);
		listaEntidades.addEntidade(static_cast<Entidade*>(en7T1));
		GerenciadorDeColisao::addInimigo(static_cast<Inimigo*>(en7T1));

		Esqueleto* en8T1 = new Esqueleto(120, 4512);
		listaEntidades.addEntidade(static_cast<Entidade*>(en8T1));
		GerenciadorDeColisao::addInimigo(static_cast<Inimigo*>(en8T1));
	}
	if (id == 2) {
		Esqueleto* en1T1 = new Esqueleto(1672, 5504);
		listaEntidades.addEntidade(static_cast<Entidade*>(en1T1));
		GerenciadorDeColisao::addInimigo(static_cast<Inimigo*>(en1T1));
	}

	Zumbi* zumbi = new Zumbi;
	Chefe* boss = new Chefe;


	listaEntidades.addEntidade(static_cast<Entidade*>(jogador));
	listaEntidades.addEntidade(static_cast<Entidade*>(jogador2));
	listaEntidades.addEntidade(static_cast<Entidade*>(zumbi));
	listaEntidades.addEntidade(static_cast<Entidade*>(boss));
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
		GerenciadorDeCamera::Atualiza();
		GerenciadorDeColisao::atualizaProjeteis();
		GerenciadorDeColisao::atualizaObstaculos();
		//GerenciadorDeColisao::atualizaInimigos();
		GerenciadorDeColisao::colisao_jogador1();
		event_manager->atualizar();

		if (GerenciadorDeColisao::getJogador1()->isAttacking()) {
			GerenciadorDeColisao::ataqueJ1();
		}
		if (GerenciadorDeColisao::getJogador2()->isAttacking()) {
			GerenciadorDeColisao::ataqueJ2();
		}
	}
	else {
		clear();
		jogo->gameOverMenu();
	}
}

void Fase::render() {
	mapa->render();
	GerenciadorDeColisao::renderObstaculos();
	GerenciadorDeColisao::renderProjeteis();
	listaEntidades.render();

	if (player_is_alive) {
		int saude = GerenciadorDeColisao::getJogador1()->getComponente<ComponenteSaude>()->getHealth();
		SDL_Rect fonte = { 0,0,40,40 };
		SDL_Rect posRect;

		for (int i = 0; i < saude; i++) {
			posRect.x = (0.03 * i + 0.02) * GerenciadorDeCamera::camera.w;
			posRect.y = (0.03) * GerenciadorDeCamera::camera.h;
			posRect.w = posRect.h = 40;
			graphics->renderCoracao(fonte, posRect);
		}

		saude = GerenciadorDeColisao::getJogador2()->getComponente<ComponenteSaude>()->getHealth();
		for (int i = 0; i < saude; i++) {
			posRect.x = (-0.03 * i + 0.97) * GerenciadorDeCamera::camera.w - 40;
			posRect.y = (0.03) * GerenciadorDeCamera::camera.h;
			posRect.w = posRect.h = 40;
			graphics->renderCoracao(fonte, posRect);
		}

		int pontuacao = GerenciadorDeColisao::getJogador1()->getPontuacao() + GerenciadorDeColisao::getJogador2()->getPontuacao();
		//int pontuacao = 34500;
		graphics->renderPontuacao(pontuacao);
	}
}

void Fase::clear() {

	mapa->clear();
	listaEntidades.clear();
	//event_manager->deleteInstance();
}

void Fase::gameOver() {
	//clear();
	player_is_alive = false;
}

void Fase::save()  {
	std::ofstream out;
	if (id == 1) {
		out.open("Saves/Fase1/jogadores.dat", std::ios::out);
		if (out) {
			Jogador* jog1 = GerenciadorDeColisao::getJogador1();
			Jogador* jog2 = GerenciadorDeColisao::getJogador2();
			if (mapa->isOnBossRoom()) out << 1 << std::endl;
			else out << 0 << std::endl;
			out << "1 " << jog1->getComponente<ComponenteTransform>()->posicao.x << " "
				<< jog1->getComponente<ComponenteTransform>()->posicao.y << " "
				<< jog1->getComponente<ComponenteTransform>()->velocidade.x << " "
				<< jog1->getComponente<ComponenteTransform>()->velocidade.y << " "
				<< jog1->getComponente<ComponenteSaude>()->getHealth() << " "
				<< jog1->getPontuacao() << std::endl
				<< "2 " << jog2->getComponente<ComponenteTransform>()->posicao.x << " "
				<< jog2->getComponente<ComponenteTransform>()->posicao.y << " "
				<< jog2->getComponente<ComponenteTransform>()->velocidade.x << " "
				<< jog2->getComponente<ComponenteTransform>()->velocidade.y << " "
				<< jog2->getComponente<ComponenteSaude>()->getHealth() << " "
				<< jog2->getPontuacao() << std::endl;
		}//aqui salva os dados
		else {
			std::cout << "Failed saving!\n";
			return;
		}
		out.close();

		
		GerenciadorDeColisao::saveProjeteis("Saves/Fase1/projeteis.dat");
		GerenciadorDeColisao::saveObstaculos("Saves/Fase1/obstaculos.dat");
		GerenciadorDeColisao::saveInimigos("Saves/Fase1/inimigos.dat");
	}

	else if (id == 2) {
		out.open("Saves/Fase2/jogadores.dat", std::ios::out);
		if (out) {
			Jogador* jog1 = GerenciadorDeColisao::getJogador1();
			Jogador* jog2 = GerenciadorDeColisao::getJogador2();
			if (mapa->isOnBossRoom()) out << 1 << std::endl;
			else out << 0 << std::endl;
			out << "1 " << jog1->getComponente<ComponenteTransform>()->posicao.x << " "
				<< jog1->getComponente<ComponenteTransform>()->posicao.y << " "
				<< jog1->getComponente<ComponenteTransform>()->velocidade.x << " "
				<< jog1->getComponente<ComponenteTransform>()->velocidade.y << " "
				<< jog1->getComponente<ComponenteSaude>()->getHealth() << " "
				<< jog1->getPontuacao() << std::endl
				<< "2 " << jog2->getComponente<ComponenteTransform>()->posicao.x << " "
				<< jog2->getComponente<ComponenteTransform>()->posicao.y << " "
				<< jog2->getComponente<ComponenteTransform>()->velocidade.x << " "
				<< jog2->getComponente<ComponenteTransform>()->velocidade.y << " "
				<< jog2->getComponente<ComponenteSaude>()->getHealth() << " "
				<< jog2->getPontuacao() << std::endl;
		}//aqui salva os dados
		else {
			std::cout << "Failed saving!\n";
			return;
		}
		out.close();


		GerenciadorDeColisao::saveProjeteis("Saves/Fase2/projeteis.dat");
		GerenciadorDeColisao::saveObstaculos("Saves/Fase2/obstaculos.dat");
		GerenciadorDeColisao::saveInimigos("Saves/Fase2/inimigos.dat");
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
	event_manager = GerenciadorDeEventos::getInstance();

	GerenciadorDeColisao::setFase(this);
	mapa = new Mapa;
	player_is_alive = true;

	this->id = id;

	if (id == 1) {
		in.open("Saves/Fase1/jogadores.dat", std::ios::in);
		if (in) {
			int saude, id, pontuacao;
			float x, y, vx, vy;

			in >> id; //se esta na boss room
			if (id) mapa->setBossRoom(true);
			mapa->reload(this->id);
			while (in >> id >> x >> y >> vx >> vy >> saude >> pontuacao) {
				Jogador* jog = new Jogador;
				jog->getComponente<ComponenteTransform>()->posicao.x = x;
				jog->getComponente<ComponenteTransform>()->posicao.y = y;
				jog->getComponente<ComponenteTransform>()->velocidade.x = vx;
				jog->getComponente<ComponenteTransform>()->velocidade.y = vy;
				jog->getComponente<ComponenteSaude>()->init(saude);
				jog->setPontuacao(pontuacao);
				listaEntidades.addEntidade(static_cast<Entidade*>(jog));
				
				if (id == 1) {
					GerenciadorDeCamera::setJogador(jog);
					GerenciadorDeColisao::setJogador(jog);
					jog->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/HenriqueIsFallingx32.png");
					event_manager->setJogador1(jog);
				}
				else if (id == 2) {
					GerenciadorDeCamera::setJogador2(jog);
					GerenciadorDeColisao::setJogador2(jog);
					jog->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/player2.png");
					event_manager->setJogador2(jog);
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

		in.open("Saves/Fase1/inimigos.dat", std::ios::in);
		if (in) {
			string classe, nomeClasse;
			float x, y, vx, vy;

			while (in >> classe >> nomeClasse >> x >> y >> vx >> vy) {
				if (nomeClasse == esqueleto) {
					Esqueleto* inimigo = new Esqueleto(x, y);
					inimigo->getComponente<ComponenteTransform>()->velocidade.x = vx;
					inimigo->getComponente<ComponenteTransform>()->velocidade.y = vy;
					GerenciadorDeColisao::addInimigo(inimigo);
					listaEntidades.addEntidade(static_cast<Entidade*>(inimigo));
				}
				else if (nomeClasse == zumbi) {
					Zumbi* inimigo = new Zumbi;
					inimigo->getComponente<ComponenteTransform>()->posicao.x = x;
					inimigo->getComponente<ComponenteTransform>()->posicao.y = y;
					inimigo->getComponente<ComponenteTransform>()->velocidade.x = vx;
					inimigo->getComponente<ComponenteTransform>()->velocidade.y = vy;
					GerenciadorDeColisao::addInimigo(inimigo);
					listaEntidades.addEntidade(static_cast<Entidade*>(inimigo));
				}
				else if (nomeClasse == chefe) {
					Chefe* inimigo = new Chefe;
					inimigo->getComponente<ComponenteTransform>()->posicao.x = x;
					inimigo->getComponente<ComponenteTransform>()->posicao.y = y;
					inimigo->getComponente<ComponenteTransform>()->velocidade.x = vx;
					inimigo->getComponente<ComponenteTransform>()->velocidade.y = vy;
					GerenciadorDeColisao::addInimigo(inimigo);
					listaEntidades.addEntidade(static_cast<Entidade*>(inimigo));
				}
			}
		}
		in.close();
	}

	else if (id == 2) {

		in.open("Saves/Fase2/jogadores.dat", std::ios::in);
		if (in) {
		int saude, id, pontuacao;
		float x, y, vx, vy;

		in >> id; //se esta na boss room
		if (id) mapa->setBossRoom(true);
		mapa->reload(this->id);
		while (in >> id >> x >> y >> vx >> vy >> saude >> pontuacao) {
			Jogador* jog = new Jogador;
			jog->getComponente<ComponenteTransform>()->posicao.x = x;
			jog->getComponente<ComponenteTransform>()->posicao.y = y;
			jog->getComponente<ComponenteTransform>()->velocidade.x = vx;
			jog->getComponente<ComponenteTransform>()->velocidade.y = vy;
			jog->getComponente<ComponenteSaude>()->init(saude);
			jog->setPontuacao(pontuacao);
			listaEntidades.addEntidade(static_cast<Entidade*>(jog));

			if (id == 1) {
				GerenciadorDeCamera::setJogador(jog);
				GerenciadorDeColisao::setJogador(jog);
				jog->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/HenriqueIsFallingx32.png");
				event_manager->setJogador1(jog);
			}
			else if (id == 2) {
				GerenciadorDeCamera::setJogador2(jog);
				GerenciadorDeColisao::setJogador2(jog);
				jog->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/player2.png");
				event_manager->setJogador2(jog);
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

		in.open("Saves/Fase2/inimigos.dat", std::ios::in);
		if (in) {
			string classe, nomeClasse;
			float x, y, vx, vy;

			while (in >> classe >> nomeClasse >> x >> y >> vx >> vy) {
				if (nomeClasse == esqueleto) {
					Esqueleto* inimigo = new Esqueleto(x, y);
					inimigo->getComponente<ComponenteTransform>()->velocidade.x = vx;
					inimigo->getComponente<ComponenteTransform>()->velocidade.y = vy;
					GerenciadorDeColisao::addInimigo(inimigo);
					listaEntidades.addEntidade(static_cast<Entidade*>(inimigo));
				}
				else if (nomeClasse == zumbi) {
					Zumbi* inimigo = new Zumbi;
					inimigo->getComponente<ComponenteTransform>()->posicao.x = x;
					inimigo->getComponente<ComponenteTransform>()->posicao.y = y;
					inimigo->getComponente<ComponenteTransform>()->velocidade.x = vx;
					inimigo->getComponente<ComponenteTransform>()->velocidade.y = vy;
					GerenciadorDeColisao::addInimigo(inimigo);
					listaEntidades.addEntidade(static_cast<Entidade*>(inimigo));
				}
				else if (nomeClasse == chefe) {
					Chefe* inimigo = new Chefe;
					inimigo->getComponente<ComponenteTransform>()->posicao.x = x;
					inimigo->getComponente<ComponenteTransform>()->posicao.y = y;
					inimigo->getComponente<ComponenteTransform>()->velocidade.x = vx;
					inimigo->getComponente<ComponenteTransform>()->velocidade.y = vy;
					GerenciadorDeColisao::addInimigo(inimigo);
					listaEntidades.addEntidade(static_cast<Entidade*>(inimigo));
				}
			}
		}
		in.close();
	}

}