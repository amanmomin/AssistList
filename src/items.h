#pragma once
#include <pebble.h>
void products_init();
void products_set_index(int index);
void products_deinit();
Window *get_products_window();

typedef struct Booleans {
    bool checkmark_account[5][7];
} Booleans;