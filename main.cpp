//#include <SFML/Graphics.hpp>
//
//using namespace sf;
//
//int main()
//{
//    RenderWindow window(VideoMode(800, 600), "аћср");
//    window.setFramerateLimit(60);
//
//    Texture fish_texture;
//    fish_texture.loadFromFile("lab1.png");
//
//    Sprite fish_sprite;
//    fish_sprite.setTexture(fish_texture);
//    fish_sprite.setPosition(300,200);
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear(Color(100,100,250));
//        window.draw(fish_sprite);
//        window.display();
//    }
//
//    return 0;
//}
