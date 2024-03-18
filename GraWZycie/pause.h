#pragma once
#include <stdio.h> 
#include <conio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

void stop(ALLEGRO_EVENT event, ALLEGRO_TIMER* timer);
void resume(ALLEGRO_EVENT event, ALLEGRO_TIMER* timer);

void init_pause(ALLEGRO_EVENT event,
				ALLEGRO_TIMER* timer) {
	
	stop(event, timer);
	resume(event, timer);

}

void stop(ALLEGRO_EVENT event,
		  ALLEGRO_TIMER* timer) {
	
	switch (event.keyboard.keycode) {
	case ALLEGRO_KEY_0:
		al_stop_timer(timer);
	}
}


void resume(ALLEGRO_EVENT event,
			ALLEGRO_TIMER* timer) {

	switch (event.keyboard.keycode) {
	case ALLEGRO_KEY_1:
		al_start_timer(timer);
	}
}