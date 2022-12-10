#include "Game.h"

#define MAP 50
#define MAX_BELT 4

// Создание окна
void Game::initWindow()
{
    this->window = new RenderWindow(VideoMode(1600,900), "GAME", Style::Close);
    this->window->setFramerateLimit(60);

    settings.set_window(window);
    menu.set_window(window);
    pause.set_window(window);
    game_map.set_window(window);
}

Game::Game()
{
    this->initWindow();
    loader.load_settings(volume_level,volume_level_ambient, is_play_ambient);
    this->set_sounds();
    ambient.set_sound("./gamedata/sounds/game/ambient_menu");
    click_on_button.set_sound("./gamedata/sounds/game/click");
    open_inventory.set_sound("./gamedata/sounds/game/inventory");
    change_inventory.set_sound("./gamedata/sounds/game/inventory_change");
    treasures[0].set_sound("./gamedata/sounds/game/treasure_chest");
    treasures[1].set_sound("./gamedata/sounds/game/treasure_medium");
    treasures[2].set_sound("./gamedata/sounds/game/treasure_small");
    treasures[3].set_sound("./gamedata/sounds/game/treasure_key");
    if (is_play_ambient)
    {
        ambient.play_sound();
    }

    verdana.loadFromFile("./gamedata/fonts/verdana.ttf");
    skills = Text("", verdana, 75);
    skills.setColor(Color(4,4,4));

    points = Text("", verdana, 80);
    points.setStyle(Text::Bold);
    points.setColor(Color(240,170,10));
}

Game::~Game()
{
    saver.save_settings(volume_level, volume_level_ambient, is_play_ambient);
    delete this->window;
}

void Game::set_sounds()
{
    ambient.get_sound().setVolume(volume_level_ambient);
    Listener::setGlobalVolume(volume_level);
}

// Обновление событий
void Game::updateEvents()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == Event::Closed)
        {
            this->window->close();
        }
        if (event.type == Event::KeyPressed && !this->was_pressed)
        {
            if (event.key.code == Keyboard::Z && is_inventory_items)
            {
                choose_belt(1);
            }
            if (event.key.code == Keyboard::X && is_inventory_items)
            {
                choose_belt(0);
            }
            if (event.key.code == Keyboard::C && is_inventory_items)
            {
                pull_belt();
            }
            int key_code = event.key.code;
            if (was_attack)
            {
                continue;
            }
            if (event.key.code == Keyboard::Escape)
            {
                if (!is_battle)
                {
                    is_inventory = false;
                    is_inventory_items = false;
                    if (is_settings)
                    {
                        is_settings = false;
                    }
                    else
                    {
                        is_paused = !is_paused;
                        set_pause(is_paused);
                    }
                }
                if (!lvl)
                {
                    lvl = -1;
                }
            }



            if (event.key.code == Keyboard::Tab && !is_paused && (lvl > 0))
            {
                open_inventory.play_sound();
                is_inventory = !is_inventory;
                this->is_inventory_items = false;
                item_number = inventory_items.size() - 1;
                belt_number = 0;
                if (ACTOR.get_level_points())
                {
                    skill_number = 0;
                }
                else
                {
                    skill_number = -1;
                }

                if (!is_battle)
                {
                    ACTOR.set_freeze(is_inventory);
                    set_all_freeze(is_inventory);
                }
                this->was_pressed = true;
            }
            //-------------------------------------------------
            if ((key_code > 26) && (key_code < 36))
            {

                if (!lvl)
                {
                    ACTOR.get_camera().reset(FloatRect(0,0,1600,900));
                    this->lvl = key_code - 26;
                    loader.load_treasure(lvl, Cur_level_treasure);
                    loader.load_level(lvl, Cur_level);
                    loader.load_spawn(lvl, Cur_level_spawn);
                    this->fill_all_spawn();
                }
                else if (is_inventory)
                {
                    change_inventory.play_sound();
                    if (key_code == 27)
                    {
                        this->is_inventory_items = false;
                        if (ACTOR.get_level_points())
                        {
                            skill_number = 0;
                        }
                    }
                    else if (key_code == 28)
                    {
                        this->is_inventory_items = true;
                    }
                }
            }
            //-------------------------------------------------
            ACTOR.move(this->delta / 4, get_tile_walk());
            if (collision())
            {
                ACTOR.update_back(this->delta / 4);
            }
            if (collision_treasure())
            {
                use_treasure();
            }


            if (lvl && is_inventory)
            {
                if (event.key.code == Keyboard::W)
                {
                    if (is_inventory_items)
                    {
                         this->choose_item(0);
                    }
                    else if (ACTOR.get_level_points())
                    {
                        choose_skill(1);
                    }
                    this->was_pressed = true;
                }
                if (event.key.code == Keyboard::S)
                {
                    if (is_inventory_items)
                    {
                        this->choose_item(1);
                    }
                    else if (ACTOR.get_level_points())
                    {
                        choose_skill(0);
                    }
                    this->was_pressed = true;
                }
            }

            if (event.key.code == Keyboard::Q)
            {
                if (is_battle && !is_inventory && !was_attack)
                {
                    all_spawn[number_battler]->set_health(all_spawn[number_battler]->get_health() - ACTOR.attack(1));
                    this->battle_timer.restart().asMilliseconds();
                    this->was_attack = true;
                    this->was_pressed = true;
                }
            }
            if (event.key.code == Keyboard::E)
            {
                if (is_inventory)
                {
                    if (is_inventory_items)
                    {
                       timer.restart();
                        this->show_use(item_number);
                    }
                    else
                    {
                        this->add_skill();
                    }
                }
                else if (is_battle && !was_attack)
                {
                    all_spawn[number_battler]->set_health(all_spawn[number_battler]->get_health() - ACTOR.attack(0));
                    this->battle_timer.restart().asMilliseconds();
                    this->was_attack = true;
                }
                this->was_pressed = true;
            }
        }
        if (event.type == Event::KeyReleased && was_pressed)
        {
            was_pressed = false;
        }
        // МЫШКА
        if(event.type == Event::MouseButtonReleased)
        {
            std::cout << Mouse::getPosition(*this->window).x << "<<>>" << Mouse::getPosition(*this->window).y << std::endl;
            if (is_paused && !is_settings)
            {
                this->collision_paused(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y);
            }
            if (lvl == -1 && !is_settings)
            {
                this->collision_menu(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y);
            }
            if (is_settings)
            {
                std::cout << "i was here yopta" << std::endl;
                this->collision_setting(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y);
            }
        }
    }
}

