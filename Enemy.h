#pragma once
#include "Entity.h"
// ÄÂÈÃÀŞÙÀßÑß ÑÓÙÍÎÑÒÜ Ñ ËÎÃÎ È ÇÂÓÊÀÌÈ
class Enemy : public Move_Entity
{
protected:
    Entity *logo;
    Sounding *attack;
public:
    Enemy(String file, int X, int Y, int W, int H, int damage, int health, float speed, int experience);
    virtual ~Enemy();
    void move_to_actor(float x, float y, float delta, char material_walk);
    Entity& get_logo();
    int attack_actor(int actor_luck, int actor_agility);

};

class Knight_easy : public Enemy
{
public:
    Knight_easy(int X, int Y);
};

class Knight_medium : public Enemy
{
public:
    Knight_medium(int X, int Y);
};

class Knight_high : public Enemy
{
public:
    Knight_high(int X, int Y);
};

class Knight_high_2 : public Enemy
{
public:
    Knight_high_2(int X, int Y);
};

class Boss : public Enemy
{
public:
    Boss(int X, int Y);
};
