//#include <SFML/Graphics.hpp>
//#include <iostream>
//using namespace sf;
//
//void params(int WIDTH, int HEIGHT,int left, int right, double step, double A,RenderWindow& window)
//{
//    int MiddleX, MiddleY;
//    int KeyX = 0, KeyY = 0;
//
//    // Ћинии по иксу
//    for (int i = 0; i < WIDTH; i += WIDTH / 40)
//    {
//
//        Vertex line[] =
//        {
//            Vertex(Vector2f(i,0)),
//            Vertex(Vector2f(i,HEIGHT)),
//        };
//        window.draw(line,2,Lines);
//        if (i >= WIDTH / 2 && KeyX == 0)
//        {
//            KeyX++;
//            MiddleX = i;
//        }
//    }
//    // Ћинии по игреку
//    for (int i = 0; i < HEIGHT; i += HEIGHT / 40)
//    {
//        Vertex line[] =
//        {
//            Vertex(Vector2f(0,i)),
//            Vertex(Vector2f(WIDTH,i)),
//        };
//        window.draw(line,2,Lines);
//        if (i >= HEIGHT / 2 && KeyY == 0)
//        {
//            KeyY++;
//            MiddleY = i;
//        }
//    }
//
//
//    Vertex OX[] =
//    {
//        Vertex(Vector2f(0,MiddleY), Color::Black),
//        Vertex(Vector2f(WIDTH,MiddleY), Color::Black),
//    };
//    window.draw(OX,2,Lines);
//    // ќ—№ Y
//    Vertex OY[] =
//    {
//        Vertex(Vector2f(MiddleX,0), Color::Black),
//        Vertex(Vector2f(MiddleX, HEIGHT), Color::Black),
//    };
//
//    window.draw(OY,2,Lines);
//    double x = left;
//    while (x < right)
//    {
//        double Xgraph = MiddleX + x;
//        double Ygraph = MiddleY - A * x * x * x;
//
//        if (x != left)
//        {
//            double x_tmp = x - step;
//            Vertex line[]
//            {
//                Vertex(Vector2f(Xgraph, MiddleY - A * x_tmp * x_tmp * x_tmp), Color::Red),
//                Vertex(Vector2f(Xgraph + step, Ygraph), Color::Red),
//            };
//            window.draw(line,2,Lines);
//        }
//        x += step;
//    }
//}
//
//int main()
//{
//    setlocale(0, "");
//    int WIDTH = 800;
//    int HEIGHT = 800;
//
//    double step;
//    double A;
//    int left;
//    int right;
//
//
//    do
//    {
//    std::cout << "¬ведите левую границу: ";
//        std::cin >> left;
//    std::cout << "¬ведите правую границу: ";
//        std::cin >> right;
//    } while (right <= left);
//    do
//    {
//        std::cout << "¬ведите шаг построени€: ";
//            std::cin >> step;
//    } while (step <= 0.0001 || step > abs(left) + abs(right));
//
//    std::cout<< "¬ведите коэффициент A: ";
//        std::cin >> A;
//
//    RenderWindow window(VideoMode(WIDTH, HEIGHT), "√рафик");
//    window.setFramerateLimit(60);
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
//        window.clear(Color(175,190,35));
//        params(WIDTH,HEIGHT,left,right,step,A,window);
//        window.display();
//    }
//
//    return 0;
//}
