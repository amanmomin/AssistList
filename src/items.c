#include <pebble.h>
#include "items.h"


#define NUM_MENU_PRODUCTS_SECTIONS 1
#define NUM_FIRST_PRODUCTS_ITEMS 7
#define CHECKMARK_KEY 1

Window *s_products_window;
static SimpleMenuLayer *s_products_menu_layer;
static SimpleMenuSection s_products_sections[NUM_MENU_PRODUCTS_SECTIONS];
static SimpleMenuItem s_first_products_items[NUM_FIRST_PRODUCTS_ITEMS];
static GBitmap *unchecked;
static GBitmap *checked;
Booleans booleans;
int items_index = 0;

const char *static_data[5][7] = {
	{
		"Milk", "Cheese", "Yogurt", "Butter", "Ice cream", "Curd", "Cottage cheese"
	},
	{
		"Orange", "Tomatoes", "Apple", "Dragon Fruit", "Bananas", "Peas", "Corn"
	},
	{
		"Steak", "Pork", "Chicken", "Beef", "Shrimp", "Tuna", "Horse"
	},
	{
		"Cereal", "Bread", "Flour", "Bagels", "Croissants", "Donuts", "Timbits"
	},
	{
		"Toys", "Altoids", "Purple Drank", "Watermelone", "Buttered Noodles", "Candy", "Solo cups"
	}
};

int data_framework_save_checkboxes(){
   int result = persist_write_data(CHECKMARK_KEY, &booleans, sizeof(booleans));
	APP_LOG(APP_LOG_LEVEL_INFO, "Saved %d bytes", result);
   return result;
}

int data_framework_load_checkboxes(){
   int result = persist_read_data(CHECKMARK_KEY, &booleans, sizeof(booleans));
	APP_LOG(APP_LOG_LEVEL_INFO, "Loaded %d bytes", result);
   return result;
}

static void checkmark_select_callback(int index, void *ctx) {
    booleans.checkmark_account[items_index][index]=!booleans.checkmark_account[items_index][index];
    if (booleans.checkmark_account[items_index][index]){
      s_first_products_items[index].icon= checked;
      
    }
  else{
      s_first_products_items[index].icon=unchecked;
  }
  layer_mark_dirty(simple_menu_layer_get_layer(s_products_menu_layer));
}  


Window *get_products_window(){
  return s_products_window;
}

static void products_window_load(Window *window) {
  data_framework_load_checkboxes();
 
  int num_a_items = 0;
  
  checked = gbitmap_create_with_resource(RESOURCE_ID_checked);
  unchecked = gbitmap_create_with_resource(RESOURCE_ID_unchecked);

  
  s_first_products_items[num_a_items++] = (SimpleMenuItem) {
    .title = static_data[items_index][num_a_items],
    .callback = checkmark_select_callback,
    
  };  
  s_first_products_items[num_a_items++] = (SimpleMenuItem) {
    .title = static_data[items_index][num_a_items],
    .callback = checkmark_select_callback,
    
  };
  s_first_products_items[num_a_items++] = (SimpleMenuItem) {
    .title = static_data[items_index][num_a_items],
    .callback = checkmark_select_callback,
    
  };
  s_first_products_items[num_a_items++] = (SimpleMenuItem) {
    .title = static_data[items_index][num_a_items],
    .callback = checkmark_select_callback,
    
  };
  s_first_products_items[num_a_items++] = (SimpleMenuItem) {
    .title = static_data[items_index][num_a_items],
    .callback = checkmark_select_callback,
    
  };
  s_first_products_items[num_a_items++] = (SimpleMenuItem) {
    .title = static_data[items_index][num_a_items],
    .callback = checkmark_select_callback,
    
  };
  s_first_products_items[num_a_items++] = (SimpleMenuItem) {
    .title = static_data[items_index][num_a_items],
    .callback = checkmark_select_callback,
    
  };
  s_products_sections[0] = (SimpleMenuSection) {
    .num_items = NUM_FIRST_PRODUCTS_ITEMS,
    .items = s_first_products_items,
  };
  
	for(int i = 0; i < NUM_FIRST_PRODUCTS_ITEMS; i++){
		APP_LOG(APP_LOG_LEVEL_INFO, "Running %d:%d %d", items_index, i, booleans.checkmark_account[items_index][i]);
		s_first_products_items[i].icon = booleans.checkmark_account[items_index][i] ? checked : unchecked;
	}

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  s_products_menu_layer = simple_menu_layer_create(bounds, window, s_products_sections, NUM_MENU_PRODUCTS_SECTIONS, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(s_products_menu_layer));
}

void products_window_unload(Window *window) {
  data_framework_save_checkboxes();
  simple_menu_layer_destroy(s_products_menu_layer);
}
							   
void products_set_index(int index){
	items_index = index;
}

void products_init() {
  s_products_window = window_create();
  window_set_window_handlers(s_products_window, (WindowHandlers) {
    .load = products_window_load,
    .unload = products_window_unload,
  });
}

void products_deinit() {
  window_destroy(s_products_window);
}

