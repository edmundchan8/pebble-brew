#include "frenchpress.h"
#include "string.h" // required for string concatenation

// Forward declarations for helper functions
// static void pop_french();]

// window for this script
static Window *s_french_window;

// current layer
static int s_current_layer = 1;

void update_text_layer(char *string_content){
   
    Layer *window_layer = window_get_root_layer(s_french_window);

    GRect bounds = layer_get_bounds(window_layer);
    TextLayer *text_layer = text_layer_create(GRect(0, 50, bounds.size.w, 50));
    text_layer_set_text(text_layer, string_content);
    text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
    layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void select_click_handler(){
    ++s_current_layer;
    char my_string[80];
    switch(s_current_layer){
        case 1:
            // load default
            // strcpy(my_string, "how much coffee do you need?");
            // update_text_layer(my_string);
            update_text_layer("how much coffee do you need?");
            break;
        case 2:
            // load countdown screen
            // strcpy(my_string, "counting down");
            // update_text_layer(my_string);
            update_text_layer("counting down");
            break;
        case 3:
            // first instruction
            // strcpy(my_string, "pour coffee into french press");
            // update_text_layer(my_string);
            update_text_layer("pour coffee into french press");
            break;
        default:
            // back home
            // strcpy(my_string, "this is default");
            // update_text_layer(my_string);
            update_text_layer("this is default");
            break;
    }
}

// Function prototype for click_config_provider - do we need new handlers in this script?
static void click_config_provider_french(void *context){
    // if up/down arrows clicked, call respective function
    // window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    // window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}


void french_window_unload(Window *window){
    window_destroy(s_french_window);
    s_french_window = NULL;
}

void french_window_load(Window *window){
    // Layer *window_layer = window_get_root_layer(window);
    // GRect bounds = layer_get_bounds(window_layer);
    update_text_layer("French Press\nSet Coffee\nPress Select Continue");

    // TextLayer *text_layer = text_layer_create(GRect(0, 50, bounds.size.w, 50));
    // text_layer_set_text(text_layer, "French Press\nSet Coffee and Water\nPress SELECT to Continue");
    // text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
    // layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

// gets called from pebble brew script, create window and returns it back with the load and unload methods
Window* push_french(){
    s_french_window = window_create();
    window_set_window_handlers(s_french_window, (WindowHandlers){
        .load = french_window_load,
        .unload = french_window_unload,
    });
    window_set_click_config_provider(s_french_window, click_config_provider_french);
    
    return s_french_window;
}