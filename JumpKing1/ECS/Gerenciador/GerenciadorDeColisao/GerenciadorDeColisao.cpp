#include "GerenciadorDeColisao.h"
#include "../GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../GerenciadorDeEventos/GerenciadorDeEventos.h"
#include "../GerenciadorDeSave/GerenciadorDeSave.h"

#include "../../../Jogo/Fase/Fase.h"
#include "../../../Jogo/Fase/Mapa/Mapa.h"
#include "../../../Jogo/Fase/Mapa/TileMap/TileMap.h"
#include "../../Entidade/Personagem/Jogador/Jogador.h"
#include "../../Entidade/Personagem/Inimigo/Esqueleto/Esqueleto.h"
#include "../../Entidade/Personagem/Inimigo/Zumbi/Zumbi.h"
#include "../../Entidade/Obstaculo/Obstaculo.h"

GerenciadorDeColisao* GerenciadorDeColisao::manager = nullptr;

GerenciadorDeColisao::GerenciadorDeColisao() {
	tilemap = nullptr;
	jogador1 = nullptr;
	jogador2 = nullptr;
	fase = nullptr;
}

GerenciadorDeColisao::~GerenciadorDeColisao() {}

GerenciadorDeColisao* GerenciadorDeColisao::getInstance() {
	if (manager == nullptr) {
		manager = new GerenciadorDeColisao;
	}
	return manager;
}

void GerenciadorDeColisao::deleteInstance() {
	if (manager != nullptr) {
		delete manager;
		manager = nullptr;
	}
}

void GerenciadorDeColisao::colidir() {
	atualizaProjeteis();
	atualizaObstaculos();
	//GerenciadorDeColisao::atualizaInimigos();
	colisao_jogadores();
	colisao_projeteis_obstaculos();
	GerenciadorDeEventos::getInstance()->atualizar();

	if (jogador1->isAttacking()) {
		ataqueJ1();
	}
	if (getJogador2()->isAttacking()) {
		ataqueJ2();
	}
}

void GerenciadorDeColisao::setJogador(Jogador* jg) {
	jogador1 = jg;
}

void GerenciadorDeColisao::setJogador2(Jogador* jg) {
	jogador2 = jg;
}

void GerenciadorDeColisao::setTileMap(TileMap* tmap) {
	tilemap = tmap;
}

void GerenciadorDeColisao::setFase(Fase* fs) {
	fase = fs;
}

void GerenciadorDeColisao::addInimigo(Inimigo* in) {
	inimigos.push_back(in);
}

void GerenciadorDeColisao::atualizaInimigos() {
	for (auto& i : inimigos) {
		if (i->isAlive()) {
			i = nullptr;
		}
	}
}

void GerenciadorDeColisao::addObstaculo(Obstaculo* obst) {
	obstaculos.push_back(obst);
}

void GerenciadorDeColisao::atualizaObstaculos() {

	for (auto& o : obstaculos) {
		o->setScreen(false);
		if (AABB(o->getComponente<ComponenteColisao>()->getColisor(), GerenciadorDeCamera::GerenciadorDeCamera::getInstance()->camera))
			o->setScreen(true);
	}

}

void GerenciadorDeColisao::addProjetil(Projetil* proj) {
	projeteis.push_back(proj);
	fase->addEntidade(static_cast<Entidade*>(proj));
}

void GerenciadorDeColisao::atualizaProjeteis() {
	for (auto& p: projeteis) {
		p->setScreen(false);
		if (AABB(p->getComponente<ComponenteColisao>()->getColisor(), GerenciadorDeCamera::GerenciadorDeCamera::getInstance()->camera))
			p->setScreen(true);
	}
}

bool GerenciadorDeColisao::allEnemiesDead() {
	for (auto& i : inimigos) {
		if (i->isAlive()) return false;
	}
	return true;
}

