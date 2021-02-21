#include "MainMenu.h"

void MainMenu::onKeyDown(GAME* game)
{
	switch (game->keyLetter)
	{
	case 'Q':
		onQuitClick(0);
		break;
	case 'S':
		onStoryModeClick(0);
		break;
	case 'P':
		onPlayClick(0);
		break;
	default:
		break;
	}
}

MainMenu::MainMenu(Player& p, GAME* g) : Menu(p, g)
{
	RenderContext& r = *(g->renderer);

	addButton(new Button("PLAY", r, SZ_SCREENWIDTH / 3, SZ_SCREENHEIGHT - 150, 0, [this](int id) {onPlayClick(id); }, 0x00ffaaff, 0xffff00ff));
	addButton(new Button("STORYMODE", r, SZ_SCREENWIDTH / 2 - 40, SZ_SCREENHEIGHT - 150, 1, [this](int id) {onStoryModeClick(id); }, 0xff8800ff, 0xffff00ff));

	addButton(new Button("QUIT", r, 2 * SZ_SCREENWIDTH / 3, SZ_SCREENHEIGHT - 150, 2, [this](int id) {onQuitClick(id); }, 0xff00aaff, 0xffff00ff));


	Texture* welcome = r.LoadString("Welcome", 0xAA00FFFF);

	list<int> clrs;
	for (int i = 0; i < 20; i++)
	{
		clrs.push_back(255 | GetRandom(255) << 8 | GetRandom(255) << 16 | GetRandom(255) << 24);
	}
	Texture* banner = r.LoadAnimatedString("Dream of a Ridiculous Man !", clrs, 100);
	Texture* subtitle = r.LoadString("PROJECT", 0x007ACCFF);
	Texture* info = r.LoadString("PRESSMAIN", 0xaaaaaaff);
	addLabel(new Label(welcome, (SZ_SCREENWIDTH - welcome->getWidth() - banner->getWidth()) / 2, SZ_SCREENHEIGHT / 3));
	animation = new Label(banner, labels.front()->getX() + welcome->getWidth(), labels.front()->getY());
	addLabel(new Label(subtitle, (SZ_SCREENWIDTH - subtitle->getWidth()) / 2, labels.front()->getY() + welcome->getHeight() + 10));
	addLabel(new Label(info, (SZ_SCREENWIDTH - info->getWidth()) / 2, SZ_SCREENHEIGHT - 200));
	addLabel(animation);

	player.teleport(BLOCKS_W / 2, BLOCKS_H / 2);
}

void MainMenu::onPlayClick(int id)
{
	changeMap(game, "MainMap", -1, 0);
}

void MainMenu::onStoryModeClick(int id)
{
	game->player->setStory(new Story("demo", game));
}

void MainMenu::onQuitClick(int id)
{
	game->quit = true;
}

MainMenu::~MainMenu()
{
	 
}

void MainMenu::render(RenderContext& renderer, int offsetX, int offsetY) const
{
	Menu::render(renderer, offsetX, offsetY);

	player.DrawableEntity::render(renderer, offsetX, offsetY);
}

void MainMenu::tick(int time, GAME* game)
{ 
	static int lastTimeMv = 0;

	if (time - lastTimeMv > 500)
	{
		player.teleport(player.getX() + GetRandom(3) - 1, player.getY() + GetRandom(3) - 1);
		lastTimeMv = time;
	}

	Menu::tick(time, game);
}
