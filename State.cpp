#include "State.h"
#define MAP 50
State::State()
{
    verdana.loadFromFile("./gamedata/fonts/verdana.ttf");
    info = Text("", verdana, 80);
    info.setColor(Color(24,240,24));
}

Settings::Settings()
{
    info.setCharacterSize(60);
}

void State::set_window(RenderWindow *window)
{
    WINDOW = window;
}

void Settings::show(int X, int Y, bool in_menu, bool& is_play_ambient, int& volume_level, int& volume_level_ambient)
{
    XX = X - 600;
    YY = Y - 255;
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

void Map::show(int X, int Y)
{
    WINDOW->draw(map_menu.get_sprite());
}

End::End()
{
    info.setColor(Color(5,5,5));
    red_end.get_sprite().setScale(10,10);
}

void End::show(int X, int Y)
{
    red_end.get_sprite().setPosition(X, Y);
    WINDOW->draw(red_end.get_sprite());

    button_end.get_sprite().setPosition(X + 600, Y + 700);
    WINDOW->draw(button_end.get_sprite());

    info.setCharacterSize(70);
    info.setString(L"ВЫ ПРОИГРАЛИ");
    info.setPosition(X + 500, Y + 100);
    WINDOW->draw(info);

    info.setCharacterSize(55);
    info.setString(L"ВЫХОД");
    info.setPosition(X + 705, Y + 725);
    WINDOW->draw(info);
}

bool Loader::is_file_actor()
{
    std::ifstream File("./gamedata/configs/actor/actor.txt");
    if (File)
    {
        return true;
    }
    return false;
}

void Loader::load_level(int level, std::string Cur_level[], int& actor_x, int& actor_y)
{
    std::string need_level = "level" + std::to_string(level);
    std::ifstream File("./gamedata/configs/levels/" + need_level + ".txt");
    File >> actor_x; File >> actor_y;
    actor_x *= 64; actor_y *= 64;
    std::string tmp;
    getline(File,tmp);
    int i = 0;
    while (!File.eof())
    {
        getline(File,tmp);
        //std::cout << tmp << "<-----" << '\n';
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

void Loader::reload_all()
{
    std::string temp;
    for (int i = 1; i < 10; i++)
    {
        std::ofstream File_w("./gamedata/configs/all_spawns/level_spawn" + std::to_string(i) + ".txt");
        std::ifstream File_r("./gamedata/configs/all_spawns_back/level_spawn" + std::to_string(i) + ".txt");
        while (!File_r.eof())
        {
            getline(File_r,temp);
            File_w << temp;
            if (!File_r.eof())
            {
                File_w << '\n';
            }
        }
        File_r.close(); File_w.close();
    }
    for (int i = 1; i < 10; i++)
    {
        std::ofstream File_w("./gamedata/configs/treasure_spawns/level_treasure" + std::to_string(i) + ".txt");
        std::ifstream File_r("./gamedata/configs/treasure_spawns_back/level_treasure" + std::to_string(i) + ".txt");
        while (!File_r.eof())
        {
            getline(File_r,temp);
            File_w << temp;
            if (!File_r.eof())
            {
                File_w << '\n';
            }
        }
        File_r.close(); File_w.close();
    }

    std::ofstream File_actor_w("./gamedata/configs/actor/actor.txt");
    std::ifstream File_actor_r("./gamedata/configs/actor_back/actor.txt");
    while (!File_actor_r.eof())
    {
        getline(File_actor_r,temp);
        File_actor_w << temp;
        if (!File_actor_r.eof())
        {
            File_actor_w << '\n';
        }
    }

    File_actor_r.close(); File_actor_w.close();

    std::ofstream File_inv_w("./gamedata/configs/actor/actor_items.txt");
    std::ifstream File_inv_r("./gamedata/configs/actor_back/actor_items.txt");
    while (!File_inv_r.eof())
    {
        getline(File_inv_r,temp);
        File_inv_w << temp;
        if (!File_inv_r.eof())
        {
            File_inv_w << '\n';
        }
    }

    File_inv_r.close(); File_inv_w.close();

    std::ofstream File_belt_w("./gamedata/configs/actor/actor_belt.txt");
    std::ifstream File_belt_r("./gamedata/configs/actor_back/actor_belt.txt");
    while (!File_belt_r.eof())
    {
        getline(File_belt_r,temp);
        File_belt_w << temp;
        if (!File_belt_r.eof())
        {
            File_belt_w << '\n';
        }
    }

    File_belt_r.close(); File_belt_w.close();
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