void GerenciadorDeColisao::clear() {
	for (auto& o : obstaculos)
		delete o;
	obstaculos.clear();

	for (auto& p : projeteis)
		delete p;
	projeteis.clear();

	for (auto& i : inimigos)
		if (i != nullptr)
			delete i;
	inimigos.clear();
}

void GerenciadorDeColisao::iniciaInimigo(Inimigo* in) {
	SDL_Rect initPos = in->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect result = { 0, 0, Mapa::tamanhoTile(), Mapa::tamanhoTile() };
	SDL_Rect platform = result;
	platform.x = static_cast<int>(initPos.x / result.w) * result.w;
	platform.y = static_cast<int>(initPos.y / result.h) * result.h;
	bool notFound = true;

	// Encontra altura
	while (notFound) {
		for (auto& t : tilemap->hitbox_plataformas) {
			if (AABB(platform, t->getPos())) { notFound = false; platform = t->getPos(); break; }
		}
		platform.y += platform.h;
	}
	platform.y -= platform.h;
	result.y = platform.y;
	in->getComponente<ComponenteTransform>()->posicao.y = result.y - initPos.h;

	// Encontra ponta esquerda
	notFound = true;
	while (notFound) {
		notFound = false;
		for (auto& t : tilemap->hitbox_plataformas) {
			if (AABB({ platform.x - platform.w, platform.y - result.h, platform.w, platform.h }, t->getPos())) {
				notFound = false;
				break;
			}
			if (AABB({ platform.x - platform.w, platform.y, platform.w, platform.h }, t->getPos())) {
				notFound = true;
				platform.x -= platform.w;
			}
		}
	}
	result.x = platform.x;

	platform.x = static_cast<int>(initPos.x / result.w) * result.w;
	platform.y = result.y;
	platform.w = platform.h = result.h;
	notFound = true;
	while ((result.x < platform.x - platform.w) && notFound) {
		for (auto& t : tilemap->hitbox_plataformas) {
			if (AABB({ platform.x - platform.w, platform.y - result.h, platform.w, platform.h }, t->getPos())) {
				notFound = false;
				result.x = platform.x;
				break;
			}
		}
		for (auto& o : obstaculos) {
			if (AABB({ platform.x - platform.w, platform.y - result.h, platform.w, platform.h * 2 }, o->getComponente<ComponenteColisao>()->getColisor())) {
				notFound = false;
				result.x = platform.x;
				break;
			}
		}
		platform.x -= platform.w;
	}

	// Encontra ponta direita
	platform.x = static_cast<int>(initPos.x / result.w) * result.w;
	platform.y = result.y;
	platform.w = platform.h = result.h;
	notFound = true;
	while (notFound) {
		notFound = false;
		for (auto& t : tilemap->hitbox_plataformas) {
			if (AABB({ platform.x + platform.w, platform.y - result.h, platform.w, platform.h }, t->getPos())) {
				notFound = false;
				break;
			}
			if (AABB({ platform.x + platform.w, platform.y, platform.w, platform.h }, t->getPos())) {
				notFound = true;
				platform.x += platform.w;
			}
		}
	}
	result.w = platform.x + platform.w - result.x;

	platform.x = static_cast<int>(initPos.x / result.h) * result.h;
	platform.y = result.y;
	platform.w = platform.h = result.h;
	notFound = true;
	while ((result.x + result.w > platform.x + platform.w) && notFound) {
		for (auto& t : tilemap->hitbox_plataformas) {
			if (AABB({ platform.x + platform.w, platform.y - result.h, platform.w, platform.h }, t->getPos())) {
				notFound = false;
				result.w = platform.x + platform.w - result.x;
				break;
			}
		}
		for (auto& o : obstaculos) {
			if (AABB({ platform.x + platform.w, platform.y - result.h, platform.w, platform.h * 2 }, o->getComponente<ComponenteColisao>()->getColisor())) {
				notFound = false;
				result.w = platform.x + platform.w - result.x;
				break;
			}
		}
		platform.x += platform.w;
	}

	in->setPlatform(result);
}

