#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{
    public:
        Enemy();

        ///setters
        void setDamage(int damage){_damage = damage;}
        ///getters
        int getHealth(){return _health;}
        int getDamage(){return _damage;}

    private:
        int _health;
        int _damage;
};

#endif // ENEMY_H
