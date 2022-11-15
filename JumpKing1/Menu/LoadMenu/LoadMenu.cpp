#include "LoadMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

LoadMenu::LoadMenu() {
	background = nullptr;
}

LoadMenu::~LoadMenu() {
	SDL_DestroyTexture(background);
}

void LoadMenu::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	back.set(0.1 * dm.w, 0.8 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	back.setTex("Assets/Buttons/Back Button.png");

	save1.set(0.75 * dm.w, 0.25 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	save1.setTex("Assets/Buttons/Level 1.png");

	save2.set(0.75 * dm.w, 0.43 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	save2.setTex("Assets/Buttons/Level 2.png");

	background = graphics->LoadTexture("Assets/Buttons/menu.png");
}

void LoadMenu::reset() {
	save1.reset();
	save2.reset();
	back.reset();
}

int LoadMenu::update() {
	graphics->clear();
	SDL_PollEvent(&Jogo::evento);
	render();
	graphics->present();

	save1.handleEvents();
	if (save1.click()) return BUTTON_START1;	
	
	save2.handleEvents();
	if (save2.click()) return BUTTON_START2;
	
	back.handleEvents();
	if (back.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void LoadMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,graphics->getDimensoesJanela().x,graphics->getDimensoesJanela().y };
	graphics->render(background, fonte, destino);
	save1.render();
	save2.render();
	back.render();
}