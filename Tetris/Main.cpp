// Main.cpp contains the main function which is the entry point to the game

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"

void initAllegro() {
	bool init = true;
	if (!al_init()) {
		init = false;
	}
	if (!al_install_keyboard()) {
		init = false;
	}
	if (!al_install_audio()) {
		init = false;
	}
	if (!al_init_acodec_addon()) {
		init = false;
	}
	if (!al_init_image_addon()) {
		init = false;
	}
	if (!al_init_primitives_addon()) {
		init = false;
	}
	if (!al_install_mouse()) {
		init = false;
	}
	al_init_font_addon();
	al_init_ttf_addon();
	if (!init) {
		throw "Could not fully initialise Allegro 5";
	}
}

/*
* Entry point to the game.
*/
int main(int n, char** args) {
	initAllegro();
	Tetris::Game game;
	return game.loop();
}