#include "Enemy.h"
#include <cmath>

Sounding step_sounds[] = {
    Sounding("./gamedata/sounds/actor/walk_grass"),
    Sounding("./gamedata/sounds/actor/walk_water"),
    Sounding("./gamedata/sounds/actor/walk_water_echo"),
    Sounding("./gamedata/sounds/actor/walk_road"),
    Sounding("./gamedata/sounds/actor/walk_sand"),
};


Sounding enemy_sounds[2]
{
    Sounding("./gamedata/sounds/enemy/attack_miss"),
    Sounding("./gamedata/sounds/enemy/attack"),
};

Enemy::Enemy(String file, int X, int Y, int W, int H, int damage, int health, float speed, int experience):Move_Entity(file, 1, X,Y,W,H, damage, health,experience)
{
    this->speed = speed;
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::move_to_actor(float x1, float y1, float delta, char material_walk)
{
    if (!is_freezed)
    {
        float distance = sqrt((x1 - this->x) * (x1 - this->x) + (y1 - this->y) * (y1 - this->y));
        float rotation = atan2(y1 - this->y, x1 - this->x) * 180 / 3.14159265;
        if (distance < 700)
        {
            this->get_sprite().setRotation(rotation);
        }
        if (distance > 16 && distance < 520)
        {
            this->x += delta * speed * (x1 - this->x) / distance;
            this->y += delta * speed * (y1 - this->y) / distance;

            switch(material_walk)
            {
            case '-':
                if(step_sounds[0].get_sound().getStatus() == Sound::Status::Stopped)
                {
                    step_sounds[0].play_sound();
                }
                break;
            case 'w':
                if(step_sounds[1].get_sound().getStatus() == Sound::Status::Stopped)
                {
                    step_sounds[1].play_sound();
                    step_sounds[2].play_sound();
                }
                break;
            case 'r':
                if(step_sounds[3].get_sound().getStatus() == Sound::Status::Stopped)
                {
                    step_sounds[3].play_sound();
                }
                break;
            case 's':
                if(step_sounds[4].get_sound().getStatus() == Sound::Status::Stopped)
                {
                    step_sounds[4].play_sound();
                }
                break;
            }
        }
    }
}

Entity& Enemy::get_logo()
{
    return *logo;
}

int Enemy::attack_actor(int actor_luck, int actor_agility)
{
    int temp_attack = damage + rand() % 5;
    if ((1.5 * actor_agility +  0.5 * actor_luck) > rand() % 60)
    {
        temp_attack = 0;
    }
    if (temp_attack)
    {
        attack->play_sound();
    }
    else
    {
        enemy_sounds[0].play_sound();
    }
    return temp_attack;
}
//-------------------------------------------------------------------------------------------------------------------------
Knight_easy::Knight_easy(int X, int Y):Enemy("./gamedata/textures/enemy/enemy1.png", X, Y,64,64, 17, 85,1.2, 17)
{
    this->logo = new Entity("./gamedata/textures/logos/enemy1_logo.png", 0);
    attack = &enemy_sounds[1];
}

Knight_medium::Knight_medium(int X, int Y):Enemy("./gamedata/textures/enemy/enemy2.png", X, Y,64,64, 24, 95,1.25, 24)
{
    this->logo = new Entity("./gamedata/textures/logos/enemy1_logo.png", 0);
    attack = &enemy_sounds[1];
}

Knight_high::Knight_high(int X, int Y):Enemy("./gamedata/textures/enemy/enemy3.png", X, Y,64,64, 32, 115,1.27, 32)
{
    this->logo = new Entity("./gamedata/textures/logos/enemy1_logo.png", 0);
    attack = &enemy_sounds[1];
}

Knight_high_2::Knight_high_2(int X, int Y):Enemy("./gamedata/textures/enemy/enemy4.png", X, Y,64,64, 35, 130,1.3, 35)
{
    this->logo = new Entity("./gamedata/textures/logos/enemy1_logo.png", 0);
    attack = &enemy_sounds[1];
}

Boss::Boss(int X, int Y):Enemy("./gamedata/textures/hero.png", X, Y,64,64, 50, 200,1.5, 45)
{
    this->logo = new Entity("./gamedata/textures/logos/enemy1_logo.png", 0);
    attack = &enemy_sounds[1];
}
//-------------------------------------------------------------------------------------------------------------------------
