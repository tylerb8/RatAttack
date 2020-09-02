#include "bullet.hpp"
		
// Parametrized Constructor : Creates bullet with given speed
Bullet::Bullet(Texture *texture, Vector2f position, Vector2f scale, Vector2f direction, float initialVelocity, float maxVelocity, float acceleration) {
	// Create Bullet
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->maxVelocity = 15.f;
	this->acceleration = acceleration;
	this->sprite.setPosition(position);
	this->sprite.setScale(scale);
	
	// Set bullet speed
	this->maxVelocity = maxVelocity;
	this->currentVelocity = Vector2f(initialVelocity * this->direction.x, initialVelocity * this->direction.y);

	// Set bullet direction
	this->direction = direction;

	// Set Origin
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().height/2);

	// Set rotation
	this->sprite.setRotation(atan2(this->direction.y, this->direction.y) * 180 / 3.14159265359 + 180);
}

// Destructor
Bullet::~Bullet() {
}

// ***** Functions *****
// Controls the movement of the bullet
void Bullet::Movement() {
	// Rat Snot bullet
	if(this->acceleration > 0.f) {
		if(this->currentVelocity.x < this->maxVelocity && this->direction.x > 0.f ||
		this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0.f)
			this->currentVelocity.x += this->acceleration * this->direction.x;

		if(this->currentVelocity.y < this->maxVelocity && this->direction.y > 0.f ||
		this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0.f)
			this->currentVelocity.y += this->acceleration * this->direction.y;
	}
	// Player bullet
	else {
		this->currentVelocity = Vector2f(this->maxVelocity * this->direction.x, this->maxVelocity * this->direction.y);
	}
		    
	// Moves the bullet based on above set vector currentVelocity
	this->sprite.move(this->currentVelocity);
}

// Updates the bullets Movement
void Bullet::Update() {
	this->Movement();
}

// Draws the Bullet to screen
void Bullet::Draw(RenderTarget &target) {
	target.draw(this->sprite);
}	


