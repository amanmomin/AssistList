#include <pebble.h>
#include "Splash.h"
#include "main.h"  
#include <time.h>
  

Window *splash_window; 

TextLayer *text_layer;

static GBitmap *s_splash_bitmap;
static BitmapLayer *s_splash_bitmap_layer;

Window *get_splash_window(){
  return splash_window;
} 

void timer_callback(void *data) {
  window_stack_pop(true);
  window_stack_push(get_main_window(),true);
}

static void splash_window_load(Window *window)
{
  app_timer_register(2000, (AppTimerCallback) timer_callback, NULL);
  Layer *window_layer = window_get_root_layer(window); 
  s_splash_bitmap = gbitmap_create_with_resource(RESOURCE_ID_logo);
  s_splash_bitmap_layer = bitmap_layer_create(GRect(9, 10, 130, 130));
  bitmap_layer_set_bitmap(s_splash_bitmap_layer, s_splash_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_splash_bitmap_layer));  
}
static void splash_window_unload(Window *window)
{
  gbitmap_destroy(s_splash_bitmap);
  bitmap_layer_destroy(s_splash_bitmap_layer);  
}

void handle_init(void) {
  splash_window = window_create(); 
  window_set_window_handlers(splash_window, (WindowHandlers) {
    .load = splash_window_load,
    .unload = splash_window_unload,
  });
  window_stack_push(splash_window, true);
}

void handle_deinit(void) {
  window_destroy(splash_window);
}

