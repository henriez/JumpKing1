#include "Jogador.h"
#include "../../../Gerenciador/GerenciadorDeCamera.h"
#include "../../../../Jogo/Jogo.h"
#include "../../../../Jogo/Fase/Mapa/Mapa.h"

Jogador::Jogador() {
	inicializar();
	controladorEventos.setTransform(this);
	GerenciadorDeCamera::setJogador(this);
	speed = 8;
}

Jogador::~Jogador() {}

void Jogador::inicializar(){
	addComponente<ComponenteAudio>();
	addComponente<ComponenteColisao>();
	addComponente<ComponenteSaude>();
	addComponente<ComponenteSprite>();
	addComponente<ComponenteTransform>();

	getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/HenriqueIsFallingx32.png");
	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 0;
	transform->velocidade.y = 0;
	transform->posicao.x = (float)(Jogo::getDimensoesJanela().x / 2.0 - Mapa::tamanhoTile() / 2.0);
	transform->posicao.y = (float)(Jogo::getDimensoesJanela().y / 2.0 - Mapa::tamanhoTile() / 2.0);
}

void Jogador::atualizar() {
	controladorEventos.atualizar();
}

void Jogador::render() {
	// Posicao Jogador na tela = Posicao Jogador no Mapa - Posicao Camera no Mapa
	SDL_Rect posRect = {0,0,Mapa::tamanhoTile(),Mapa::tamanhoTile()};
	posRect.x = (int)getComponente<ComponenteTransform>()->posicao.x - Mapa::camera.x;
	posRect.y = (int)getComponente<ComponenteTransform>()->posicao.y - Mapa::camera.y;

	getComponente<ComponenteSprite>()->render(posRect);
}