void Game::set_pause(bool ispaused)
{
    set_all_freeze(ispaused);
    ACTOR.set_freeze(ispaused);
}

void Game::load_actor()
{
    std::ifstream File("./gamedata/configs/actor.txt");
    std::cout << "loaded" << std::endl;
    int temp; // ЛУВС
    File >> temp; ACTOR.set_agility(temp);
    File >> temp; ACTOR.set_luck(temp);
    File >> temp; ACTOR.set_endurance(temp);
    File >> temp; ACTOR.set_strength(temp);

    File >> temp; ACTOR.set_health(temp);
    File >> temp; ACTOR.set_experience(temp);
    File >> temp; ACTOR.set_level(temp);
    File >> temp ; ACTOR.set_level_points(temp);

    File.close();

    std::ifstream File2("./gamedata/configs/actor_items.txt");

    File2 >> temp;
    for (uint16_t i = 0; i < temp; i++){ inventory_items.push_back(new Magic_stone()); }
    File2 >> temp;
    for (uint16_t i = 0; i < temp; i++){ inventory_items.push_back(new Health_potion()); }
    File2 >> temp;
    for (uint16_t i = 0; i < temp; i++){ inventory_items.push_back(new Big_Health_potion()); }
    File2 >> temp;
    for (uint16_t i = 0; i < temp; i++){ inventory_items.push_back(new Experience_potion()); }
    File2 >> temp;
    for (uint16_t i = 0; i < temp; i++){ inventory_items.push_back(new Rune_granite()); }
    File2 >> temp;
    for (uint16_t i = 0; i < temp; i++){ inventory_items.push_back(new Rune_crystal()); }
    File2 >> temp;
    for (uint16_t i = 0; i < temp; i++){ inventory_items.push_back(new Rune_strength()); }
    File2 >> temp;
    for (uint16_t i = 0; i < temp; i++){ inventory_items.push_back(new Rune_luck()); }
    File2 >> temp;
    for (uint16_t i = 0; i < temp; i++){ inventory_items.push_back(new Rune_endurance()); }
    File2 >> temp;
    for (uint16_t i = 0; i < temp; i++){ inventory_items.push_back(new Rune_agility()); }

    File2.close();

    std::sort(inventory_items.begin(), inventory_items.end(), [](Item* a, Item* b)
                         {return a->get_name() > b->get_name();}
                         );
    item_number = inventory_items.size() - 1;

    std::ifstream File3("./gamedata/configs/actor_belt.txt");

    File3 >> temp;
    int temp_temp = temp;
    Item* temp_item;
    for (int i = 0; i < temp_temp; i++)
    {
        File3 >> temp;
        switch(temp)
        {
        case 0:
            temp_item = new Rune_granite();
            break;
        case 1:
            temp_item = new Rune_crystal();
            break;
        case 2:
            temp_item = new Rune_strength();
            break;
        case 3:
            temp_item = new Rune_luck();
            break;
        case 4:
            temp_item = new Rune_endurance();
            break;
        case 5:
            temp_item = new Rune_agility();
            break;
        default:
            temp_item = new Rune_luck();
            break;
        }
        this->add_belt_load(temp_item);
    }

    File3.close();


}

