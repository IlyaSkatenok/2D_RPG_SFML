#pragma once
#include "Actor.h"
#include "Sounding.h"
// ПРЕДМЕТЫ, КОТОРЫМ МОЖЕТ ПОЛЬЗОВАТЬСЯ ГГ
class Item
{
protected:
    std::wstring name;       // Название предмета
    bool usable;         // Можно ли использовать
    bool can_belt;
    Sounding* used;

    Entity* logo_item;
    std::wstring* descr_item;
public:
        Item(std::wstring name,bool usable,bool can_belt);
        virtual ~Item();
        virtual void use(Actor& hero, bool is_silent = 0) = 0;
        virtual void set_need_sprite() = 0;
        virtual void re_use(Actor& hero, bool is_silent = 0);           // ДЛЯ ПРЕДМЕТОВ С ПОЯСА
        Entity& get_entity();
        std::wstring get_name();
        std::wstring get_description();
        bool get_usable();
        bool get_can_belt();
        void play_sound();
};

class Health_potion : public Item
{
public:
    Health_potion();
    void set_need_sprite() override;
    void use(Actor& hero, bool is_silent = 0) override;
};

class Big_Health_potion : public Item
{
public:
    Big_Health_potion();
    void set_need_sprite() override;
    void use(Actor& hero, bool is_silent = 0) override;
};

class Experience_potion : public Item
{
    public:
    Experience_potion();
    void set_need_sprite() override;
    void use(Actor& hero, bool is_silent = 0) override;
};

class Rune_granite : public Item
{
public:
    Rune_granite();
    void set_need_sprite() override;
    void use(Actor& hero, bool is_silent = 0) override;
    void re_use(Actor& hero, bool is_silent = 0) override;
};

class Rune_crystal : public Item
{
public:
    Rune_crystal();
    void set_need_sprite() override;
    void use(Actor& hero, bool is_silent = 0) override;
    void re_use(Actor& hero, bool is_silent = 0) override;
};

class Rune_strength : public Item
{
public:
    Rune_strength();
    void set_need_sprite() override;
    void use(Actor& hero, bool is_silent = 0) override;
    void re_use(Actor& hero, bool is_silent = 0) override;
};

class Rune_luck : public Item
{
public:
    Rune_luck();
    void set_need_sprite() override;
    void use(Actor& hero, bool is_silent = 0) override;
    void re_use(Actor& hero, bool is_silent = 0) override;
};

class Rune_endurance : public Item
{
public:
    Rune_endurance();
    void set_need_sprite() override;
    void use(Actor& hero, bool is_silent = 0) override;
    void re_use(Actor& hero, bool is_silent = 0) override;
};

class Rune_agility : public Item
{
public:
    Rune_agility();
    void set_need_sprite() override;
    void use(Actor& hero, bool is_silent = 0) override;
    void re_use(Actor& hero, bool is_silent = 0) override;
};


class Magic_stone : public Item
{
public:
    Magic_stone();
    void set_need_sprite() override;
    void use(Actor& hero, bool is_silent = 0) override;
};
