#include "Actor.h"
#include <iostream>

#define CONST_HEALTH 90

Actor::Actor(String file, int X, int Y, int W, int H):Move_Entity(file, 1, X,Y,W,H, 0,0,0)
{
    damage = 15;
    max_health = CONST_HEALTH;
    max_experience = 100;
    level = 1;
    level_points = 0;
    bonus_damage = 0;
    bonus_health = 0;

    attack_left.set_sound("./gamedata/sounds/actor/attack");
    attack_right.set_sound("./gamedata/sounds/actor/attack_2");
    attack_crit.set_sound("./gamedata/sounds/actor/attack_crit");
    attack_miss.set_sound("./gamedata/sounds/actor/attack_miss");
    level_new.set_sound("./gamedata/sounds/actor/level_up");

    walk_grass.set_sound("./gamedata/sounds/actor/walk_grass");
    walk_water.set_sound("./gamedata/sounds/actor/walk_water");
    walk_water_echo.set_sound("./gamedata/sounds/actor/walk_water_echo");
}

Actor::~Actor()
{

}

void Actor::set_skills(int luck, int strength, int agility, int endurance)
{
    srand(time(NULL));
    this->luck = luck;
    this->strength = strength;
    this->agility = agility;
    this->endurance = endurance;

    this->max_health = CONST_HEALTH + 5 * this->strength + 2 * this->endurance + bonus_health;
    this->health = this->max_health;
    this->damage = 15 + 3.15 * this->strength + bonus_damage;
    this->max_experience = 100;
    this->experience = 0;
    this->level = 1;
}

// яеррепш церрепш яйхккнб
void Actor::set_luck(int luck)
{
    this->luck = luck;
}
void Actor::set_strength(int strength)
{
    bool maxer = (health == max_health);
    this->strength = strength;
    this->max_health = CONST_HEALTH + 5 * this->strength + 2 * this->endurance + bonus_health;
    this->damage = 15 + 3.15 * this->strength + bonus_damage;

    if (maxer)
    {
        health = max_health;
    }
}
void Actor::set_agility(int agility)
{
    this->agility = agility;
}
void Actor::set_endurance(int endurance)
{
    bool maxer = (health == max_health);
    this->endurance = endurance;
    this->max_health = CONST_HEALTH + 5 * this->strength + 2 * this->endurance + bonus_health;

    if (maxer)
    {
        health = max_health;
    }
}

int Actor::get_luck()
{
    return luck;
}
int Actor::get_strength()
{
    return strength;
}
int Actor::get_agility()
{
    return agility;
}
int Actor::get_endurance()
{
    return endurance;
}

void Actor::set_dead(bool isdead)
{
    this->is_dead = isdead;
}

void Actor::set_level(int lvl)
{
    level = lvl;
    max_experience = max_experience + level * 20;
}

void Actor::set_health(int heal)
{
    if (heal > max_health)
    {
        health = max_health;
    }
    else
    {
        health = heal;
    }
}

void Actor::add_health(int heal)
{
    health += (heal + 1.5 * endurance);
    if (health > max_health)
    {
        health = max_health;
    }
}

void Actor::set_max_health(int heal)
{
    max_health = heal;
}

int Actor::get_bonus_damage()
{
    return bonus_damage;
}

int Actor::get_bonus_health()
{
    return bonus_health;
}

void Actor::set_bonus_damage(int dmg)
{
    bonus_damage = dmg;
    this->damage = 15 + 3.15 * this->strength + bonus_damage;

}

void Actor::set_bonus_health(int heal)
{
    bool maxer = (health == max_health);
    bonus_health = heal;
    this->max_health = CONST_HEALTH + 5 * this->strength + 2 * this->endurance + bonus_health;

    if (maxer)
    {
        health = max_health;
    }
}

void Actor::update_camera()
{
    float tmpx = this->x;
    float tmpy = this->y;
    if (tmpx < 800)
    {
        tmpx = 800;
    }
    if (tmpx > 2400)
    {
        tmpx = 2400;
    }
    if (tmpy < 470)
    {
        tmpy = 470;
    }
    if (tmpy > 2750)
    {
        tmpy = 2750;
    }
    camera.setCenter(tmpx, tmpy);
}

View& Actor::get_camera()
{
    return camera;
}

int Actor::get_max_health()
{
    return max_health;
}

