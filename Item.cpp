#include "Item.h"

Sounding item_sounds[4] = {
Sounding("./gamedata/sounds/items/Health_potion"),
Sounding("./gamedata/sounds/items/Experience_potion"),
Sounding("./gamedata/sounds/items/rune_use"),
Sounding("./gamedata/sounds/items/rune_drop"),
};

Entity artifacts = Entity("./gamedata/textures/tiles/tiles_artifacts.png", 1);
Entity potions = Entity("./gamedata/textures/tiles/tiles_potions.png", 1);

std::wstring descriptions[]
{
    L"Лечебное зелье\nЛечение зависит от вашей выносливости.\nБазовое лечение: 30",
    L"Лечебный элексир\nЛечение зависит от вашей выносливости.\nБазовое лечение: 45",
    L"Зелье опыта\nПовышает опыт до следующего уровня.",
    L"Волшебный камень\nВ нём заключена большая сила.",
    L"Руна хрусталя\nПовышает урон.\nУрон +20\nЗдоровье -20\nВНС -1",
    L"Руна гранита\nПовышает здоровье.\nУрон -12\nЗдоровье +20\nВНС +2",
    L"Руна силы\nПовышает силу.\nСИЛ +2",
    L"Руна удачи\nПовышает удачу.\nУДЧ +2",
    L"Руна ловкости\nПовышает ловкость.\nЛВК +2",
    L"Руна выносливости\nПовышает выносливость.\nВНС +2",
};


Item::Item(std::wstring name, bool usable, bool can_belt)
{
    this->name = name;
    this->usable = usable;
    this->can_belt = can_belt;
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

void Item::re_use(Actor& hero, bool is_silent)
{

}

//----------------------------------------------------------------------------
Health_potion::Health_potion() : Item(L"Лечебное зелье",1, 0)
{
    used = &item_sounds[0];
    descr_item = &descriptions[0];
    logo_item = &potions;
}

void Health_potion::use(Actor& hero, bool is_silent)
{
    hero.add_health(30 + hero.get_endurance() / 3);
    if (!is_silent)
    {
        play_sound();
    }
}
void Health_potion::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(90,0,90,130));
}
//----------------------------------------------------------------------------
Big_Health_potion::Big_Health_potion() : Item(L"Лечебный элексир",1, 0)
{
    used = &item_sounds[0];
    descr_item = &descriptions[1];
    logo_item = &potions;
}

void Big_Health_potion::use(Actor& hero, bool is_silent)
{
    hero.add_health(45 + hero.get_endurance() / 3);
    if (!is_silent)
    {
        play_sound();
    }
}

void Big_Health_potion::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(180,0,90,130));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
Experience_potion::Experience_potion() : Item(L"Зелье опыта",1, 0)
{
    used = &item_sounds[1];
    descr_item = &descriptions[2];
    logo_item = &potions;
}

void Experience_potion::use(Actor& hero, bool is_silent)
{
    hero.set_experience(hero.get_max_experience());
    if (!is_silent)
    {
        play_sound();
    }
}

void Experience_potion::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(0,0,90,130));
}

//----------------------------------------------------------------------------
Rune_granite::Rune_granite() : Item (L"Руна гранита",1, 1)
{
    used = &item_sounds[2];
    descr_item = &descriptions[5];
    logo_item = &artifacts;
}

void Rune_granite::use(Actor& hero, bool is_silent)
{
    hero.set_bonus_damage(hero.get_bonus_damage() - 12);
    hero.set_bonus_health(hero.get_bonus_health() + 20);
    hero.set_endurance(hero.get_endurance() + 2);
    if (!is_silent)
    {
        play_sound();
    }
}

void Rune_granite::re_use(Actor& hero, bool is_silent)
{
    hero.set_bonus_damage(hero.get_bonus_damage() + 12);
    hero.set_bonus_health(hero.get_bonus_health() - 20);
    hero.set_endurance(hero.get_endurance() - 2);
    if (!is_silent)
    {
        item_sounds[3].play_sound();
    }
}

void Rune_granite::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(0,0,34,44));
}


