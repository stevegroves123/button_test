/*
 * main.c
 * Sets up the Window, ClickConfigProvider and ClickHandlers.
 */

#include <pebble.h>
#include <select_buttons.h>
  
static Window *s_main_window;

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create output TextLayer
  // GRect(spaces in from left,spaces down from top,left_end,down_end)
  s_output_layer = text_layer_create(GRect(10, 50, window_bounds.size.w / 2, window_bounds.size.h / 2));
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text(s_output_layer, "No button pressed.");
  text_layer_set_text_alignment(s_output_layer, GTextAlignmentCenter);
  text_layer_set_overflow_mode(s_output_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_color(s_output_layer, GColorGreen);
  text_layer_set_background_color(s_output_layer, GColorBlack);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
}

static void main_window_unload(Window *window) {
  // Destroy output TextLayer
  text_layer_destroy(s_output_layer);
}

static void init() {
  // Create main Window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_set_click_config_provider(s_main_window, click_config_provider);
  window_stack_push(s_main_window, true);
}

static void deinit() {
  // Destroy main Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}