#include "MainMenu.h"


void MainMenu::onMouseEvent(MOUSE_DATA* md)
{
	for (int i = 0; i < buttonCount; i++)
	{
		buttons[i]->onMouseEvent(md);
	}
}

MainMenu::MainMenu(Player& p, GAME* g) : Map(p, 0), game(g)
{
	buttonCount = 2;
	buttons = new Button * [buttonCount];

	buttons[0] = new Button("Play", *(g->renderer) , 20, 20, 0, [this](int id) {onPlayClick(id); }, 0x00ffaaff);
	buttons[1] = new Button("Quit", *(g->renderer), 20, 40, 0, [this](int id) {onQuitClick(id); }, 0xff00aaff);
}

void MainMenu::onPlayClick(int id)
{
	string worldName = "FinalMap";

	Map::worldFromFile(MAPFILES_LOCATION, worldName);
	worldName = MAPFILES_LOCATION + worldName + "/" + worldName;
	game->worldName = worldName;
	*(game->currentMapId) = 0;
	game->currentMap = new Map(worldName, *(game->player), *(game->renderer), game->currentMapId);
}

void MainMenu::onQuitClick(int id)
{
	game->quit = true;
}

MainMenu::~MainMenu()
{
	delete[] buttons;
}

void MainMenu::render(RenderContext& renderer, int offsetX, int offsetY)
{
	for (int i = 0; i < buttonCount; i++)
	{
		buttons[i]->render(renderer, offsetX, offsetY);
	}
}

void MainMenu::tick(int time, RenderContext& r)
{
}
