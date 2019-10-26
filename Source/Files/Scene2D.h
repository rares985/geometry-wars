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



class Scene2D : public SimpleScene
{
	public:
		struct ViewportSpace
		{
			ViewportSpace() : x(0), y(0), width(1), height(1) {}
			ViewportSpace(int x, int y, int width, int height)
				: x(x), y(y), width(width), height(height) {}
			int x;
			int y;
			int width;
			int height;
		};

		struct LogicSpace
		{
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

		void Init() override;

	private:

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void DrawScene(glm::mat3 visMatrix,float deltaTimeSeconds);

		void OnInputUpdate(float deltaTime, int mods) override;
		
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	
		
		glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

		void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

		void spawnEnemies();

		void freezeScreen(glm::mat3 visMatrix);

		void spawnPowerup();

	protected:
		ViewportSpace view_space;
		LogicSpace logic_space;
		glm::mat3 vis_matrix;
		glm::vec3 background_color;

		Player* player;
		std::list<Enemy*> enemies;
		std::list<Projectile*> projectiles;
		std::list<Powerup*> powerups;

		GameInstance* game_instance;

		float time_elapsed;
		float enemy_spawn_timer;
		float enemy_spawn_threshold;
		float powerup_spawn_timer;
		float powerup_spawn_threshold;
		float freeze_timer;

		bool freeze_enemies;
};

#endif /* SCENE_2D_H_ */
