// graphics.h contains the class declarations for displayable objects

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <stdlib.h>
#include <string>
#include <allegro5/allegro_font.h>
#include "utils.h"

namespace Tetris {
	namespace Graphics {
		/*
		* Used for representing the bounds of objects.
		*/
		class Rectangle {
		public:
			/*
			* Creates a new rectangle with the given bounds.
			*/
			Rectangle(float x, float y, float width, float height);
			/*
			* Gets the x coordinate of the rectangle.
			*/
			float getX();
			/*
			* Sets the x coordinate of the rectangle.
			*/
			void setX(float x);
			/*
			* Gets the x coordinate of the rectangle.
			*/
			float getY();
			/*
			* Sets the y coordinate of the rectangle.
			*/
			void setY(float y);
			/*
			* Gets the width of the rectangle.
			*/
			float getWidth();
			/*
			* Sets the width of the rectangle.
			*/
			void setWidth(float width);
			/*
			* Gets the height of the rectangle.
			*/
			float getHeight();
			/*
			* Sets the height of the rectangle.
			*/
			void setHeight(float height);
			/*
			* Sets the bounds of the rectangle.
			*/
			void setBounds(float x, float y, float width, float height);
			/*
			* Determines whether two rectangles intersect or not.
			*/
			bool intersects(Rectangle rect);
		private:
			float x;
			float y;
			float width;
			float height;
		};

		/*
		* The base class for all objects that can be displayed on the screen.
		*/
		class Displayable {
		public:
			/*
			* Initialises the bounding rectangle.
			*/
			Displayable() : bounds(Rectangle(0, 0, 0, 0)) {}
			/*
			* Gets the bounding rectangle of the displayable object.
			*/
			Rectangle getBounds();
			/*
			* Sets the position to be drawn to.
			*/
			void setPosition(float x, float y);
			/*
			* Sets the bounding rectangle of the displayable object.
			*/
			void setBounds(Rectangle bounds);
			/*
			* Draws the displayable object to the screen.
			*/
			virtual void draw() = 0;
		private:
			Rectangle bounds;			// The bounds of the displayable object.
		};

		/*
		* Represents a user interface component.
		*/
		class Widget : public Displayable {
		public:
			/*
			* Draws the displayable object to the screen.
			*/
			virtual void draw() = 0;
			/*
			* Called when the mouse is hovering over the widget.
			*/
			virtual Widget* onMouseOver(Rectangle mouse) = 0;
			/*
			* Called when the mouse moves out of this component.
			*/
			virtual void onMouseOut() = 0;
			/*
			* Called when the mouse clicks the widget.
			*/
			virtual void onMouseClick(Rectangle mouse) = 0;
		};

		/*
		* Widget that can contain other widgets.
		*/
		class Panel : public Widget {
		public:
			/*
			* Creates a new panel.
			*/
			Panel() {}
			/*
			* Adds the widget to this panel.
			*/
			void addWidget(Widget *widget);
			/*
			* Draws the panel by drawing all its children widgets.
			*/
			void draw();
			/*
			* Called when the mouse is hovering over the widget.
			*/
			Widget* onMouseOver(Rectangle mouse);
			/*
			* Do nothing on mouse click.
			*/
			void onMouseClick(Rectangle mouse);
			/*
			* Called when the mouse moves out of this component.
			*/
			void onMouseOut();
		private:
			std::vector<Widget*> widgets;			// The widgets on the panel.
		};

		/*
		* A label of text.
		*/
		class Label : public Widget {
		public:
			/*
			* Creates a new label with the given text and font.
			*/
			Label(std::string l, ALLEGRO_FONT* f);
			/*
			* Changes the text of the label.
			*/
			void setText(std::string label);
			/*
			* Sets the colour of the label.
			*/
			void setColour(ALLEGRO_COLOR colour);
			/*
			* Do nothing on mouse over.
			*/
			Widget* onMouseOver(Rectangle mouse) { return nullptr; }
			/*
			* Do nothing on mouse click.
			*/
			void onMouseClick(Rectangle mouse) {}
			/*
			* Do nothing on mouse out.
			*/
			void onMouseOut() {}
			/*
			* Draws the text.
			*/
			void draw();
		protected:
			std::string label;			// The label's text.
			ALLEGRO_FONT* font;			// The font to be used.
			ALLEGRO_COLOR colour;		// The colour for the text.
		};

