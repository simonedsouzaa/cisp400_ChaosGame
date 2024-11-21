//Simone and Mildred
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);
    
    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Load the font for text
    Font font;
    if (!font.loadFromFile("Arial.ttf"))  // Replace with the correct path if necessary
    {
        cout << "Error loading font" << endl;
        return -1;
    }

    // Set up text to display instructions
    Text instructions("Click on 3 points for triangle vertices", font, 30);
    instructions.setPosition(10, 10);
    instructions.setFillColor(Color::White);

    Text prompt("then click on 4th point to start", font, 30);
    prompt.setPosition(10, 50);
    prompt.setFillColor(Color::White);

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the player's input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "The left button was pressed" << endl;
                    cout << "Mouse X: " << event.mouseButton.x << endl;
                    cout << "Mouse Y: " << event.mouseButton.y << endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (vertices.size() == 3 && points.size() == 0)
                    {
                        // Storing  4th click as the starting point
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0)
        {
            // generate more points for the chaos game algorithm
            Vector2f lastPoint = points.back();
	    //select random vertex
            int randomVertexIndex = rand() % 3;  
            Vector2f randomVertex = vertices[randomVertexIndex];
            
            // calculate midpoint between random vertex and last point
            Vector2f newPoint = (lastPoint + randomVertex) / 2.f;
	    //push back the newly generated coord.
            points.push_back(newPoint);
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        // Draw the vertices as blue squares
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(vertices[i]);
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        // Draw the chaos game points as red circles
        for (size_t i = 0; i < points.size(); ++i)
        {
            RectangleShape pointShape(Vector2f(2, 2));  // Smaller red dots
            pointShape.setPosition(points[i]);
            pointShape.setFillColor(Color::Red);
            window.draw(pointShape);
        }

        // Draw all prompts and instructions
        window.draw(instructions);
        window.draw(prompt);

        window.display();
    }

    return 0;
}
