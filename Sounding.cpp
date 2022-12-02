#include "Sounding.h"
Sounding::Sounding()
{

}

Sounding::Sounding(String name)
{
    buffer.loadFromFile(name + ".ogg");
    sound.setBuffer(buffer);
}

void Sounding::set_sound(String name)
{
    if (!sound.getBuffer())
    {
        buffer.loadFromFile(name + ".ogg");
        sound.setBuffer(buffer);
    }
}

Sounding::~Sounding()
{

}

void Sounding::play_sound()
{
    sound.play();
}

void Sounding::stop_sound()
{
    sound.stop();
}

Sound& Sounding::get_sound()
{
    return sound;
}

