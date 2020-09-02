#include "game.hpp"
#include "config.hpp"


// Constructor for initalization
Game::Game(RenderWindow *window) {
	this->window = window;

	// Limit the framerate to a maximum fixed frequency
	this->window->setFramerateLimit(60);

	// Initalizes Font
	this->font.loadFromFile("fonts/Dosis-EBold.ttf");

	// Initalizes Textures
	this->playerTexture.loadFromFile("images/shooter1.jpg");
	this->bulletTexture.loadFromFile("images/bullet1.jpg");
	this->eBulletTexture.loadFromFile("images/bullet.jpg");
	this->enemyTexture.loadFromFile("images/zombie2.jpg");
	this->enemyTexture2.loadFromFile("images/zombie1.jpg");
	this->boostTexture.loadFromFile("images/hpBoost.jpg");

	// Initalizes Player
	this->players.push_back(Player(&playerTexture, &bulletTexture));
	this->playersAlive = this->players.size();

	// Initalizes Enemies
	// DEBUG: texture, windowbounds, position, direction, scale, type, hpmax, damagemax and min, and the player
	Enemy e1(&enemyTexture, &this->eBulletTexture, this->window->getSize(), Vector2f(0.f, 0.f), 
	Vector2f(-1.f, 0.f), rand()%ENEMY_TYPE, rand()%ENEMY1_HEALTH + 1, ENEMY_DAMAGE_MAX, ENEMY_DAMAGE_MIN, 0);
	this->enemiesSaved.push_back(Enemy(e1));

	Enemy e2(&enemyTexture2, &this->eBulletTexture, this->window->getSize(), Vector2f(0.f, 0.f), 
	Vector2f(-1.f, 0.f), rand()%ENEMY_TYPE, rand()%ENEMY2_HEALTH + 1, ENEMY_DAMAGE_MAX, ENEMY_DAMAGE_MIN, 0);
	this->enemiesSaved.push_back(Enemy(e2));

	// Initalizes enemy timer
	this->enemySpawnTimerMax = ENEMY_SPAWN_RATE;		// Change enemy spawn rate
	this->enemySpawnTimer = this->enemySpawnTimerMax;

	// Player Score :
	this->score = 0;
	this->gainScore = GAIN_SCORE;
	this->loseScore = LOSE_SCORE;

	// Initalizes Texts
	this->initializeUI();
}

// Destructor
Game::~Game() {

}

// ***** Functions *****
// Initalizes Texts
void Game::initializeUI() {
	// Follow Text Initiation		
	this->followPlayerTexts.setFont(font);
	this->followPlayerTexts.setCharacterSize(14);
	this->followPlayerTexts.setColor(Color::White);

	// Static Text Initiation
	this->staticPlayerTexts.setFont(font);
	this->staticPlayerTexts.setCharacterSize(14);
	this->staticPlayerTexts.setColor(Color::White);

	// Player Xp Bar
	this->playerExpBar.setSize(Vector2f(15.f, 10.f));
	this->playerExpBar.setFillColor(Color(0.f, 128.f, 0.f));

	// Enemy Hp Text
	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(14);
	this->enemyText.setFillColor(Color::White);

	// Game Over Text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setStyle(Text::Bold);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setString("GAME OVER");
	this->gameOverText.setPosition(this->window->getSize().x/2 - 150.f, this->window->getSize().y/2 - 80.f);

	// Escape Text (Gameover)
	this->escapeText.setFont(this->font);
	this->escapeText.setFillColor(Color::White);
	this->escapeText.setCharacterSize(40);
	this->escapeText.setString("Press 'Escape' Button to Exit");
	this->escapeText.setPosition(this->window->getSize().x/2 - 230.f, this->window->getSize().y/2);

	// Score Text
	this->scoreText.setFont(this->font);
	this->scoreText.setFillColor(Color::White);
	this->scoreText.setCharacterSize(40);
	this->scoreText.setString("Score: 0");
	this->scoreText.setPosition(10.f, 10.f);
}

// Draws Player HP health, and exp bar
	// Index set to 0 unless add another palyer (Debating if gonna add feature)
