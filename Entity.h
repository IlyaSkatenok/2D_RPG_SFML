#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include "Sounding.h"
using namespace sf;

class Entity
{
protected:
    Texture texture;
    Sprite sprite;
    String filename;
public:
    Entity();
    Entity(const String file, int origin = 0);
    virtual ~Entity();

    Sprite& get_sprite();

};


class Move_Entity : public Entity
{
protected:
    int direction = 1; // Положение игрока ПЛНВ |ПН-ПВ-ЛВ-ЛН
    float x, y, w, h, dx, dy, speed = 0;
    bool is_freezed = false;

    int damage;
    int health;
    int experience;    // Сколько падает опыта с врага

public:
    Move_Entity(const String file, int origin,int X, int Y, int W, int H, int damage, int health,int experience);
    virtual ~Move_Entity();

    float get_x();
    float get_y();
    float get_w();
    float get_h();

    void set_x(float x);
    void set_y(float y);

    bool get_freeze();
    void set_freeze(bool state);

    int get_health();
    void set_health(int heal);

    int get_damage();
    void set_damage(int dmg);

    int get_experience();

    void show();



};
