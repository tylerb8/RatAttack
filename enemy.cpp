#include "enemy.hpp"
#include "config.hpp"

//Enumeration of player controls
enum eTypes {MOVELEFT = 0, FOLLOW, MOVELEFTSHOOT};

// Parametrized Constructor : Creates Enemy  
Enemy::Enemy(Texture *texture, Texture *eBulletTexture, Vector2u windowBounds, Vector2f position, Vector2f moveDirection, 
	     int type, int hpMax, int damageMax, int damageMin, int playerFollow) {

	// Creates Enemy
	this->texture = texture;
	this->eBulletTexture = eBulletTexture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(0.3f, 0.3f);
	this->sprite.setPosition(windowBounds.x, (rand()%windowBounds.y) - this->sprite.getGlobalBounds().height);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, this->sprite.getGlobalBounds().height/2);

	// Gets windowBounds
	this->windowBounds = windowBounds;

	// MOVELEFT = 0, FOLLOW = 1, or MOVELEFTSHOOT = 2
	this->type = type;

	// Set direction
	this->moveDirection = moveDirection;
	this->playerFollow = playerFollow;
	
	// Enemys HP
	this->hpMax = hpMax;
	this->hp = this->hpMax;

	// Enemys damage to player
	this->damageMax = damageMax;
	this->damageMin = damageMin;

	// Timer for damage
	this->damageTimerMax = 4.f;
	this->damageTimer = 0;

	// Timer for snot bullets
	this->shootTimerMax = ENEMY_BULLET_MAX;
	this->shootTimer = 0.f;
}

// Destructor
Enemy::~Enemy() {

}

// ***** Functions *****
// Enemy takes damage given set damage 
void Enemy::takeDamage(int damage) {
	// Updates damage given damage parameters
	this->hp -= damage;

	// if hp is less or equal to 0
	if(this->hp <= 0)
		//player is dead
		this->hp = 0;	
}

// Updates the Enemys movement 
void Enemy::Update(Vector2f playerPosition) {
	// Moves player depending on type of movement
	switch(this->type) {
		case MOVELEFT:
			// Moves the enemy left
			this->sprite.move(this->moveDirection.x * 3.f, this->moveDirection.y * 3.f);
			break;

		case FOLLOW:
			// If the Enemy is on the right of the player
			if(this->sprite.getPosition().x > playerPosition.x) {
				// get direction: Player vector - enemy vector
				this->moveDirection.x = playerPosition.x - this->sprite.getPosition().x;
				this->moveDirection.y = playerPosition.y - this->sprite.getPosition().y;
			}
			
			// Get direction with unit length of 1 (1 makes it easier to multiply)
			normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));

			// Enemy will follow until a certain point
			if(this->normalizedMoveDir.y > 0.7) 
				this->normalizedMoveDir.y = 0.7;
			else if(this->normalizedMoveDir.y < -0.7)
				this->normalizedMoveDir.y = -0.7;
			if(this->normalizedMoveDir.x > -1.5)
				this->normalizedMoveDir.x = -1.5;

			// Rotates the enemy accordingly to follow player 
				// atan(y/x) gets theta (angle of adj side to hypothenuse) 
				// * 180/PI to turn radians to degrees
				// 180/pi is half the circle (without would end up upside down) (adjust for orientation of enemy sprite)
			this->sprite.setRotation(atan2(this->normalizedMoveDir.y, this->normalizedMoveDir.x) * 180 / 3.1415926539 + 180);

			// Move the enemy towards player
			// Get direction and multiply speed
			this->sprite.move(this->normalizedMoveDir.x * 1.f, this->normalizedMoveDir.y * 1.f);
			break;

		case MOVELEFTSHOOT:
			// shooting timer updater
			if(shootTimer < this->shootTimerMax) 
				this->shootTimer += 1.f;

			// If the sprite is on the right of the player
			if(this->sprite.getPosition().x > playerPosition.x) {
				// get direction: Player vector - enemy vector
				lookDirection.x = playerPosition.x - this->sprite.getPosition().x;
				lookDirection.y = playerPosition.y - this->sprite.getPosition().y;
			}

			// Get LOOKING Direction with unit length of 1 (1 makes it easier to multiply)
			this->normalizedLookDir = normalize(this->lookDirection, vectorLength(this->lookDirection));
				
			// Enemy will follow until a certain point
			if(this->normalizedMoveDir.y > 0.7) 
				this->normalizedMoveDir.y = 0.7;
			else if(this->normalizedMoveDir.y < -0.7)
				this->normalizedMoveDir.y = -0.7;
			if(this->normalizedMoveDir.x > -1.5)
				this->normalizedMoveDir.x = -1.5;

			// Rotates the enemy accordingly to LOOK at player 
				// atan(y/x) gets theta (angle of adj side to hypothenuse) 
				// * 180/PI to turn radians to degrees
				// 180/pi is half the circle (without would end up upside down) (adjust for orientation of enemy sprite)
			this->sprite.setRotation(atan2(this->normalizedLookDir.y, this->normalizedLookDir.x) * 180 / 3.1415926539 + 180);

			// Moves the enemy Left
			this->sprite.move(this->moveDirection.x * 2.f, this->moveDirection.y * 2.f);

			// Get MOVE direction with unit length of 1 (1 makes it easier to multiply)
			this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(moveDirection));
			
			// Shoots snot bullet
			if(this->shootTimer >= this->shootTimerMax) {
				// RELEASE THE BULLET : bullet constructor called
					//Bullet(Texture *texture, Vector2f position, Vector2f scale, Vector2f direction, 
					//float initialVelocity, float maxVelocity, float acceleration);
				this->enemyBullets.push_back(Bullet(this->eBulletTexture,
				this->sprite.getPosition(),Vector2f(0.2f, 0.2f), normalizedLookDir, 2.f, 4.f, 0.2f));
				// Update shoot timer after each bullet that fires
				this->shootTimer = 0.f;
			}
			break;

		default:
			break;
	}
}

// Draws the Bullet to screen given target(Enemy)
void Enemy::Draw(RenderTarget &target) {
	target.draw(this->sprite);

	// Draws snot bullets
	for (size_t i = 0; i < this->enemyBullets.size(); i++) 
		this->enemyBullets[i].Draw(target);
}

