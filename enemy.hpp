#pragma once // causes the current source file to be included only once in a single compilation.
#include "bullet.hpp"

class Enemy {
	private:
		// Texture/Sprite for enemys
		Texture *texture;
		Sprite sprite;
	
		// get windowbounds as a unsinged vector
		Vector2u windowBounds;

		// get direction of enemy as a float vector
		Vector2f moveDirection;
		Vector2f normalizedMoveDir;

		// get direction of enemy as a float vector
		Vector2f lookDirection;
		Vector2f normalizedLookDir;

		// MOVELEFT = 0, FOLLOW = 1, or FOLLOWLEFTSHOOT = 2
		int type;

		// Enemys HP
		int hp;
		int hpMax;
		
		// Enemys damage to self
		int damageMin;
		int damageMax;

		// Timer for damage
		float damageTimerMax;
		float damageTimer;

		// Enemy Snot bullets
		Texture *eBulletTexture;
		std::vector<Bullet> enemyBullets;

		// Timer for snot bullets
		float shootTimerMax;
		float shootTimer;

		// Enemy follow player, keep track of player
		int playerFollow;

	public:
		// Parametrized Constructor : Creates Enemy given 
			// - texture, windowbounds, position, direction,type, hpmax, damagemin and max, and the player
		Enemy(Texture *texture, Texture *eBulletTexture, Vector2u windowBounds, Vector2f position, Vector2f direction, 
		int type, int hpMax, int damageMax, int damageMin, int playerFollow);
		// Virtual Destructor : used to clean up all class methods used in hierarchy (derived class -> Base class) 
		virtual ~Enemy();

		// ***** Functions Getters *****
		// Returns a random damage amount 
		inline const int getDamage() const {
			return rand() % this->damageMax + this->damageMin; 
		}
		// Returns the HP of the enemy
		inline const int getHP() const {
			return this->hp;
		}
		// Returns the Max HP of the enemy
		inline const int getHPMax() const {
			return this->hpMax;
		}
		// Check is enemy is dead
		inline const bool isDead() const {
			return this->hp <= 0;
		}
		// Returns the bounds of the enemy in the 2d coordinate system 
		inline const FloatRect getGlobalBounds() const {
			return this->sprite.getGlobalBounds();
		}
		// Returns current position of the enemy
		inline const Vector2f getPosition() const {
			return this->sprite.getPosition();
		}
		// Returns which player to follow
		inline const int getPlayerFollow() const {
			return this->playerFollow;
		}
		// Returns enemys snot bullets
		inline std::vector<Bullet> &getBullets() {
			return this->enemyBullets;
		}

		// ***** Functions *****
		// Enemy takes damage given set damage 
		void takeDamage(int damage);
		// Updates the Enemys movement 
		void Update(Vector2f playerPosition);
		// Draws the Bullet to screen given target(Enemy)
		void Draw(RenderTarget &target);

		// TYPE : FOLLOW
		// Finding a straight path from one sprite to another given two vectors (Hypothenuse)
		float vectorLength(Vector2f side) {
			return sqrt(pow(side.x, 2) + pow(side.y, 2));
		}
		// Makes sure that the vector length is pointing in same direction from enemy to player
			// Get direction with unit length of 1 
		Vector2f normalize(Vector2f side, float length) {
			return side/length;
		} 

};

