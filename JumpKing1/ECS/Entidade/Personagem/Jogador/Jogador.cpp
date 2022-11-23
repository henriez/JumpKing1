#include "Jogador.h"
#include "../../../Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../../Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include "../../../../Jogo/Jogo.h"
#include "../../../../Jogo/Fase/Mapa/Mapa.h"

Jogador::Jogador() : speed(8), maxSpeed(4), points(200000) {
	inicializar();
	onGround = false;
	flip = false;
	attacking = false;
	id = 1;
}

Jogador::Jogador(float x, float y, int points, int hp, int id) : speed(8), maxSpeed(4){
	timer = 0;
	this->points = points;
	onGround = false;
	flip = false;
	attacking = false;

	this->id = id;

	addComponente<ComponenteColisao>();
	addComponente<ComponenteSprite>();
	addComponente<ComponenteTransform>();

	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 0;
	transform->velocidade.y = 0;
	transform->posicao.x = x;
	transform->posicao.y = y; //inicializa na fase->inicializar(id)

	getComponente<ComponenteColisao>()->set(transform->posicao.x, transform->posicao.y, 32, 32);
	getComponente<ComponenteSaude>()->init(hp);

	if (id == 1) getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/HenriqueIsFallingx32.png");
	else if (id == 2) getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/player2.png");
}

Jogador::~Jogador() {}

void Jogador::inicializar(){
	addComponente<ComponenteColisao>();
	addComponente<ComponenteSprite>();
	addComponente<ComponenteTransform>();

	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 0;
	transform->velocidade.y = 0;
	transform->posicao.x = 0;
	transform->posicao.y = 0; //inicializa na fase->inicializar(id)

	getComponente<ComponenteColisao>()->set(transform->posicao.x, transform->posicao.y, 32, 32);
	getComponente<ComponenteSaude>()->init(6);
}

void Jogador::atualizar() {
	if (!vulnerable) {
		if (SDL_GetTicks() - vulnerable_timer > 1000) //dano a cada 1 segundo
			vulnerable = true;
	}
	if (attacking) {
		if (SDL_GetTicks() - timer > 500) //0.5 segundo de duração de ataque
			attacking = false;
	}
	if (getComponente<ComponenteTransform>()->velocidade.x < 0 ) { flip = true; }
	else if ((getComponente<ComponenteTransform>()->velocidade.x > 0)) { flip = false; }
	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	getComponente<ComponenteColisao>()->setPos(transform->posicao.x, transform->posicao.y);

	setGround(false);
	transform->posicao.x += transform->velocidade.x * speed;
	transform->posicao.y += transform->velocidade.y * speed;
	if (transform->velocidade.y < -maxSpeed) transform->velocidade.y = -maxSpeed;
	else if (transform->velocidade.y > maxSpeed) transform->velocidade.y = maxSpeed; //velocidade terminal para queda

	points--;

	
	//controladorEventos.atualizar();
}

void Jogador::atacar() {
	attacking = true;
	timer = SDL_GetTicks();
}

void Jogador::setGround(const bool inGround) {
	onGround = inGround;
}

bool Jogador::inGround() const {
	return onGround;
}

void Jogador::render() {
	// Posicao Jogador na tela = Posicao Jogador no Mapa - Posicao Camera no Mapa
	SDL_Rect posRect = {0,0,Mapa::tamanhoTile(),Mapa::tamanhoTile()};
	posRect.x = (int)getComponente<ComponenteTransform>()->posicao.x - GerenciadorDeCamera::getInstance()->camera.x;
	posRect.y = (int)getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::getInstance()->camera.y;

	SDL_Rect fonte = { 0,0,32,32 }; //muda caso jogador seja animado
	getComponente<ComponenteSprite>()->render(posRect, fonte, flip);

	if (attacking) {
		SDL_Rect fonte = { 32,0,32,32 };
		SDL_Rect destino = { 0,0,32,32 };
		if (flip) { //virado para a esquerda
			destino.x = getComponente<ComponenteTransform>()->posicao.x - Mapa::tamanhoTile() -GerenciadorDeCamera::getInstance()->camera.x;
			destino.y = getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::getInstance()->camera.y;
			graphics->renderHitbox(fonte, destino);

			destino.x = getComponente<ComponenteTransform>()->posicao.x - 2*Mapa::tamanhoTile() - GerenciadorDeCamera::getInstance()->camera.x;
			destino.y = getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::getInstance()->camera.y;
			graphics->renderHitbox(fonte, destino);

		}
		else {
			destino.x = getComponente<ComponenteTransform>()->posicao.x + Mapa::tamanhoTile() - GerenciadorDeCamera::getInstance()->camera.x;
			destino.y = getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::getInstance()->camera.y;
			graphics->renderHitbox(fonte, destino);

			destino.x = getComponente<ComponenteTransform>()->posicao.x + 2*Mapa::tamanhoTile() - GerenciadorDeCamera::getInstance()->camera.x;
			destino.y = getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::getInstance()->camera.y;
			graphics->renderHitbox(fonte, destino);
		}
	}
}

void Jogador::shoot() {
	Projetil* proj = new Projetil;
	proj->getComponente<ComponenteTransform>()->posicao.x = getComponente<ComponenteTransform>()->posicao.x;
	proj->getComponente<ComponenteTransform>()->posicao.y = getComponente<ComponenteTransform>()->posicao.y;
	if (flip) { proj->getComponente<ComponenteTransform>()->velocidade.x = -3; }
	else { proj->getComponente<ComponenteTransform>()->velocidade.x = 3; }
	
	GerenciadorDeColisao::getInstance()->addProjetil(proj);
}

void Jogador::damage(int dmg) {
	if (vulnerable) {
		vulnerable_timer = SDL_GetTicks();
		getComponente<ComponenteSaude>()->damage(dmg);
		vulnerable = false;
		getComponente<ComponenteTransform>()->velocidade.y = -0.5;
	}
}