int Actor::get_level()
{
    return level;
}

void Actor::set_level_points(int points)
{
    level_points = points;
}

int Actor::get_level_points()
{
    return level_points;
}

int Actor::get_max_experience()
{
    return max_experience;
}

int Actor::get_direction()
{
    return direction;
}

void Actor::set_experience(int xp)
{
    std::cout << "Get xp" << std::endl;
    this->experience = xp;
    this->level_up();
}

void Actor::level_up()
{
    if (experience >= max_experience)
    {
        std::cout << "Get lvl" << std::endl;
        experience -= max_experience;
        max_experience = max_experience + level * 20;
        level++;
        level_points++;
        level_new.play_sound();
    }
}


void Actor::update(float delta)
{
    switch(direction)
    {
    case 0: dx = speed; dy = 0;     // бопюбн
            this->get_sprite().setRotation(0);
        break;
    case 1: dx = -speed; dy = 0;    // бкебн
            this->get_sprite().setRotation(180);
        break;
    case 2: dx = 0; dy = speed;     // бмхг
            this->get_sprite().setRotation(90);
        break;
    case 3: dx = 0; dy = -speed;    // ббепу
            this->get_sprite().setRotation(-90);
        break;
    case 4:
        dx = speed; dy = speed;     // бопюбн бмхг
            this->get_sprite().setRotation(45);
        break;
    case 5:
        dx = speed; dy = -speed;    // бопюбн ббепу
            this->get_sprite().setRotation(-45);
        break;
    case 6:
        dx = -speed; dy = speed;    // бкебн бмхг
            this->get_sprite().setRotation(135);
        break;
    case 7:
        dx = -speed; dy = -speed;    // бкебн ббепу
            this->get_sprite().setRotation(-135);
        break;
    }

    this->x += dx * delta;
    this->y += dy * delta;
    speed = 0;  // вРНАШ НЯРЮМНБХКЯЪ ОНЯКЕ ЬЮЦЮ

    this->get_sprite().setPosition(x,y);

}

void Actor::update_back(float delta)
{
    this->x -= dx * delta;
    this->y -= dy * delta;

    this->get_sprite().setPosition(x,y);
}

void Actor::move(float delta, char material_walk)
{
    if (!is_freezed)
    {
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            this->direction = 1; this->speed = 1;
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            this->direction = 0; this->speed = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            this->direction = 3; this->speed = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            this->direction = 2; this->speed = 1;
        }
    // дбхфемхе он дхюцнмюкх
        if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
        {
            this->direction = 7; this->speed = 0.9;
        }

        if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S))
        {
            this->direction = 6; this->speed = 0.9;
        }

        if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W))
        {
            this->direction = 5; this->speed = 0.9;
        }

        if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
        {
            this->direction = 4; this->speed = 0.9;
        }
        if (speed)
        {
            switch(material_walk)
            {
            case 'b':
                if(walk_grass.get_sound().getStatus() == Sound::Status::Stopped)
                {
                    walk_grass.play_sound();
                }
                break;
            case '-':
                if(walk_water.get_sound().getStatus() == Sound::Status::Stopped)
                {
                    walk_water.play_sound();
                    walk_water_echo.play_sound();
                }
                break;
            }
        }
        this->update(delta);
    }
}

int Actor::attack(bool left)
{
    int attack_damage = 0;
    int miss_chance = 0;
    int attack_sound = 0;
    if (left)
    {
        attack_damage = damage + 1.45 * agility;
        miss_chance = 17 - 0.5 * luck - 1.5 * agility;
        attack_sound = 1;
    }
    else
    {
        attack_damage = 1.1 * damage + 1.5 * strength + 1.25 * endurance;
        miss_chance = 31 - 0.75 * luck - 1 * agility;
        attack_sound = 2;
    }

    if (miss_chance > (rand() % 100))
    {
        attack_damage = 0;
        attack_sound = 0;
    }
    if (luck > (rand() % 100) && attack_damage)
    {
        attack_damage += attack_damage / 3;
        attack_sound = 3;
    }

    switch(attack_sound)
    {
    case 0:
        attack_miss.play_sound();
        break;
    case 1:
        attack_left.play_sound();
        break;
    case 2:
        attack_right.play_sound();
        break;
    case 3:
        attack_crit.play_sound();
        break;
    }

    return attack_damage;
}