void Game::save_actor()
{
    std::wstring temp_wstr;
    std::string temp_str;

    std::ofstream File3("./gamedata/configs/actor_belt.txt");

    File3 << inventory_belt.size() << '\n';
    for (int i = 0; i < inventory_belt.size(); i++)
    {
        temp_wstr = inventory_belt[i]->get_name();
        if (temp_wstr == L"Руна гранита")
        {
            temp_str = "0";
        }
        else if(temp_wstr == L"Руна хрусталя")
        {
            temp_str = "1";
        }
        else if(temp_wstr == L"Руна силы")
        {
            temp_str = "2";
        }
        else if(temp_wstr == L"Руна удачи")
        {
            temp_str = "3";
        }
        else if(temp_wstr == L"Руна выносливости")
        {
            temp_str = "4";
        }
        else
        {
            temp_str = "5";
        }
        File3 << temp_str;
        if (i != inventory_belt.size() - 1)
        {
            File3 << '\n';
        }
    }

    File3.close();

    std::ofstream File2("./gamedata/configs/actor_items.txt");

    File2 << std::count_if(inventory_items.begin(), inventory_items.end(), [](Item* obj) {return (obj->get_name() == L"Волшебный камень");}) << '\n';
    File2 << std::count_if(inventory_items.begin(), inventory_items.end(), [](Item* obj) {return (obj->get_name() == L"Лечебное зелье");}) << '\n';
    File2 << std::count_if(inventory_items.begin(), inventory_items.end(), [](Item* obj) {return (obj->get_name() == L"Лечебный элексир");}) << '\n';
    File2 << std::count_if(inventory_items.begin(), inventory_items.end(), [](Item* obj) {return (obj->get_name() == L"Зелье опыта");}) << '\n';
    File2 << std::count_if(inventory_items.begin(), inventory_items.end(), [](Item* obj) {return (obj->get_name() == L"Руна гранита");}) << '\n';
    File2 << std::count_if(inventory_items.begin(), inventory_items.end(), [](Item* obj) {return (obj->get_name() == L"Руна хрусталя");}) << '\n';
    File2 << std::count_if(inventory_items.begin(), inventory_items.end(), [](Item* obj) {return (obj->get_name() == L"Руна силы");}) << '\n';
    File2 << std::count_if(inventory_items.begin(), inventory_items.end(), [](Item* obj) {return (obj->get_name() == L"Руна удачи");}) << '\n';
    File2 << std::count_if(inventory_items.begin(), inventory_items.end(), [](Item* obj) {return (obj->get_name() == L"Руна выносливости");}) << '\n';
    File2 << std::count_if(inventory_items.begin(), inventory_items.end(), [](Item* obj) {return (obj->get_name() == L"Руна ловкости");});

    File2.close();

    belt_number = 0;
    while(inventory_belt.size())
    {
        pull_belt();
    }


    std::ofstream File("./gamedata/configs/actor.txt");

    int temp; // ЛУВС
    File << ACTOR.get_agility() << ' ';
    File << ACTOR.get_luck() << ' ';
    File << ACTOR.get_endurance() << ' ';
    File << ACTOR.get_strength() << '\n';

    File << ACTOR.get_health() << ' ';
    File << ACTOR.get_experience() << '\n';
    File << ACTOR.get_level() << ' ';
    File << ACTOR.get_level_points() << '\n';

    File.close();
}

void Game::fill_all_spawn()
{
    for (int i = 0; i < MAP; i++)
    {
            for (int j = 0; j < MAP; j++)
            {
                if (Cur_level_spawn[i][j] == 'q')
                {
                    all_spawn.push_back(new Wolf(j * 64, i * 64));
                }
            }
    }
}

char Game::get_tile_walk()
{
    return Cur_level[int(ACTOR.get_y() / 64)][int(ACTOR.get_x() / 64)];
}

char Game::get_tile_walk(float x, float y)
{
    return Cur_level[int(y / 64)][int(x / 64)];
}

bool Game::collision()
{
    // ВЫХОД ЗА КАРТУ
    if ((ACTOR.get_x() < 64) || ACTOR.get_x() > (64 * MAP) || (ACTOR.get_y() < 64) || (ACTOR.get_y() > (64 * MAP)))
    {
        return true;
    }

    for (float i = ACTOR.get_y() / 64; i < (ACTOR.get_y() + ACTOR.get_h()) / 64; i++)
    {
        for (float j = ACTOR.get_x() / 64; j < (ACTOR.get_x() + ACTOR.get_w()) / 64; j++)
        {
            if (Cur_level[int(i)][int(j)] == 'b' || Cur_level[int(i)][int(j)] == 'd')
                {
                    std::cout << i << "<--->" << j << std:: endl;
                    return true;
                }
        }
    }
    return false;
}

