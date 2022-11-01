#include "PauseMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

PauseMenu::PauseMenu() {
	background = nullptr;
}

PauseMenu::~PauseMenu() {
	SDL_DestroyTexture(background);
}

void PauseMenu::init() {
	quit.set(100, 500, 324, 156);
	quit.setTex("Assets/Buttons/quit.png");

	resume.set(500, 300, 324, 156);
	resume.setTex("Assets/Buttons/resume.png");

	background = GerenciadorGrafico::CarregaTextura("Assets/Buttons/menu.png");
}

void PauseMenu::reset() {
	resume.reset();
	quit.reset();
}

int PauseMenu::update() {
	resume.handleEvents();
	if (resume.click()) return BUTTON_RESUME;

	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void PauseMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,GerenciadorGrafico::getDimensoesJanela().x,GerenciadorGrafico::getDimensoesJanela().y };
	GerenciadorGrafico::Desenhe(background, fonte, destino);
	resume.render();
	quit.render();
}