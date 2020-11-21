#include "Player.h"

Player::Player()
{
    _health = 200;
    _weapon = 0;
    _healthRank = 0;
    _armor = 0;
    _damage = 10;
    _NOEK = 0;
    _money = 5;
    _potions = 0;
}

void Player::IncMaxHealth(int value){_health += value;}

void Player::IncArmor(int value){_armor+=value;}

void Player::IncNOEK(){_NOEK++;}
