#include "pebble.h"
#include "items.h"
#include "main.h"
#include "Splash.h"
#define NUM_MENU_SECTIONS 1
#define NUM_FIRST_MENU_ITEMS 5
#define NUM_SECOND_MENU_ITEMS 1

static Window *s_main_window;
static SimpleMenuLayer *s_simple_menu_layer;
static SimpleMenuSection s_menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem s_first_menu_items[NUM_FIRST_MENU_ITEMS];
static GBitmap *s_menu_icon_image;

Window *get_main_window(){
  return s_main_window;
}

static void menu_select_callback(int index, void *ctx) {
	products_set_index(index);
 window_stack_push(get_products_window(), true);
  

}

static void main_window_load(Window *window) {
  s_menu_icon_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_1);

  int num_a_items = 0;

  s_first_menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "Dairy",
    .callback = menu_select_callback,
};
  s_first_menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "Fruits and Veggies",
    .callback = menu_select_callback,
  };
  s_first_menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "Meats and Fish",
    .callback = menu_select_callback,
  };
   s_first_menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "Grains",
    .callback = menu_select_callback,
  };
 s_first_menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "Misc.",
    .callback = menu_select_callback,
  };

  s_menu_sections[0] = (SimpleMenuSection) {
    .num_items = NUM_FIRST_MENU_ITEMS,
    .items = s_first_menu_items,
  };
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  s_simple_menu_layer = simple_menu_layer_create(bounds, window, s_menu_sections, NUM_MENU_SECTIONS, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(s_simple_menu_layer));
}

void main_window_unload(Window *window) {
  simple_menu_layer_destroy(s_simple_menu_layer);
  gbitmap_destroy(s_menu_icon_image);
}

static void init() {
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });

}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  products_init();
  handle_init();
  app_event_loop();
  deinit();
  products_deinit();
  handle_deinit();
}