void GerenciadorDeColisao::colisao_jogadores() {
	SDL_Rect initialhitbox = jogador1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect hitbox = initialhitbox;

	ComponenteTransform* transform = jogador1->getComponente<ComponenteTransform>();
	ComponenteTransform* transform2 = jogador2->getComponente<ComponenteTransform>();
	Vector2D velocity = transform->velocidade;

	SDL_Point dimMapa = Mapa::getDimensoes();

	// Checa bordas do mapa em X
	if (transform->posicao.x < 0 && transform->velocidade.x < 0)
		transform->posicao.x = transform->velocidade.x = 0;
	else if (transform->posicao.x + Mapa::tamanhoTile() > dimMapa.x && transform->velocidade.x > 0) {
		transform->posicao.x = dimMapa.x - Mapa::tamanhoTile();
		transform->velocidade.x = 0;
	}

	// Checa bordas do mapa em Y
	if (transform->posicao.y < 0 && transform->velocidade.y < 0)
		transform->posicao.y = transform->velocidade.y = 0;
	else if (transform->posicao.y + Mapa::tamanhoTile() > dimMapa.y && transform->velocidade.y > 0) {
		transform->posicao.y = dimMapa.y - Mapa::tamanhoTile();
		transform->velocidade.y = 0;
	}

	// Checa bordas do mapa em X
	if (transform2->posicao.x < 0 && transform2->velocidade.x < 0)
		transform2->posicao.x = transform2->velocidade.x = 0;
	else if (transform2->posicao.x + Mapa::tamanhoTile() > dimMapa.x && transform2->velocidade.x > 0) {
		transform2->posicao.x = dimMapa.x - Mapa::tamanhoTile();
		transform2->velocidade.x = 0;
	}

	// Checa bordas do mapa em Y
	if (transform2->posicao.y < 0 && transform2->velocidade.y < 0)
		transform2->posicao.y = transform2->velocidade.y = 0;
	else if (transform2->posicao.y + Mapa::tamanhoTile() > dimMapa.y && transform2->velocidade.y > 0) {
		transform2->posicao.y = dimMapa.y - Mapa::tamanhoTile();
		transform2->velocidade.y = 0;
	}

	
	colisao_jogadores_obstaculos();
	colisao_jogadores_inimigos();
	colisao_jogadores_projeteis();


	if (!jogador2->isAlive()) { //morreu -> encerra fase
		fase->gameOver();
	}
	if (!jogador1->isAlive()) { //morreu -> encerra fase
		fase->gameOver();
	}

}

void GerenciadorDeColisao::colisao_jogadores_inimigos() {
	//jogador1
	SDL_Rect initialhitbox = jogador1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect hitbox = initialhitbox;

	ComponenteTransform* transform = jogador1->getComponente<ComponenteTransform>();
	ComponenteTransform* transform2 = jogador2->getComponente<ComponenteTransform>();
	Vector2D velocity = transform->velocidade;

	for (auto& i : inimigos) {
		if (i->isAlive()) {
			velocity.x = transform->velocidade.x - i->getComponente<ComponenteTransform>()->velocidade.x;
			velocity.y = transform->velocidade.y - i->getComponente<ComponenteTransform>()->velocidade.y; //velocidade do jogador em relação ao inimigo
			hitbox = initialhitbox;
			SDL_Rect colisor = i->getComponente<ComponenteColisao>()->getColisor();
			if (AABB(colisor, hitbox)) {
				transform->velocidade.y = -1.4;
				if (velocity.x >= 0) transform->velocidade.x = -1;
				else if (velocity.x < 0) transform->velocidade.x = 1;
				jogador1->damage();
				break;
			}
		}
	}
	//jogador2
	initialhitbox = jogador2->getComponente<ComponenteColisao>()->getColisor();
	hitbox = initialhitbox;

	transform = jogador2->getComponente<ComponenteTransform>();
	velocity = transform->velocidade;

	for (auto& i : inimigos) {
		if (i->isAlive()) {
			hitbox = initialhitbox;
			hitbox.y += velocity.y * jogador1->getSpeed();
			SDL_Rect colisor = i->getComponente<ComponenteColisao>()->getColisor();
			if (AABB(colisor, hitbox)) {
				if (velocity.y > 0) { //colidiu por cima
					transform->posicao.y = colisor.y - hitbox.h;
					transform->velocidade.y = -1.4;
				}
				jogador2->damage();
				break;
			}

			hitbox = initialhitbox;
			hitbox.x += velocity.x * jogador1->getSpeed();
			if (AABB(colisor, hitbox)) {
				if (velocity.x > 0) { //colidiu pela esquerda
					transform->posicao.x = colisor.x - hitbox.w;
					transform->velocidade.x = -1;
				}
				else if (velocity.x < 0) { //colidiu pela direita
					transform->posicao.x = colisor.x + colisor.w;
					transform->velocidade.x = 1;
				}
				jogador2->damage();
				break;
			}
		}
	}
}