bool Game::collision_treasure()
{
    for (float i = ACTOR.get_y() / 64; i < (ACTOR.get_y() + ACTOR.get_h()) / 64; i++)
    {
        for (float j = ACTOR.get_x() / 64; j < (ACTOR.get_x() + ACTOR.get_w()) / 64; j++)
        {
            if (Cur_level_treasure[int(i)][int(j)] == '1' || Cur_level_treasure[int(i)][int(j)] == '2' || Cur_level_treasure[int(i)][int(j)] == '3' || Cur_level_treasure[int(i)][int(j)] == '4')
                {
                    collision_loot = Cur_level_treasure[int(i)][int(j)];
                    Cur_level_treasure[int(i)][int(j)] = '0';
                    was_found = true;
                    return true;
                }
        }
    }
    return false;
}


void Game::show_hero()
{
    ACTOR.update_camera();
    window->setView(ACTOR.get_camera());
    window->draw(ACTOR.get_sprite());
}

void Game::show_map()
{
   for (int i = 0; i < MAP; i++)
        {
                for (int j = 0; j < MAP; j++)
                {
                    switch(Cur_level[i][j])
                    {
        // ЗЕМЛЯ
                    case '-':
                        tiles.get_sprite().setTextureRect(IntRect(0,1,70,70));
                        break;
        // КУСТ
                    case 'b':
                        tiles.get_sprite().setTextureRect(IntRect(68,1,70,70));
                        break;
        // ВОДА
                    case 'w':
                        tiles.get_sprite().setTextureRect(IntRect(138,1,70,70));
                        break;
        // ГЛУБОКАЯ ВОДА
                    case 'd':
                        tiles.get_sprite().setTextureRect(IntRect(209,1,70,70));
                        break;
        // ПЕСОК
                    case 's':
                        tiles.get_sprite().setTextureRect(IntRect(281,1,70,70));
                        break;
        // ДОРОГА
                    case 'r':
                        tiles.get_sprite().setTextureRect(IntRect(355,1,70,70));
                        break;
                    }

                    tiles.get_sprite().setPosition(j * 64, i * 64);

                    window->draw(tiles.get_sprite());
                }
        }
}

void Game::show_spawn()
{
   for (auto enemy : all_spawn)
        {
            enemy->get_sprite().setPosition(enemy->get_x(),enemy->get_y());
            window->draw(enemy->get_sprite());
        }
}

void Game::show_treasure()
{
     for (int i = 0; i < MAP; i++)
        {
                    for (int j = 0; j < MAP; j++)
                    {
                        if (Cur_level_treasure[i][j] != '1' && Cur_level_treasure[i][j] != '2' && Cur_level_treasure[i][j] != '3' && Cur_level_treasure[i][j] != '4')
                        {
                            tiles_treasure.get_sprite().setTextureRect(IntRect(0,0,0,0));
                        }
                        else
                        {
                            if (Cur_level_treasure[i][j] == '1')
                            {
                                tiles_treasure.get_sprite().setTextureRect(IntRect(0,0,48,48));
                            }
                            if (Cur_level_treasure[i][j] == '2')
                            {
                                tiles_treasure.get_sprite().setTextureRect(IntRect(48,0,48,48));
                            }
                            if (Cur_level_treasure[i][j] == '3')
                            {
                                tiles_treasure.get_sprite().setTextureRect(IntRect(96,0,48,48));
                            }
                            if (Cur_level_treasure[i][j] == '4')
                            {
                                tiles_treasure.get_sprite().setTextureRect(IntRect(144,0,34,48));
                            }
                        }

                            tiles_treasure.get_sprite().setPosition(j * 64, i * 64);
                        window->draw(tiles_treasure.get_sprite());
                    }
        }
}

void Game::update_battle()
{
    float distance;
    uint16_t counter = 0;
    for (auto enemy : all_spawn)
        {
            // НАЧАЛО БИТВЫ
            distance = sqrt((ACTOR.get_x() - enemy->get_x()) * (ACTOR.get_x() - enemy->get_x()) + (ACTOR.get_y() - enemy->get_y()) * (ACTOR.get_y() - enemy->get_y()));
            if (distance < 46)
            {
                this->number_battler = counter;
                ACTOR.set_freeze(true);
                set_all_freeze(true);
                this->is_battle = true;
                break;
            }
            counter++;
        }
}

void Game::check_attack()
{
    if (battle_timer.getElapsedTime().asMilliseconds() > 700 && was_attack)
    {
        std::cout << "ATTACK HERO" << std::endl;
        was_attack = false;
        ACTOR.set_health(ACTOR.get_health() - all_spawn[number_battler]->attack_actor(ACTOR.get_luck(), ACTOR.get_agility()));
    }
}

void Game::show_battle()
{
    if (ACTOR.get_health() < 0)
    {
//        ACTOR.set_dead(true);
//        this->end_battle();
    }
    if (all_spawn[number_battler]->get_health() > 0)
    {
        this->check_attack();
        this->show_battle_gui();
    }
    else
    {
        this->end_battle();
    }

}

