#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "prop.h"

#include "toml.h"

toml_table_t* GetScript( FILE* fp_script );

toml_table_t* GetScene( toml_table_t* script );
toml_table_t* GetCharacter( toml_table_t* script );
toml_table_t* GetItem( toml_table_t* script );

toml_table_t* GetEvent( toml_table_t* script );
toml_table_t* GetDialogue( toml_table_t* script );

toml_table_t* GetMusic( toml_table_t* script );

void GetValue( Property* prop, toml_table_t* table );
