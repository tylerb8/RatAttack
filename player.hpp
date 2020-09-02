#pragma once // causes the current source file to be included only once in a single compilation.
#include "bullet.hpp"
#include <iostream>

class Player {
	private:
		// Should only have one copy of each type of player
		static unsigned players;
	
		// Different players? 
		unsigned playerNr;

		// Player Sprite
		Texture *texture;
		Sprite sprite;
		RectangleShape hitbox;

		// Players Damage
		int damage;		
		int damageMax;
		int damageTimer;	
		int damageTimerMax;	
		int shootTimer;
		int shootTimerMax;

		// control keys : Movement 
		int controls[5];

		// Players XP
		int level;
		int exp;
		int expNext;

		// Players Health
		int hp;
		int hpMax;

		// Score
		int score;

		// Bullets
		Texture *bulletTexture;
		std::vector<Bullet> bullets;

	public:
		// Parametrized Constructor : Creates Players with respective texture and control keys
			// sfml Enum Key : W(22), S(18), A(0), D(3), " "(57) , dont write keypressed::...
		Player(Texture *texture, Texture *bulletTexture, int UP = 22, 
		       int DOWN = 18, int LEFT = 0, int RIGHT = 3, int SHOOT = 57);
		// Virtual Destructor : used to clean up all class methods used in hierarchy (derived class -> Base class) 
		virtual ~Player();

		// *****Function Getters*****
		// Returns bullets
		inline std::vector<Bullet> &getBullets() {
			return this->bullets;
		}
		// Returns current position of the
		inline const Vector2f &getPosition() const {
			return this->sprite.getPosition();
		}
		// Return hp as a string (Used to display HP)
		inline const String getHPAsString() const {
			return std::to_string(this->hp) + "/" + std::to_string(this->hpMax);
		}
		// Returns a random damage amount 
		inline const int getDamage() const {
			return rand()%this->damageMax + this->damage;
		}
		// Returns the bounds of the player in the 2d coordinate system
		inline FloatRect getGlobalBounds() const {
			return this->sprite.getGlobalBounds();
		}
		// Returns the HP of the enemy
		inline const int &getHP() const {
			return this->hp;
		}
		// Returns the Max HP of the enemy
		inline const int &getHPMax() const {
			return this->hpMax;
		}
		// Updates the players hp as it takes damage
		inline void takeDamage(int damage) {
			this->hp -= damage;
		}
		// Check is enemy is still alive
		inline bool isAlive() const {
			return this->hp > 0;
		}
		// Returns the player number
		inline const int getplayerNr() const {
			return this->playerNr;
		}
		// Returns players level
		inline const int &getLevel() const {
			return this->level;
		}
		// Returns the players EXP
		inline const int &getExp() const {
			return this->exp;
		}
		// Returns xp increase
		inline const int &getExpNext() const {
			return this->expNext;
		}
		// Updates (Increases exp)
		inline void gainExp(int exp) {
			this->exp += exp;
			this->UpdateLeveling();
		}
		// Updates score
		inline void gainScore(int score) {
			this->score += score;
		}
		// Returns score
		inline const int getScore() const {
			return this->score;
		}


		// ***** Functions *****
		// Updates the players exp
		void UpdateLeveling();
		// Controls the movement of the player
		void Movement(Vector2u windowBounds);
		// Controls bullet timer and shooting bullet
		void Combat();
		// Updates the players movement
		void Update(Vector2u windowBounds);
		// Draws the players to screen given target(bullet)
		void Draw(RenderTarget &target);
		// Gains HP with Boost
		void gainHP(int hp);
};
