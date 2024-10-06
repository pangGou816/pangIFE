#include "incl.h"

int main( int argc, char** argv ) {
	char game_dir[896] = {0};
	if( argc == 1 ) strcpy( game_dir, DFT_GAME_DIR );
	else if( argc == 2 ) strcpy( game_dir, argv[1] );
	else Usage();

	char script_path[1024] = {0};
	sprintf( script_path, "%s/%s", game_dir, "script.toml" );
	FILE* fp_script = fopen( script_path, "r" );
	if( !fp_script ) NoScript( script_path );

	toml_table_t* script = GetScript( fp_script );
	toml_table_t* scene = NULL,* character = NULL,* item = NULL,* event = NULL,* dialogue = NULL,* music = NULL;
	if( GetScene( script ) ) scene = GetScene( script );
	if( GetCharacter( script ) ) character = GetCharacter( script );
	if( GetItem( script ) ) item = GetItem( script );
	if( GetEvent( script ) ) event = GetEvent( script );
	if( GetDialogue( script ) ) dialogue = GetDialogue( script );
	if( GetMusic( script ) ) music = GetMusic( script );

	if( !InitAll() ) exit( 1 );

	SDL_Window* win = SDL_CreateWindow( "IFE Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_W, SCR_H, SDL_WINDOW_SHOWN );
	if( !win ) SDLError();
	SDL_Surface* win_sfc = NULL;
	win_sfc = SDL_GetWindowSurface( win );

	bool running = true;
	SDL_Event user_event;
	SDL_Surface* cur_scene = NULL;
	SDL_Surface* cur_avatar = NULL;
	SDL_Surface* cur_tachie = NULL;
	Mix_Music* bgm = NULL;
	int32_t score = 0;
	TTF_Font* font = TTF_OpenFont( "./font/font.ttf", 19 );
	if( !font ) TTFError();
	SDL_Surface* text_sfc = NULL;
	toml_table_t* cur_table = toml_table_table( event, "one" );
	Property prop = {0};
	GetValue( &prop, cur_table );
	for( ; running; ) {
		for( ; SDL_PollEvent( &user_event ); ) {
			if( user_event.type == SDL_QUIT ) running = false;
			if( user_event.type == SDL_KEYDOWN && user_event.key.keysym.sym == SDLK_RETURN ) {
				SDL_FillRect( win_sfc, &screen_rect, 0 );
				toml_table_t* scene_name = toml_table_table( scene, prop.scene );
				toml_value_t path = toml_table_string( scene_name, "path" );
				cur_scene = IMG_Load( path.u.s );
				if( !cur_scene ) IMGError();
				cur_scene = SDL_ConvertSurface( cur_scene, win_sfc->format, 0 );
				SDL_BlitScaled( cur_scene, NULL, win_sfc, &screen_rect );
				SDL_FreeSurface( cur_scene );
				cur_scene = NULL;
				free( path.u.s );
				if( prop.music ) {
					toml_table_t* music_name = toml_table_table( music, prop.music );
					toml_value_t music_path = toml_table_string( music_name, "path" );
					if( bgm ) {
						Mix_FreeMusic( bgm );
						bgm = NULL;
					}
					bgm = Mix_LoadMUS( music_path.u.s );
					if( !bgm ) MIXError();
					free( music_path.u.s );
					Mix_PlayMusic( bgm, -1 );
				}
				if( prop.next ) {
					cur_table = toml_table_table( dialogue, prop.next );
					GetValue( &prop, cur_table );
					if( prop.character ) {
						toml_table_t* character_name = toml_table_table( character, prop.character );
						toml_value_t name = toml_table_string( character_name, "name" );
						toml_value_t ava_path = toml_table_string( character_name, "avatar" );
						toml_value_t tac_path = toml_table_string( character_name, "tachie" );
						cur_avatar = IMG_Load( ava_path.u.s );
						if( !cur_avatar ) IMGError();
						cur_tachie = IMG_Load( tac_path.u.s );
						if( !cur_tachie ) IMGError();
						SDL_BlitScaled( cur_avatar, NULL, win_sfc, &ava_rect );
						SDL_BlitScaled( cur_tachie, NULL, win_sfc, &tac_rect );
						SDL_FillRect( win_sfc, &charname_rect, 0 );
						text_sfc = TTF_RenderUTF8_Solid( font, name.u.s, text_color );
						if( !text_sfc ) TTFError();
						SDL_BlitSurface( text_sfc, NULL, win_sfc, &charnametext_rect );
						SDL_FreeSurface( cur_tachie );
						cur_tachie = NULL;
						SDL_FreeSurface( cur_avatar );
						cur_avatar = NULL;
						SDL_FreeSurface( text_sfc );
						text_sfc = NULL;
						free( tac_path.u.s );
						free( ava_path.u.s );
						free( name.u.s );
					}
					if( prop.text ) {
						toml_value_t text = toml_table_string( cur_table, "text" );
						SDL_FillRect( win_sfc, &textbox_rect, 0 );
						text_sfc = TTF_RenderUTF8_Solid( font, text.u.s, text_color );
						if( !text_sfc ) TTFError();
						SDL_BlitSurface( text_sfc, NULL, win_sfc, &text_rect );
						SDL_FreeSurface( text_sfc );
						text_sfc = NULL;
						free( text.u.s );
					}
				} else if( prop.event ) {
					cur_table = toml_table_table( event, prop.event );
					GetValue( &prop, cur_table );
					if( prop.total ) {
						if( score < strtol( prop.total, NULL, 10 ) ) {
							free( prop.event );
							prop.event = NULL;
						} else {
							cur_table = toml_table_table( event, prop.event );
							GetValue( &prop, cur_table );
						}
					}
				} else if( prop.dialogue ) {
					cur_table = toml_table_table( dialogue, prop.dialogue );
					GetValue( &prop, cur_table );
					if( prop.character ) {
						toml_table_t* character_name = toml_table_table( character, prop.character );
						toml_value_t name = toml_table_string( character_name, "name" );
						toml_value_t ava_path = toml_table_string( character_name, "avatar" );
						toml_value_t tac_path = toml_table_string( character_name, "tachie" );
						cur_avatar = IMG_Load( ava_path.u.s );
						if( !cur_avatar ) IMGError();
						cur_tachie = IMG_Load( tac_path.u.s );
						if( !cur_tachie ) IMGError();
						SDL_BlitScaled( cur_avatar, NULL, win_sfc, &ava_rect );
						SDL_BlitScaled( cur_tachie, NULL, win_sfc, &tac_rect );
						SDL_FillRect( win_sfc, &charname_rect, 0 );
						text_sfc = TTF_RenderUTF8_Solid( font, name.u.s, text_color );
						if( !text_sfc ) TTFError();
						SDL_BlitSurface( text_sfc, NULL, win_sfc, &charnametext_rect );
						SDL_FreeSurface( cur_tachie );
						cur_tachie = NULL;
						SDL_FreeSurface( cur_avatar );
						cur_avatar = NULL;
						SDL_FreeSurface( text_sfc );
						text_sfc = NULL;
						free( name.u.s );
						free( tac_path.u.s );
						free( ava_path.u.s );
					}
					if( prop.text ) {
						toml_value_t text = toml_table_string( cur_table, "text" );
						SDL_FillRect( win_sfc, &textbox_rect, 0 );
						text_sfc = TTF_RenderUTF8_Solid( font, text.u.s, text_color );
						if( !text_sfc ) TTFError();
						SDL_BlitSurface( text_sfc, NULL, win_sfc, &text_rect );
						SDL_FreeSurface( text_sfc );
						text_sfc = NULL;
						free( text.u.s );
					}
				} else {
					if( prop.character ) {
						toml_table_t* character_name = toml_table_table( character, prop.character );
						toml_value_t name = toml_table_string( character_name, "name" );
						toml_value_t ava_path = toml_table_string( character_name, "avatar" );
						toml_value_t tac_path = toml_table_string( character_name, "tachie" );
						cur_avatar = IMG_Load( ava_path.u.s );
						if( !cur_avatar ) IMGError();
						cur_tachie = IMG_Load( tac_path.u.s );
						if( !cur_tachie ) IMGError();
						SDL_BlitScaled( cur_avatar, NULL, win_sfc, &ava_rect );
						SDL_BlitScaled( cur_tachie, NULL, win_sfc, &tac_rect );
						SDL_FillRect( win_sfc, &charname_rect, 0 );
						text_sfc = TTF_RenderUTF8_Solid( font, name.u.s, text_color );
						if( !text_sfc ) TTFError();
						SDL_BlitSurface( text_sfc, NULL, win_sfc, &charnametext_rect );
						SDL_FreeSurface( cur_tachie );
						cur_tachie = NULL;
						SDL_FreeSurface( cur_avatar );
						cur_avatar = NULL;
						SDL_FreeSurface( text_sfc );
						text_sfc = NULL;
						free( tac_path.u.s );
						free( ava_path.u.s );
						free( name.u.s );
					}
					if( prop.text ) {
						toml_value_t text = toml_table_string( cur_table, "text" );
						SDL_FillRect( win_sfc, &textbox_rect, 0 );
						text_sfc = TTF_RenderUTF8_Solid( font, text.u.s, text_color );
						if( !text_sfc ) TTFError();
						SDL_BlitSurface( text_sfc, NULL, win_sfc, &text_rect );
						SDL_FreeSurface( text_sfc );
						text_sfc = NULL;
						free( text.u.s );
					}
					toml_array_t* options = toml_table_array( cur_table, "options" );
					if( options ) {
						int32_t options_len = toml_array_len( options );
						for( int32_t i = 0; i < options_len; ++i ) {
							SDL_Rect num_rect = {150, 480 + i * 50, 680, 100};
							SDL_Rect option_rect = {190, 480 + i * 50, 640, 100};
							SDL_Rect item_rect = {700 + i * 110, 500, 50, 50};
							toml_table_t* option = toml_array_table( options, i );
							toml_value_t text = toml_table_string( option, "text" );
							if( text.ok ) text = text;
							else {
								text = toml_table_string( option, "item" );
								toml_table_t* item_name = toml_table_table( item, text.u.s );
								toml_value_t item_path = toml_table_string( item_name, "icon" );
								SDL_Surface* item_sfc = IMG_Load( item_path.u.s );
								if( !item_sfc ) IMGError();
								SDL_BlitSurface( item_sfc, NULL, win_sfc, &item_rect );
								SDL_FreeSurface( item_sfc );
								item_sfc = NULL;
							}
							char num[12] = {0};
							snprintf( num, 12, "%2d", i + 1 );
							text_sfc = TTF_RenderUTF8_Solid( font, num, text_color );
							if( !text_sfc ) TTFError();
							SDL_BlitSurface( text_sfc, NULL, win_sfc, &num_rect );
							SDL_FreeSurface( text_sfc );
							text_sfc = NULL;
							text_sfc = TTF_RenderUTF8_Solid( font, text.u.s, text_color );
							if( !text_sfc ) TTFError();
							SDL_BlitSurface( text_sfc, NULL, win_sfc, &option_rect );
							SDL_FreeSurface( text_sfc );
							text_sfc = NULL;
							free( text.u.s );
						}

						SDL_UpdateWindowSurface( win );

						for( ; 7; ) {
							SDL_Event choice_event;
							SDL_PollEvent( &choice_event );
							if( choice_event.type == SDL_QUIT ) return 0;
							if( choice_event.type == SDL_KEYDOWN ) {
								int32_t choice = choice_event.key.keysym.sym - 49;
								if( choice >= 0 && choice < options_len ) {
									toml_table_t* option = toml_array_table( options, choice );
									toml_value_t score_table = toml_table_string( option, "score" );
									if( score_table.u.s ) {
										score += strtol( score_table.u.s, NULL, 10 );
										free( score_table.u.s );
									}
									GetValue( &prop, option );

									break;
								}
							}
						}
					}
				}
			}
		}

		SDL_UpdateWindowSurface( win );
	}

	if( bgm ) {
		Mix_FreeMusic( bgm );
		bgm = NULL;
	}
	SDL_FreeSurface( win_sfc );
	win_sfc = NULL;
	SDL_DestroyWindow( win );
	win = NULL;

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	toml_free( script );

	return 0;
}
