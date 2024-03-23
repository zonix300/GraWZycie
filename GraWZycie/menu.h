#pragma once
#include <stdio.h> 
#include <conio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "button.h"
#include "mouse_handler.h"

typedef enum {
	MENU,
	GAME
}Game_states;

Game_states state = MENU;

Button play_button;
Button close_button;

int pos_x;
int pos_y;
bool running = true;

void menu(ALLEGRO_DISPLAY* display,
	ALLEGRO_EVENT_QUEUE* queue,
	ALLEGRO_TIMER* timer,
	ALLEGRO_EVENT event) {

	ALLEGRO_FONT* font = al_load_font("Silkscreen-Regular.ttf", 32, 0);

	create_button(300, 200, 700, 275, al_map_rgb(255, 255, 255), &play_button);
	create_button(300, 400, 700, 475, al_map_rgb(255, 255, 255), &close_button);

	show_button(play_button);
	show_button(close_button);

	al_draw_text(font, al_map_rgb(0, 0, 0), 425, 215, 0, "Resume");
	al_draw_text(font, al_map_rgb(0, 0, 0), 455, 415, 0, "Exit");

	while (state == MENU && running) {
		al_wait_for_event(queue, &event);
		
		al_flip_display(display);
		
		
		
		
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			get_mouse_position(event, &pos_x, &pos_y);
			if (button_pressed(&play_button, event)) {
				puts("resume button was pressed");
				state = GAME;
			}
			if (button_pressed(&close_button, event)) {
				puts("close button was pressed");
				running = false;
			}
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			running = false;
		}
		
	}
}