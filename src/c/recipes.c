#include "recipes.h"

const char *font = FONT_KEY_GOTHIC_28_BOLD;

TextLayer* get_french_press_text_layer(){
    
    // Create the text layer with a local text_layer variable
    TextLayer *french_press_text_layer = text_layer_create(GRect(0, 15, 144, 50)); // Position and size of text layer

    // Set text and alignment
    text_layer_set_text(french_press_text_layer, "French Press");
    text_layer_set_text_alignment(french_press_text_layer, GTextAlignmentLeft);

    // Set text size
    text_layer_set_font(french_press_text_layer, fonts_get_system_font(font));
    
    return french_press_text_layer;
}

TextLayer* get_hario_text_layer(){
    
    // Create the text layer with a local text_layer variable
    TextLayer *hario_text_layer = text_layer_create(GRect(5, 65, 144, 50)); // Position and size of text layer

    // Set text and alignment
    text_layer_set_text(hario_text_layer, "Hario V60");
    text_layer_set_text_alignment(hario_text_layer, GTextAlignmentLeft);

    // Set text size
    text_layer_set_font(hario_text_layer, fonts_get_system_font(font));
    
    return hario_text_layer;
}

TextLayer* get_aeropress_text_layer(){
    
    // Create the text layer with a local text_layer variable
    TextLayer *aeropress_text_layer = text_layer_create(GRect(5, 115, 144, 50)); // Position and size of text layer

    // Set text and alignment
    text_layer_set_text(aeropress_text_layer, "Aeropress");
    text_layer_set_text_alignment(aeropress_text_layer, GTextAlignmentLeft);

    // Set text size
    text_layer_set_font(aeropress_text_layer, fonts_get_system_font(font));
    
    return aeropress_text_layer;
}
