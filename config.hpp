#include <iostream>

// ****** Player.cpp ******
// Players HP
#define HP_CONFIG 10     
// Players Max HP
#define HP_MAX_CONFIG 10
// Players damage
#define DAMAGE_CONFIG 1
// Players Max Damage
#define DAMAGE_MAX_CONFIG 3


// ****** game.cpp ******
// Enemy spawn rate (lower = faster)
#define ENEMY_SPAWN_RATE 300
// Type of enemy + 1 (MOVELEFT = 0, FOLLOW = 1, or FOLLOWLEFTSHOOT = 2)
#define ENEMY_TYPE 3
// Enemy 1 Health (Big rats)
#define ENEMY1_HEALTH 5
// Enemy 2 Health (Small rats)
#define ENEMY2_HEALTH 3
// Enemy damage min
#define ENEMY_DAMAGE_MIN 1
// Enemy damage max
#define ENEMY_DAMAGE_MAX 2

// Player Score gain for killing Enemy
#define GAIN_SCORE 5
// Player score loss for passing Enemy
#define LOSE_SCORE 2

// HP boost chance (/10)
#define HP_BOOST_CHANCE 7 
// HP spawn time (Duration)
#define HP_BOOST_DURATION 700.f
// Player HP gain from HP boost
#define HP_BOOST_GAIN 2


// ****** enemy.cpp ******
// Enemy Snot bullet Max timer
#define ENEMY_BULLET_MAX 100.f