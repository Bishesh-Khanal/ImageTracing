#include "GameEngine.h"

int main()
{
    
    std::shared_ptr<GameEngine> game = std::make_shared<GameEngine>();
    game->run(game);
    

    /*
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arbitrary Shape with Mapped Texture");

    // Load the texture
    sf::Texture texture;
    if (!texture.loadFromFile("bin/Images/pokemon2.png")) {
        std::cerr << "Error: Could not load texture!" << std::endl;
        return -1;
    }
    texture.setSmooth(true);

    sf::Sprite sprite(texture);
    Vec2 mSize(texture.getSize().x, texture.getSize().y);
    sprite.setOrigin(mSize.x/2, mSize.y/ 2);
    sprite.setPosition(400, 300);

    // Define an arbitrary shape in screen space
    std::vector<sf::Vector2f> screenShape = {
        {sprite.getPosition().x - mSize.x / 2, sprite.getPosition().y - mSize.y / 2}, {sprite.getPosition().x, sprite.getPosition().y - mSize.y / 2}, { sprite.getPosition().x + mSize.x / 2, sprite.getPosition().y }, { sprite.getPosition().x - mSize.x / 2, sprite.getPosition().y }  // 6 vertices
    };

    // Define the corresponding arbitrary shape in texture space
    std::vector<sf::Vector2f> textureShape = {
        {0, 0}, {mSize.x / 2, 0}, {mSize.x, mSize.y / 2}, { 0, mSize.y / 2 }  // Must match the structure of screenShape
    };

    // Triangulate and generate vertex array
    sf::VertexArray triangles = triangulate(screenShape, textureShape);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (auto& pointScreen : screenShape)
        {
            sf::CircleShape point(4);
            point.setPosition(pointScreen.x, pointScreen.y);
            point.setFillColor(sf::Color::Green);
            point.setOrigin(2, 2);
            window.draw(point);
        }

        // Render the triangulated polygon
        sf::RenderStates states;
        states.texture = &texture;
        window.draw(triangles, states);
        //window.draw(sprite);

        window.display();
    }
    */

    return 0;
}
