#include "Scene2D.h"
#include "Player.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>

#include <Core/Engine.h>

#include "Transform2D.h"
#include "Object2D.h"
#include "constants.h"


using namespace std;

Scene2D::Scene2D()
{
	game_instance = std::unique_ptr<GameInstance>(new GameInstance());


	/* define the logic space and width */
	logic_space_ptr = std::unique_ptr<LogicSpace>(new LogicSpace(0, 0, LOGIC_WINDOW_WIDTH, LOGIC_WINDOW_HEIGHT));
 

	background_color = black;

}

Scene2D::~Scene2D()
{
	delete meshes[PLAYER_SHIP_MESH_NAME];
	delete meshes[PROJECTILE_MESH_NAME];
	delete meshes[WEAK_ENEMY_SHIP_MESH_NAME];
	delete meshes[STRONG_ENEMY_SHIP_MESH_NAME];
	delete meshes[SHRINKED_ENEMY_SHIP_MESH_NAME];
	delete meshes[LIVES_INDICATOR_MESH_NAME];
	delete meshes[LIFE_POWERUP_MESH_NAME];
	delete meshes[FREEZE_POWERUP_MESH_NAME];

}

void Scene2D::Init()
{

	Player& player = *(game_instance->player);

	/* Fix the camera so we can ignore the Z axis */
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);


	/* Create the meshes we  will use */

	Mesh* player_mesh(Object2D::GetShipMesh(PLAYER_SHIP_MESH_NAME, origin, PLAYER_SIZE, ivory, true));
	Mesh* projectile_mesh = Object2D::GetProjectileMesh(PROJECTILE_MESH_NAME, glm::vec3(0, 0, 0), PROJECTILE_SIZE, yellow, true);
	Mesh* weak_enemy_mesh = Object2D::GetShipMesh(WEAK_ENEMY_SHIP_MESH_NAME, origin, DEFAULT_ENEMY_SIZE, deepskyblue, true);
	Mesh* strong_enemy_mesh = Object2D::GetShipMesh(STRONG_ENEMY_SHIP_MESH_NAME, origin, DEFAULT_ENEMY_SIZE, gold, true);
	Mesh* shrinked_enemy_mesh = Object2D::GetShipMesh(SHRINKED_ENEMY_SHIP_MESH_NAME, origin, SHRINKED_ENEMY_SIZE, firebrick, true);
	Mesh* lives_mesh = Object2D::GetLifeIndicatorMesh(LIVES_INDICATOR_MESH_NAME,origin,LIVES_SIZE, ivory,true);
	Mesh* life_powerup_mesh = Object2D::GetLifePowerupMesh(LIFE_POWERUP_MESH_NAME, origin, LIFE_POWERUP_SIZE, forestgreen, true);
	Mesh* freeze_powerup_mesh = Object2D::GetFreezePowerupMesh(FREEZE_POWERUP_MESH_NAME, origin, FREEZE_POWERUP_SIZE, aquamarine, true);

	AddMeshToList(player_mesh);
	AddMeshToList(projectile_mesh);
	AddMeshToList(weak_enemy_mesh);
	AddMeshToList(strong_enemy_mesh);
	AddMeshToList(shrinked_enemy_mesh);
	AddMeshToList(lives_mesh);
	AddMeshToList(life_powerup_mesh);
	AddMeshToList(freeze_powerup_mesh);

	player.setInitialPosition(logic_space_ptr->width / 2, logic_space_ptr->height / 2);

}