void Game::show_battle_gui()
{
        actor_logo.get_sprite().setScale(1.5,1.5);
                all_spawn[number_battler]->get_logo().get_sprite().setScale(1.5,1.5);
        actor_logo.get_sprite().setPosition(ACTOR.get_camera().getCenter().x - 575  ,ACTOR.get_camera().getCenter().y  - 190) ;
       all_spawn[number_battler]->get_logo().get_sprite().setPosition(ACTOR.get_camera().getCenter().x + 50,ACTOR.get_camera().getCenter().y - 190);
        window->draw(actor_logo.get_sprite());
        window->draw(all_spawn[number_battler]->get_logo().get_sprite());

    points.setString(std::to_string(ACTOR.get_health()) + "/" + std::to_string(ACTOR.get_max_health()));
            points.setPosition(ACTOR.get_camera().getCenter().x - 500 ,ACTOR.get_camera().getCenter().y - 280);
    window->draw(points);

    points.setString(std::to_string(all_spawn[number_battler]->get_health()));
            points.setPosition(ACTOR.get_camera().getCenter().x + 310, ACTOR.get_camera().getCenter().y - 280);
    window->draw(points);


}

void Game::collision_paused(int X, int Y)
{
    if (X > 430 && X < 1130)
    {
        if (Y > 40 && Y < 270)
        {
            this->save_actor();
            window->setView(window->getDefaultView());
            saver.save_spawn(this->lvl,Cur_level_spawn);
            saver.save_treasure(this->lvl, Cur_level_treasure);
            all_spawn.clear();
            is_paused = false;
            is_settings = false;
            this->set_pause(false);
            inventory_items.clear();
            inventory_belt.clear();
            lvl = -1;
        }
        else if (Y > 335 && Y < 565)
        {
            is_settings = true;
        }
        else if (Y > 625 && Y < 860)
        {
            this->set_pause(false);
            is_paused = false;
        }
    }
}

void Game::collision_setting(int X, int Y)
{
    if (X > 1007 && X < 1120 && Y > 240 && Y < 280)
    {
        is_play_ambient = !is_play_ambient;
        if (is_play_ambient)
        {
            ambient.play_sound();
        }
        else
        {
            ambient.stop_sound();
        }
    }
    else if (X > 930 && X < 962)
    {
        if (Y > 320 && Y < 350 && volume_level_ambient)
        {
            volume_level_ambient -= 10;
            ambient.get_sound().setVolume(volume_level_ambient);
        }
        else if (Y > 395 && Y < 425 && volume_level)
        {
            volume_level -= 10;
            Listener::setGlobalVolume(volume_level);
        }
    }
    else if(X > 1155 && X < 1185)
    {
        if (Y > 320 && Y < 350 && volume_level_ambient < 100)
        {
            volume_level_ambient += 10;
            ambient.get_sound().setVolume(volume_level_ambient);
        }
        else if (Y > 395 && Y < 425 && volume_level < 100)
        {
            volume_level += 10;
            Listener::setGlobalVolume(volume_level);
        }
    }
}

void Game::collision_menu(int X, int Y)
{
    if (X > 500 && X < 1100)
    {
        if (Y > 150 && Y < 295)
        {
           //ambient.get_sound().stop();
           //ambient.set_sound("./gamedata/sounds/game/ambient_map");
           //ambient.play_sound();
           this->lvl = 0;
           this->load_actor();
        }
        if (Y > 325 && Y < 475)
        {
            this->lvl = 0;
            ACTOR.set_skills(1,1,1,1);
            ACTOR.set_level_points(8);
        }
        if (Y > 500 && Y < 645)
        {
            this->is_settings = true;
        }
        if (Y > 675 && Y < 825)
        {
            this->window->close();
        }

    }
}

void Game::add_item(Item* loot)
{
    found_item = loot->get_name();
    inventory_items.push_back(loot);
    std::sort(inventory_items.begin(), inventory_items.end(), [](Item* a, Item* b)
                         {return (a->get_name() > b->get_name());}
                         );
    item_number = inventory_items.size() - 1;
}

void Game::use_treasure()
{
    switch(collision_loot)
    {
    case '1':
        open_chest(4);
        treasures[0].play_sound();
        break;
    case '2':
        treasures[1].play_sound();
        open_chest(8);
        break;
    case '3':
        treasures[2].play_sound();
        open_chest(15);
        break;
    case '4':
        treasures[3].play_sound();
        add_item(new Magic_stone());
        break;
    }
}

void Game::open_chest(int rander)
{
    int rand_item = rand() % rander;
    found_timer.restart();

    std::cout << "rand = " << rand_item << '\n';
    switch(rand_item)
    {
    case 0:
        this->add_item(new Big_Health_potion());
        break;
    case 1:
        this->add_item(new Rune_granite());
        break;
    case 2:
        this->add_item(new Rune_crystal());
        break;
    case 3:
        this->add_item(new Rune_endurance());
        break;
    case 4:
        this->add_item(new Rune_strength());
        break;
    case 5:
        this->add_item(new Rune_agility());
        break;
    case 6:
        this->add_item(new Rune_luck());
        break;
    case 7: case 8: case 9:
        this->add_item(new Experience_potion());
        break;
    default:
        this->add_item(new Health_potion());
        break;
    }
    collision_loot = ' ';
}

