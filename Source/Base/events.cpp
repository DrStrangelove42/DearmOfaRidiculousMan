#include "events.h"

void manageEvents(GAME* game)
{
	SDL_Event event;
	
	/*ea->currentRoom = &(game->currentMap->currentRoom);
	ea->currentMap = game->currentMapId;
	ea->warp_IsExternal = false;
	ea->player = game->player;
	ea->key = Other;
	 The following will allow us to know if the player needs to be teleported. 
	ea->destX = -1;
	ea->destY = -1;*/

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
		{
		        onKeyDown(event, game);
			break;
		}
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			onMouseEvent(event, game);
			break;
		case SDL_WINDOWEVENT:
			onWindowEvent(event, game);
			break;

		default:

			break;
		}
	}
}

void onWindowEvent(SDL_Event event, GAME* game)
{
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		game->quit = true;
}

void onMouseEvent(SDL_Event event, GAME* game)
{
	MOUSE_DATA* md = new MOUSE_DATA();

	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		md->state = MouseStateNone;
		md->x = event.motion.x;
		md->y = event.motion.y;
		md->button = MouseNoButton;
		break;
	default:
		md->x = event.button.x;
		md->y = event.button.y;
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			md->state = MouseStatePushed;
			break;
		case SDL_MOUSEBUTTONUP:
			md->state = MouseStateReleased;
			break;
		default:
			break;
		}

		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			md->button = MouseLeft;
			break;
		case SDL_BUTTON_MIDDLE:
			md->button = MouseMiddle;
			break;
		case SDL_BUTTON_RIGHT:
			md->button = MouseRight;
			break;
		default:
			break;
		}
		break;
	}

	game->currentMap->onMouseEvent(md);
}

void onKeyDown(SDL_Event event, GAME* game)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_DOWN:
	case SDLK_s:
		game->key = Down;
		break;
	case SDLK_UP:
	case SDLK_z:
		game->key = Up;
		break;
	case SDLK_LEFT:
	case SDLK_q:
		game->key = Left;
		break;
	case SDLK_RIGHT:
	case SDLK_d:
		game->key = Right;
		break;
	case SDLK_a:
		game->key = A;
		break;
	case SDLK_b:
		game->key = B;
		break;
	default:
		game->key = Other;
		break;
	}

	const char* sc = SDL_GetKeyName(event.key.keysym.sym);
	if (NULL != sc)
	{
		string scancode(sc);

		if (scancode.size() == 1)
			game->keyLetter = scancode[0];
		else
			game->keyLetter = 0;
	}

	game->currentMap->onKeyDown(game,game->key);
}

void quitGame(GAME* game)
{
	delete game->currentMap;
	delete game->player;

	FreeTextures();

	delete game->renderer;
	SDL_DestroyWindow(game->window);

	delete game;
}
 