/* Uniform transformation matrix from (1280,720) to (16,9) */
glm::mat3 Scene2D::VisualizationTransf2DUnif(const LogicSpace & logic_space, const ViewportSpace & view_space)
{
	float sx , sy, tx, ty, smin;
	sx = view_space.width / logic_space.width;
	sy = view_space.height / logic_space.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;
	tx = view_space.x - smin * logic_space.x + (view_space.width - smin * logic_space.width) / 2;
	ty = view_space.y - smin * logic_space.y + (view_space.height - smin * logic_space.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}

void Scene2D::SetViewportArea(const ViewportSpace & view_space, glm::vec3 clearing_color, bool clear)
{
	glViewport(view_space.x, view_space.y, view_space.width, view_space.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(view_space.x, view_space.y, view_space.width, view_space.height);

	
	glClearColor(clearing_color.r, clearing_color.g, clearing_color.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)view_space.x, (float)(view_space.x + view_space.width), (float)view_space.y, (float)(view_space.y + view_space.height), 0.1f, 400);
	GetSceneCamera()->Update();
}

void Scene2D::FrameStart()
{
	
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Scene2D::Update(float deltaTimeSeconds) {

	GameState gs = game_instance->getGameState();

	glm::ivec2 resolution = window->GetResolution();
	view_space_ptr = std::unique_ptr<ViewportSpace>(new ViewportSpace(0, 0, resolution.x, resolution.y));
	SetViewportArea(*view_space_ptr,background_color, true);
	
	vis_matrix = VisualizationTransf2DUnif(*logic_space_ptr, *view_space_ptr);

	switch (gs) {

		case GameState::GS_ENDED:
			if (background_color.x <= 1.0f) {
				background_color += glm::vec3(deltaTimeSeconds / 2.0f, 0, 0);
			}
			freezeScreen(vis_matrix);
			break;

		case GameState::GS_FROZEN:
			game_instance->freeze_timer += deltaTimeSeconds;

		default:
			DrawScene(vis_matrix, deltaTimeSeconds);
			break;
	}

	game_instance->updateTimers(deltaTimeSeconds);
}

void Scene2D::FrameEnd()
{
	Player &player = *(game_instance->player);

	game_instance->deleteInvisibleEntities();

	if (player.isDead()) {
		game_instance->OnGameEnd();
	}
}

void Scene2D::DrawScene(glm::mat3 vis_matrix, float deltaTimeSeconds)
{
	Player& player = *(game_instance->player);
	std::list<std::unique_ptr<Projectile>>& projectiles = game_instance->projectiles;
	std::list<std::unique_ptr<Enemy>>& enemies = game_instance->enemies;
	std::list<std::unique_ptr<Powerup>>& powerups = game_instance->powerups;
	
	/* render the player's ship */
	player.computeModelMatrix(vis_matrix);
	RenderMesh2D(meshes[player.getMeshName()],shaders["VertexColor"],player.getModelMatrix());
	
	/* Render projectiles and check for enemy-projectile collision */
	std::list<std::unique_ptr<Enemy>>::iterator enemy_it;
	std::list<std::unique_ptr<Projectile>>::iterator proj_it;

	for (proj_it = projectiles.begin(); proj_it != projectiles.end(); proj_it++) {
		(*proj_it)->updatePosition(24 * deltaTimeSeconds);
		(*proj_it)->computeModelMatrix(vis_matrix);
		for (enemy_it = enemies.begin(); enemy_it != enemies.end(); enemy_it++) {
			if ((*enemy_it)->collidesWith(**proj_it)) {
				(*enemy_it)->handleCollisionWith(**proj_it);
				// game_instance->updateScore(enemy->initial_lives);
			}
		}
		renderIfVisible(**proj_it);
		
	}


	/* Render enemies and check for enemy-player collision */
	for (enemy_it = enemies.begin(); enemy_it != enemies.end(); enemy_it++) {
		/* Make the enemy move towards the player */
		(*enemy_it)->moveTowards(player.getPosition());

		if ((*enemy_it)->shrink) { /* if the enemy is strong and has been hit, the speed doubles */
			(*enemy_it)->performShrink(deltaTimeSeconds);
		}

		if (player.collidesWith(**enemy_it)) {
			player.handleCollisionWith(**enemy_it);
		}

		if (!game_instance->isFrozen()) {
			(*enemy_it)->updatePosition(deltaTimeSeconds);
			(*enemy_it)->computeModelMatrix(vis_matrix);
		}

		renderIfVisible(**enemy_it);
	}

	/* Draw powerups */
	std::list<std::unique_ptr<Powerup>>::iterator it;
	for (it = powerups.begin(); it != powerups.end(); it++) {
		(*it)->computeModelMatrix(vis_matrix);
		/* Check for collision with player */
		if (player.collidesWith(**it)) {
			player.handleCollisionWith(**it);
			if ((*it)->getMeshName() == FREEZE_POWERUP_MESH_NAME) {
				game_instance->freezeGame();
			}
		}
		renderIfVisible(**it);
	}

	/* Draw lives indicator */
	RenderLivesIndicator(player.getLivesLeft());

}

void Scene2D::RenderLivesIndicator(int how_many)
{
	float tx = 16.0f;
	float ty = 8.5f;
	for (int i = 0; i < how_many; i++) {
		tx -= (LIVES_SIZE + 0.1f);
		glm::mat3 model_matrix = vis_matrix;
		model_matrix *= Transform2D::Translate(tx, ty);
		RenderMesh2D(meshes[LIVES_INDICATOR_MESH_NAME], shaders["VertexColor"], model_matrix);
	}
}

void Scene2D::OnInputUpdate(float deltaTime, int mods) {

	Player& player = *(game_instance->player);

	float x_cuantif = 0.0f;
	float y_cuantif = 0.0f;

	if (window->KeyHold(GLFW_KEY_W) || window->KeyHold(GLFW_KEY_UP)) {
		y_cuantif += 3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_S) || window->KeyHold(GLFW_KEY_DOWN)) {
		y_cuantif -= 3 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_A) || window->KeyHold(GLFW_KEY_LEFT)) {
		x_cuantif += -3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_D) || window->KeyHold(GLFW_KEY_RIGHT)) {
		x_cuantif += 3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_V)) {
		game_instance->spawnPowerup(); // only for testing purposes
	}

	player.updatePosition(x_cuantif, y_cuantif);


	glm::ivec2 mouse_pos = window->GetCursorPosition();

	float logic_mouse_x = (float)(mouse_pos.x) / LOGIC_SCALE_FACTOR;
	float logic_mouse_y = (float)(WINDOW_HEIGHT_PX - mouse_pos.y) / LOGIC_SCALE_FACTOR;

	player.rotateTowards(glm::vec2(logic_mouse_x, logic_mouse_y));
}

