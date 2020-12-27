#include "MainMenu.h"

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
	default:
		break;
	}
}

MainMenu::MainMenu(Player& p, GAME* g) : Menu(p, g)
{
	RenderContext& r = *(g->renderer);

	addButton(new Button("Play", r, SZ_SCREENWIDTH / 3, SZ_SCREENHEIGHT - 150, 0, [this](int id) {onPlayClick(id); }, 0x00ffaaff, 0xffff00ff));
	addButton(new Button("Quit", r, 2 * SZ_SCREENWIDTH / 3, SZ_SCREENHEIGHT - 150, 0, [this](int id) {onQuitClick(id); }, 0xff00aaff, 0xffff00ff));
	
	Texture* welcome = r.LoadString("Welcome to the ", 0xAA00FFFF);
	animationTextures = new Texture * [20];
	int color;
	for (int i = 0; i < 20; i++)
	{
		color = 255 | GetRandom(255) << 8 | GetRandom(255) << 16 | GetRandom(255) << 24;
		animationTextures[i] = r.LoadString("Dream of a Ridiculous Man !", color);
	}

	Texture* subtitle = r.LoadString("ENS Software Engineering Project, year 2020", 0x007ACCFF);
	Texture* info = r.LoadString("Press S to start, Q to quit. You can also click on the text-buttons below.", 0xaaaaaaff);
	addLabel(new Label(welcome, (SZ_SCREENWIDTH - welcome->getWidth() - animationTextures[0]->getWidth()) / 2, SZ_SCREENHEIGHT / 3));
	animation = new Label(animationTextures[0], labels.front()->getX() + welcome->getWidth(), labels.front()->getY());
	addLabel(new Label(subtitle, (SZ_SCREENWIDTH - subtitle->getWidth()) / 2, labels.front()->getY() + welcome->getHeight() + 10));
	addLabel(new Label(info, (SZ_SCREENWIDTH - info->getWidth()) / 2, SZ_SCREENHEIGHT - 200));
	addLabel(animation);

	player.teleport(BLOCKS_W / 2, BLOCKS_H / 2);
}

void MainMenu::onPlayClick(int id)
{
	string worldName = "MainMap";
	game->worldName = worldName;
	*(game->currentMapId) = -1;
	game->currentMap = new Map(worldName, *(game->player), *(game->renderer), game->currentMapId);
	delete this;
}

void MainMenu::onQuitClick(int id)
{
	game->quit = true;
}

MainMenu::~MainMenu()
{
	//Not delete[] animationTextures because these ones were created through LoadString.
}

void MainMenu::render(RenderContext& renderer, int offsetX, int offsetY) const
{
	Menu::render(renderer, offsetX, offsetY);

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

	Menu::tick(time, game);
}