void Game::choose_skill(bool side)
{
    std::cout << "skills_change" << std::endl;
    if(!side)
    {
        if (skill_number < 3)
        {
            skill_number++;
        }
    }
    else
    {
        if (skill_number)
        {
            skill_number--;
        }
    }
}
// ЛУСВ
void Game::add_skill()
{
    if (ACTOR.get_level_points())
    {
        switch(skill_number)
        {
            case 0:
                ACTOR.set_agility(ACTOR.get_agility() + 1);
                break;
            case 1:
                ACTOR.set_luck(ACTOR.get_luck() + 1);
                break;
            case 2:
                ACTOR.set_strength(ACTOR.get_strength() + 1);
                break;
            case 3:
                ACTOR.set_endurance(ACTOR.get_endurance() + 1);
                break;
        }
         ACTOR.set_level_points(ACTOR.get_level_points() - 1);
    }
    if (!ACTOR.get_level_points())
    {
        skill_number = -1;
    }

}

void Game::choose_belt(bool side)
{
    if (inventory_belt.size())
    {
        int8_t tmp_belt_number = belt_number;
        if (!side)
        {
            tmp_belt_number++;
        }
        else
        {
            tmp_belt_number--;
        }
        if (tmp_belt_number < inventory_belt.size() && tmp_belt_number > -1)
        {
            belt_number = tmp_belt_number;
        }
    std::cout << "CHOOSE ->" << belt_number << '\n';
    }
}

void Game::choose_item(bool side)
{
    if (inventory_items.size())
    {
          auto iter = inventory_items.begin() + item_number;
         uint8_t tmp_item_number = item_number;
        if (!side)
        {
            while((*iter)->get_name() == inventory_items[item_number]->get_name() && (iter != inventory_items.begin() + inventory_items.size() - 1))
            {
                iter++;
                tmp_item_number++;
            }
        }
        else
        {
            while((*iter)->get_name() == inventory_items[item_number]->get_name() && iter != inventory_items.begin())
            {
                iter--;
                tmp_item_number--;
            }
        }
        item_number = tmp_item_number;
        inventory_items[item_number]->set_need_sprite();
//        std::wcout << L"Номер итема-> "<< +item_number << std::endl;
//        std::wcout << L"длина итемов-> "<< inventory_items.size() << std::endl;
//        for (auto a: inventory_items[+item_number]->get_name())
//        {
//            std::wcout << a;
//        }
    }
}

bool Game::add_belt()
{
    if (inventory_items[item_number]->get_can_belt() && inventory_belt.size() < MAX_BELT)
    {
        inventory_items[item_number]->use(ACTOR);
        inventory_belt.push_back(inventory_items[item_number]);
        inventory_items.erase(inventory_items.begin() + item_number);
        item_number = inventory_items.size() - 1;
        return true;
    }
    return false;
}

void Game::add_belt_load(Item* rune)
{
    rune->use(ACTOR, 1);
    inventory_belt.push_back(rune);
}

void Game::pull_belt()
{
    if (inventory_belt.size())
    {
        this->add_item(inventory_belt[belt_number]);
        inventory_belt[belt_number]->re_use(ACTOR);
        inventory_belt.erase(inventory_belt.begin() + belt_number);
        belt_number = 0;
    }
}


void Game::show_founded_item()
{
    if (found_timer.getElapsedTime().asMilliseconds() < 1400)
    {
        uint16_t bebra = skills.getCharacterSize();
        skills.setCharacterSize(38);
        skills.setString(L"Найдено: " + found_item);
        skills.setPosition(ACTOR.get_camera().getCenter().x - 275, ACTOR.get_camera().getCenter().y - 345);
        window->draw(skills);
        skills.setCharacterSize(bebra);
    }
    else
    {
        this->was_found = false;
    }
}

void Game::show_use(int item)
{
        if (item != -1 && inventory_items.size() && inventory_items[item_number]->get_usable())
        {
            if (!add_belt() && !inventory_items[item_number]->get_can_belt())
            {
                inventory_items[item_number]->use(ACTOR);
                inventory_items.erase(inventory_items.begin() + item_number);
                item_number = inventory_items.size() - 1;
            }
            if (is_battle)
            {
                is_inventory = false;
                is_inventory_items = false;
                ACTOR.set_health(ACTOR.get_health() - all_spawn[number_battler]->attack_actor(ACTOR.get_luck(), ACTOR.get_agility()));

            }
        }
}

