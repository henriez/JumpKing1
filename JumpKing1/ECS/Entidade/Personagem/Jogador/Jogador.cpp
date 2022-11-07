#include "Jogador.h"
#include "../../../Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../../Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include "../../../../Jogo/Jogo.h"
#include "../../../../Jogo/Fase/Mapa/Mapa.h"

Jogador::Jogador() : speed(8), maxSpeed(4) {
	inicializar();
	controladorEventos.setTransform(this);
	onGround = false;
	flip = false;
}

Jogador::~Jogador() {}

void Jogador::inicializar(){
	addComponente<ComponenteColisao>();
	addComponente<ComponenteSaude>();
	addComponente<ComponenteSprite>();
	addComponente<ComponenteTransform>();

	getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/HenriqueIsFallingx32.png");
	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 0;
	transform->velocidade.y = 0;
	transform->posicao.x = 0;
	transform->posicao.y = 0; //inicializa na fase->inicializar(id)

	getComponente<ComponenteColisao>()->set(transform->posicao.x, transform->posicao.y, 32, 32);
	getComponente<ComponenteSaude>()->init(6);
}

void Jogador::atualizar() {

	if (getComponente<ComponenteTransform>()->velocidade.x < 0 ) { flip = true; }
	else if ((getComponente<ComponenteTransform>()->velocidade.x > 0)) { flip = false; }
	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	getComponente<ComponenteColisao>()->setPos(transform->posicao.x, transform->posicao.y);

	setGround(false);
	transform->posicao.x += transform->velocidade.x * speed;
	transform->posicao.y += transform->velocidade.y * speed;
	if (transform->velocidade.y < -maxSpeed) transform->velocidade.y = -maxSpeed;
	else if (transform->velocidade.y > maxSpeed) transform->velocidade.y = maxSpeed; //velocidade terminal para queda

	
	controladorEventos.atualizar();
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
	posRect.x = (int)getComponente<ComponenteTransform>()->posicao.x - GerenciadorDeCamera::camera.x;
	posRect.y = (int)getComponente<ComponenteTransform>()->posicao.y - GerenciadorDeCamera::camera.y;

	SDL_Rect fonte = { 0,0,32,32 }; //muda caso jogador seja animado
	getComponente<ComponenteSprite>()->render(posRect, fonte, flip);

	//coloca CORACOES na tela
	int maxSaude = getComponente<ComponenteSaude>()->getMaxHealth();
	int saude = getComponente<ComponenteSaude>()->getHealth();
	fonte = { 0,0,40,40 };

	for (int i = 0; i < saude; i++) {
		posRect.x = (0.03 * i + 0.02) * GerenciadorDeCamera::camera.w;
		posRect.y = (0.03) * GerenciadorDeCamera::camera.h;
		posRect.w = posRect.h = 40;
		GerenciadorGrafico::renderCoracao(fonte, posRect);
	}
}

void Jogador::shoot() {
	Projetil* proj = new Projetil;
	proj->getComponente<ComponenteTransform>()->posicao.x = getComponente<ComponenteTransform>()->posicao.x;
	proj->getComponente<ComponenteTransform>()->posicao.y = getComponente<ComponenteTransform>()->posicao.y;
	if (flip) { proj->getComponente<ComponenteTransform>()->velocidade.x = -3; }
	else { proj->getComponente<ComponenteTransform>()->velocidade.x = 3; }
	
	GerenciadorDeColisao::addProjetil(proj);
}

void Jogador::damage() {
	getComponente<ComponenteSaude>()->damage();
}

bool Jogador::isAlive() {
	if (getComponente<ComponenteSaude>()->atualiza() == DEAD)
		return false;
	return true;
}