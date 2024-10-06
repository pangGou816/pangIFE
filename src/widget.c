#include "widget.h"

bool InitAll( void ) {
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
		fprintf( stderr, "%s\n", SDL_GetError() );
		success = false;
	}

	int flag = IMG_INIT_JPG | IMG_INIT_PNG;
	if( !( IMG_Init( flag ) & flag ) ) {
		fprintf( stderr, "%s\n", IMG_GetError() );
		success = false;
	}

	if( TTF_Init() < 0 ) {
		fprintf( stderr, "%s\n", TTF_GetError() );
		success = false;
	}

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
		fprintf( stderr, "%s\n", Mix_GetError() );
		success = false;
	}

	return success;
}
