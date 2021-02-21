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
	 
	int c;
	int R, G, B;
	R = 255;
	G = 0;
	B = 0;
	list<int> clrs;
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
		clrs.push_back(0xFF | R << 8 | G << 16 | B << 24);

	}
	c = 255 | (127 + GetRandom(128)) << 8 | (127 + GetRandom(128)) << 16 | (127 + GetRandom(128)) << 24;
	Texture* namest = r.LoadString("Q@DrStrangelove42       A@ads5699        V@vbonczak", c);
	Texture* at = r.LoadAnimatedString("THANKS", clrs, 50);
	animation = new Label(at, (SZ_SCREENWIDTH - at->getWidth()) / 2, SZ_SCREENHEIGHT - 50);
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
 
}


void EndCredits::tick(int time, GAME* game)
{
	static int i = 0; 

	if (names->getY() > 250)
	{
		names->teleport(-1, names->getY() - 4);
		animation->teleport(-1, animation->getY() - 4);
		if (i == 40)
			i = 0;
	}

	Menu::tick(time, game);
}
