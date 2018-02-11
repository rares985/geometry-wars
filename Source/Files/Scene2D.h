#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

#include "GameObject.h"

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

		bool checkCollision(GameObject* a, GameObject* b);

		void eraseInvisibleEntities();

		void freezeScreen(glm::mat3 visMatrix);

		void spawnPowerup();


	protected:
		ViewportSpace view_space;
		LogicSpace logic_space;
		glm::mat3 vis_matrix;
		glm::vec3 background_color;

		GameObject* player_ship;
		std::vector<GameObject*> enemies;
		std::vector<GameObject*> projectiles;
		std::vector<GameObject*> powerups;

		float length;

		float time_elapsed;
		float enemy_spawn_timer;
		float enemy_spawn_threshold;
		float powerup_spawn_timer;
		float powerup_spawn_threshold;
		float freeze_timer;

		int score;

		bool end_game;
		bool freeze_enemies;
};
