#include <iostream>
#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow m_window(sf::VideoMode(800, 800), "Test");
    sf::Event event;
    while (m_window.isOpen())
    {
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }
    }
}