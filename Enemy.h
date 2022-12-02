#pragma once
#include "Entity.h"

class Enemy : public Move_Entity
{
protected:
    Entity *logo;
    Sounding *attack;
public:
    Enemy(String file, int X, int Y, int W, int H, int damage, int health, float speed, int experience);
    virtual ~Enemy();
    void move_to_actor(float x, float y, float delta);
    Entity& get_logo();
    int attack_actor();

};

class Wolf : public Enemy
{
public:
    Wolf(int X, int Y);
    virtual ~Wolf();
};
