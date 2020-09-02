#pragma once
#define SFML_NO_DEPRECATED_WARNINGS
#include "SFML/Graphics.hpp"
using namespace sf;

// 4 sections to instructions
#define MAX_NUMBER_OF_ITEMS_INST 4	

class Instruct {
	private:
		// Texture/Sprite for Background
		Texture itexture;
		Sprite isprite;
		
		// Font/ Text for instructions
		Font ifont;
		Text instruct[MAX_NUMBER_OF_ITEMS_INST];

	public:
		// Parametrized constructor : given window dimensions
		Instruct(int width, int height);
		// Virtual Destructor : used to clean up all class methods used in hierarchy (derived class -> Base class) 
		virtual ~Instruct();

		// ***** Functions *****
		// Draws the Background to screen
		void draw(RenderWindow &window);
};
