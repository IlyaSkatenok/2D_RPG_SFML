#pragma once
#include "Actor.h"
#include "Sounding.h"

class Item
{
protected:
    std::wstring name;       // Название предмета
    bool usable;         // Можно ли использовать
    bool can_belt;
    int points;
    Sounding* used;

    Entity* logo_item;
    std::wstring* descr_item;
public:
        Item(std::wstring name,bool usable,bool can_belt, int points);
        virtual ~Item();
        virtual void use(Actor& hero) = 0;
        virtual void set_need_sprite() = 0;

        Entity& get_entity();
        std::wstring get_name();
        std::wstring get_description();
        bool get_usable();
        bool get_can_belt();
        void play_sound();
};


class Item_belt
{
protected:
    virtual void re_use(Actor& hero) = 0;
};

class Health_potion : public Item
{
public:
    Health_potion();
    virtual ~Health_potion();
    void set_need_sprite() override;
    void use(Actor& hero) override;
};

class Big_Health_potion : public Item
{
public:
    Big_Health_potion();
    virtual ~Big_Health_potion();
    void set_need_sprite() override;
    void use(Actor& hero) override;
};

class Experience_potion : public Item
{
    public:
    Experience_potion();
    virtual ~Experience_potion();
    void set_need_sprite() override;
    void use(Actor& hero) override;
};

class Armor_rune : public Item , public Item_belt
{
public:
    Armor_rune();
    virtual ~Armor_rune();
    void set_need_sprite() override;
    void use(Actor& hero) override;
    void re_use(Actor& hero) override;
};

class Weapon_rune : public Item , public Item_belt
{
public:
    Weapon_rune();
    virtual ~Weapon_rune();
    void set_need_sprite() override;
    void use(Actor& hero) override;
    void re_use(Actor& hero) override;
};

class Golden_key : public Item
{
public:
    Golden_key();
    virtual ~Golden_key();
    void set_need_sprite() override;
    void use(Actor& hero) override;
};
