#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>

class Player
{
    public:
        Player();
        void IncMaxHealth(int value);
        void IncArmor(int value);
        void IncNOEK();

        ///setters
        void setDamage(int damage){_damage = damage;}
        void setMoney(int value){_money = value;}
        void setHealth(int value){_health = value;}
        void UpMoney(){_money++;}
        void UpWeapon(){_weapon++;}
        void UpArmor(){_armor++;}
        void UpHealth(){_healthRank++;}
        void UpdatePotions(int value){_potions += value;}
        void UpdateHealth(int value){if(_health + value <= 200 + (20 * _healthRank)) _health += value; else _health = 200 + (50*_healthRank);}

        ///getters
        int getHealth(){return _health;}
        int getMoney(){return _money;}
        int getHealthRank(){return _healthRank;}
        int getDamage(){return _damage;}
        int getWeapon(){return _weapon;}
        int getArmor(){return _armor;}
        int getPotions(){return _potions;}
        int getNOEK(){return _NOEK;}

    private:
        int _health;
        int _money;
        int _healthRank;
        int _damage;
        int _weapon;
        int _armor;
        int _potions;
        int _NOEK; ///Number of enemies killed;
};

#endif // PLAYER_H
