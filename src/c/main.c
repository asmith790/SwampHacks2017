#include <pebble.h>


static Window *s_main_window;
static TextLayer *s_alert;


static void main_window_load(Window *window){
  //Get info about the window 
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
	window_set_background_color(window, GColorRed);
	
	//Create text layer displaying alert with specific bounds
	s_alert = text_layer_create(
	GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w,50));
	
	//Edit alert display 
	text_layer_set_background_color(s_alert, GColorClear);
	text_layer_set_text_color(s_alert, GColorWhite);
	text_layer_set_text(s_alert, "ALERT");
	text_layer_set_font(s_alert, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_alert, GTextAlignmentCenter);
	
	 layer_add_child(window_layer, text_layer_get_layer(s_alert));
    }
 
static void main_window_unload(Window *window){
     // Destroy TextLayer
  text_layer_destroy(s_alert);
  }

static void init(){
	//Causes vibration notification
	vibes_double_pulse();
  
 //Create a window element
  s_main_window = window_create();
  
  //Manage  elements inside the main window 
  window_set_window_handlers(s_main_window, (WindowHandlers){
  .load = main_window_load,
  .unload = main_window_unload
  });
	
	//Displays the alert window
	window_stack_push(s_main_window, true);
}

static void deinit(){
  //Destroy Window
  window_destroy(s_main_window);
}

int main(void){
  init();
    app_event_loop();
  deinit();
}

