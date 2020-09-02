#pragma once
#define SFML_NO_DEPRECATED_WARNINGS
#include "SFML/Graphics.hpp"
using namespace sf;

// 4 Total sections
#define MAX_NUMBER_OF_ITEMS 4
// Only want 3 to be cycled through
#define POSITION 3

class Menu {
	private:
		// Texture/Sprite for Background
		Texture texture;
		Sprite sprite;

		// Font/Text
		Font font;
		Text menu[MAX_NUMBER_OF_ITEMS];

		// Play, Instructions, Exit
		int selectedItemIndex;

	public:
		// Parametrized constructor : given window dimensions
		Menu(int width, int height);
		// Virtual Destructor : used to clean up all class methods used in hierarchy (derived class -> Base class) 
		virtual ~Menu();

		// ***** Functions *****
		// Draws the Background to screen
		void draw(RenderWindow &window);
		// Controls moving up to prev selected item
		void moveUp();
		// Controls moving down to next selected item
		void moveDown();
		// Opens selected item
		int GetPressedItem() {
			return selectedItemIndex;
		}

};
