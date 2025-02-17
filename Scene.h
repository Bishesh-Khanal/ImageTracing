#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <memory>

#include "Action.h"
#include "EntityManager.h"

class GameEngine;

class Scene
{
protected:
	friend class GameEngine;

	std::shared_ptr<GameEngine>		m_game;
	EntityManager					m_entities;
	int								m_currentFrame = 0;
	bool							m_hasEnded = false;

	virtual void update() = 0;
	virtual void sRender() = 0;
	virtual void sDoAction(const Action&) = 0;
	virtual void onEnd() = 0;

	size_t width() const;
	size_t height() const;
	size_t currentFrame() const;

	void doAction(const Action&);
public:
	Scene(std::shared_ptr<GameEngine>);
	virtual ~Scene() = default;
};

#endif