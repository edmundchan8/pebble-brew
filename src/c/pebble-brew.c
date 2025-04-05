#include <pebble.h>
#include "recipes.h"  // include the helper file for recipes
#include "frenchpress.h"

// #define FONT_KEY_GOTHIC_28 "RESOURCE_ID_GOTHIC_28"


// Declare a window and a text layer
static Window *s_main_window;
// copy of french window obtains from frenchpress script
static Window *s_french_window_copy;

// Forward declarations for helper functions
// static void pop_french();

// static Window *s_recipe_window;
static TextLayer *s_text_layer;
// static TextLayer *s_text_layer_french;
#define MAX_RECIPES 3
static TextLayer *text_layer_array[MAX_RECIPES]; // create array of TextLayers
static int s_selected_layer = 1; // this sets the highlight field to first recipe

// changes the background of recipe selection
static void update_selection(){
  int size = sizeof(text_layer_array) / sizeof(text_layer_array[0]);
  for (int i = 0; i < size; i++){
    if (s_selected_layer == i){
      text_layer_set_background_color(text_layer_array[i], GColorBlack);
      text_layer_set_text_color(text_layer_array[i], GColorWhite);
    } else {
      text_layer_set_background_color(text_layer_array[i], GColorWhite);
      text_layer_set_text_color(text_layer_array[i], GColorBlack);
    }
  }
}

// Window load handler
static void main_window_load(Window *window) {

  // use the recipes.c and recipes.h to import text layer codes
  text_layer_array[0] = get_aeropress_text_layer();
  text_layer_array[1] = get_french_press_text_layer();
  text_layer_array[2] = get_hario_text_layer();
  
  int size = sizeof(text_layer_array) / sizeof(text_layer_array[0]);

  for (int i = 0; i < size; i++){

    if (s_selected_layer == i){
      text_layer_set_background_color(text_layer_array[i], GColorBlack);
      text_layer_set_text_color(text_layer_array[i], GColorWhite);
    }
    // Add the text layer to the window's root layer for each array index
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer_array[i]));
  }
}

static void main_window_unload(Window *window){
  text_layer_destroy(s_text_layer);
  // text_layer_destroy(s_text_layer_french);
}



static void up_click_handler(ClickRecognizerRef recognizer, void *context){
  // Move selection up
  s_selected_layer = (s_selected_layer - 1 + 3) % 3; // configures which recipe to point to
  update_selection();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context){
  // Move selection down
  s_selected_layer = (s_selected_layer + 1 + 3) % 3; // configures which recipe to point to
  update_selection();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context){
  
  // TODO here we should do a while loop, that gets the current s_selected_layer an uses that to determine which recipe to get  
  // when select button clicked, get french press window from frenchpress.c
  s_french_window_copy = push_french();
  // push french press window to stack
  window_stack_push(s_french_window_copy, true);
}

static void click_config_provider(void *context){
  // if up/down arrows clicked, call respective function
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

// App initialization
static void init() {
  // Create the main window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers){
    .load = main_window_load,
    .unload = main_window_unload
  });

   // Set the click config provider - to manage click events
   window_set_click_config_provider(s_main_window, click_config_provider);

  // Show window
  window_stack_push(s_main_window, true);
}

// App deinitialization
static void deinit() {
  // Destory the main window
  window_destroy(s_main_window);
  window_destroy(s_french_window_copy);

}

// main function
int main(void) {
  init();
  app_event_loop();
  deinit();
}