#include "Item.h"

Sounding item_sounds[4] = {
Sounding("./gamedata/sounds/items/Health_potion"),
Sounding("./gamedata/sounds/items/Experience_potion"),
Sounding("./gamedata/sounds/items/Armor_rune"),
Sounding("./gamedata/sounds/items/Weapon_rune"),
};

Entity artifacts = Entity("./gamedata/textures/tiles/tiles_artifacts.png", 1);
Entity potions = Entity("./gamedata/textures/tiles/tiles_potions.png", 1);

std::wstring descriptions[]
{
    L"Лечебное зелье\nЛечение зависит от вашей выносливости.\nБазовое лечение: 30",
    L"Лечебный элексир\nЛечение зависит от вашей выносливости.\nБазовое лечение: 45",
    L"Зелье опыта\nПовышает опыт до следующего уровня.",
    L"Руна хрусталя\nПовышает урон, но понижает здоровье.\nУрон +20\nЗдоровье -20\nВНС -1",
    L"Руна гранита\nПовышает здоровье, но понижает урон.\nУрон -12\nЗдоровье +20\nСИЛ +1\nВНС +1",

};


Item::Item(std::wstring name, bool usable, bool can_belt, int points)
{
    this->name = name;
    this->usable = usable;
    this->can_belt = can_belt;
    this->points = points;
}

Item::~Item()
{

}

bool Item::get_usable()
{
    return usable;
}

bool Item::get_can_belt()
{
    return can_belt;
}

std::wstring Item::get_name()
{
    return name;
}
void Item::play_sound()
{
    used->play_sound();
}

std::wstring Item::get_description()
{
    return *descr_item;
}
Entity& Item::get_entity()
{
    return *logo_item;
}

//----------------------------------------------------------------------------
Health_potion::Health_potion() : Item(L"Лечебное зелье",1, 0, 30)
{
    used = &item_sounds[0];
    descr_item = &descriptions[0];
    logo_item = &potions;
}

Health_potion::~Health_potion()
{
    //dtor
}

void Health_potion::use(Actor& hero)
{
    hero.add_health(points + hero.get_endurance() / 3);
    play_sound();
}
void Health_potion::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(90,0,90,130));
}
//----------------------------------------------------------------------------
Big_Health_potion::Big_Health_potion() : Item(L"Лечебный элексир",1, 0, 45)
{
    used = &item_sounds[0];
    descr_item = &descriptions[1];
    logo_item = &potions;
}

Big_Health_potion::~Big_Health_potion()
{
    //dtor
}

void Big_Health_potion::use(Actor& hero)
{
    hero.add_health(points + hero.get_endurance() / 3);
    play_sound();
}

void Big_Health_potion::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(180,0,90,130));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
Experience_potion::Experience_potion() : Item(L"Зелье опыта",1, 0, 1)
{
    used = &item_sounds[1];
    descr_item = &descriptions[2];
    logo_item = &potions;
}

Experience_potion::~Experience_potion()
{
    //dtor
}

void Experience_potion::use(Actor& hero)
{
    hero.set_experience(hero.get_max_experience());
    play_sound();
}

void Experience_potion::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(0,0,90,130));
}
//----------------------------------------------------------------------------
Armor_rune::Armor_rune() : Item (L"Руна защиты",1, 1, 10)
{
    used = &item_sounds[2];
    descr_item = &descriptions[3];
    logo_item = &artifacts;
}

Armor_rune::~Armor_rune()
{
    //dtor
}

void Armor_rune::use(Actor& hero)
{
    hero.set_bonus_health(hero.get_bonus_health() + points);
    play_sound();
}

void Armor_rune::re_use(Actor& hero)
{
    hero.set_bonus_health(hero.get_bonus_health() - points);
    play_sound();
}

void Armor_rune::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(0,0,34,44));
}

//----------------------------------------------------------------------------
Weapon_rune::Weapon_rune() : Item (L"Руна урона",1, 1, 5)
{
    used = &item_sounds[3];
    descr_item = &descriptions[4];
    logo_item = &artifacts;
}

Weapon_rune::~Weapon_rune()
{
    //dtor
}

void Weapon_rune::use(Actor& hero)
{
    hero.set_bonus_damage(hero.get_bonus_damage() + points);
    play_sound();
}

void Weapon_rune::re_use(Actor& hero)
{
    hero.set_bonus_damage(hero.get_bonus_damage() - points);
    play_sound();
}

void Weapon_rune::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(34,0,31,44));
}

//----------------------------------------------------------------------------
Golden_key::Golden_key() : Item (L"Золотой ключ",0, 0, 0)
{
    used = &item_sounds[1];
    descr_item = &descriptions[4];
    logo_item = &artifacts;
}

Golden_key::~Golden_key()
{
    //dtor
}

void Golden_key::use(Actor& hero)
{

}

void Golden_key::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(65,0,37,44));
}
