#pragma once
#ifndef SCENEPLAY_H
#define SCENEPLAY_H

#include "Scene.h"

class ScenePlay :public Scene
{
private:
	std::string				m_levelPath;
	std::shared_ptr<Entity>	m_player;
	const Vec2				m_gridSize = { 64, 64 };
	sf::Text				m_gridText;
	Vec2					m_mPos;
	sf::CircleShape			m_mShape;
	struct Intersect
	{
		bool result;
		Vec2 pos;
		std::vector<Vec2> intersections;
	};
	std::vector<Vec2> m_IntersectedPoints;
	std::vector<Vec2> m_VerticesTarget;
	std::vector<Vec2> m_TexturePoints;

	std::shared_ptr<Entity> target;


	void init();

	void onEnd()							override;
	void update()							override;
	void sRender()							override;
	void sDoAction(const Action&)			override;

	void sAnimation();

	void enemySpawner(std::vector<std::vector<int>>, const sf::Color&);
	void addInterSectionPoints(const Vec2&, const Vec2&);
	void checkVerticesTarget(const Vec2&);
	Intersect intersection(const Vec2&, const Vec2&);
	Intersect checkIntersectionTarget(const Vec2&, const std::vector<Vec2>&) const;
	Vec2 increament(float, const Vec2&, const Vec2&);

public:
	ScenePlay(std::shared_ptr<GameEngine>);
};

#endif