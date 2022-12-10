#include "State.h"
#define MAP 50
State::State()
{
    verdana.loadFromFile("./gamedata/fonts/verdana.ttf");
    info = Text("", verdana, 80);
    info.setColor(Color(24,240,24));
}

State::~State()
{

}

Settings::Settings()
{
    info.setCharacterSize(60);
}

Settings::~Settings()
{

}

void State::set_window(RenderWindow *window)
{
    WINDOW = window;
}

void Settings::show(int X, int Y, bool in_menu, bool& is_play_ambient, int& volume_level, int& volume_level_ambient)
{
    XX = X - 600;
    YY = Y - 300;
    if(in_menu)
    {
        XX = 200;
        YY = 200;
    }
    settings_info.get_sprite().setPosition(XX, YY);
    WINDOW->draw(settings_info.get_sprite());

    XX += 50;

    info.setString(L"ФОНОВАЯ МУЗЫКА");
        info.setPosition(XX,YY + 25);
    WINDOW->draw(info);

    info.setString(L"ФОНОВАЯ МУЗЫКА");
        info.setPosition(XX,YY + 100);
    WINDOW->draw(info);

    info.setString(L"ОБЩАЯ ГРОМКОСТЬ");
        info.setPosition(XX,YY + 175);
    WINDOW->draw(info);

    info.setString(L"ПОЛНЫЙ ЭКРАН");
        info.setPosition(XX,YY + 250);
    WINDOW->draw(info);

    info.setColor(Color(240,20,100));

    if (is_play_ambient)
    {
        info.setString(L"ВКЛ");
        info.setPosition(XX + 750,YY + 25);
    }
    else
    {
         info.setString(L"ВЫКЛ");
        info.setPosition(XX + 720,YY + 25);
    }
    WINDOW->draw(info);

    info.setString(std::to_string(volume_level_ambient));
    info.setPosition(XX + 750,YY + 100);
    WINDOW->draw(info);

    info.setString(std::to_string(volume_level));
    info.setPosition(XX + 750,YY + 175);
    WINDOW->draw(info);

    info = Text("", verdana, 55);
    info.setColor(Color(2,20,18));
    info.setString("<");
    info.setPosition(XX + 675,YY + 100);
    WINDOW->draw(info);
    info.setPosition(XX + 675,YY + 175);
    WINDOW->draw(info);

    info.setString(">");
    info.setPosition(XX + 900,YY + 100);
    WINDOW->draw(info);
    info.setPosition(XX + 900,YY + 175);
    WINDOW->draw(info);


    info = Text("", verdana, 60);
    info.setColor(Color(24,240,24));

}

Menu::Menu()
{
        info.setCharacterSize(55);
}

Menu::~Menu()
{

}

void Menu::show(int X, int Y, bool is_file, bool is_hide_buttons)
{
    WINDOW->draw(menu_background.get_sprite());
    if (!is_hide_buttons)
    {
        if (is_file)
        {
            menu_buttons.get_sprite().setPosition(565, 150);
            WINDOW->draw(menu_buttons.get_sprite());

            info.setString(L"ПРОДОЛЖИТЬ");
                info.setPosition(585,175);
           WINDOW->draw(info);
        }

        menu_buttons.get_sprite().setPosition(565, 325);
        WINDOW->draw(menu_buttons.get_sprite());

            info.setString(L"НОВАЯ ИГРА");
                info.setPosition(605,350);
           WINDOW->draw(info);

        menu_buttons.get_sprite().setPosition(565, 500);
        WINDOW->draw(menu_buttons.get_sprite());

            info.setString(L"НАСТРОЙКИ");
                info.setPosition(615,520);
           WINDOW->draw(info);

        menu_buttons.get_sprite().setPosition(565, 675);
        WINDOW->draw(menu_buttons.get_sprite());

            info.setString(L"ВЫХОД");
                info.setPosition(675,695);
           WINDOW->draw(info);
        }

}

