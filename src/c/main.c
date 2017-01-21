#include <pebble.h>
static Window *s_main_window;
static TextLayer *s_time_layer;

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  //  doAlert();
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


static void main_window_load(Window *window){
  //Get info about the window 
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
	
  //test
	//Create text layer with specific bounds
	s_time_layer = text_layer_create(
	GRect(0,PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));
	
	//Improve the layout
	text_layer_set_background_color(s_time_layer, GColorClear);
	text_layer_set_text_color(s_time_layer, GColorBlue);
	//APP NAME GOES HERE
  text_layer_set_text(s_time_layer, "BUZZ");
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
	
	 // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
    }
 
static void main_window_unload(Window *window){
     // Destroy TextLayer
  text_layer_destroy(s_time_layer);
  }

static void init(){
  
  // Register callbacks
app_message_register_inbox_received(inbox_received_callback);
app_message_register_inbox_dropped(inbox_dropped_callback);
app_message_register_outbox_failed(outbox_failed_callback);
app_message_register_outbox_sent(outbox_sent_callback);


 //Create a window element
  s_main_window = window_create();
  
  //Manage  elements inside the window 
  window_set_window_handlers(s_main_window, (WindowHandlers){
  .load = main_window_load,
  .unload = main_window_unload
  });
  
  //Show the window on the watch
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