void GerenciadorDeColisao::colisao_jogadores_obstaculos() {

	//jogador1
	SDL_Rect initialhitbox = jogador1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect hitbox = initialhitbox;

	ComponenteTransform* transform = jogador1->getComponente<ComponenteTransform>();
	ComponenteTransform* transform2 = jogador2->getComponente<ComponenteTransform>();
	Vector2D velocity = transform->velocidade;


	if (!jogador1->inGround())
		transform->velocidade.y += 0.05; // simula gravidade 

	for (auto& t : tilemap->hitbox_plataformas) {
		//	if (t->isOnScreen()) {
		hitbox = initialhitbox;
		hitbox.x += velocity.x * jogador1->getSpeed();
		if (AABB(t->getPos(), hitbox)) {
			if (velocity.x > 0) { //colidiu pela esquerda
				transform->posicao.x = t->getPos().x - hitbox.w;
			}
			else if (velocity.x < 0) //colidiu pela direita
				transform->posicao.x = t->getPos().x + hitbox.w;
			transform->velocidade.x = 0;
		}

		hitbox = initialhitbox;
		hitbox.y += velocity.y * jogador1->getSpeed();
		if (AABB(t->getPos(), hitbox)) {
			if (velocity.y > 0) { //colidiu por cima
				jogador1->setGround(true);
				transform->posicao.y = t->getPos().y - hitbox.h;
			}
			else if (velocity.y < 0) //colidiu por baixo
				transform->posicao.y = t->getPos().y + hitbox.h;
			transform->velocidade.y = 0;

		}
		//	}
	}
	for (auto& o : obstaculos) {
		if (o->isOnScreen()) {
			hitbox = initialhitbox;
			hitbox.y += velocity.y * jogador1->getSpeed();
			SDL_Rect colisor = o->getComponente<ComponenteColisao>()->getColisor();
			if (AABB(colisor, hitbox)) {
				if (velocity.y > 0) { //colidiu por cima
					transform->posicao.y = colisor.y - hitbox.h;
					transform->velocidade.y = -1.4;
				}
				jogador1->damage();
				break;
			}
			hitbox = initialhitbox;
			hitbox.x += velocity.x * jogador1->getSpeed();
			if (AABB(colisor, hitbox)) {
				if (velocity.x > 0) { //colidiu pela esquerda
					transform->posicao.x = colisor.x - hitbox.w;
					transform->velocidade.x = -1;
				}
				else if (velocity.x < 0) { //colidiu pela direita
					transform->posicao.x = colisor.x + colisor.w;
					transform->velocidade.x = 1;
				}
				jogador1->damage();
			}
		}
	}

	//jogador2
	initialhitbox = jogador2->getComponente<ComponenteColisao>()->getColisor();
	hitbox = initialhitbox;

	transform = jogador2->getComponente<ComponenteTransform>();
	velocity = transform->velocidade;

	if (!jogador2->inGround())
		transform->velocidade.y += 0.05; // simula gravidade 

	for (auto& t : tilemap->hitbox_plataformas) {
		//if (t->isOnScreen()) {
		hitbox = initialhitbox;
		hitbox.x += velocity.x * jogador1->getSpeed();
		if (AABB(t->getPos(), hitbox)) {
			if (velocity.x > 0) { //colidiu pela esquerda
				transform->posicao.x = t->getPos().x - hitbox.w;
			}
			else if (velocity.x < 0) //colidiu pela direita
				transform->posicao.x = t->getPos().x + hitbox.w;
			transform->velocidade.x = 0;
		}
		hitbox = initialhitbox;
		hitbox.y += velocity.y * jogador1->getSpeed();
		if (AABB(t->getPos(), hitbox)) {
			if (velocity.y > 0) { //colidiu por cima
				jogador2->setGround(true);
				transform->posicao.y = t->getPos().y - hitbox.h;
			}
			else if (velocity.y < 0) //colidiu por baixo
				transform->posicao.y = t->getPos().y + hitbox.h;
			transform->velocidade.y = 0;

		}
		//}
	}

	for (auto& o : obstaculos) {
		if (o->isOnScreen()) {
			hitbox = initialhitbox;
			hitbox.y += velocity.y * jogador2->getSpeed();
			SDL_Rect colisor = o->getComponente<ComponenteColisao>()->getColisor();
			if (AABB(colisor, hitbox)) {
				if (velocity.y > 0) { //colidiu por cima
					transform->posicao.y = colisor.y - hitbox.h;
					transform->velocidade.y = -1.4;
				}
				jogador2->damage();
				break;
			}

			hitbox = initialhitbox;
			hitbox.x += velocity.x * jogador2->getSpeed();
			if (AABB(colisor, hitbox)) {
				if (velocity.x > 0) { //colidiu pela esquerda
					transform->posicao.x = colisor.x - hitbox.w;
					transform->velocidade.x = -1;
				}
				else if (velocity.x < 0) { //colidiu pela direita
					transform->posicao.x = colisor.x + colisor.w;
					transform->velocidade.x = 1;
				}
				jogador2->damage();
				break;
			}
		}

	}

}

