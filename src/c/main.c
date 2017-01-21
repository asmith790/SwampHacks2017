#include <pebble.h>
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_app_name;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, s_buffer);
}

static void main_window_load(Window *window){
  //Get info about the window 
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
	
	
	//Create text layer displaying app name with specific bounds
	s_app_name = text_layer_create(
	GRect(0, PBL_IF_ROUND_ELSE(20, 15), bounds.size.w,50));
	
	//Edit App Name Display 
	//NOT CURRENTLY FUNCTIONAL
	text_layer_set_background_color(s_app_name, GColorClear);
	text_layer_set_text_color(s_app_name, GColorBlack);
	text_layer_set_text(s_app_name, "00:00");
	text_layer_set_font(s_app_name, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_app_name, GTextAlignmentCenter);
	
	
	//Create clock text layer with specific bounds for displaying time
	s_time_layer = text_layer_create(
	GRect(0,PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));
	
	//Improve the layout
	text_layer_set_background_color(s_time_layer, GColorClear);
	text_layer_set_text_color(s_time_layer, GColorBlue);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
	
	 // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
    }
 
static void main_window_unload(Window *window){
     // Destroy TextLayer
  text_layer_destroy(s_time_layer);
  }

//Gets Time
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
update_time();
}
static void init(){


 //Create a window element
  s_main_window = window_create();
  
  //Manage  elements inside the window 
  window_set_window_handlers(s_main_window, (WindowHandlers){
  .load = main_window_load,
  .unload = main_window_unload
  });
  
  //Show the window on the watch
  window_stack_push(s_main_window, true);
	// Make sure the time is displayed from the start
update_time();

	// Register with TickTimerService
tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
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


static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
// doAlert();
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}