#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

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

    Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        cout << "Error loading font" << endl;
        return -1;
    }

    // Set up text to display instructions
    Text instructions("Click on 3 points to set the triangle vertices.", font, 30);
    instructions.setPosition(10, 10);
    instructions.setFillColor(Color::White);

    Text prompt("Click on a 4th point to start the algorithm.", font, 30);
    prompt.setPosition(10, 50);
    prompt.setFillColor(Color::White);

    // To track whether the prompt has been shown
    bool promptDisplayed = false;  

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
                    else if (vertices.size() == 3 && !promptDisplayed)
                    {
                        // Show the prompt after the 3rd vertex is clicked
                        promptDisplayed = true;
                    }
                    else if (points.size() == 0 && promptDisplayed)
                    {
                        // Store the 4th click as the starting point for the chaos game
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
            // Generate more points for the chaos game algorithm
            Vector2f lastPoint = points.back();
			// Randomly select one of the 3 vertices
            int randomVertexIndex = rand() % 3;  
            Vector2f randomVertex = vertices[randomVertexIndex];
            
            // Calculate midpoint between random vertex and last point
            Vector2f newPoint = (lastPoint + randomVertex) / 2.f;
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
			// Smaller red dots
            RectangleShape pointShape(Vector2f(2, 2));  
            pointShape.setPosition(points[i]);
            pointShape.setFillColor(Color::White);
            window.draw(pointShape);
        }

        // Draw the instructions and prompt texts
        window.draw(instructions);
        if (promptDisplayed)
        {
            window.draw(prompt);
        }

        window.display();
    }

    return 0;
}