void GerenciadorDeColisao::colisao_jogadores_projeteis() {
	//jogador1
	SDL_Rect initialhitbox = jogador1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect hitbox = initialhitbox;

	ComponenteTransform* transform = jogador1->getComponente<ComponenteTransform>();
	ComponenteTransform* transform2 = jogador2->getComponente<ComponenteTransform>();
	Vector2D velocity = transform->velocidade;

	for (auto& p : projeteis) {
		if (p->isActive()) {
			if (p->isOnScreen()) {
				hitbox = initialhitbox;
				hitbox.y += velocity.y * jogador1->getSpeed();
				SDL_Rect colisor = p->getComponente<ComponenteColisao>()->getColisor();
				if (AABB(colisor, hitbox)) {
					if (velocity.y > 0) { //colidiu por cima
						transform->posicao.y = colisor.y - hitbox.h;
						transform->velocidade.y = -1.4;
					}
					jogador1->damage();
					break;
				}

				hitbox = initialhitbox;
				hitbox.x += velocity.x * jogador1->getSpeed();
				if (AABB(colisor, hitbox)) {
					if (velocity.x > 0) { //colidiu pela esquerda
						transform->posicao.x = colisor.x - hitbox.w;
						transform->velocidade.x = -1;
					}
					else if (velocity.x < 0) { //colidiu pela direita
						transform->posicao.x = colisor.x + colisor.w;
						transform->velocidade.x = 1;
					}
					jogador1->damage();
					break;
				}
			}
		}

	}
	//jogador2
	initialhitbox = jogador2->getComponente<ComponenteColisao>()->getColisor();
	hitbox = initialhitbox;

	transform = jogador2->getComponente<ComponenteTransform>();
	velocity = transform->velocidade;

	for (auto& o : projeteis) {
		if (o->isOnScreen()) {
			hitbox = initialhitbox;
			hitbox.y += velocity.y * jogador1->getSpeed();
			SDL_Rect colisor = o->getComponente<ComponenteColisao>()->getColisor();
			if (AABB(colisor, hitbox)) {
				if (velocity.y > 0) { //colidiu por cima
					transform->posicao.y = colisor.y - hitbox.h;
					transform->velocidade.y = -1.4;
				}
				jogador2->damage();
				break;
			}
			hitbox = initialhitbox;
			hitbox.x += velocity.x * jogador1->getSpeed();
			if (AABB(colisor, hitbox)) {
				if (velocity.x > 0) { //colidiu pela esquerda
					transform->posicao.x = colisor.x - hitbox.w;
					transform->velocidade.x = -1;
				}
				else if (velocity.x < 0) { //colidiu pela direita
					transform->posicao.x = colisor.x + colisor.w;
					transform->velocidade.x = 1;
				}
				jogador2->damage();
				break;
			}
		}

	}
}

