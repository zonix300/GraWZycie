#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h> 
#include <conio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "logic.h"
#include "mouse_handler.h"
#include "menu.h"

int main(){
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;

	Cell grid[HEIGHT][WIDTH] = { DEAD };
	init_grid(grid);

	
	al_init();

	display = al_create_display(900, 900);
	queue = al_create_event_queue();
	timer = al_create_timer(1);

	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	if (!display){
		return -1;
	}
	if (!queue) {
		return -1;
	}
	if (!timer) {
		return -1;
	}
	
	bool is_paused = false;
	  
	al_start_timer(timer);

	state = GAME;

	while (state == GAME && running) {
		
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		al_flip_display(display);
		
		

		if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				state = MENU;
				menu(display, queue, timer, event); //переход в меню
				break;
			case ALLEGRO_KEY_0:
				al_stop_timer(timer); // пауза
				break;
			case ALLEGRO_KEY_1:
				al_set_timer_speed(timer, 2); // всё что ниже отвечает за смену скоррости
				al_start_timer(timer);
				break;
			case ALLEGRO_KEY_2:
				al_set_timer_speed(timer, 0.5);
				al_start_timer(timer);
				break;
			case ALLEGRO_KEY_3:
				al_set_timer_speed(timer, 0.1);
				al_start_timer(timer);
				break;
			case ALLEGRO_KEY_4:
				al_set_timer_speed(timer, 0.01);
				al_start_timer(timer);
				break;
			}
			

		}

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			running = false;
		}
		if (event.type == ALLEGRO_EVENT_TIMER) {
			next_generation(grid);

		}
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			ALLEGRO_MOUSE_STATE mouse_state;
			al_get_mouse_state(&mouse_state);
			if (al_mouse_button_down(&mouse_state, 1)) {
				draw_on_click(event, grid); // рисовать

			}
			if (al_mouse_button_down(&mouse_state, 2)) {
				erase_on_click(event, grid); // удалять клетки
			}
		}
	}

	al_stop_timer(timer);

	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	return 0;
}

