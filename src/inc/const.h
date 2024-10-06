#pragma once

#define DFT_GAME_DIR "./demo"

#define SCR_W 1280
#define SCR_H 720

static SDL_Rect screen_rect = {0, 0, SCR_W, SCR_H};

static SDL_Rect ava_rect = {100, 340, 50, 50};
static SDL_Rect tac_rect = {550, 120, 270, 530};

static SDL_Rect charname_rect = {160, 339, 290, 50};
static SDL_Rect charnametext_rect = {170, 345, 270, 50};
static SDL_Rect textbox_rect = {100, 400, 1080, 260};
static SDL_Rect text_rect = {150, 430, 680, 100};
static SDL_Color text_color = {0xFF, 0xFF, 0xFF, 0xFF};
