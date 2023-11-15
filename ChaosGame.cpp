//Partner: Francis Bae
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Chaos Game", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    vector<Color> colors = {
        Color::Green,
        Color::Red,
        Color::Green,
    };

    int currentColorIndex = 0;

    Font font;
    if (!font.loadFromFile("Cheese Cake.ttf"))
    {
        cerr << "Error loading font\n";
        return -1;
    }

    Text text;
    text.setFont(font);
    text.setCharacterSize(48);
    text.setFillColor(Color::Green);
    text.setPosition(10, 10);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    cout << "Mouse x: " << event.mouseButton.x << " Mouse y: " << event.mouseButton.y << endl;
                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (points.size() > 0)
        {
            for (int i = 0; i < 10; i++) 
            {
                int randomVertexIndex = rand() % vertices.size();
                Vector2f randomVertex = vertices[randomVertexIndex];
                Vector2f midpoint = (randomVertex + points.back()) / 2.0f;
                points.push_back(midpoint);
            }
        }

        window.clear();

        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Yellow);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++)
        {
            CircleShape circle(2);
            circle.setPosition(points[i]);
            circle.setFillColor(colors[currentColorIndex]);
            currentColorIndex = (currentColorIndex + 1) % colors.size();             
            window.draw(circle);
           
        }

        text.setString("Create a Christmas tree light show! Select three points and a fourth within!");
        window.draw(text);

        window.display();
    }

    return 0;
}