void Game::end_battle()
{
    std::cout << number_battler << std::endl;
    ACTOR.set_experience(all_spawn[number_battler]->get_experience() + ACTOR.get_experience());
    all_spawn.erase(all_spawn.begin() + number_battler);
    set_all_freeze(false);
    ACTOR.set_freeze(false);
    this->is_battle = false;
    was_attack = false;
    int counter_battler = -1;
    for (int i = 0; i < MAP; i++)
    {
        if (counter_battler == -2)
        {
            break;
        }
        for (int j = 0; j < MAP; j++)
        {
            if (Cur_level_spawn[i][j] == 'q')
            {
                counter_battler++;
            }
            if(counter_battler == number_battler)
            {
                Cur_level_spawn[i][j] = '-';
                counter_battler = -2;
                break;
            }

        }
    }
    this->number_battler = -1;
}

void Game::move_spawn()
{
    for (auto& enemy : all_spawn)
        {
            enemy->move_to_actor(ACTOR.get_x(), ACTOR.get_y(),this->delta / 4, get_tile_walk(enemy->get_x(), enemy->get_y()));
        }
}

void Game::set_all_freeze(bool frz)
{
    for (auto& enemy : all_spawn)
    {
        enemy->set_freeze(frz);
    }
}

void Game::show_cur_item()
{
    skills.setCharacterSize(18);
    skills.setString(inventory_items[item_number]->get_description());
    skills.setPosition(inv_tile.get_sprite().getPosition().x + 500,inv_tile.get_sprite().getPosition().y + 300);
    window->draw(skills);
    inventory_items[item_number]->set_need_sprite();
    inventory_items[item_number]->get_entity().get_sprite().setPosition(inv_tile.get_sprite().getPosition().x + 775,inv_tile.get_sprite().getPosition().y + 175);
    window->draw(inventory_items[item_number]->get_entity().get_sprite());

    skills.setCharacterSize(37);
}

void Game::show_belt()
{
    int x_adder = 55;
    for (auto& item: inventory_belt)
    {
        item->set_need_sprite();
        item->get_entity().get_sprite().setPosition(inv_tile.get_sprite().getPosition().x + 640 + x_adder,inv_tile.get_sprite().getPosition().y + 500);
        window->draw(item->get_entity().get_sprite());
        if (x_adder == (55 * (belt_number + 1)))
        {
            belt_choosen.get_sprite().setPosition(inv_tile.get_sprite().getPosition().x + 538 + x_adder,inv_tile.get_sprite().getPosition().y + 500);
            window->draw(belt_choosen.get_sprite());
        }
        x_adder += 55;
    }
}