Pause::Pause()
{
        info.setCharacterSize(60);
}

Pause::~Pause()
{

}

void Pause::show(int X, int Y)
{
    pause_menu.get_sprite().setPosition(X - 260 , Y  - 330 );
    WINDOW->draw(pause_menu.get_sprite());

        info.setString(L"ВЫХОД");
            info.setPosition(X - 165,Y - 310);
       WINDOW->draw(info);

    pause_menu.get_sprite().setPosition(X - 260 , Y  - 80);
    WINDOW->draw(pause_menu.get_sprite());

        info.setString(L"НАСТРОЙКИ");
            info.setPosition(X - 225,Y - 60);
       WINDOW->draw(info);

    pause_menu.get_sprite().setPosition(X - 260 , Y  + 160);
    WINDOW->draw(pause_menu.get_sprite());

        info.setString(L"ВЕРНУТЬСЯ");
            info.setPosition(X - 210,Y + 185);
       WINDOW->draw(info);
}

Map::Map()
{

}

Map::~Map()
{

}

void Map::show(int X, int Y)
{
    WINDOW->draw(map_menu.get_sprite());
}

bool Loader::is_file_actor()
{
    std::ifstream File("./gamedata/configs/actor.txt");
    if (File)
    {
        return true;
    }
    return false;
}

void Loader::load_level(int level, std::string Cur_level[])
{
    std::string need_level = "level" + std::to_string(level);
    std::ifstream File("./gamedata/configs/levels/" + need_level + ".txt");
    std::string tmp;
    int i = 0;
    while (!File.eof())
    {
        getline(File,tmp);
        Cur_level[i] = tmp;
        i++;
    }
    File.close();
}

void Loader::load_spawn(int level, std::string Cur_level_spawn[])
{
    std::string need_level = "level_spawn" + std::to_string(level);
    std::ifstream File("./gamedata/configs/all_spawns/" + need_level + ".txt");
    std::string tmp;
    int i = 0;
    while (!File.eof())
    {
        getline(File,tmp);
        Cur_level_spawn[i] = tmp;
        i++;
    }
    File.close();
}

void Loader::load_treasure(int level, std::string Cur_level_treasure[])
{
    std::string need_level = "level_treasure" + std::to_string(level);
    std::ifstream File("./gamedata/configs/treasure_spawns/" + need_level + ".txt");
    std::string tmp;
    int i = 0;
    while (!File.eof())
    {
        getline(File,tmp);
        Cur_level_treasure[i] = tmp;
        i++;
    }
    File.close();
}

void Loader::load_settings(int& volume_level, int& volume_level_ambient, bool& is_play_ambient)
{
    std::ifstream File("./gamedata/configs/settings.txt");
    int temp;
    File >> temp; volume_level = temp;
    File >> temp; volume_level_ambient = temp;
    File >> temp; is_play_ambient = temp;
    File.close();
}

void Saver::save_settings(int& volume_level, int& volume_level_ambient, bool& is_play_ambient)
{
    std::ofstream File("./gamedata/configs/settings.txt");
    File << volume_level << '\n';
    File << volume_level_ambient << '\n';
    File << is_play_ambient;
    File.close();
}

void Saver::save_spawn(int& level, std::string level_spawn[])
{
    std::string need_level = "level_spawn" + std::to_string(level);
    std::ofstream File("./gamedata/configs/all_spawns/" + need_level + ".txt");
    for (int i = 0; i < MAP; i++)
    {
        File << level_spawn[i];
        if (i != (MAP - 1))
        {
            File << '\n';
        }
    }

    File.close();
}

void Saver::save_treasure(int& level, std::string level_treasure[])
{
    std::string need_level = "level_treasure" + std::to_string(level);
    std::ofstream File("./gamedata/configs/treasure_spawns/" + need_level + ".txt");
    for (int i = 0; i <  MAP; i++)
    {
        File << level_treasure[i];
        if (i != (MAP - 1))
        {
            File << '\n';
        }
    }

    File.close();
}
