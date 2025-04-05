#ifndef RECIPES_H   // check if RECIPES_H has not been defined yes
#define RECIPES_H   // define the RECIPES_H

// ifndef and define and endif are known as 'include guard', ensuring contents here only included once

#include <pebble.h>

TextLayer* get_french_press_text_layer(); // get french press text

TextLayer* get_hario_text_layer(); // get Hario V60 text

TextLayer* get_aeropress_text_layer(); // get Hario V60 text

TextLayer* start_french_press_recipe_text_layer(); // get French Press Recipe

#endif