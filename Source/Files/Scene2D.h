#pragma once

#ifndef SCENE_2D_H_
#define SCENE_2D_H_

#include <Component/SimpleScene.h>
#include <string>
#include <list>
#include <Core/Engine.h>

#include "GameObject.h"
#include "Player.h"
#include "Powerup.h"
#include "Projectile.h"
#include "Enemy.h"
#include "GameInstance.h"



class Scene2D : public SimpleScene {

public:
	struct ViewportSpace {
		ViewportSpace() : x(0), y(0), width(1), height(1) {}
		ViewportSpace(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height) {}
		int x;
		int y;
		int width;
		int height;
	};

	struct LogicSpace {
		LogicSpace() : x(0), y(0), width(1), height(1) {}
		LogicSpace(float x, float y, float width, float height)
			: x(x), y(y), width(width), height(height) {}
		float x;
		float y;
		float width;
		float height;
	};

public:
	Scene2D();
	~Scene2D();

	void		Init() override;

private:

	void		FrameStart() override;
	void		Update(float deltaTimeSeconds) override;
	void		FrameEnd() override;

	void		DrawScene(glm::mat3 visMatrix,float deltaTimeSeconds);
	void		RenderLivesIndicator(int how_many);

	void		OnInputUpdate(float deltaTime, int mods) override;	
	void		OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void		OnKeyPress(int key, int mods) override;
	
		
	glm::mat3	VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
	void		SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

	void		DrawScreenFrozen(glm::mat3 vis_matrix);
	void		RenderObject(GameObject &object);

protected:
	
	glm::mat3							vis_matrix;
	glm::vec3							background_color;

	std::unique_ptr<ViewportSpace>		view_space_ptr;
	std::unique_ptr<LogicSpace>			logic_space_ptr;

	std::unique_ptr<GameInstance>		game_instance;
};

#endif /* SCENE_2D_H_ */