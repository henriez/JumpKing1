#include "SaveMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

SaveMenu::SaveMenu() {
	background = nullptr;
}

SaveMenu::~SaveMenu() {
	SDL_DestroyTexture(background);
}

void SaveMenu::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	back.set(0.1 * dm.w, 0.65 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	back.setTex("Assets/Buttons/Back Button.png");

	quit.set(0.1 * dm.w, 0.8 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	quit.setTex("Assets/Buttons/Exit Button.png");

	save.set(0.75 * dm.w, 0.25 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	save.setTex("Assets/Buttons/Save.png");

	background = graphics->LoadTexture("Assets/Buttons/menu.png");
}

void SaveMenu::reset() {
	save.reset();
	back.reset();
	quit.reset();
}

int SaveMenu::update() {
	save.handleEvents();
	if (save.click()) return BUTTON_SAVE;	
	
	back.handleEvents();
	if (back.click()) return BUTTON_BACK;

	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void SaveMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,graphics->getDimensoesJanela().x,graphics->getDimensoesJanela().y };
	graphics->render(background, fonte, destino);
	save.render();
	back.render();
	quit.render();
}