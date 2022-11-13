#include "PauseMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

PauseMenu::PauseMenu() {
	background = nullptr;
}

PauseMenu::~PauseMenu() {
	SDL_DestroyTexture(background);
}

void PauseMenu::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	quit.set(0.1 * dm.w, 0.6 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	quit.setTex("Assets/Buttons/Exit Button.png");

	resume.set(0.35* dm.w, 0.3 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	resume.setTex("Assets/Buttons/Button Resume.png");

	save.set(0.35 * dm.w, 0.45 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	save.setTex("Assets/Buttons/Save.png");

	background = graphics->LoadTexture("Assets/Buttons/menu.png");
}

void PauseMenu::reset() {
	resume.reset();
	quit.reset();
	save.reset();
}

int PauseMenu::update() {
	resume.handleEvents();
	if (resume.click()) return BUTTON_RESUME;

	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	save.handleEvents();
	if (save.click()) 
		return BUTTON_SAVE;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void PauseMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,graphics->getDimensoesJanela().x,graphics->getDimensoesJanela().y };
	graphics->render(background, fonte, destino);
	resume.render();
	quit.render();
	save.render();
}