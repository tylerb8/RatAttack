#include "player.hpp"
#include "config.hpp"

// initalize static member 
unsigned Player::players = 0;

// Enum of player controls
enum controls {UP = 0, DOWN, LEFT, RIGHT, SHOOT}; 

// Parametrized Constructor : Creates Players with respective texture and control keys
Player::Player(Texture *texture, Texture *bulletTexture,
			   int UP, int DOWN, int LEFT, int RIGHT, int SHOOT) 
	           :level(1), exp(0), expNext(0), hp(HP_CONFIG), hpMax(HP_MAX_CONFIG), damage(DAMAGE_CONFIG), damageMax(DAMAGE_MAX_CONFIG), score(0) {
		       // Initalizing players vriables (**Change depending on level**)

	// Player exp
	this->expNext = 20 + static_cast<int>((50 / 3)*((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12));

	// Player Sprite
	this->texture = texture;
	this->bulletTexture = bulletTexture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(0.4f, 0.4f);
	this->sprite.setOrigin(156.f, 103.f);
	this->sprite.setRotation(0.f);
	this->sprite.setPosition(150, 300);

	// Players Damage
	this->shootTimerMax = 25;
	this->shootTimer = this->shootTimerMax;
	this->damageTimer = 10;
	this->damageTimer = this->damageTimer;
	
	// Control keys: movement
	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;

	// Might delete (But adds numbers to players for multiple player use)
	this->playerNr = Player::players;
	Player::players++;
}

// Destructor
Player::~Player() {
}

// ***** Functions *****
// Updates the players exp
void Player::UpdateLeveling() {	
	// If not enough room for exp
	if(this->exp >= this->expNext) {
		// Increase level
		this->level++;
		// Remove current exp and add 
		this->exp -= this->expNext;
		// Add exp (stackoverflow)
		this->expNext = static_cast<int>((50 / 3)*((pow(level, 3) - 6 * pow(level, 2)) + 17 * level -12));
	}
}

// Controls the movement of the player
void Player::Movement(Vector2u windowBounds) {
	// Keypressed W : UP
	if(Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP]))) {
		// Windowbound check
		if(this->getPosition().y <= 50) 
			this->sprite.setPosition(this->sprite.getPosition().x, 50.f);
		// Else move up
		else 
			this->sprite.move(0.f, -5.f);
	}
	// Keypressed S : DOWN
	if(Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN]))) {
		// Windowbound check
		if(this->getPosition().y >= 660.f) 
			this->sprite.setPosition(this->sprite.getPosition().x, windowBounds.y -40.f);
		// Else move down
		else 
			this->sprite.move(0.f, 5.f);
	}
	// Keypressed A : LEFT
	if(Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT]))) {
		// Windowbound check
		if(this->getPosition().x  <= 50) 
			this->sprite.setPosition(50.f, this->sprite.getPosition().y);
		// Else move left
		else
			this->sprite.move(-5.f, 0.f);
	}
	// Keypressed D : RIGHT
	if(Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT]))) {
		// Windowbound check
		if(this->getPosition().x >= 960.f) 
			this->sprite.setPosition(windowBounds.x - 40.f, this->sprite.getPosition().y);
		// Else move right
		else 
			this->sprite.move(5.f, 0.f);
	}
}

// Controls bullet timer and shooting bullet
void Player::Combat() {
	// If key is pressed and within timer (Controls spam clicking)
	if(Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT])) && this->shootTimer >= shootTimerMax) {
		// RELEASE THE BULLET : bullet constructor called
		// Bullet(Texture *texture, Vector2f position, Vector2f scale, Vector2f direction, 
			       	// float initialVelocity, float maxVelocity, float acceleration);
		this->bullets.push_back(Bullet(bulletTexture,Vector2f(this->sprite.getPosition().x + 100.f , this->sprite.getPosition().y + 18.f), Vector2f(0.1f, 0.03f), Vector2f(1.f, 0.f), 
				5.f, 20.f, 2.f));
		// Reset timer
		this->shootTimer = 0;
	}
}

// Updates the players
void Player::Update(Vector2u windowBounds) {
	// Update timers
	if(this->shootTimer < this->shootTimerMax)
		this->shootTimer++;

	if(this-damageTimer < this-damageTimerMax)
		this->damageTimer++;

	// Updates movement
	this->Movement(windowBounds);
	// Checks bullet
	this->Combat();
}

// Gains HP with Boost
void Player::gainHP(int hp) {
	// Increase players HP
	this->hp += hp;
	// If hp is larger than max hp
	if(this->hp > this->hpMax)
		// Set hp to hp
		this->hp = this->hp;
	// update maxHp to new hp
	this->hpMax = this->hp;
}

// Draws the players to screen given target(bullet)
void Player::Draw(RenderTarget &target) {
	// Draws the player sprite
	target.draw(this->sprite);
	// Draws bullet 
	for(size_t i = 0; i < this->bullets.size(); i++) 
		this->bullets[i].Draw(target);
}	


