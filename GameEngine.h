#pragma once
#include "Assets.h"

class Scene;

typedef std::map<std::string, std::shared_ptr<Scene>> Scenes;

class GameEngine
{
	friend class SceneMenu;
	friend class ScenePlay;

	Scenes					m_scenes;
	sf::RenderWindow		m_window;
	Assets					m_assets;
	std::string				m_currentScene;
	size_t					m_simulationSpeed = 1;
	bool					m_running = true;
	float					m_width;
	float					m_height;
	float					m_worldWidth;

	void init(const std::string&);
	const std::shared_ptr<Scene>& currentScene();
	void update();

	Assets& getAssets();
	void changeScene(const std::string&, std::shared_ptr<Scene>);

	void sUserInput();

public:
	GameEngine();
	void run(const std::shared_ptr<GameEngine>&);
	void quit();
};