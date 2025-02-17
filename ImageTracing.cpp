#include "GameEngine.h"

int main()
{
    
    std::shared_ptr<GameEngine> game = std::make_shared<GameEngine>();
    game->run(game);
    

    /*
    sf::RenderWindow window(sf::VideoMode(800, 600), "Image Tracing");

    // Load the texture
    sf::Texture texture;
    if (!texture.loadFromFile("bin/Images/pokemon.png")) {
        return -1; // Handle error
    }

    // Create a vertex array with 4 vertices (Quad)
    sf::VertexArray quad(sf::Quads, 4);

    // Define the quad vertices in world space (screen coordinates)
    quad[0].position = sf::Vector2f(100, 100);  // Top-left
    quad[1].position = sf::Vector2f(300, 120);  // Top-right
    quad[2].position = sf::Vector2f(280, 300);  // Bottom-right
    quad[3].position = sf::Vector2f(120, 280);  // Bottom-left

    // Define texture coordinates (the part of the texture to be displayed)
    quad[0].texCoords = sf::Vector2f(50, 50);   // Corresponding top-left texture coordinate
    quad[1].texCoords = sf::Vector2f(200, 60);  // Top-right texture coordinate
    quad[2].texCoords = sf::Vector2f(190, 200); // Bottom-right texture coordinate
    quad[3].texCoords = sf::Vector2f(60, 190);  // Bottom-left texture coordinate

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw the quad with the texture
        sf::RenderStates states;
        states.texture = &texture;  // Apply the texture
        window.draw(quad, states);

        window.display();
    }
    */


    return 0;
}
