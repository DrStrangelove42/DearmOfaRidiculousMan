#include "Menu.h"

Menu::Menu(Player& p, GAME* g) : Map(p, 0, (*g->renderer)), game(g)
{

}


Menu::~Menu()
{

	for (Button* b : buttons)
	{
		removeMouseHandler(b);
		delete b;
	}
	for (Label* l : labels)
	{
		delete l;
	}
	buttons.clear();
	labels.clear();
	//Not delete[] animationTextures because these ones were created through LoadString.
}

void Menu::render(RenderContext& renderer, int offsetX, int offsetY) const
{
	for (Button* b : buttons)
	{
		b->render(renderer, offsetX, offsetY);
	}

	for (Label* l : labels)
	{
		l->render(renderer, offsetX, offsetY);
	}
}

void Menu::tick(int time, GAME* game)
{
	for (Button* b : buttons)
	{
		b->tick(time, game);
	}
}

void Menu::addButton(Button* b)
{
	buttons.push_back(b);
	addMouseHandler(b,
		[b](MOUSE_DATA* md)
		{
			b->onMouseEvent(md);
		}
	);
}

void Menu::addLabel(Label* l)
{
	labels.push_back(l);
}