void Game::show_inventory()
{
    // ОТРИСОВКА НАВЫКОВ
    inv_tile.get_sprite().setPosition(ACTOR.get_camera().getCenter().x - ACTOR.get_camera().getSize().x / 3.1f,
                                        ACTOR.get_camera().getCenter().y - ACTOR.get_camera().getSize().y / 2.8f);
    window->draw(inv_tile.get_sprite());
    if (!is_inventory_items)
    {
            skills.setString(L"ЛОВ");
            if (!skill_number)
            {
                skills.setColor(Color(150,240,140));

            }
                skills.setPosition(inv_tile.get_sprite().getPosition().x + 525,inv_tile.get_sprite().getPosition().y + 45);
            points.setString(std::to_string(ACTOR.get_agility()));
            points.setPosition(inv_tile.get_sprite().getPosition().x + 700,inv_tile.get_sprite().getPosition().y + 40);
        window->draw(skills);
    skills.setColor(Color(4,4,4));
        window->draw(points);

            skills.setString(L"УДЧ");
            if (skill_number == 1)
            {
                skills.setColor(Color(150,240,140));
            }
                skills.setPosition(inv_tile.get_sprite().getPosition().x + 525,inv_tile.get_sprite().getPosition().y + 120);
            points.setString(std::to_string(ACTOR.get_luck()));
            points.setPosition(inv_tile.get_sprite().getPosition().x + 700,inv_tile.get_sprite().getPosition().y + 115);
        window->draw(skills);
    skills.setColor(Color(4,4,4));
        window->draw(points);

            skills.setString(L"СИЛ");
            if (skill_number == 2)
            {
                skills.setColor(Color(150,240,140));
            }
                skills.setPosition(inv_tile.get_sprite().getPosition().x + 525,inv_tile.get_sprite().getPosition().y + 195);
            points.setString(std::to_string(ACTOR.get_strength()));
            points.setPosition(inv_tile.get_sprite().getPosition().x + 700,inv_tile.get_sprite().getPosition().y + 190);
        window->draw(skills);
    skills.setColor(Color(4,4,4));
        window->draw(points);

            skills.setString(L"ВНС");
            if (skill_number == 3)
            {
                skills.setColor(Color(150,240,140));
            }
                skills.setPosition(inv_tile.get_sprite().getPosition().x + 525,inv_tile.get_sprite().getPosition().y + 270);
            points.setString(std::to_string(ACTOR.get_endurance()));
            points.setPosition(inv_tile.get_sprite().getPosition().x + 700,inv_tile.get_sprite().getPosition().y + 265);
        window->draw(skills);
    skills.setColor(Color(4,4,4));
        window->draw(points);
        //-----------------------------------------------------------------------------------------------------------------

        // ОТРИСОВКА ЗДОРОВЬЯ И ОПЫТА
        skills.setCharacterSize(45);
        points.setCharacterSize(55);

        skills.setString(L"ОЗ");
            skills.setPosition(inv_tile.get_sprite().getPosition().x + 60,inv_tile.get_sprite().getPosition().y + 50);
        window->draw(skills);

        skills.setString(L"ОО");
            skills.setPosition(inv_tile.get_sprite().getPosition().x + 60,inv_tile.get_sprite().getPosition().y + 100);
        window->draw(skills);

        skills.setString(L"ОУ");
            skills.setPosition(inv_tile.get_sprite().getPosition().x + 60,inv_tile.get_sprite().getPosition().y + 150);
        window->draw(skills);

        points.setString(std::to_string(ACTOR.get_health()) + "/" + std::to_string(ACTOR.get_max_health()));
                points.setPosition(inv_tile.get_sprite().getPosition().x + 140,inv_tile.get_sprite().getPosition().y + 40);
        window->draw(points);

        points.setString(std::to_string(ACTOR.get_experience()) + "/" + std::to_string(ACTOR.get_max_experience()));
                points.setPosition(inv_tile.get_sprite().getPosition().x + 140,inv_tile.get_sprite().getPosition().y + 90);
        window->draw(points);

        points.setString(std::to_string(ACTOR.get_damage()));
                points.setPosition(inv_tile.get_sprite().getPosition().x + 140,inv_tile.get_sprite().getPosition().y + 140);
        window->draw(points);
        if (ACTOR.is_boring())
        {
            points.setCharacterSize(65);
            skills.setString(L"УСТАЛОСТЬ");
                skills.setPosition(inv_tile.get_sprite().getPosition().x + 60,inv_tile.get_sprite().getPosition().y + 260);
            window->draw(skills);
        }
        points.setCharacterSize(77);
        //----------------------------------------------------------------------------------------------------------------

        // Количество свободных очков
        skills.setCharacterSize(48);
            skills.setString(L"Очков умений");
            skills.setPosition(inv_tile.get_sprite().getPosition().x + 490,inv_tile.get_sprite().getPosition().y + 430);
        points.setString(std::to_string(ACTOR.get_level_points()));
                points.setPosition(inv_tile.get_sprite().getPosition().x + 840,inv_tile.get_sprite().getPosition().y + 410);
        window->draw(skills);
        window->draw(points);

        skills.setCharacterSize(75);
    }
    else
    {
        skills.setCharacterSize(37);
        int y_adder = 25;
        this->show_cur_item();
        this->show_belt();
        for (auto item: inventory_items)
        {
            inventory_items_counter[item->get_name()]++;
        }

        for (auto [name, count]: inventory_items_counter)
        {
            if (name == inventory_items[item_number]->get_name())
            {
                skills.setColor(Color(150,240,140));
            }
            skills.setString(name + " " + std::to_string(count));
                skills.setPosition(inv_tile.get_sprite().getPosition().x + 38,inv_tile.get_sprite().getPosition().y + y_adder);
            window->draw(skills);
            skills.setColor(Color(4,4,4));
            y_adder += 50;
        }
        inventory_items_counter.clear();
        skills.setCharacterSize(75);
    }
}



// Обновление на время затраченное на рендер одного кадра
void Game::updateDelta()
{
    this->delta = this->clock.restart().asMilliseconds();
}


void Game::update()
{
    this->updateEvents();

}
void Game::render()
{
    this->window->display();
}


// ЗАПУСК
void Game::run()
{
    this->is_save_file = loader.is_file_actor();
    this->battle_timer.restart().asMilliseconds();
    this->found_timer.restart().asMilliseconds();
    while(this->window->isOpen())
    {
        this->updateDelta();
        this->clock.restart();
        this->window->clear();
        if (lvl > -1)
        {
            if (lvl)
            {
                this->show_map();
                this->show_treasure();
                this->move_spawn();
                this->show_hero();
                this->show_spawn();
                if (this->number_battler == -1)
                {
                    this->update_battle();
                }
                else
                {
                    this->show_battle();
                }
                if (is_inventory)
                {
                    this->show_inventory();
                }

                if (is_paused && !is_settings)
                {
                    pause.show(ACTOR.get_camera().getCenter().x, ACTOR.get_camera().getCenter().y);
                }
                if (was_found)
                {
                    this->show_founded_item();
                }
            }
            else
            {
                game_map.show(0,0);
            }

        }
        else
        {
            menu.show(0,0, is_save_file, is_settings);
        }
        if (is_settings)
        {
            settings.show(ACTOR.get_camera().getCenter().x, ACTOR.get_camera().getCenter().y, (lvl == -1),
                         is_play_ambient, volume_level, volume_level_ambient);
        }
        this->update();
        this->render();
    }
}

