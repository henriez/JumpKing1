#include "GerenciadorDeColisao.h"
#include "../GerenciadorDeCamera/GerenciadorDeCamera.h"

#include "../../../Jogo/Fase/Fase.h"
#include "../../../Jogo/Fase/Mapa/Mapa.h"
#include "../../../Jogo/Fase/Mapa/TileMap/TileMap.h"
#include "../../Entidade/Personagem/Jogador/Jogador.h"
#include "../../Entidade/Personagem/Inimigo/Esqueleto/Esqueleto.h"
#include "../../Entidade/Obstaculo/Obstaculo.h"

TileMap* GerenciadorDeColisao::tilemap = nullptr;
Jogador* GerenciadorDeColisao::jogador1 = nullptr;
Fase* GerenciadorDeColisao::fase = nullptr;
std::vector<Obstaculo*> GerenciadorDeColisao::obstaculos;
std::vector<Projetil*> GerenciadorDeColisao::projeteis;

GerenciadorDeColisao::GerenciadorDeColisao() {
	tilemap = nullptr;
	jogador1 = nullptr;
}

GerenciadorDeColisao::~GerenciadorDeColisao() {}

void GerenciadorDeColisao::saveObstaculos(const char* path) {
	
	std::ofstream out(path, std::ios::out);
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
}

void GerenciadorDeColisao::saveProjeteis(const char* path) {
	std::ofstream out(path, std::ios::out);
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
}

void GerenciadorDeColisao::setJogador(Jogador* jg) {
	jogador1 = jg;
}

void GerenciadorDeColisao::setTileMap(TileMap* tmap) {
	tilemap = tmap;
}

void GerenciadorDeColisao::setFase(Fase* fs) {
	fase = fs;
}

void GerenciadorDeColisao::addObstaculo(Obstaculo* obst) {
	obstaculos.push_back(obst);
}

void GerenciadorDeColisao::atualizaObstaculos() {

	for (auto& o : obstaculos) {
		o->setScreen(false);
		if (AABB(o->getComponente<ComponenteColisao>()->getColisor(), GerenciadorDeCamera::camera))
			o->setScreen(true);
	}

}

void GerenciadorDeColisao::renderObstaculos() {
	for (auto& o : obstaculos)
		if (o->isOnScreen())
			o->render();
}

void GerenciadorDeColisao::addProjetil(Projetil* proj) {
	projeteis.push_back(proj);
}

void GerenciadorDeColisao::atualizaProjeteis() {
	for (auto& p: projeteis) {
		p->atualizar();
		p->setScreen(false);
		if (AABB(p->getComponente<ComponenteColisao>()->getColisor(), GerenciadorDeCamera::camera))
			p->setScreen(true);
	}
}

void GerenciadorDeColisao::renderProjeteis() {
	for (auto& p : projeteis)
		if (p->isOnScreen())
			p->render();
}

void GerenciadorDeColisao::clear() {
	for (auto& o : obstaculos)
		delete o;
	obstaculos.clear();

	for (auto& p : projeteis)
		delete p;
	projeteis.clear();
}

void GerenciadorDeColisao::iniciaInimigo(Inimigo* in) {
	SDL_Rect initPos = in->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect result = { 0, 0, Mapa::tamanhoTile(), Mapa::tamanhoTile() };
	SDL_Rect platform = result;
	platform.x = static_cast<int>(initPos.x / result.w) * result.w;
	platform.y = static_cast<int>(initPos.y / result.h) * result.h;
	bool notFound = true;

	std::vector<Tile*>::iterator iter = tilemap->hitbox_plataformas.begin();

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
		// auto& t : tilemap->hitbox_plataformas
		for (auto& t : tilemap->hitbox_plataformas) {
			if (AABB({ platform.x - platform.w, platform.y, platform.w, platform.h }, t->getPos())) {
				notFound = true;
				platform.x -= platform.w;
			}
			else if (AABB({ platform.x - platform.w, platform.y - result.h, platform.w, platform.h }, t->getPos())) {
				notFound = true;
				platform.x -= platform.w;
			}
		}
	}
	result.x = platform.x;

	// Encontra ponta direita
	platform.x = static_cast<int>(initPos.x / result.w) * result.w;
	platform.y = result.y;
	platform.w = platform.h = result.h;
	notFound = true;
	while (notFound) {
		notFound = false;
		for (auto& t : tilemap->hitbox_plataformas) {
			if (AABB({ platform.x + platform.w, platform.y, platform.w, platform.h }, t->getPos())) {
				notFound = true;
				platform.x += platform.w;
			}
		}
	}
	result.w = platform.x + platform.w - result.x;

	in->setPlatform(result);
}

void GerenciadorDeColisao::colisao_jogador1() {
	SDL_Rect initialhitbox = jogador1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect hitbox = initialhitbox;

	ComponenteTransform* transform = jogador1->getComponente<ComponenteTransform>();
	Vector2D velocity = transform->velocidade;

	if (!jogador1->inGround())
		transform->velocidade.y += 0.05; // simula gravidade 

	for (auto& t : tilemap->hitbox_plataformas) {
		if (t->isOnScreen()) {
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
		}
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
				break;
			}
		}

	}
	
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

	if (!jogador1->isAlive()) { //morreu -> encerra fase
		fase->gameOver();
	}
}



void GerenciadorDeColisao::colisao_esqueleto(Esqueleto* in1) {
	SDL_Rect hitbox = in1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect platform = in1->getPlatform();
	ComponenteTransform* transform = in1->getComponente<ComponenteTransform>();
	SDL_Rect target = jogador1->getComponente<ComponenteColisao>()->getColisor();

	platform.y -= 3 * Mapa::tamanhoTile();
	platform.h += 2 * Mapa::tamanhoTile();
	if (AABB(platform, target)) {
		in1->setTarget(true);
		if (target.x > hitbox.x) {
			in1->setDistance(target.x - (hitbox.x + static_cast<int>(hitbox.w / 2)));
		}
		else {
			in1->setDistance(target.x - static_cast<int>(target.w / 2) - hitbox.x);
		}
	}
	else { in1->setTarget(false); }
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

