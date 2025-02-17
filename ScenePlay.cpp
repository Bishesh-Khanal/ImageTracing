#include "ScenePlay.h"
#include "GameEngine.h"

#include <fstream>
#include <sstream>

void ScenePlay::init()
{
	std::cout << "Game started" << std::endl;
	std::cout << m_game->m_width << " " << m_game->m_height << std::endl;
	std::vector<std::vector<int>> pos;
	pos = { { 0, 0 }, { 0, static_cast<int>(m_game->m_height) }, { static_cast<int>(m_game->m_width), static_cast<int>(m_game->m_height) }, { static_cast<int>(m_game->m_width), 0 } };
	enemySpawner(pos, sf::Color::Black);
	pos = { { 100, 100 }, { 450, 110 }, { 620,390 }, { 430, 400 }, { 300, 350 } };
	enemySpawner(pos, sf::Color(192, 192, 192));
	pos = { { 600, 800 }, { 950, 810 }, { 1120,1090 }, { 930, 1100 }, { 800, 1050 } };
	enemySpawner(pos, sf::Color(192, 192, 192));
	pos = { { 970, 400 }, { 1320, 410 }, { 1490,690 }, { 1300, 700 }, { 1170, 650 } };
	enemySpawner(pos, sf::Color(192, 192, 192));
	pos = { { 1350, 100 }, { 1700, 110 }, { 1870,390 }, { 1680, 400 }, { 1550, 350 } };
	enemySpawner(pos, sf::Color(192, 192, 192));
}

void ScenePlay::enemySpawner(std::vector<std::vector<int>> pos, const sf::Color& color)
{
	auto entity = m_entities.addEntity("enemy");

	entity->addComponent<CShape>(pos.size(), pos, color);

	//m_player = entity;
}


ScenePlay::ScenePlay(std::shared_ptr<GameEngine> game)
	: Scene(std::move(game))
{
	init();
}

void ScenePlay::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		if (action.name() == "MOUSE_MOVE")
		{
			m_mPos = action.pos();
			m_mShape.setPosition(m_mPos.x, m_mPos.y);
		}
	}

	if (action.type() == "END")
	{
	}
}

void ScenePlay::update() {
	m_entities.update();
}


void ScenePlay::onEnd()
{
	for (auto& entity : m_entities.getEntities())
	{
		entity->destroy();
	}
	m_game->quit();
}

ScenePlay::Intersect ScenePlay::intersection(const Vec2& a, const Vec2& b)
{
	Vec2 r = b - a;
	Vec2 c, d;

	std::vector<Vec2> intersectionPoints(0);

	for (auto& entity : m_entities.getEntities())
	{
		auto& shapeComponent = entity->getComponent<CShape>();
		auto& convexShape = shapeComponent.convex;

		if (shapeComponent.size <= 0) continue; // Safety check

		for (int i = 0; i < shapeComponent.size; i++)
		{
			c = Vec2(convexShape.getPoint(i).x, convexShape.getPoint(i).y);
			d = Vec2(convexShape.getPoint((i + 1) % shapeComponent.size).x, convexShape.getPoint((i + 1) % shapeComponent.size).y);
			Vec2 s = d - c;
			float rxs = r.x * s.y - r.y * s.x;

			if (rxs == 0) continue; // Parallel lines

			Vec2 cma = c - a;
			float t = (cma.x * s.y - cma.y * s.x) / rxs;
			float u = (cma.x * r.y - cma.y * r.x) / rxs;
			if ((t > 0 && t < 1) && (u > 0 && u < 1))
			{
				//return { true, Vec2(a.x + t * r.x, a.y + t * r.y) };
				intersectionPoints.push_back(Vec2(a.x + t * r.x, a.y + t * r.y));
			}
		}
	}
	size_t size = intersectionPoints.size();
	if (size != 0)
	{
		for (int i = 0; i < size - 1; ++i)
		{
			bool swapped = false;
			for (int j = 0; j < size - i - 1; ++j)
			{
				if (a.distq(intersectionPoints[j]) > a.distq(intersectionPoints[j + 1]))
				{
					std::swap(intersectionPoints[j], intersectionPoints[j + 1]);
					swapped = true;
				}
			}
			if (!swapped)
			{
				break;
			}
		}
		return { true, intersectionPoints[0] };
	}
	return { false, Vec2(0, 0) };
}

Vec2 ScenePlay::increament(float angle, const Vec2& mousePos, const Vec2& position)
{
	Vec2 p = position + Vec2(cos(angle), sin(angle));
	ScenePlay::Intersect intersectResult = intersection(mousePos, p);

	if (position.distq(mousePos) > 10000000) {
		return position;
	}


	if (!intersectResult.result)
	{
		return increament(angle, mousePos, p);
	}
	else {
		return intersectResult.pos;
	}
}

void ScenePlay::sRender()
{
	m_game->m_window.clear();

	Vec2 mousePos(m_mShape.getPosition().x, m_mShape.getPosition().y);

	for (auto& e : m_entities.getEntities())
	{
		auto& shapeComponent = e->getComponent<CShape>();
		auto& convexShape = shapeComponent.convex;
		m_game->m_window.draw(convexShape);

		int maxPoints = std::min(shapeComponent.size, convexShape.getPointCount());
		for (int i = 0; i < maxPoints; i++)
		{
			Vec2 vertex(convexShape.getPoint(i).x, convexShape.getPoint(i).y);
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(mousePos.x, mousePos.y), sf::Color::Red),
				sf::Vertex(sf::Vector2f(vertex.x, vertex.y), sf::Color::Red)
			};

			ScenePlay::Intersect intersectResult = intersection(mousePos, vertex);
			if (!intersectResult.result)
			{
				float vertexAngle = vertex.angle(mousePos);

				m_IntersectedPoints.emplace_back(vertex);
				//m_game->m_window.draw(line, 2, sf::Lines);

				Vec2 neighbour(increament(vertexAngle - 0.000349, mousePos, mousePos));
				m_IntersectedPoints.emplace_back(neighbour);

				neighbour = increament(vertexAngle + 0.000349, mousePos, mousePos);
				m_IntersectedPoints.emplace_back(neighbour);
			}
			else
			{
				m_IntersectedPoints.emplace_back(intersectResult.pos);
			}
		}
	}


	size_t size = m_IntersectedPoints.size();
	std::sort(m_IntersectedPoints.begin(), m_IntersectedPoints.end(),
		[&](const Vec2& a, const Vec2& b) {
			return a.angle(mousePos) < b.angle(mousePos);
		});

	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setFillColor(sf::Color::White);

	for (size_t k = 0; k < size; ++k)
	{
		triangle.setPoint(0, sf::Vector2f(mousePos.x, mousePos.y));
		triangle.setPoint(1, sf::Vector2f(m_IntersectedPoints[k].x, m_IntersectedPoints[k].y));
		triangle.setPoint(2, sf::Vector2f(m_IntersectedPoints.at((k + 1) % size).x, m_IntersectedPoints.at((k + 1) % size).y));
		m_game->m_window.draw(triangle);
	}

	m_IntersectedPoints.clear();


	m_mShape.setFillColor(sf::Color::Red);
	m_mShape.setRadius(10);
	m_mShape.setOrigin(5, 5);

	m_mShape.setPosition(m_mPos.x, m_mPos.y);
	m_game->m_window.draw(m_mShape);

	m_game->m_window.display();
}

/*
	sf::CircleShape point(4);
	point.setPosition(intersectionPoint.x, intersectionPoint.y);
	point.setFillColor(sf::Color::Green);
	point.setOrigin(2, 2);
	m_game->m_window.draw(point);
*/