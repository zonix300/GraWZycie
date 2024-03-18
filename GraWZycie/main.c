#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h> 
#include <conio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "pause.h"
#include "logic.h"

int main(){
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;

	Cell grid[HEIGHT][WIDTH] = { DEAD };
	init_grid(grid);

	
	al_init();

	display = al_create_display(500, 500);
	queue = al_create_event_queue();
	timer = al_create_timer(0.1);

	al_install_keyboard();
	al_init_primitives_addon();

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());

	if (!display){
		return -1;
	}
	bool running = true;
	bool is_paused = false;
	  
	al_start_timer(timer);

	init_logic(display, queue, timer);
	while (running){
		
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		al_flip_display(display);
		

		if (event.type == ALLEGRO_EVENT_KEY_UP) {
			init_pause(event, timer);
    	}
		
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			running = false;
		}
		if (event.type == ALLEGRO_EVENT_TIMER) {
			next_generation(grid);
		}
		
	}

	al_stop_timer(timer);

	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	return 0;
}

