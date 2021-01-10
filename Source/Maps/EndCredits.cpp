#include "EndCredits.h"

void EndCredits::onKeyDown(GAME* game)
{
	switch (game->keyLetter)
	{
	case 'B':
		onPlayClick(0);
		break;
	default:
		break;
	}
}

EndCredits::EndCredits(Player& p, GAME* g) : Menu(p, g)
{
	RenderContext& r = *(g->renderer);

	addButton(new Button("Close", r, SZ_SCREENWIDTH / 2 - 20, SZ_SCREENHEIGHT - 200, 0, [this](int id) {onPlayClick(id); }, 0x00ffaaff, 0xbbffbbff));

	animationTextures = new Texture * [42];
	int color, c;
	int R, G, B;
	R = 255;
	G = 0;
	B = 0;
	int step = 0;
	for (int i = 0; i < 42; i++)
	{
		step = i / 7;
		c = i % 7;
		switch (step)
		{
		case 0:
			G = c * 255 / 6;
			break;
		case 1:
			R = (6 - c) * 255 / 6;
			break;
		case 2:
			B = c * 255 / 6;
			break;
		case 3:
			G = (6 - c) * 255 / 6;
			break;
		case 4:
			R = c * 255 / 6;
			break;
		case 5:
			B = (6 - c) * 255 / 6;
			break;
		default:
			break;
		}
		color = 0xFF | R << 8 | G << 16 | B << 24;
		cout << R << ' ' << G << ' ' << B << endl;
		animationTextures[i] = r.LoadString("THANKS", color);
	}
	c = color = 255 | (127 + GetRandom(128)) << 8 | (127 + GetRandom(128)) << 16 | (127 + GetRandom(128)) << 24;
	Texture* namest = r.LoadString("Q@DrStrangelove42       A@ads5699        V@vbonczak", c);
	animation = new Label(animationTextures[0], (SZ_SCREENWIDTH - animationTextures[0]->getWidth()) / 2, SZ_SCREENHEIGHT - 50);
	addLabel(animation);
	names = new Label(namest, (SZ_SCREENWIDTH - namest->getWidth()) / 2, SZ_SCREENHEIGHT);
	addLabel(names);
}

void EndCredits::onPlayClick(int id)
{
	changeMap(game, "Main menu", 0, 0);
}

EndCredits::~EndCredits()
{
	//Not delete[] animationTextures because these ones were created through LoadString.
}


void EndCredits::tick(int time, GAME* game)
{
	static int i = 0;
	static int lastTime = 0;
	if (time - lastTime > 50)
	{
		animation->setTexture(animationTextures[i++]);
		if (i == 40)
			i = 0;
		lastTime = time;
	}

	if (names->getY() > 250)
	{
		names->teleport(-1, names->getY() - 4);
		animation->teleport(-1, animation->getY() - 4);
		if (i == 40)
			i = 0;
	}

	Menu::tick(time, game);
}
