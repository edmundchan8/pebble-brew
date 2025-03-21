#include <pebble.h>
#include "recipes.h"  // include the helper file for recipes

// #define FONT_KEY_GOTHIC_28 "RESOURCE_ID_GOTHIC_28"


// Declare a window and a text layer
static Window *s_main_window;
static Window *s_recipe_window;
static TextLayer *s_text_layer;
static TextLayer *s_text_layer_two;
#define MAX_RECIPES 3
static TextLayer *text_layer_array[MAX_RECIPES]; // create array of TextLayers
static int s_selected_layer = 1; // this sets the highlight field to first recipe

// Function prototype for click_config_provider
static void click_config_provider(void *context);

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

static void recipe_window(){
  APP_LOG(APP_LOG_LEVEL_INFO, "recipe_window() was called!");

  // create recipe window
  s_recipe_window = window_create();

  TextLayer *recipe_text_layer = text_layer_create(GRect(5, 15, 144, 50));
  text_layer_set_text(recipe_text_layer, "Where recipe shows");
  text_layer_set_text_alignment(recipe_text_layer, GTextAlignmentCenter);
  text_layer_set_font(recipe_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));

  layer_add_child(window_get_root_layer(s_recipe_window), text_layer_get_layer(recipe_text_layer));

  // push to top of window stack
  window_stack_push(s_recipe_window, true);
}

static void main_window_unload(Window *window){
  text_layer_destroy(s_text_layer);
  text_layer_destroy(s_text_layer_two);
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
  recipe_window();
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
  if (s_recipe_window){
    window_destroy(s_recipe_window);
    s_recipe_window = NULL;
  }
}

// main function
int main(void) {
  init();
  app_event_loop();
  deinit();
}