//----------------------------------------------------------------------------
Rune_crystal::Rune_crystal() : Item (L"Руна хрусталя",1, 1)
{
    used = &item_sounds[2];
    descr_item = &descriptions[4];
    logo_item = &artifacts;
}

void Rune_crystal::use(Actor& hero, bool is_silent)
{
    hero.set_bonus_damage(hero.get_bonus_damage() + 20);
    hero.set_bonus_health(hero.get_bonus_health() - 20);
    hero.set_endurance(hero.get_endurance() - 1);
    if (!is_silent)
    {
        play_sound();
    }
}

void Rune_crystal::re_use(Actor& hero, bool is_silent)
{
    hero.set_bonus_damage(hero.get_bonus_damage() - 20);
    hero.set_bonus_health(hero.get_bonus_health() + 20);
    hero.set_endurance(hero.get_endurance() + 1);
    if (!is_silent)
    {
        item_sounds[3].play_sound();
    }
}

void Rune_crystal::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(34,0,31,44));
}
//----------------------------------------------------------------------------
Rune_strength::Rune_strength() : Item (L"Руна силы",1, 1)
{
    used = &item_sounds[2];
    descr_item = &descriptions[6];
    logo_item = &artifacts;
}

void Rune_strength::use(Actor& hero, bool is_silent)
{
    hero.set_strength(hero.get_strength() + 2);
    if (!is_silent)
    {
        play_sound();
    }
}

void Rune_strength::re_use(Actor& hero, bool is_silent)
{
    hero.set_strength(hero.get_strength() - 2);
    if (!is_silent)
    {
        item_sounds[3].play_sound();
    }
}

void Rune_strength::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(65,0,37,44));
}
//----------------------------------------------------------------------------
Rune_luck::Rune_luck() : Item (L"Руна удачи",1, 1)
{
    used = &item_sounds[2];
    descr_item = &descriptions[7];
    logo_item = &artifacts;
}

void Rune_luck::use(Actor& hero, bool is_silent)
{
    hero.set_luck(hero.get_luck() + 2);
    if (!is_silent)
    {
        play_sound();
    }
}

void Rune_luck::re_use(Actor& hero, bool is_silent)
{
    hero.set_luck(hero.get_luck() - 2);
    if (!is_silent)
    {
        item_sounds[3].play_sound();
    }
}

void Rune_luck::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(102,0,32,44));
}
//----------------------------------------------------------------------------
Rune_endurance::Rune_endurance() : Item (L"Руна выносливости",1, 1)
{
    used = &item_sounds[2];
    descr_item = &descriptions[9];
    logo_item = &artifacts;
}

void Rune_endurance::use(Actor& hero, bool is_silent)
{
    hero.set_endurance(hero.get_endurance() + 2);
    if (!is_silent)
    {
        play_sound();
    }
}

void Rune_endurance::re_use(Actor& hero, bool is_silent)
{
    hero.set_endurance(hero.get_endurance() - 2);
    if (!is_silent)
    {
        item_sounds[3].play_sound();
    }
}

void Rune_endurance::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(134,0,39,44));
}
//----------------------------------------------------------------------------
Rune_agility::Rune_agility() : Item (L"Руна ловкости",1, 1)
{
    used = &item_sounds[2];
    descr_item = &descriptions[8];
    logo_item = &artifacts;
}

void Rune_agility::use(Actor& hero, bool is_silent)
{
    hero.set_agility(hero.get_agility() + 2);
    if (!is_silent)
    {
        play_sound();
    }
}

void Rune_agility::re_use(Actor& hero, bool is_silent)
{
    hero.set_agility(hero.get_agility() - 2);
    if (!is_silent)
    {
        item_sounds[3].play_sound();
    }
}

void Rune_agility::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(173,0,35,44));
}
//----------------------------------------------------------------------------
Magic_stone::Magic_stone() : Item (L"Волшебный камень",0, 0)
{
    used = &item_sounds[1];
    descr_item = &descriptions[3];
    logo_item = &artifacts;
}

void Magic_stone::use(Actor& hero, bool is_silent)
{

}

void Magic_stone::set_need_sprite()
{
    logo_item->get_sprite().setTextureRect(IntRect(207,0,34,44));
}
