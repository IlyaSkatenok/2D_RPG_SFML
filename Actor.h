#pragma once

#include "Entity.h"
#include <vector>
// ГЛАВНЫЙ ГЕРОЙ
class Actor: public Move_Entity
{
private:
    int luck, strength, agility, endurance; // Удача Сила Ловкость Выносливость
    int max_health;
    int max_experience;
    int level;
    int level_points;

    int bonus_damage;
    int bonus_health;

    View camera;    // КАМЕРА

    bool is_dead = false;
    bool is_bored = false;

    Sounding attack_left;
    Sounding attack_right;
    Sounding attack_crit;
    Sounding attack_miss;
    Sounding level_new;

    Sounding walk_road;
    Sounding walk_sand;
    Sounding walk_grass;
    Sounding walk_water;
    Sounding walk_water_echo;

    void update_health();
    void update_damage();

    void update_bored();

public:
    Actor(String file, int X, int Y, int W, int H);
    virtual ~Actor();

    void set_skills(int luck,int strength, int agility,int endurance);

    // сеттеры для скиллов
    void set_luck(int luck);
    void set_strength(int strength);
    void set_agility(int agility);
    void set_endurance(int endurance);
    // геттеры для скиллов
    int get_luck();
    int get_strength();
    int get_agility();
    int get_endurance();

    bool get_dead();

    int get_max_health();
    void set_health(int heal);
    void set_max_health(int heal);
    void add_health(int heal);

    void set_experience(int xp);
    int get_level();
    void set_level(int lvl);
    int get_level_points();
    int get_max_experience();
    void set_level_points(int points);

    int get_direction();

    void update_camera();
    View& get_camera();

    void set_dead(bool isdead);
    bool is_boring();

    void level_up();

    int get_bonus_damage();
    int get_bonus_health();
    void set_bonus_damage(int dmg);
    void set_bonus_health(int heal);


    void update(float delta);
    void update_back(float delta);
    int attack(bool left);


    void move(float delta, char material_walk);

};
