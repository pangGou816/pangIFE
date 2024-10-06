#include "parse.h"

toml_table_t* GetScript( FILE* fp_script ) {
	char errbuf[256] = {0};
	toml_table_t* script = toml_parse_file( fp_script, errbuf, sizeof( errbuf ) );
	if( !script ) {
		fprintf( stderr, "Cannot parse \"%s\"\n", errbuf );

		exit( 1 );
	}

	fclose( fp_script );

	return script;
}

toml_table_t* GetScene( toml_table_t* script ) {
	toml_table_t* scene = toml_table_table( script, "scene" );

	return scene;
}
toml_table_t* GetCharacter( toml_table_t* script ) {
	toml_table_t* character = toml_table_table( script, "character" );

	return character;
}
toml_table_t* GetItem( toml_table_t* script ) {
	toml_table_t* item = toml_table_table( script, "item" );

	return item;
}

toml_table_t* GetEvent( toml_table_t* script ) {
	toml_table_t* event = toml_table_table( script, "event" );

	return event;
}
toml_table_t* GetDialogue( toml_table_t* script ) {
	toml_table_t* dialogue = toml_table_table( script, "dialogue" );

	return dialogue;
}

toml_table_t* GetMusic( toml_table_t* script ) {
	toml_table_t* music = toml_table_table( script, "music" );

	return music;
}

void GetValue( Property* prop, toml_table_t* table ) {
	toml_value_t scene = toml_table_string( table, "scene" );
	if( scene.u.s ) prop->scene = scene.u.s;

	toml_value_t character = toml_table_string( table, "character" );
	prop->character = character.u.s;

	toml_value_t item = toml_table_string( table, "item" );
	prop->item = item.u.s;

	toml_value_t text = toml_table_string( table, "text" );
	prop->text = text.u.s;

	toml_value_t next = toml_table_string( table, "next" );
	prop->next = next.u.s;

	toml_value_t event = toml_table_string( table, "event" );
	prop->event = event.u.s;

	toml_value_t score = toml_table_string( table, "score" );
	prop->score = score.u.s;

	toml_value_t total = toml_table_string( table, "total" );
	prop->total = total.u.s;

	toml_value_t dialogue = toml_table_string( table, "dialogue" );
	prop->dialogue = dialogue.u.s;

	toml_value_t music = toml_table_string( table, "music" );
	prop->music = music.u.s;
}