void Game::UpdateUIPlayer(int index) {
	if(index >= this->players.size()) 
		std::cout << "DEBUG ERROR : UpdateUI";

	// Follow Text
	else {
		// *** Player Health Initalization ***
		// Set Position : Above Player
		this->followPlayerTexts.setPosition(this->players[index].getPosition().x - 40.f, 
											this->players[index].getPosition().y - 50.f);
		// HP   10/10
		this->followPlayerTexts.setString(" HP    " + this->players[index].getHPAsString() + "\n\n\n\n\n" + 
										  std::to_string(this->players[index].getLevel()));

		// *** Experience Bar Initalization ***
		// Set Position : Below Player
		this->playerExpBar.setPosition(this->players[index].getPosition().x - 25.f,
									   this->players[index].getPosition().y + 40);
		// Scale
		this->playerExpBar.setScale(static_cast<float>(this->players[index].getExp())/this->players[index].getExpNext(), 1.f);
	}
}

// Draws enemy HP Health
void Game::UpdateUIEnemy(int index) {
	// *** Enemy Health Initalization ***
	// Set Position : Above Enemy
	this->enemyText.setPosition(this->enemies[index].getPosition().x, 
					this->enemies[index].getPosition().y - this->enemies[index].getGlobalBounds().height/2);
	// HP	3/3
	this->enemyText.setString("HP    " + std::to_string(this->enemies[index].getHP()) + " / " + 
										 std::to_string(this->enemies[index].getHPMax()));
}

// Updates: Timers, enemies, players, bullets, collisions, window bounds
void Game::Update() {
	// If player is alive
	if(this->playersAlive > 0) {
		// Update Enemy Timers
		if(this->enemySpawnTimer < this->enemySpawnTimerMax)
			this->enemySpawnTimer++;

		// Spawn Enemies
		if(this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->enemies.push_back(Enemy(&enemyTexture, &this->eBulletTexture, this->window->getSize(), 
						Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), rand()%ENEMY_TYPE, rand()%ENEMY1_HEALTH + 1, ENEMY_DAMAGE_MAX, ENEMY_DAMAGE_MIN, 0));
			this->enemies.push_back(Enemy(&enemyTexture2, &this->eBulletTexture, this->window->getSize(), 
						Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), rand()%ENEMY_TYPE, rand()%ENEMY2_HEALTH + 1, ENEMY_DAMAGE_MAX, ENEMY_DAMAGE_MIN, 0));
			// Reset Enemy Spawn Timer
			this->enemySpawnTimer = 0;	
		}

		// *** All Player Settings (Players, Bullets, Collision, Damage) ***
		// For each player 
		for(size_t i = 0; i < this->players.size(); i++) { 
			// If player is alive
			if(this->players[i].isAlive()) {

				// Update Players (Shoot/damage timers, Movement, Combat)
				this->players[i].Update(this->window->getSize());

				// Bullet update (For each bullet)
				for(size_t k = 0; k < this->players[k].getBullets().size(); k++) {
					// Return a bullet and update its position (moving)
					this->players[i].getBullets()[k].Update();
	
					// Enemy collision check (For each Enemy)
					for(size_t j = 0; j < this->enemies.size(); j++) {
						// If bullet hits enemy
						if(this->players[i].getBullets()[k].getGlobalBounds().intersects(
						this->enemies[j].getGlobalBounds())) {
							// Erase the bullet
							this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);	
							
							// Enemy takes damage
							if(this->enemies[j].getHP() > 0) 
								this->enemies[j].takeDamage(this->players[i].getDamage());

							// Enemy died
							if(this->enemies[j].getHP() <= 0) {
								// Get Xp for killing Enemy
								this->players[i].gainExp(this->enemies[j].getHPMax() + 
								(rand()% this->enemies[j].getHPMax() + 1));

								// Get score for killing enemy
								this->score += gainScore;	
								this->scoreText.setString("Score: " + std::to_string(this->score));
								
								// Add boost chance
								int boostChance = rand() % 10;
									if(boostChance > HP_BOOST_CHANCE) 
										this->boost.push_back(Boost(&this->boostTexture, 
										this->enemies[j].getPosition(), HP_BOOST_DURATION));
								// Erase Enemy
								this->enemies.erase(this->enemies.begin() + j);
							}
						}
					}
					// window bounds check for off screen bullets
					if(this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x) {
						this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
						return;
					}	
				}
			}
		}

		//Update enemies (For each enemy)
		for(size_t i = 0; i < this->enemies.size(); i++) {
			// Update its position to players position
			this->enemies[i].Update(this->players[this->enemies[i].getPlayerFollow()].getPosition());

			// Enemy bullet update
			for(size_t k = 0; k < this->enemies[i].getBullets().size(); k++) {
				this->enemies[i].getBullets()[k].Update();
			}

			// For each player
			for(size_t k = 0; k < this->players.size(); k++) {
				// if Player is still alive
				if(this->players[k].isAlive()) {
					// Check if player touches Enemy
					if(this->players[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds())) {
						// If true player takes damage
						this->players[k].takeDamage(this->enemies[i].getDamage());
						// If player dies remove player
						if(!this->players[k].isAlive())
							this->playersAlive--;
						// Erase enemy if hits player
						this->enemies.erase(this->enemies.begin() + i);
						return;
					}
				}
			}
			// window bounds check for Enemy
			if(this->enemies[i].getPosition().x < 0 -this->enemies[i].getGlobalBounds().width) {
				// Lose score for enemy passing
				this->score -= loseScore;	
				this->scoreText.setString("Score: " + std::to_string(this->score));

				// Erase enemies
				this->enemies.erase(this->enemies.begin() + i);
				return;
			}

			// Health Boosts (for each HP boost)
			for(size_t i = 0; i < this->boost.size(); i++) {
				// Update timers and spin boost
				this->boost[i].Update();

				// For each Player
				for(size_t k = 0; k < this->players.size(); k++) {
					// If player intersects with boost
					if(this->boost[i].checkCollision(this->players[k].getGlobalBounds()))  {
						// Increase player HP by 2
						this->players[k].gainHP(HP_BOOST_GAIN);
						// Erase HP Boost that was collied with
						this->boost.erase(this->boost.begin() + i);
					}
				}
				// If boost has exceeded time limit
				if(this->boost[i].canDelete()) {
					// Erase HP boost
					this->boost.erase(this->boost.begin() + i);
					break;
				}
			}
		}
	}

	// Enemy Bullet Update
	for(size_t i = 0; i < this->enemies[i].getBullets().size(); i++) {
		// Updates enemy bullet movement
		this->enemies[i].getBullets()[i].Update();

		// Player collision check
		for (size_t k = 0; k < this->players.size(); k++) {
			// While that player is still alive
			if(this->players[k].isAlive()) {
				// If the enemy bullet intersects with player 
				if(this->enemies[i].getBullets()[i].getGlobalBounds().intersects(
				this->players[k].getGlobalBounds())) {

					// Erase the bullet
					this->enemies[i].getBullets().erase(this->enemies[i].getBullets().begin() + i);	

					// Player takes damage
					this->players[k].takeDamage(this->enemies[i].getDamage());

					// If player dies remove player
					if(!this->players[k].isAlive()) {
						//this->players.erase(this->players.begin() + k);
						this->playersAlive--;
						return;
					}
				}
			}
		}
		// Window Bound Check for Enemy Bullets
		if(this->enemies[i].getBullets()[i].getPosition().x > this->window->getSize().x ||
		this->enemies[i].getBullets()[i].getPosition().x < 100 ||
		this->enemies[i].getBullets()[i].getPosition().y > this->window->getSize().y ||
		this->enemies[i].getBullets()[i].getPosition().y < 100) {
			// Erase if past window bounds
			this->enemies[i].getBullets().erase(this->enemies[i].getBullets().begin() + i);	
			return;
		}
	}
}

