#include <pebble.h>
#include "recipes.h"  // include the helper file for recipes

// Declare a window and a text layer
static Window *s_main_window;
static TextLayer *s_text_layer;
static TextLayer *s_text_layer_two;
#define MAX_RECIPES 3
static TextLayer *text_layer_array[MAX_RECIPES]; // create array of TextLayers
static int s_selected_layer = 2;

// Function prototype for click_config_provider
static void click_config_provider(void *context);

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
  text_layer_destroy(s_text_layer_two);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context){
  // Move selection up
  s_selected_layer = (s_selected_layer - 1 + 3) % 3; // Wrap around
  update_selection();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context){
  // Move selection down
  s_selected_layer = (s_selected_layer + 1 + 3) % 3; // Wrap around
  update_selection();
}

static void click_config_provider(void *context){
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  
}

// App initialization
static void init() {
  // update_selection();
  // Create the main window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers){
    .load = main_window_load,
    .unload = main_window_unload
  });

   // Set the click config provider
   window_set_click_config_provider(s_main_window, click_config_provider);


  // Show window
  window_stack_push(s_main_window, true);
}

// App deinitialization
static void deinit() {
  // Destory the main window
  window_destroy(s_main_window);
}

// main function
int main(void) {
  init();
  app_event_loop();
  deinit();
}