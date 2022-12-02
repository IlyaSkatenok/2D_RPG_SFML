#include "Enemy.h"
#include <cmath>

Sounding enemy_sounds[1]
{
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

void Enemy::move_to_actor(float x1, float y1, float delta)
{
    if (!is_freezed)
    {
        float distance = sqrt((x1 - this->x) * (x1 - this->x) + (y1 - this->y) * (y1 - this->y));
        float rotation = atan2(y1 - this->y, x1 - this->x) * 180 / 3.14159265;
        if (distance > 16 && distance < 520)
        {
            this->x += delta * speed * (x1 - this->x) / distance;
            this->y += delta * speed * (y1 - this->y) / distance;
            this->get_sprite().setRotation(rotation);
        }
    }
}

Entity& Enemy::get_logo()
{
    return *logo;
}

int Enemy::attack_actor()
{
    attack->play_sound();
    return damage + rand() % 5;
}
//-------------------------------------------------------------------------------------------------------------------------
Wolf::Wolf(int X, int Y):Enemy("./gamedata/textures/enemy/enemy1.png", X, Y,64,64, 10, 100,1.15, 30)
{
    this->logo = new Entity("./gamedata/textures/logos/enemy1_logo.png", 0);
    attack = &enemy_sounds[0];
}

Wolf::~Wolf()
{
    //dtor
}

//-------------------------------------------------------------------------------------------------------------------------
