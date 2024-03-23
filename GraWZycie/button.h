#pragma once
#include <stdio.h> 
#include <conio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "mouse_handler.h"

typedef enum {
	IDLE,
	PRESSED
} States;

typedef struct {
	States state;
	float x1;
	float y1;
	float x2;
	float y2;
	ALLEGRO_COLOR color;
} Button;

void create_button(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, Button* button) {
	button->state = IDLE;
	button->x1 = x1;
	button->y1 = y1;
	button->x2 = x2;
	button->y2 = y2;
	button->color = color;
}

bool button_pressed(Button* button, ALLEGRO_EVENT event) {
	if ((pos_x >= button->x1 && pos_x <= button->x2) && (pos_y >= button->y1 && pos_y <= button->y2)) { // если находится в пределах кнопки
		button->state = PRESSED;
		return true;
	}
	return false;
}

void show_button(Button button) {
	al_draw_filled_rectangle(button.x1, button.y1, button.x2, button.y2, button.color);
}
