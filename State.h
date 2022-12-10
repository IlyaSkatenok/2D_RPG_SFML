#pragma once
#include "Entity.h"
// ������, �������������� ����� ��������� ����
class State
{
protected:
    RenderWindow *WINDOW;

    Font verdana;
    Text info;


public:
    State();
    virtual ~State();
    void set_window(RenderWindow *window);
};

class Settings: public State
{
protected:
    int XX, YY;
    Entity settings_info = Entity("./gamedata/textures/info/settings_menu.png");
public:
    Settings();
    virtual ~Settings();
    void show(int X, int Y, bool in_menu, bool& is_play_ambient,int& volume_level,int& volume_level_ambient);
};

class Menu: public State
{
protected:
    Entity menu_background = Entity("./gamedata/textures/info/menu_background.png");
    Entity menu_buttons = Entity("./gamedata/textures/info/menu_button.png");
public:
    Menu();
    virtual ~Menu();
    void show(int X, int Y, bool is_file, bool is_hide_buttons);
};

class Pause: public State
{
protected:
    Entity pause_menu = Entity("./gamedata/textures/info/menu_button.png");
public:
    Pause();
    virtual ~Pause();
    void show(int X, int Y);
};

class Map: public State
{
protected:
    Entity map_menu = Entity("./gamedata/textures/info/game_map.png");
public:
    Map();
    virtual ~Map();
    void show(int X, int Y);
};

class Loader
{
public:

    bool is_file_actor();
    void load_level(int level, std::string Cur_level[]);
    void load_spawn(int level, std::string Cur_level_spawn[]);
    void load_treasure(int level, std::string Cur_level_treasure[]);
    void load_settings(int& volume_level, int& volume_level_ambient, bool& is_play_ambient);
};

class Saver
{
public:

    void save_settings(int& volume_level, int& volume_level_ambient, bool& is_play_ambient);
    void save_spawn(int& level, std::string level_spawn[]);
    void save_treasure(int& level, std::string level_treasure[]);
};
