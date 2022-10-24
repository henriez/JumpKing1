#include "Botao.h"
#include "../../Jogo/Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorDeTexturas.h"

//classe button

Button::Button() {
	pos.x = pos.y = pos.w = pos.h = 0;
	SDL_Color white;
	white.r = white.g = white.b = 255;
	idleColor = hoverColor = clickColor = white;
	buttonText = "";
	isClicked = isHovering = false;


}

void Button::set(int xpos, int ypos, int width, int height, SDL_Color idle, SDL_Color hover, SDL_Color click, std::string text) {
	pos.x = xpos;
	pos.y = ypos;
	pos.w = width;
	pos.h = height;
	idleColor = idle;
	hoverColor = hover;
	clickColor = click;
	buttonText = text;
	isClicked = isHovering = false;

	texture = GerenciadorDeTexturas::CarregaTextura("Assets/button.png"); // para todos os botoes
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
			if (Jogo::evento.key.keysym.sym == SDL_BUTTON_LEFT) {
				isClicked = true;
				onClick(); //chama função de clique
			}
		}
		else isClicked = false;
	}
}

void Button::render() {
	//chamar textureManager
	SDL_Rect fonte;
	fonte.x = fonte.y = 0;
	fonte.w = pos.w;
	fonte.h = pos.h;
	GerenciadorDeTexturas::Desenhe(texture, fonte, pos);
	//testar flags isHovering e isClicked
}

intVector2D Button::getMousePos() {
	intVector2D v;
	SDL_GetMouseState(&v.x, &v.y);
	return v;
}

void Button::setButtonText(std::string text) {
	buttonText = text;
	//desenha texto na tela
	//usa SDL_ttf
}

void Button::onClick() {
	std::cout << "Button Clicked!\n";
}

//classe startButton

void StartButton::handleEvents() {
	
	if (getMousePos().x > pos.x && getMousePos().x < pos.x + pos.w &&
		getMousePos().y > pos.y && getMousePos().y < pos.y + pos.h)
		isHovering = true;
	else isHovering = false;

	if (isHovering) {
		if (Jogo::evento.type == SDL_MOUSEBUTTONDOWN) {
			if (Jogo::evento.button.button == SDL_BUTTON_LEFT) {
				isClicked = true; //verificar se entra aqui
				onClick(); //chama função de clique
			}
		}
		else isClicked = false;
	}
}

void StartButton::onClick() {
	std::cout << "StartButton Clicked!\n";
}

//class quitButton

void QuitButton::handleEvents() {
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

void QuitButton::onClick() {
	std::cout << "QuitButton Clicked!\n";
}

void SettingsButton::handleEvents() {
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

void SettingsButton::onClick() {
	std::cout << "QuitButton Clicked!\n";
}