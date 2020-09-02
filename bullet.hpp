#pragma once // causes the current source file to be included only once in a single compilation.
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
using namespace sf;

class Bullet {
	private:
		// Texture/Sprite for Bullet
		Texture *texture;
	 	Sprite sprite;

		// Gets bullet direction to change rotation when shooting (mainly used for Enemy Snot Bullets)
		Vector2f direction;

		// ** Speed of bullet when shot **
		Vector2f currentVelocity; // current speed
		float  maxVelocity;	// Max speed
		float acceleration; // gain speed
		float initialVelocity; // starting speed

	public:
		// Parametrized Constructor : Creates bullet
		Bullet(Texture *texture, Vector2f position, Vector2f scale, Vector2f direction, 
				float initialVelocity, float maxVelocity, float acceleration);
		// Virtual Destructor : used to clean up all class methods used in hierarchy (derived class -> Base class) 
		virtual ~Bullet();

		// ***** Functions Getters *****
		// Returns the bounds of the bullet in the 2d coordinate system 
		inline const FloatRect getGlobalBounds() const {
			return this->sprite.getGlobalBounds();
		}
		// Returns current position of the bullet
		inline const Vector2f getPosition() const {
			return this->sprite.getPosition();
		}

		// ***** Functions *****
		// Controls the movement of the bullet
		void Movement();
		// Updates the bullet movement 
		void Update();
		// Draws the Bullet to screen given target(bullet)
		void Draw(RenderTarget &target);

};
