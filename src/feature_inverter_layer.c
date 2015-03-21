#include "pebble.h"
	
#define TITLE_BAR_SIZE
	
#define ANIM_DURATION 500
#define ANIM_DELAY 300

static Window *s_victory_window;
static TextLayer *s_text_victory;
static InverterLayer *s_inverted_layer;

/*static void do_animation(Layer* newlayer, Window *window){
	//In a loop, create the layer, delay for half a second&vibrate?, destroy the layer
	int i = 0;
	for(i = 0; i < 3; i++){
		layer_add_to_window(newlayer, window);
		psleep(1000);
		layer_show(newlayer);
		psleep(1000);
		layer_hide(newlayer);
		s_inverted_layer = inverter_layer_create(GRect(0, 0, 80, 80));
		layer_add_child(first_layer, inverter_layer_get_layer(s_inverted_layer));
		psleep(1000);
		inverter_layer_destroy(s_inverted_layer);
		psleep(1000);
	}
}*/

static void victory_window_load(Window *window) {
	//Create the text layer
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  s_text_victory = text_layer_create(GRect(0, 54, bounds.size.w, bounds.size.h-54 /* height */));
  text_layer_set_text(s_text_victory, "Victory!");
  text_layer_set_font(s_text_victory, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  text_layer_set_text_alignment(s_text_victory, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_text_victory));

	//Create InverterLayer
	s_inverted_layer = inverter_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
	layer_add_child(window_layer, inverter_layer_get_layer(s_inverted_layer));
	//psleep(2000);
	//layer_set_hidden((Layer*)s_inverted_layer, true);
	 vibes_double_pulse();
}

static void victory_window_unload(Window *window) {
  text_layer_destroy(s_text_victory);
}

static void init() {
	//Create the victory window
  s_victory_window = window_create();
  window_set_window_handlers(s_victory_window, (WindowHandlers) {
    .load = victory_window_load,
    .unload = victory_window_unload,
  });
  window_stack_push(s_victory_window, true);
}

static void deinit() {
  window_destroy(s_victory_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
