#include "GerenciadorGrafico.h"
#include <iostream>

#include "../GerenciadorDeCamera/GerenciadorDeCamera.h"

#include "../../../Jogo/Jogo.h"
#include "../../../Jogo/Fase/Fase.h"

GerenciadorGrafico* GerenciadorGrafico::manager = nullptr;

GerenciadorGrafico::GerenciadorGrafico() {
	tileset = nullptr;
	tilesetHitbox = nullptr;
	lava = nullptr;
	espinhos = nullptr;
	coracao = nullptr;
	renderer = nullptr;
	window = nullptr;
	font = nullptr;
	dimensoesJanela = { 0,0 };
}

GerenciadorGrafico::~GerenciadorGrafico() {
	SDL_DestroyTexture(tileset);
	SDL_DestroyTexture(tilesetHitbox);
	SDL_DestroyTexture(lava);
	SDL_DestroyTexture(espinhos);
	SDL_DestroyTexture(coracao);
	TTF_Quit();
}

GerenciadorGrafico* GerenciadorGrafico::getInstance() {
	if (manager == nullptr)
		manager = new GerenciadorGrafico;
	return manager;
}

void GerenciadorGrafico::deleteInstance() {
	delete manager;
	manager = nullptr;
}

void GerenciadorGrafico::init(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	SDL_DisplayMode dm;
	dm.w = largJanela;
	dm.h = alturaJanela;

	TTF_Init();

	if (telaCheia) {
		SDL_GetCurrentDisplayMode(0, &dm);
		largJanela = dm.w;
		alturaJanela = dm.h;
	}
	window = SDL_CreateWindow("Jump King", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largJanela, alturaJanela, NULL);
	if (!window) std::cout << "Failed Creating Window! Error:" << SDL_GetError();

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) { std::cout << "Failed Creating Renderer! Error:" << SDL_GetError(); }

	dimensoesJanela.x = (float)dm.w;
	dimensoesJanela.y = (float)dm.h;

	font = TTF_OpenFont("Assets/fonts/Roboto-Medium.ttf", 200);
	tilesetHitbox = IMG_LoadTexture(renderer, "Assets/TileMap/hitboxes colisao.png");
	tileset = IMG_LoadTexture(renderer, "Assets/TileMap/Tiles.png");
	lava = IMG_LoadTexture(renderer, "Assets/TileMap/lava.png");
	espinhos = IMG_LoadTexture(renderer, "Assets/TileMap/espinhos.png");
	coracao = IMG_LoadTexture(renderer, "Assets/coracao.png");
}

SDL_Texture* GerenciadorGrafico::LoadTexture(const char* fileName){
	SDL_Texture* tex = IMG_LoadTexture(renderer, fileName);
	if (!tex)
		std::cout << SDL_GetError() << std::endl;

	return tex;
}

SDL_Texture* GerenciadorGrafico::TextTexture(std::string str) {
	TTF_Font* tmpFont = TTF_OpenFont("Assets/fonts/acme.ttf", 30);
	SDL_Surface* TextSurface = TTF_RenderText_Solid(tmpFont, str.c_str(), { 0,0,0 });//load a surface with the text
	SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);//create a texture from the surface
	TTF_CloseFont(tmpFont);
	SDL_FreeSurface(TextSurface);
	return TextTexture;
}

SDL_Point GerenciadorGrafico::getDimensoesJanela() {
	return dimensoesJanela;
}

void GerenciadorGrafico::render(SDL_Texture* tex, SDL_Rect fonte, SDL_Rect destino, bool flip) {
	if (flip)
		SDL_RenderCopyEx(renderer, tex, &fonte, &destino, 0, NULL, SDL_FLIP_HORIZONTAL);
	else
		SDL_RenderCopy(renderer, tex, &fonte, &destino);
}

void GerenciadorGrafico::renderFase(Fase* fase) {
	SDL_RenderClear(renderer);

	fase->render();

	SDL_RenderPresent(renderer);
}

void GerenciadorGrafico::renderTile(SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(renderer, tileset, &fonte, &destino);
}

void GerenciadorGrafico::renderHitbox(SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(renderer, tilesetHitbox, &fonte, &destino);
}

void GerenciadorGrafico::renderEspinho(SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(renderer, espinhos, &fonte, &destino);
}

void GerenciadorGrafico::renderCoracao(SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(renderer, coracao, &fonte, &destino);
}

void GerenciadorGrafico::renderPontuacao(int pontuacao) {
	std::string ss = std::to_string(pontuacao);
	SDL_Surface* temp = TTF_RenderText_Solid(font, ss.c_str(), { 255,255,255 });
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_Rect camera = GerenciadorDeCamera::camera;

	SDL_Rect textRect = { 0,0.03* camera.h,0,0.05*camera.h };
	if (pontuacao < 10) { // 1 digito
		textRect.x = 0.49 * camera.w;
		textRect.w = 0.02 * camera.w;
	}
	else if (pontuacao < 100){ //2 digitos
		textRect.x = 0.48 * camera.w;
		textRect.w = 0.04 * camera.w;
	}
	else if (pontuacao < 1000) { //2 digitos
		textRect.x = 0.47 * camera.w;
		textRect.w = 0.06 * camera.w;
	}
	else if (pontuacao < 10000) { //4 digitos
		textRect.x = 0.46 * camera.w;
		textRect.w = 0.08 * camera.w;
	}
	else if (pontuacao < 100000) { //5 digitos
		textRect.x = 0.45 * camera.w;
		textRect.w = 0.1 * camera.w;
	}
	else{ //6+ digitos
		textRect.x = 0.44 * camera.w;
		textRect.w = 0.12 * camera.w;
	}
	
	SDL_RenderCopy(renderer, tex, NULL, &textRect);
	
	SDL_FreeSurface(temp);
	SDL_DestroyTexture(tex);
}

void GerenciadorGrafico::renderText(std::string text, SDL_Point position) {
	TTF_Font* tmpFont = TTF_OpenFont("Assets/fonts/acme.ttf", 30);
	SDL_Surface* TextSurface = TTF_RenderText_Solid(tmpFont, text.c_str(), { 0,0,0 });//load a surface with the text
	SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);//create a texture from the surface

	SDL_Rect tmp_Rect = { position.x,position.y,500,50 };
	SDL_QueryTexture(TextTexture, NULL, NULL, &tmp_Rect.w, &tmp_Rect.h);
	SDL_RenderCopy(renderer, TextTexture, NULL, &tmp_Rect);//copy to the renderer

	TTF_CloseFont(tmpFont);
	SDL_FreeSurface(TextSurface);
	SDL_DestroyTexture(TextTexture);
}

void GerenciadorGrafico::renderLava(SDL_Rect fonte, SDL_Rect destino) {
	SDL_RenderCopy(renderer, lava, &fonte, &destino);
}

void GerenciadorGrafico::renderRect(SDL_Rect rect, SDL_Color fill, SDL_Color outline) {
	SDL_SetRenderDrawColor(renderer, fill.r, fill.g, fill.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, outline.r, outline.g, outline.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);

}

