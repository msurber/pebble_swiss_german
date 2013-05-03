#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xC7, 0x77, 0xDC, 0x1B, 0x0D, 0xFF, 0x4D, 0x40, 0x9E, 0x37, 0x14, 0x5B, 0x5D, 0xE1, 0xE2, 0xFD }
PBL_APP_INFO(MY_UUID,
             "Swiss German", "Micha Surber",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
TextLayer minuteLayer; // The Minutes
TextLayer hourLayer; // The hours

void init_text_layers(int linecount) {
  (void)linecount;
  int skippLines = 3 - linecount;
  text_layer_init(&minuteLayer, GRect(10, 10 - (skippLines * 21), 144-10 /* width */, 168-14 /* height */));
  text_layer_set_text_color(&minuteLayer, GColorWhite);
  text_layer_set_background_color(&minuteLayer, GColorClear);
  text_layer_set_font(&minuteLayer, fonts_get_system_font(FONT_KEY_GOTHAM_42_LIGHT));

  text_layer_init(&hourLayer, GRect(10, 94 - (skippLines * 21), 144-10 /* width */, 168-14 /* height */));
  text_layer_set_text_color(&hourLayer, GColorWhite);
  text_layer_set_background_color(&hourLayer, GColorClear);
  text_layer_set_font(&hourLayer, fonts_get_system_font(FONT_KEY_GOTHAM_42_BOLD));
}


void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)t;
  (void)ctx;

const char *hour_string[25] = { "zwölfi", "eis","zwei", "drü", "viäri", "föifi", "sächsi",
		 "sibni", "achti", "nüni", "zäni", "elfi", "zwölfi", "eis", "zwei", "drü", "viäri",
		 "föifi", "sächsi", "sibni", "achti", "nüni", "zäni", "elfi" , "zwölfi"};

  PblTm time;
  /* Get the current time from our time object */
  get_time(&time);

  int hour = time.tm_hour;
  int min = time.tm_min;
  char minute_text[50];
  char hour_text[50];
  if (min < 25) {
    strcpy(hour_text , hour_string[hour]);
  } else {
  	strcpy(hour_text , hour_string[hour + 1]);
  }
  if (-1 < min && min < 5) {
  	 strcpy(minute_text , "");
  }
  if (4 < min && min < 10) {
  	 strcpy(minute_text , "\nföif ab");
  }
  if (9 < min && min < 15) {
  	 strcpy(minute_text , "\nzäh ab");
  }
  if (14 < min && min < 20) {
  	 strcpy(minute_text , "viertel ab");
  }
  if (19 < min && min < 25) {
  	 strcpy(minute_text , "zwänzg ab");
  }
  if (24 < min && min < 30) {
  	 strcpy(minute_text , "föif vor halbi");
  }
  if (29 < min && min < 35) {
  	 strcpy(minute_text , "\nhalbi");
  }
  if (34 < min && min < 40) {
  	 strcpy(minute_text , "föif ab halbi");
  }
  if (39 < min && min < 45) {
  	 strcpy(minute_text , "zwänzg vor");
  }
  if (44 < min && min < 50) {
  	 strcpy(minute_text , "viertel vor");
  }
  if (49 < min && min < 55) {
  	 strcpy(minute_text , "\nzäh vor");
  }
  if (54 < min && min < 60) {
  	 strcpy(minute_text , "\nföif vor");
  }
/*
  if (linecount > 4) {
	  init_text_layers(linecount);
  }
*/
  
  static char staticTimeText[50] = ""; // Needs to be static because it's used by the system later.
  strcpy(staticTimeText , "");
  strcat(staticTimeText , minute_text);
  text_layer_set_text(&minuteLayer, staticTimeText);

  static char staticHourText[50] = ""; // Needs to be static because it's used by the system later.
  strcpy(staticHourText , "");
  strcat(staticHourText , hour_text);
  text_layer_set_text(&hourLayer, staticHourText);
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Swiss German");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);

  init_text_layers(3);

  layer_add_child(&window.layer, &minuteLayer.layer);
  layer_add_child(&window.layer, &hourLayer.layer);

  PblTm tick_time;
  get_time(&tick_time);
  handle_minute_tick(ctx, NULL);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,

    .tick_info = {
      .tick_handler = &handle_minute_tick,
      .tick_units = MINUTE_UNIT
    }

  };
  app_event_loop(params, &handlers);
}