void Scene2D::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {

	Player& player = *(game_instance->player);
	std::list<std::unique_ptr<Projectile>> &projectiles = game_instance->projectiles;

	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		
		std::unique_ptr<Projectile> projectile(new Projectile());

		float logic_mouse_x = (float)(mouseX) / LOGIC_SCALE_FACTOR;
		float logic_mouse_y = (float)(WINDOW_HEIGHT_PX - mouseY) / LOGIC_SCALE_FACTOR;

		projectile->setInitialPosition(player.getPosition());
		projectile->moveTowards(glm::vec2(logic_mouse_x, logic_mouse_y));
	
		projectiles.push_back(std::move(projectile));
	}
}


void Scene2D::freezeScreen(glm::mat3 vis_matrix) {

	Player& player = *(game_instance->player);
	std::list<std::unique_ptr<Projectile>> &projectiles = game_instance->projectiles;
	std::list<std::unique_ptr<Enemy>> &enemies = game_instance->enemies;
	std::list<std::unique_ptr<Powerup>>& powerups = game_instance->powerups;

	/*render player*/
	RenderMesh2D(meshes[player.getMeshName()],shaders["VertexColor"],player.getModelMatrix());

	/* render enemies */
	std::list<std::unique_ptr<Enemy>>::iterator enemy_it;
	for (enemy_it = enemies.begin(); enemy_it != enemies.end(); enemy_it++) {
		renderIfVisible(**enemy_it);
	}

	/* Render projectiles */
	std::list<std::unique_ptr<Projectile>>::iterator proj_it;
	for (proj_it = projectiles.begin(); proj_it != projectiles.end(); proj_it++) {
		renderIfVisible(**proj_it);
	}

	/* render powerups */
	std::list<std::unique_ptr<Powerup>>::iterator pow_it;
	for (pow_it = powerups.begin(); pow_it != powerups.end(); pow_it++) {
		(*pow_it)->computeModelMatrix(vis_matrix);
		renderIfVisible(**pow_it);
	}

	/*render lives indicator */
	float tx = 16.0f;
	float ty = 8.5f;
	for (int i = 0; i < player.lives_left; i++) {
		tx -= (LIVES_SIZE + 0.1f);
		glm::mat3 model_matrix(vis_matrix);
		model_matrix *= Transform2D::Translate(tx, ty);
		RenderMesh2D(meshes[LIVES_INDICATOR_MESH_NAME], shaders["VertexColor"], model_matrix);
	}
}

void Scene2D::renderIfVisible(GameObject &object)
{
	if (object.isVisible()) {
		RenderMesh2D(meshes[object.getMeshName()], shaders["VertexColor"], object.getModelMatrix());
	}
}

