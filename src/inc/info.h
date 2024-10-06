#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>

void Usage( void );
void NoScript( char* path );

void SDLError( void );
void IMGError( void );
void MIXError( void );
void TTFError( void );
