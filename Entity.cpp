#include "Entity.h"


Entity::Entity() {}

Entity::Entity(const String file, int origin)
{
    filename = file;
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    if (origin)
    {
        sprite.setOrigin((Vector2f)texture.getSize() / 2.f);
    }
}

Entity::~Entity()
{

}

Sprite& Entity::get_sprite()
{
    return sprite;
}
//--------------------------------------
Move_Entity::Move_Entity(const String file, int origin,int X, int Y, int W, int H, int damage, int health, int experience) : Entity(file, origin)
{
    this->x = X;
    this->y = Y;
    this->w = W;
    this->h = H;
    this->damage = damage;
    this->health = health;
    this->experience = experience;
}

//--------------------------------------
float Move_Entity::get_x()
{
    return x;
}
float Move_Entity::get_y()
{
    return y;
}
float Move_Entity::get_w()
{
    return w;
}
float Move_Entity::get_h()
{
    return h;
}

void Move_Entity::set_x(float x)
{
    this->x = x;
}
void Move_Entity::set_y(float y)
{
    this->y = y;
}

//--------------------------------------

bool Move_Entity::get_freeze()
{
    return is_freezed;
}

void Move_Entity::set_freeze(bool state)
{
    this->is_freezed = state;
}
//--------------------------------------
void Move_Entity::set_health(int health)
{
    this->health = health;
}

int Move_Entity::get_health()
{
    return health;
}
//--------------------------------------
void Move_Entity::set_damage(int damage)
{
    this->damage = damage;
}

int Move_Entity::get_damage()
{
    return damage;
}
//--------------------------------------
int Move_Entity::get_experience()
{
    return experience;
}
//--------------------------------------
void Move_Entity::show()
{
    this->get_sprite().setTextureRect(IntRect(w,h,w,h));
}


Move_Entity::~Move_Entity()
{

}