		/*
		* Button that can be pressed.
		*/
		class Button : public Label {
		public:
			/*
			* Creates a new button woth the given text and font
			*/
			Button(std::string l, ALLEGRO_FONT* f);
			/*
			* Change background colour.
			*/
			Widget* onMouseOver(Rectangle mouse);
			/*
			* Do nothing on mouse click.
			*/
			void onMouseClick(Rectangle mouse) { onClick(); }
			/*
			* Change background colour.
			*/
			void onMouseOut();
			/*
			* To be overridden to perform button click action.
			*/
			virtual void onClick() {}
			/*
			* Draws the text.
			*/
			void draw();
		private:
			ALLEGRO_COLOR normalBack;		// The colour for the text.
			ALLEGRO_COLOR hoverBack;		// The colour for the text.
			bool hover;						// Whether the mouse is hovering over it or not.
		};

		/*
		* The box which keeps the scorecard and instructions.
		*/
		class InformationBox : public Widget {
		public:
			enum State{ ACTIVE, PAUSED, OVER, DEMO };
			/*
			* Creates a new Information Box.
			*/
			InformationBox(float width, float height, ALLEGRO_FONT* font);
			/*
			* Updates the score to be displayed.
			*/
			void updateScore(int score);
			/*
			* Sets the state of the game. A different instruction message will be displayed depending on whether the game
			* is paused or not.
			*/
			void setState(State state);
			/*
			* Draws the InformationBox.
			*/
			void draw();
			/*
			* Do nothing.
			*/
			Widget* onMouseOver(Rectangle mouse) { return nullptr; }
			/*
			* Do nothing.
			*/
			void onMouseClick(Rectangle mouse) {}
			/*
			* Do nothing.
			*/
			void onMouseOut() {}
		private:
			ALLEGRO_FONT* font;			// The font to use when drawing the text.
			ALLEGRO_COLOR white;		// White
			ALLEGRO_COLOR black;		// Black
			int score;					// The score to be displayed
			State state;				// Whether the game is paused.
		};

		/*
		* Represents an object to be moved around the screen.
		*/
		class Sprite : public Widget {
		public:
			/*
			* Creates a new sprite with the given image.
			*/
			Sprite(ALLEGRO_BITMAP* image);
			/*
			* Called when the mouse is hovering over the widget.
			*/
			Widget* onMouseOver(Rectangle mouse) { return nullptr; }
			/*
			* Called when the mouse moves out of this component.
			*/
			void onMouseOut() {}
			/*
			* Called when the mouse clicks the widget.
			*/
			void onMouseClick(Rectangle mouse) {}
			/*
			* Sets the velocity of the sprite.
			*/
			void setVelocity(float dx, float dy);
			/*
			* Gets the horizontal velocity.
			*/
			float getVelocityX();
			/*
			* Sets the horizontal velocity.
			*/
			void setVelocityX(float dx);
			/*
			* Gets the vertical velocity.
			*/
			float getVelocityY();
			/*
			* Sets the vertical velocity.
			*/
			void setVelocityY(float dy);
			/*
			* Updates the position of the sprite based on its velocity and time elapsed.
			*/
			void update(float delta);
			/*
			* Sets the image of the sprite.
			*/
			void setImage(ALLEGRO_BITMAP* image);
			/*
			* Draws the sprite to the screen.
			*/
			void draw();
		protected:
			float dx = 0;					// The horizontal velocity
			float dy = 0;					// The vertical velocity
			ALLEGRO_BITMAP* image;			// The sprite's image
		};

		/*
		* Represents the Tetris character.
		*/
		class TetrisSprite : public Sprite {
		public:
			/*
			* Creates the Tetris sprite.
			*/
			TetrisSprite(ALLEGRO_BITMAP *j) : Sprite(j) {}
			/*
			* Updates JetMan's velocity by applying gravity.
			*/
			void update(float delta);
		private:
			const float gravity = 90;			// gravity value - tweak for preferrence
		};

		/*
		* Represents the wall sprite.
		*/
		class Wall : public Sprite {
		public:
			/*
			* Creates a new wall sprite.
			*/
			Wall(ALLEGRO_BITMAP* w, int gapPosition);
			/*
			* Frees allocated memory.
			*/
			~Wall();
			/*
			* Updates the wall and each wall segments bounds.
			*/
			void update(float delta);
			/*
			* Randomly chooses the position of the hole.
			*/
			void updateGap();
			/*
			* Checks whether the rectangle collides with the wall.
			*/
			bool collides(Rectangle rect);
			/*
			* Draws the wall with the gap.
			*/
			void draw();
			/*
			* Need to update the wall bounds when the position is changed.
			*/
			void setPosition(float x, float y);
			/*
			* The position of the gap.
			*/
			int Tetris::Graphics::Wall::getGapPosition();
		private:
			/*
			* blocks 1-3 from the top can be a gap.
			*/
			int gapPosition;
			/*
			* The rectangles represeting the walls.
			*/
			Rectangle* walls[4];
			/*
			* Updates the bounds of the wall rectangles.
			*/
			void updateWalls();
		};
	}
}

#endif