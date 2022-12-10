#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <clocale>

#include "Entity.h"
#include "Item.h"
#include "Enemy.h"
#include "Actor.h"
#include "State.h"
using namespace sf;

// РАБОТА С ОКНОМ И ИГРОЙ
class Game
{
private:
    RenderWindow *window;
    Event event;

    Clock clock;
    float delta;

    Entity tiles = Entity("./gamedata/textures/tiles/tiles_big.png");
    Entity tiles_treasure = Entity("./gamedata/textures/tiles/TILES_TREASURE.png");

    void initWindow();

    Settings settings;
    Menu menu;
    Pause pause;
    Map game_map;
    Loader loader;
    Saver saver;

    Sounding ambient;
    Sounding click_on_button;
    Sounding open_inventory;
    Sounding change_inventory;
    Sounding treasures[4];


    int lvl = -1;

    Actor ACTOR = Actor("./gamedata/textures/hero.png",180,180,64,64);
    Entity actor_logo = Entity("./gamedata/textures/logos/actor_logo.png");

    Entity inv_tile = Entity("./gamedata/textures/info/Inventory_1.png");

    Entity belt_choosen = Entity("./gamedata/textures/info/belt_choose.png", 1);

    std::string Cur_level[50];
    std::string Cur_level_spawn[50];
    std::string Cur_level_treasure[50];

    std::vector<Enemy*> all_spawn;
    std::vector<Item*> inventory_items;
    std::map<std::wstring, int> inventory_items_counter;
    std::vector<Item*> inventory_belt;

    std::wstring found_item = L"";

    int item_number = 0;
    int skill_number = 0;
    int belt_number = 0;

    bool is_fullscreen = false;
    int volume_level = 100;
    int volume_level_ambient = 100;
    bool is_play_ambient = false;


    bool is_save_file = false;
    bool is_inventory = false;
    bool is_inventory_items = false;

    bool is_paused = false;
    bool is_settings = false;

    bool was_pressed = false;

    bool is_battle = false;
    bool was_attack = false;
    bool was_found = false;
    int16_t number_battler = -1;

    char collision_loot = ' ';



    Font verdana;
    Text skills;

    Text points;

    Clock timer;
    Clock battle_timer;
    Clock found_timer;


public:


    Game();
    ~Game();

    void set_sounds();
    void load_actor();
    void save_actor();
    bool collision();
    bool collision_treasure();
    void fill_all_spawn();

    void show_spawn();
    void show_hero();
    void show_map();
    void show_inventory();
    void show_treasure();
    void show_paused();
    void show_battle();
    void show_battle_gui();
    void show_use(int item = -1);
    void show_cur_item();
    void show_belt();

    void collision_setting(int X, int Y);
    void collision_paused(int X, int Y);
    void collision_menu(int X, int Y);

    void use_treasure();
    void move_spawn();

    void show_founded_item();
    void check_attack();
    void update_battle();
    void end_battle();

    void set_all_freeze(bool frz);

    void add_skill();
    void choose_skill(bool side);
    void choose_item(bool side);
    void choose_belt(bool side);
    void pull_belt();

    bool add_belt();
    void add_belt_load(Item* rune);
    void add_item(Item* loot);
    void open_chest(int rander);

    char get_tile_walk();
    char get_tile_walk(float x, float y);


    void updateDelta();
    void updateEvents();
    void set_pause(bool ispaused);
    void update();
    void render();
    void run();
};

