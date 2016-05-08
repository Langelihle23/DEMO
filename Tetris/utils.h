// utils.h contains the declarations of utility classes used in Tetris

#ifndef UTILS_H
#define UTILS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

namespace Tetris {
	namespace Utils {
		/*
		* Handles the sound loading and playing.
		*/
		class SoundManager {
		public:
			/*
			* Initilaises the sound manager and loads all the resources.
			*/
			SoundManager();
			/*
			* Cleans up allocated resources.
			*/
			~SoundManager();
			/*
			* The different sounds that can be played.
			*/
			enum SoundTrack { GAME_MUSIC, MISSION_IMPOSSIBLE, CRASH };

			/*
			* Plays a sound in the given playback mode.
			*/
			void playSound(SoundTrack sound, ALLEGRO_PLAYMODE mode, float volume);
			/*
			* Stops playing the sound. Usually for sound tracks that are played in a loop.
			*/
			void stopSound(SoundTrack sound);
		private:
			ALLEGRO_SAMPLE *gameMusic;
			ALLEGRO_SAMPLE_ID gameMusicId;
			ALLEGRO_SAMPLE *missionImpossible;
			ALLEGRO_SAMPLE_ID missionImpossibleId;
			ALLEGRO_SAMPLE *crash;
			ALLEGRO_SAMPLE_ID crashId;
		};

		/*
		* Class to handle working with images.
		*/
		class ImageManager {
		public:
			/*
			* Creates a new ImageManager.
			*/
			ImageManager();
			/*
			* Frees allocated memory.
			*/
			~ImageManager();
			/*
			* The different images available.
			*/
			enum Image { GAMEMUSIC, TETRIS, WALL };
			/*
			* Retrieves the Bitmap linked to the Image enum.
			*/
			ALLEGRO_BITMAP* getImage(Image image);
		private:
			ALLEGRO_BITMAP* gameMusic;
			ALLEGRO_BITMAP* Tetris;
			ALLEGRO_BITMAP* wall;
		};
	}
}

#endif