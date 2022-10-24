#include "Botao.h"
#include "../../Jogo/Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorDeTexturas.h"

//classe button

Button::Button() {
	pos.x = pos.y = pos.w = pos.h = 0;
	SDL_Color white;
	white.r = white.g = white.b = 255;
	isClicked = isHovering = false;
	texture = nullptr;
}

void Button::set(int xpos, int ypos, int width, int height, std::string text) {
	pos.x = xpos;
	pos.y = ypos;
	pos.w = width;
	pos.h = height;
	isClicked = isHovering = false;
}

void Button::setTex(const char* path) {
	texture = GerenciadorDeTexturas::CarregaTextura(path);
	if (texture) std::cout << "button loaded!\n";
	else std::cout << IMG_GetError();
}

Button::~Button() {
	SDL_DestroyTexture(texture);
}

void Button::handleEvents() {
	if (getMousePos().x > pos.x && getMousePos().x < pos.x + pos.w &&
		getMousePos().y > pos.y && getMousePos().y < pos.y + pos.h)
		isHovering = true;
	else isHovering = false;

	if (isHovering) {
		SDL_PollEvent(&Jogo::evento);
		if (Jogo::evento.type == SDL_MOUSEBUTTONDOWN) {
			if (Jogo::evento.button.button == SDL_BUTTON_LEFT) {
				isClicked = true;
				onClick(); //chama função de clique
			}
		}
		else isClicked = false;
	}
}

void Button::render() {
	SDL_Rect fonte;
	fonte.x = fonte.y = 0;
	fonte.w = pos.w;
	fonte.h = pos.h;
	GerenciadorDeTexturas::Desenhe(texture, fonte, pos);
}

intVector2D Button::getMousePos() {
	intVector2D v;
	SDL_GetMouseState(&v.x, &v.y);
	return v;
}

void Button::onClick() {
	std::cout << "Button Clicked!\n";
}