void GerenciadorDeColisao::colisao_inimigo_obstaculos(Inimigo* in1) {
	SDL_Rect hitbox = in1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect platform = in1->getPlatform();
	ComponenteTransform* transform = in1->getComponente<ComponenteTransform>();
	SDL_Rect target1 = jogador1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect target2 = jogador2->getComponente<ComponenteColisao>()->getColisor();

	platform.y -= 3 * Mapa::tamanhoTile();
	platform.h += 2 * Mapa::tamanhoTile();

	float dist1 = Mapa::getDimensoes().x;
	float dist2 = Mapa::getDimensoes().x;
	in1->setTarget(false);
	if (AABB(platform, target1)) {
		in1->setTarget(true);
		dist1 = (target1.x > hitbox.x) ? target1.x - (hitbox.x + static_cast<int>(hitbox.w / 2)) : target1.x + static_cast<int>(hitbox.w / 2) - hitbox.x;
	}
	if (AABB(platform, target2)) {
		in1->setTarget(true);
		dist2 = (target2.x > hitbox.x) ? target2.x - (hitbox.x + static_cast<int>(hitbox.w / 2)) : target2.x + static_cast<int>(hitbox.w / 2) - hitbox.x;
	}
	if (abs(dist2) < abs(dist1)) { in1->setDistance(dist2); }
	else { in1->setDistance(dist1); }
}

void GerenciadorDeColisao::colisao_projeteis_obstaculos() {
	SDL_Rect initialhitbox, hitbox;
	SDL_Rect obstHitbox; 
	ComponenteTransform* transform = nullptr;
	Vector2D velocity;

	for (auto& p : projeteis) {
		if (p->isActive()) {
			transform = p->getComponente<ComponenteTransform>();
			initialhitbox = p->getComponente<ComponenteColisao>()->getColisor();
			hitbox = initialhitbox;

			velocity.x = transform->velocidade.x * p->getSpeed();
			velocity.y = transform->velocidade.y * p->getSpeed();

			for (auto& t : tilemap->hitbox_plataformas) {
				if (t->isOnScreen()) {
					hitbox = initialhitbox;
					hitbox.y += velocity.y; //futura posicao em y
					if (AABB(hitbox, t->getPos())) {
						if (velocity.y > 0) { //colidiu por cima
							transform->posicao.y = t->getPos().y - hitbox.h;
						}
						else if (velocity.y < 0) //colidiu por baixo
							transform->posicao.y = t->getPos().y + hitbox.h;
						transform->velocidade.y *= -1;
						p->collide();
						break;
					}

					hitbox = initialhitbox;
					hitbox.x += velocity.x; //futura posicao em x
					if (AABB(hitbox, t->getPos())) {
						if (velocity.x > 0) { //colidiu pela esquerda
							transform->posicao.x = t->getPos().x - hitbox.w;
						}
						else if (velocity.x < 0) //colidiu pela direita
							transform->posicao.x = t->getPos().x + hitbox.w;
						transform->velocidade.x *= -1;
						p->collide();
					}

				}
			}
		}
		
	}


}

