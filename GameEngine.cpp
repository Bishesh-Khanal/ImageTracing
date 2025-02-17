#include "GameEngine.h"
#include "Scene.h"
#include "ScenePlay.h"
#include <fstream>
#include <sstream>

GameEngine::GameEngine()
{
    std::cout << "Created the game engine" << std::endl;
    init("bin/assets.txt");
}

void GameEngine::init(const std::string& path)
{
    std::ifstream myFiles(path);
    if (!myFiles.is_open())
    {
        std::cerr << "Failed to open the file: " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(myFiles, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream lineStream(line);
        std::string assetType, nameAsset, pathAsset;
        size_t frameCount;
        float animationSpeed;

        if (lineStream >> assetType >> nameAsset >> pathAsset >> frameCount >> animationSpeed)
        {
            if (assetType == "Texture")
            {
                getAssets().addTexture(nameAsset, pathAsset);
            }
            else if (assetType == "Animation")
            {
                getAssets().addAnimations(nameAsset, Animation(nameAsset, getAssets().getTexture(pathAsset), frameCount, animationSpeed));
            }
        }
        else
        {
            std::cerr << "Malformed line" << std::endl;
        }
    }

    m_window.create(sf::VideoMode::getDesktopMode(), "Image Tracing", sf::Style::Default);
    m_width = m_window.getSize().x;
    m_worldWidth = m_window.getSize().x;
    m_height = m_window.getSize().y;
    m_window.setFramerateLimit(60);

    std::cout << "Game engine initialized successfully." << std::endl;
}


void GameEngine::run(const std::shared_ptr<GameEngine>& game)
{
    std::cout << "Running the game engine" << std::endl;
    changeScene("PLAY", std::make_shared<ScenePlay>(game));

    while (m_running)
    {
        update();
        sUserInput();
        currentScene()->sRender();

        currentScene()->m_currentFrame++;
    }
}

const std::shared_ptr<Scene>& GameEngine::currentScene()
{
    return m_scenes[m_currentScene];
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene)
{
    m_scenes[sceneName] = scene;
    m_currentScene = sceneName;
}

void GameEngine::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
            m_window.close();
        }

        auto mousePos = sf::Mouse::getPosition(m_window);
        Vec2 mpos(mousePos.x, mousePos.y);

        if (event.type == sf::Event::MouseMoved)
        {
            currentScene()->doAction(Action("MOUSE_MOVE", "START", Vec2(event.mouseMove.x, event.mouseMove.y)));
        }
    }
}

void GameEngine::update()
{
    currentScene()->update();
}

Assets& GameEngine::getAssets()
{
    return m_assets;
}

void GameEngine::quit()
{
    m_running = false;
    m_window.close();
}