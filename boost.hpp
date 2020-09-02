#pragma once // causes the current source file to be included only once in a single compilation.
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

class Boost{
	private:
		// Texture/Sprite for HP boost
		Texture *texture;
	 	Sprite sprite;

		// Used to set spawn duration for HP boost
		float aliveTimerMax;
		float aliveTimer;

	public:
		// Parametrized Constructor - Given: texture, position, and spawn duration
		Boost(Texture *texture, Vector2f position, float duration);
		// Virtual Destructor : used to clean up all class methods used in hierarchy (derived class -> Base class) 
		virtual ~Boost();
	
		// ***** Functions *****
		// Determines if spawn time limit has been reached 
		inline const bool canDelete() const {
			return this->aliveTimer >= this->aliveTimerMax;
		}
		// Checks if player has intersected with HP boost
		bool checkCollision(FloatRect rect);
		// Updates spawn timers and HP rotation
		void Update();
		// Draws the HP Boost to screen given target(HP Boost)
		void Draw(RenderTarget &target);
};
