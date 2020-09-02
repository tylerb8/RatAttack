
#include "menu.hpp"

// Parametrized constructor : given window dimensions
Menu::Menu(int width, int height) {
	// Initalizes Font
	font.loadFromFile("fonts/Dosis-EBold.ttf");

	// Creates Background
    this->texture.loadFromFile("images/menuBG.jpg");
    this->sprite.setTexture(texture);

	// Initalizes PLAY 
	menu[0].setFont(font);
	menu[0].setColor(Color::Red);
	menu[0].setCharacterSize(40);
	menu[0].setString("Play");
	menu[0].setPosition(Vector2f(width / 2 - 125, height / (MAX_NUMBER_OF_ITEMS + 1) * 2 + 250));

	// Initalizes INSTRUCTIONS
	menu[1].setFont(font);
	menu[1].setColor(Color::White);
	menu[1].setCharacterSize(40);
	menu[1].setString("Instructions");
	menu[1].setPosition(Vector2f(width / 2 - 125, height / (MAX_NUMBER_OF_ITEMS + 1) * 3 + 150));

	// Initalizes EXIT
	menu[2].setFont(font);
	menu[2].setColor(Color::White);
	menu[2].setCharacterSize(40);
	menu[2].setString("Exit");
	menu[2].setPosition(Vector2f(width / 2 - 125, height / (MAX_NUMBER_OF_ITEMS + 1) * 4 + 50));

	// Initalizes "USE ARROW KEYS: "
	menu[3].setFont(font);
	menu[3].setColor(Color::White);
	menu[3].setCharacterSize(35);
	menu[3].setString("Use arrow keys:");
	menu[3].setPosition(Vector2f(width / 2 - 125, height / (MAX_NUMBER_OF_ITEMS + 1) * 1 + 350));

	// Selected Item is first at play
	selectedItemIndex = 0;
}

// Virtual Destructor : used to clean up all class methods used in hierarchy (derived class -> Base class) 
Menu::~Menu() {
}

// ***** Functions *****
// Draws the Background to screen
void Menu::draw(RenderWindow &window) {
	// Draws background
	window.draw(sprite);

	// Draws text
	for(size_t i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(menu[i]);
	}
}

// Controls moving up to prev selected item
void Menu::moveUp() {
	// Used to selected above text (cannot go up after PLAY)
	if(selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(Color::Red);
	}
}

// Controls moving down to next selected item
void Menu::moveDown() {
	// Used to selected below text (cannot go down after EXIT)
	if(selectedItemIndex + 1 < POSITION) {
		menu[selectedItemIndex].setColor(Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(Color::Red);
	}
}

