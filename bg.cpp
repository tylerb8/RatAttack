#include "bg.hpp"

BG::BG() {
	// Creates inGame Background
    this->texture1.loadFromFile("images/bg3.jpg");
    this->sprite1.setTexture(texture1);
	this->sprite1.scale(1.7,1.7);
}

// Destructor
BG::~BG() {
}

// Draws the Background to screen
void BG::draw(RenderWindow &window){
	window.draw(sprite1);
}
