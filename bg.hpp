#pragma once // causes the current source file to be included only once in a single compilation.
#include <SFML/Graphics.hpp>
using namespace sf;

class BG {
	private:
		// Texture/Sprite for inGame Background 
		Texture texture1;
		Sprite sprite1;
		
	public:
		// Constructor
		BG();
		// Virtual Destructor : used to clean up all class methods used in hierarchy (derived class -> Base class) 
		virtual ~BG();
	
		// ***** Functions *****
		// Draws the Background to screen
    	void draw(RenderWindow &window);
};

