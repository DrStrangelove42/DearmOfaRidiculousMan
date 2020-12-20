#include "MainMenu.h"


void MainMenu::onMouseEvent(MOUSE_DATA* md)
{
	for (int i = 0; i < buttonCount; i++)
	{
		buttons[i]->onMouseEvent(md);
	}
}

void MainMenu::onKeyDown(GAME* game)
{
	switch (game->keyLetter)
	{
	case 'Q':
		onQuitClick(0);
		break;
	case 'S':
		onPlayClick(0);
		break;
	case 'M':
	{
		string worldName = "MainMap";
		game->worldName = worldName;
		*(game->currentMapId) = -1;
		game->currentMap = new Map(worldName, *(game->player), *(game->renderer), game->currentMapId);
		break;
	}
	default:
		break;
	}
}

MainMenu::MainMenu(Player& p, GAME* g) : Map(p, 0), game(g)
{
	RenderContext& r = *(g->renderer);
	buttonCount = 2;
	buttons = new Button * [buttonCount];

	buttons[0] = new Button("Play", r, SZ_SCREENWIDTH / 3,  SZ_SCREENHEIGHT -150, 0, [this](int id) {onPlayClick(id); }, 0x00ffaaff, 0xffff00ff);
	buttons[1] = new Button("Quit", r, 2 * SZ_SCREENWIDTH / 3,  SZ_SCREENHEIGHT -150, 0, [this](int id) {onQuitClick(id); }, 0xff00aaff, 0xffff00ff);

	labelCount = 4;
	labels = new Label * [labelCount];
	Texture* welcome = LoadString("Welcome to the ", r, 0xAA00FFFF);
	animationTextures = new Texture * [20];
	int color;
	for (int i = 0; i < 20; i++)
	{
		color = 255 | GetRandom(255) << 8 | GetRandom(255) << 16 | GetRandom(255) << 24;
		animationTextures[i] = LoadString("Dream of a Ridiculous Man !", r, color);
	}

	Texture* subtitle = LoadString("ENS Software Engineering Project, year 2020", r, 0x007ACCFF);
	Texture* info = LoadString("Press S to start, Q to quit. You can also click on the text-buttons below.", r, 0xaaaaaaff);
	labels[0] = new Label(welcome, (SZ_SCREENWIDTH - welcome->getWidth() - animationTextures[0]->getWidth()) / 2, SZ_SCREENHEIGHT / 3);
	animation = new Label(animationTextures[0], labels[0]->getX() + welcome->getWidth(), labels[0]->getY());
	labels[1] = new Label(subtitle, (SZ_SCREENWIDTH - subtitle->getWidth()) / 2, labels[0]->getY() + welcome->getHeight() + 10);
	labels[2] = new Label(info, (SZ_SCREENWIDTH - info->getWidth()) / 2, SZ_SCREENHEIGHT - 200);
	labels[3] = animation;

	player.teleport(BLOCKS_W / 2, BLOCKS_H / 2);
}

void MainMenu::onPlayClick(int id)
{
	string worldName = "MainMap";
	game->worldName = worldName;
	*(game->currentMapId) = -1;
	game->currentMap = new Map(worldName, *(game->player), *(game->renderer), game->currentMapId);
}

void MainMenu::onQuitClick(int id)
{
	game->quit = true;
}

MainMenu::~MainMenu()
{
	delete[] buttons;
	delete[] labels;
	//Not delete[] animationTextures because these ones were created through LoadString.
}

void MainMenu::render(RenderContext& renderer, int offsetX, int offsetY)const
{
	for (int i = 0; i < buttonCount; i++)
	{
		buttons[i]->render(renderer, offsetX, offsetY);
	}

	for (int i = 0; i < labelCount; i++)
	{
		labels[i]->render(renderer, offsetX, offsetY);
	}

	player.DrawableEntity::render(renderer, offsetX, offsetY);
}

void MainMenu::tick(int time, GAME* game)
{
	static int i = 0;
	static int lastTime = 0;
	static int lastTimeMv = 0;

	if (time - lastTime > 100)
	{
		animation->setTexture(animationTextures[i++]);
		if (i == 20)
			i = 0;
		lastTime = time;
	}

	if (time - lastTimeMv > 500)
	{
		player.teleport(player.getX() + GetRandom(3) - 1, player.getY() + GetRandom(3) - 1);
		lastTimeMv = time;
	}
}