// Draws interface
void Game::DrawUI() {
	// If player died and GAMEOVER
	if(this->playersAlive <= 0) {
		// game over Text
		this->window->draw(this->gameOverText);
		// Escape to exit text
		this->window->draw(this->escapeText);
	}
	// Update score
	this->window->draw(this->scoreText);
}

// Draws everything else
void Game::Draw() {
	// Clear window
	this->window->clear();

	// Draw the background
	this->bg.draw(*this->window);

	// For each enemy
	for(size_t i = 0; i < this->enemies.size(); i++) {
		// Draw the enemy
		this->enemies[i].Draw(*this->window);
		// Draw Enemy Texts 
		this->UpdateUIEnemy(i);
		this->window->draw(this->enemyText);
	}

	// For each player
	for(size_t i = 0; i < this->players.size(); i++) {
		// If player is still alive
		if(this->players[i].isAlive()) {
			// Draw the player
			this->players[i].Draw(*this->window);
			// Draw Player Texts
			this->UpdateUIPlayer(i);
			this->window->draw(this->followPlayerTexts);
			this->window->draw(this->playerExpBar);
		}
	}

	// Draw boosts
	for(size_t i = 0; i < this->boost.size(); i++) {
		this->boost[i].Draw(*this->window);
	}

	// Updates to check for End of Game interface
	this->DrawUI();
	// End the current frame and display its contents on screen
	this->window->display();
}