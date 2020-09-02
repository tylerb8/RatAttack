 
#include "instruct.hpp"

// Parametrized constructor : given window dimensions
Instruct::Instruct(int width, int height) {
	// Initalizes Font
	ifont.loadFromFile("fonts/Dosis-Light.ttf");

	// Creates Background
    this->itexture.loadFromFile("images/black.jpg");
    this->isprite.setTexture(itexture);

	// Initalizes Texts
	instruct[0].setFont(ifont);
	instruct[0].setColor(Color::White);
	instruct[0].setCharacterSize(50);
	instruct[0].setString("INSTRUCTIONS");
	instruct[0].setPosition(Vector2f(width / 2 - 150, 50));

	instruct[1].setFont(ifont);
	instruct[1].setColor(Color::White);
	instruct[1].setCharacterSize(20);
	instruct[1].setString("W - Up \nA - Left \nS - Down \nD - Right \nSpaceBar - Shoot \n\nYou can exit the game anytime with the 'Escape' Button\n\n\n");
	instruct[1].setPosition(Vector2f(100, 100));

	instruct[2].setFont(ifont);
	instruct[2].setColor(Color::White);
	instruct[2].setCharacterSize(20);
	instruct[2].setString("Goal: \nGet the highest score in the game!!! (ps. Dont let the rats touch or pass you)\n \nRats will deal up to 3 hp point per hit. \nBullets will deal up to 3 HP points damage per hit to enemies. \n\nEnemies killed will gain you 5 points to your score. \nEnemies that get to the other end will cause you to lose 2 points to your score\n\n\nThere is a 30 percent chance for a health drop that incrases HP by 2 points.");
	instruct[2].setPosition(Vector2f(100, 300));

	instruct[3].setFont(ifont);
	instruct[3].setColor(Color::Red);
	instruct[3].setCharacterSize(40);
	instruct[3].setString("PLAY (Hit return)");
	instruct[3].setPosition(Vector2f(width / 2 - 150, 650));
}

// Virtual Destructor : used to clean up all class methods used in hierarchy (derived class -> Base class)
Instruct::~Instruct() {
}

// ***** Functions *****
// Draws the Background to screen
void Instruct::draw(RenderWindow &window) {
	// Clears window
	window.clear();
	// Draws background
	window.draw(isprite);

	// Draws the Texts
	for(size_t i = 0; i < MAX_NUMBER_OF_ITEMS_INST; i++) {
		window.draw(instruct[i]);
	}
}

