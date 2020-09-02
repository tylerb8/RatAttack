#include "boost.hpp"

// Parametrized Constructor 
Boost::Boost(Texture *texture, Vector2f position, float duration) {
	// Creating HP Boost
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().height/2);
	this->sprite.setPosition(position);
	this->sprite.setScale(0.155f, 0.155f);

	// Max spawn time is given duration
	this->aliveTimerMax = duration;
	// Initalizing aliveTimer
	this->aliveTimer = 0;
}

// Destructor
Boost::~Boost() {

}
	
// Checks if player has intersected with HP boost
bool Boost::checkCollision(FloatRect rect) {
	// if this sprite intersects with rect(Player)
	if(this->sprite.getGlobalBounds().intersects(rect))
		return true; // Player has intersected
	else
		return false; // else Player has not intersected
}
		
// Updates spawn timers and HP rotation
void Boost::Update() {
	// If the spawn timer has not reached max increase by 1
	if(this->aliveTimer < this->aliveTimerMax)
		this->aliveTimer += 1.f;

	// Makes the HP Boost Spin :)
	this->sprite.rotate(5.f);
}

// Draws the HP Boost to screen given target(HP Boost)
void Boost::Draw(RenderTarget &target) {
	target.draw(this->sprite);
}
	
