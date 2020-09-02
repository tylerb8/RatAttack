#pragma once // causes the current source file to be included only once in a single compilation.
#define SFML_NO_DEPRECATED_WARNINGS
#include "player.hpp"
#include "enemy.hpp"
#include "bg.hpp"
#include "boost.hpp"

class Game {
	private:
		// Access windows properties (main.cpp)
		RenderWindow *window;

		// Background
		BG bg;

		// Score
		int score;
		int gainScore;
		int loseScore;

		// Text
		Font font;
		Text followPlayerTexts;
		Text staticPlayerTexts;
		Text enemyText;
		Text gameOverText;
		Text scoreText;
		Text escapeText;
		
		// Creates exp bar
		RectangleShape playerExpBar;

		// Players
		std::vector<Player> players;
		int playersAlive;

		// Enemies
		std::vector<Enemy> enemies;
		std::vector<Enemy> enemiesSaved;
		int enemySpawnTimer;
		int enemySpawnTimerMax;

		// Boosts
		std::vector<Boost> boost;

		// Textures
		Texture playerTexture;
		Texture bulletTexture;
		Texture eBulletTexture;
		Texture enemyTexture;
		Texture enemyTexture2;
		Texture boostTexture;

	public:
		// Constructor
		Game(RenderWindow *window);
		// Virtual Destructor : used to clean up all class methods used in hierarchy (derived class -> Base class) 
		virtual ~Game();

		// *****Function Getters*****
		inline RenderWindow &getWindow() {
			return *this->window;
		}

		// ***** Functions *****
		// Initalizes Texts
		void initializeUI();
		// Draws Player HP health, and exp bar
		void UpdateUIPlayer(int index);
		// Draws enemy HP Health
		void UpdateUIEnemy(int index);
		// Draws interface
		void DrawUI();
		// Updates: Timers, enemies, players, bullets, collisions, window bounds
		void Update();
		// Draws everything else
		void Draw();
};
