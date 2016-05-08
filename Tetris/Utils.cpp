// Utils.cpp implements the SoundManager utility class
#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "utils.h"

// =========================Sound Manager==================================
/*
* Initilaises the sound manager and loads all the resources.
*/
Tetris::Utils::SoundManager::SoundManager() {
	al_reserve_samples(2);
	gameMusic = al_load_sample("assets/sounds/gameMusic.ogg");
	missionImpossible = al_load_sample("assets/sounds/Mission Impossible.ogg");
	crash = al_load_sample("assets/sounds/crash.wav");
}

/*
* Frees allocated memory.
*/
Tetris::Utils::SoundManager::~SoundManager() {
	al_destroy_sample(gameMusic);
	al_destroy_sample(missionImpossible);
	al_destroy_sample(crash);
}

/*
* Plays a sound file.
*/
void Tetris::Utils::SoundManager::playSound(Tetris::Utils::SoundManager::SoundTrack sound, ALLEGRO_PLAYMODE mode, float volume) {
	if (sound == GAME_MUSIC) {
		al_play_sample(gameMusic, volume, 0.0, 1.0, mode, &gameMusicId);
	}
	else if (sound == MISSION_IMPOSSIBLE) {
		al_play_sample(missionImpossible, volume, 0.0, 1.0, mode, &missionImpossibleId);
	}
	else if (sound == CRASH) {
		al_play_sample(crash, volume, 0.0, 1.0, mode, &crashId);
	}
}

/*
* Stops playing the sound. Usually for sound tracks that are played in a loop.
*/
void Tetris::Utils::SoundManager::stopSound(Tetris::Utils::SoundManager::SoundTrack sound) {
	if (sound == GAME_MUSIC) {
		al_stop_sample(&gameMusicId);
	}
	else if (sound == MISSION_IMPOSSIBLE) {
		al_stop_sample(&missionImpossibleId);
	}
	else if (sound == CRASH) {
		al_stop_sample(&crashId);
	}
}

// ===================ImageManager============================
/*
* Initialises the image manager and loads all the resources.
*/
Tetris::Utils::ImageManager::ImageManager() {
	gameMusic = al_load_bitmap("assets/images/gameMusic.jpg");
	Tetris = al_load_bitmap("assets/images/Tetris.jpg");
	wall = al_load_bitmap("assets/images/wall.jpg");
}

/*
* Frees memory allocated to image resources.
*/
Tetris::Utils::ImageManager::~ImageManager() {
	al_destroy_bitmap(gameMusic);
	al_destroy_bitmap(Tetris);
	al_destroy_bitmap(wall);
}

/*
* Gets the image associated with the enum.
*/
ALLEGRO_BITMAP* Tetris::Utils::ImageManager::getImage(Tetris::Utils::ImageManager::Image image) {
	switch (image) {
	case GAMEMUSIC:
		return gameMusic;
		break;
	case TETRIS:
		return Tetris;
		break;
	case WALL:
		return wall;
		break;
	default:
		return NULL;
	}
}