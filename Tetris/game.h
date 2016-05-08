// game.h contains the declarations for the classes used to create Tetris

#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "utils.h"
#include "graphics.h"

namespace Tetris {
	/*
	* The main game class.
	*/
	class Game {
	public:
		/*
		* Makes the calls to initialise allegro and sets up the game components.
		*/
		Game();
		/*
		* Frees up memory allocated.
		*/
		~Game();
		/*
		* The main game loop.
		*/
		int loop();
	private:
		/*
		* Helper class for buttons.
		*/
		class PlayButton : public Tetris::Graphics::Button {
		public:
			PlayButton(Game* g) : game(g), Tetris::Graphics::Button("Play", g->normalFont) {}
			/*
			* Implements the play button being clicked.
			*/
			void onClick();
		private:
			Game* game;
		};

		/*
		* Helper class for the demo button.
		*/
		class DemoButton : public Tetris::Graphics::Button {
		public:
			DemoButton(Game* g) : game(g), Tetris::Graphics::Button("Demo", g->normalFont) {}
			/*
			* Implements the demo button being clicked.
			*/
			void onClick();
		private:
			Game* game;
		};

		/*
		* Helper class for buttons.
		*/
		class QuitButton : public Tetris::Graphics::Button {
		public:
			QuitButton(Game* g) : game(g), Tetris::Graphics::Button("Quit", g->normalFont) {}
			/*
			* Implements the quit button being clicked.
			*/
			void onClick();
		private:
			Game* game;
		};

		ALLEGRO_DISPLAY *gameWindow;			// The main window for outputting graphics.
		ALLEGRO_EVENT_QUEUE *eventQueue;		// The queue that holds all the events except the timer.
		ALLEGRO_EVENT_QUEUE *timerQueue;		// The queue for the timer events so that they don't starve handling of the other events.
		Tetris::Utils::SoundManager soundManager;				// The sound manager.
		Tetris::Utils::ImageManager imageManager;				// The image manager.
		ALLEGRO_TIMER* timer;					// Timer for updating at 60Fps.
		const int FPS = 60;						// The frame rate.
		const float FPSIncrement = 1.0f / FPS;	// Frames per second increment (delta).
		bool shouldRun;							// Whether the game should run or not.

		Tetris::Graphics::Panel *currDisplay;	// The current display.
		ALLEGRO_FONT* bigFont;					// Font for the title of the game.
		ALLEGRO_FONT* normalFont;				// Font used for everything else.

		Tetris::Graphics::Panel mainMenu;		// The main menu screen.
		Tetris::Graphics::Label* title;			// The title of the game.
		PlayButton* play;						// The play button.
		DemoButton* demo;						// The demo button.
		QuitButton* quit;						// The quit button.

		Tetris::Graphics::Panel gameScreen;		// The game screen.
		Tetris::Graphics::InformationBox* info;	// The information display at the top of the game screen.
		Tetris::Graphics::Panel gameCanvas;		// The canvase to draw Tetris and the obstacles on.

		Tetris::Graphics::Widget* lastHover;	// The last widget the mouse hovered over.
		Tetris::Graphics::InformationBox::State state;	// The state of the game
		Tetris::Graphics::TetrisSprite* tetris;	// The main character.
		Tetris::Graphics::Wall* wall1;			// The first wall.
		Tetris::Graphics::Wall* wall2;			// The second wall
		Tetris::Graphics::Wall* wall3;			// The second wall
		Tetris::Graphics::Wall* front;			// The wall that is in front
		Tetris::Graphics::Wall* back;			// The wall that is at the very back

		int score;								// The player's score.

		/*
		* Initialises the game components.
		*/
		void initGame();
		/*
		* Display graphics.
		*/
		void display();
		/*
		* Resets the game.
		*/
		void reset();
		/*
		* AI decides whether the robot should use the jet or not.
		*/
		void demoMove();
	};
}

#endif