#include "pebble.h"
	
#define TITLE_BAR_SIZE

static Window *s_victory_window;
static TextLayer *s_text_victory;
static TextLayer *s_text_score;
static TextLayer *s_text_par;
static Layer *s_canvas_layer;
static InverterLayer *s_inverted_layer;

static int score = 0;
static char buffer[15];
static char buff[15];

static void canvas_update_proc(Layer *this_layer, GContext *ctx) {

  GPoint p0 = GPoint(0, 97);
  GPoint p1 = GPoint(144, 97);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, p0, p1);
	
	GPoint p2 = GPoint(0, 67);
  GPoint p3 = GPoint(144, 67);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, p2, p3);
	
	GPoint p4 = GPoint(0, 127);
  GPoint p5 = GPoint(144, 127);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, p4, p5);
	
	GPoint p18 = GPoint(0, 67);
  GPoint p19 = GPoint(0, 127);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, p18, p19);
	
	GPoint p6 = GPoint(43, 67);
  GPoint p7 = GPoint(43, 127);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, p6, p7);

	GPoint p8 = GPoint(63, 67);
  GPoint p9 = GPoint(63, 127);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, p8, p9);
	
	GPoint p10 = GPoint(83, 67);
  GPoint p11 = GPoint(83, 127);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, p10, p11);
	
	GPoint p12 = GPoint(103, 67);
  GPoint p13 = GPoint(103, 127);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, p12, p13);
	
	GPoint p14 = GPoint(123, 67);
  GPoint p15 = GPoint(123, 127);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, p14, p15);
	
	GPoint p16 = GPoint(143, 67);
  GPoint p17 = GPoint(143, 127);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, p16, p17);
}

static void victory_window_load(Window *window) {
	//Create the text layer
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
	
	//INCREMENT THE SCORE

  s_text_victory = text_layer_create(GRect(0, 20, bounds.size.w, bounds.size.h-25 /* height */));
  text_layer_set_text(s_text_victory, "Victory!");
  text_layer_set_font(s_text_victory, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_text_victory, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_text_victory));
	
	char *parText = "Par       ";

	s_text_par = text_layer_create(GRect(5, 70, bounds.size.w, bounds.size.h-70));
	//text_layer_set_text(s_text_score, "Par: ");
	text_layer_set_font(s_text_par, fonts_get_system_font(FONT_KEY_GOTHIC_18));
	text_layer_set_text_alignment(s_text_par, GTextAlignmentLeft);
	layer_add_child(window_layer, text_layer_get_layer(s_text_par));
	snprintf(buff, 15, "%s %d", parText, score);
	text_layer_set_text(s_text_par, buff);	

	 
	char *scoreText = "Score  ";

	s_text_score = text_layer_create(GRect(5, 100, bounds.size.w, bounds.size.h-100));
	//text_layer_set_text(s_text_score, "Par: ");
	text_layer_set_font(s_text_score, fonts_get_system_font(FONT_KEY_GOTHIC_18));
	text_layer_set_text_alignment(s_text_score, GTextAlignmentLeft);
	layer_add_child(window_layer, text_layer_get_layer(s_text_score));
	snprintf(buffer, 15, "%s %d", scoreText, score);
	text_layer_set_text(s_text_score, buffer);
	
  s_canvas_layer = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  layer_add_child(window_layer, s_canvas_layer);

  // Set the update_proc
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
	
	//Create InverterLayer
	s_inverted_layer = inverter_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
	layer_add_child(window_layer, inverter_layer_get_layer(s_inverted_layer));
	vibes_double_pulse();
}

static void victory_window_unload(Window *window) {
  text_layer_destroy(s_text_victory);
	
	window_destroy(window);
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