bool GerenciadorDeColisao::AABB(SDL_Rect A, SDL_Rect B) {
	if (A.x + A.w > B.x &&
		B.x + B.w > A.x &&
		A.y + A.h > B.y &&
		B.y + B.h > A.y)
		return true;
	return false;	
}

Jogador* GerenciadorDeColisao::getJogador1(){
	return jogador1;
}

Jogador* GerenciadorDeColisao::getJogador2(){
	return jogador2;
}

void GerenciadorDeColisao::ataqueJ1() {
	SDL_Rect hitbox = { 0,0,64,32 };
	ComponenteTransform* transform = jogador1->getComponente<ComponenteTransform>();
	if (jogador1->facingLeft()) { //virado para a esquerda
		hitbox.x = transform->posicao.x - 2*Mapa::tamanhoTile();
		hitbox.y = transform->posicao.y;
	}
	else {
		hitbox.x = transform->posicao.x + Mapa::tamanhoTile();
		hitbox.y = transform->posicao.y;
	}

	SDL_Rect colisor;
	for (auto& i : inimigos) {
		if (i != nullptr) {
			if (i->isAlive()) {
				colisor = i->getComponente<ComponenteColisao>()->getColisor();
				if (AABB(hitbox, colisor)) {
					i->damage();
					//jogador1->hit(1000);
					if (!i->isAlive())//se matou o inimigo
						jogador1->hit(10000);
				}
			}
		}
	}
}

void GerenciadorDeColisao::ataqueJ2() {
	SDL_Rect hitbox = { 0,0,64,32 };
	ComponenteTransform* transform = jogador2->getComponente<ComponenteTransform>();
	if (jogador2->facingLeft()) { //virado para a esquerda
		hitbox.x = transform->posicao.x - 2 * Mapa::tamanhoTile();
		hitbox.y = transform->posicao.y;
	}
	else {
		hitbox.x = transform->posicao.x + Mapa::tamanhoTile();
		hitbox.y = transform->posicao.y;
	}

	SDL_Rect colisor;
	for (auto& i : inimigos) {
		if (i != nullptr) {
			if (i->isAlive()) {
				colisor = i->getComponente<ComponenteColisao>()->getColisor();
				if (AABB(hitbox, colisor)) {
					i->damage();
					//jogador2->hit(1000);
					if (!i->isAlive())//se matou o inimigo
						jogador2->hit(10000);
				}
			}
		}
	}
}

void GerenciadorDeColisao::ataqueEsqueleto(Esqueleto* in1) {
	SDL_Rect pos = in1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect hitbox = { 0, pos.y - pos.h, 32, 64 };
	hitbox.x = (in1->facingLeft()) ? pos.x - pos.w : pos.x + pos.w;

	if (AABB(hitbox, jogador1->getComponente<ComponenteColisao>()->getColisor())) {
		jogador1->damage();
		jogador1->getComponente<ComponenteTransform>()->velocidade.y = -0.5;
	}
	if (AABB(hitbox, jogador2->getComponente<ComponenteColisao>()->getColisor())) {
		jogador2->damage();
		jogador2->getComponente<ComponenteTransform>()->velocidade.y = -0.5;
	}
}

void GerenciadorDeColisao::ataqueGoblin(Goblin* in1) {
	SDL_Rect pos = in1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect hitbox = { 0, in1->getPlatform().y - 32, 32, 32};

	hitbox.x = (in1->facingLeft()) ? pos.x - pos.w : pos.x + pos.w;

	if (AABB(hitbox, jogador1->getComponente<ComponenteColisao>()->getColisor())) 
		jogador1->damage(in1->attack());
	
	if (AABB(hitbox, jogador2->getComponente<ComponenteColisao>()->getColisor())) 
		jogador2->damage(in1->attack());
	
}
