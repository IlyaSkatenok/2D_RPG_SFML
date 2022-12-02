#pragma once
#include <SFML/Audio.hpp>
using namespace sf;
class Sounding
{
protected:
    SoundBuffer buffer;
    Sound sound;
public:
    Sounding();
    Sounding(String name);
    virtual ~Sounding();
    void set_sound(String name = "./gamedata/sounds/items/Eat");
    void play_sound();
    void stop_sound();
    Sound& get_sound();
};
