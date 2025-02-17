#include "Scene.h"
#include "GameEngine.h"

Scene::Scene(std::shared_ptr<GameEngine> game)
	:m_game(std::move(game))
{
}

void Scene::doAction(const Action& action)
{
	sDoAction(action);
}