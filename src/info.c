#include "info.h"

void Usage( void ) {
	fprintf( stderr, "Usage: ./main [path]\n" );

	exit( 1 );
}
void NoScript( char* path ) {
	fprintf( stderr, "Path \"%s\" does not exist\n", path );

	exit( 1 );
}

void SDLError( void ) {
	fprintf( stderr, "%s\n", SDL_GetError() );

	exit( 1 );
}
void IMGError( void ) {
	fprintf( stderr, "%s\n", IMG_GetError() );

	exit( 1 );
}
void MIXError( void ) {
	fprintf( stderr, "%s\n", Mix_GetError() );

	exit( 1 );
}
void TTFError( void ) {
	fprintf( stderr, "%s\n", TTF_GetError() );

	exit( 1 );
}
