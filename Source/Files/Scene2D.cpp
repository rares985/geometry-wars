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
	game_instance = new GameInstance();
	freeze_enemies = false;

	powerup_spawn_threshold = 0;
	powerup_spawn_timer = 0;

	enemy_spawn_threshold = 0;
	enemy_spawn_timer = 0;

	time_elapsed = 0;

	freeze_timer = 0;

	enemy_spawn_threshold = INITIAL_SPAWN_TIME;

	/* define the logic space and width */
	logic_space.x = 0;
	logic_space.y = 0;
	logic_space.width = LOGIC_WINDOW_WIDTH;
	logic_space.height = LOGIC_WINDOW_HEIGHT;

	background_color = black;

	player = new Player();
}

Scene2D::~Scene2D()
{
	delete player;
	for (auto obj : projectiles) {
		delete obj;
	}
	for (auto obj : enemies) {
		delete obj;
	}
	for (auto obj : powerups) {
		delete obj;
	}
}

void Scene2D::Init()
{
	/* Fix the camera so we can ignore the Z axis */
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);


	/* Create the meshes we  will use */

	Mesh* player_mesh = Object2D::GetShipMesh("ship", origin, PLAYER_SIZE, ivory, true);
	Mesh* projectile_mesh = Object2D::GetProjectileMesh("projectile", glm::vec3(0, 0, 0), PROJECTILE_SIZE, yellow, true);
	Mesh* weak_enemy_mesh = Object2D::GetShipMesh("weak_enemy_ship", origin, DEFAULT_ENEMY_SIZE, deepskyblue, true);
	Mesh* strong_enemy_mesh = Object2D::GetShipMesh("strong_enemy_ship", origin, DEFAULT_ENEMY_SIZE, gold, true);
	Mesh* shrinked_enemy_mesh = Object2D::GetShipMesh("shrinked_enemy_ship", origin, SHRINKED_ENEMY_SIZE, firebrick, true);
	Mesh* lives_mesh = Object2D::GetLifeIndicatorMesh("lives",origin,LIVES_SIZE, ivory,true);
	Mesh* life_powerup_mesh = Object2D::GetLifePowerupMesh("life", origin, LIFE_POWERUP_SIZE, forestgreen, true);
	Mesh* freeze_powerup_mesh = Object2D::GetFreezePowerupMesh("freeze", origin, FREEZE_POWERUP_SIZE, aquamarine, true);

	AddMeshToList(player_mesh);
	AddMeshToList(projectile_mesh);
	AddMeshToList(weak_enemy_mesh);
	AddMeshToList(strong_enemy_mesh);
	AddMeshToList(shrinked_enemy_mesh);
	AddMeshToList(lives_mesh);
	AddMeshToList(life_powerup_mesh);
	AddMeshToList(freeze_powerup_mesh);

	player->setInitialPosition(logic_space.width / 2, logic_space.height / 2);

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

void Scene2D::SetViewportArea(const ViewportSpace & view_space, glm::vec3 colorColor, bool clear)
{
	glViewport(view_space.x, view_space.y, view_space.width, view_space.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(view_space.x, view_space.y, view_space.width, view_space.height);

	
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
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

void Scene2D::Update(float deltaTimeSeconds)
{
	bool end_game = game_instance->isEndGame();

	game_instance->updateTimers(deltaTimeSeconds);

	time_elapsed += deltaTimeSeconds;

	/* Timers should update only when enemies are not frozen */
	if (!freeze_enemies && !end_game) {
		enemy_spawn_timer += deltaTimeSeconds;
		powerup_spawn_timer += deltaTimeSeconds;
	}

	/* The spawn threshold decreases per frame, from 2s to 0.5s */
	if (enemy_spawn_threshold > MIN_SPAWN_TIME && !freeze_enemies && !end_game) {
		enemy_spawn_threshold -= (deltaTimeSeconds / 100);
	}
	else if (enemy_spawn_threshold < MIN_SPAWN_TIME && !end_game) {
		enemy_spawn_threshold = MIN_SPAWN_TIME;
	}

	/* Enemies spawn every spawn_threshold seconds*/
	if (enemy_spawn_timer > enemy_spawn_threshold && !end_game) {
		spawnEnemies();
		enemy_spawn_timer = 0;
	}

	/* Powerups spawn every 10 seconds */
	if (powerup_spawn_timer > POWERUP_SPAWN_THRESHOLD && !freeze_enemies && !end_game) {
		powerup_spawn_timer = 0;
		spawnPowerup();
	}

	/* If freeze is over, reset the timer */
	if (freeze_timer > FREEZE_DURATION) {
		freeze_enemies = false;
		freeze_timer = 0;
	}
	
	/* If game has ended , the background color fades to red */
	if (end_game)
		if (background_color.x <= 1.0f) {
			background_color += glm::vec3(deltaTimeSeconds / 2.0f, 0, 0);
		}

	glm::ivec2 resolution = window->GetResolution();

	view_space = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(view_space,background_color, true);
	
	vis_matrix = glm::mat3(1);
	vis_matrix *= VisualizationTransf2DUnif(logic_space, view_space);

	if (end_game) {
		freezeScreen(vis_matrix);
	}
	else {
		if (freeze_enemies) {
			freeze_timer += deltaTimeSeconds;
		}
		DrawScene(vis_matrix, deltaTimeSeconds);
	}
}

void Scene2D::FrameEnd()
{
	glm::vec2 low(0, 0);
	glm::vec2 high(LOGIC_WINDOW_WIDTH, LOGIC_WINDOW_HEIGHT);
	glm::vec2 pos;


	for (auto proj : projectiles) {
		pos = proj->getPosition();
		if (glm::any(glm::lessThan(pos, low)) || glm::any(glm::greaterThan(pos, high))) {
			proj->makeInvisible();
		}
	}
		
	projectiles.remove_if([](const Projectile* proj) {return !proj->isVisible(); });
	enemies.remove_if([](const Enemy* enemy) {return !enemy->isVisible(); });
	powerups.remove_if([](const Powerup* powerup) {return !powerup->isVisible(); });

	std::cout << "Projectiles Size: " << projectiles.size() << std::endl;
	std::cout << "Enemies Size: " << enemies.size() << std::endl;
	std::cout << "Powerups Size: " << powerups.size() << std::endl;

	if (player->isDead()) {
		game_instance->OnGameEnd();
	}
}

void Scene2D::DrawScene(glm::mat3 vis_matrix, float deltaTimeSeconds)
{
	
	/* render the player's ship */
	player->computeModelMatrix(vis_matrix);
	RenderMesh2D(meshes["ship"],shaders["VertexColor"],player->getModelMatrix());
	

	/* Render projectiles and check for enemy-projectile collision */
	for (auto proj : projectiles) {

		float cuantif = 24 * deltaTimeSeconds;
		proj->updatePosition(cuantif);
		proj->computeModelMatrix(vis_matrix);

		/* check for enemy-projectile collision */
		for (auto enemy : enemies) {
			if (enemy->collidesWith(proj)) {
				enemy->collideWith(*proj);
				// game_instance->updateScore(enemy->initial_lives);
			}
		}
		if (proj->isVisible())
			RenderMesh2D(meshes[proj->getMeshName()], shaders["VertexColor"], proj->getModelMatrix());
	}


	/* Render enemies and check for enemy-player collision */
	for (auto enemy : enemies) {
		
		/* Make the enemy move towards the player */
		enemy->moveTowards(player->getPosition());

		if (enemy->shrink) { /* if the enemy is strong and has been hit, the speed doubles */
			enemy->performShrink(deltaTimeSeconds);
		}

		if (!freeze_enemies) {
			enemy->updatePosition(deltaTimeSeconds);
			
			enemy->computeModelMatrix(vis_matrix);
		}

		if (player->collidesWith(enemy)) {
			player->collideWith(*enemy);
		}

		if (enemy->isVisible()) {
			RenderMesh2D(meshes[enemy->getMeshName()], shaders["VertexColor"], enemy->getModelMatrix());
		}
	}

	for (auto powerup : powerups) {

		powerup->computeModelMatrix(vis_matrix);

		if (player->collidesWith(powerup)) {
			player->collideWith(*powerup);
			if (powerup->getMeshName() == "freeze") {
				freeze_enemies = true;
				freeze_timer = 0;
			}
		}
		if (powerup->isVisible())
			RenderMesh2D(meshes[powerup->getMeshName()], shaders["VertexColor"], powerup->getModelMatrix());
	}

	float tx = 16.0f;
	float ty = 8.5f;
	for (int i = 0; i < player->lives_left; i++) {
		tx -= (LIVES_SIZE + 0.1f);
		glm::mat3 model_matrix = vis_matrix;
		model_matrix *= Transform2D::Translate(tx, ty);
		RenderMesh2D(meshes["lives"], shaders["VertexColor"], model_matrix);
	}
}

void Scene2D::OnInputUpdate(float deltaTime, int mods)
{
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
		spawnPowerup(); // only for testing purposes
	}

	player->updatePosition(x_cuantif, y_cuantif);


	glm::ivec2 mouse_pos = window->GetCursorPosition();

	float logic_mouse_x = (float)(mouse_pos.x) / LOGIC_SCALE_FACTOR;
	float logic_mouse_y = (float)(WINDOW_HEIGHT_PX - mouse_pos.y) / LOGIC_SCALE_FACTOR;

	player->rotateTowards(glm::vec2(logic_mouse_x, logic_mouse_y));
}




void Scene2D::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		
		Projectile* projectile = new Projectile();

		float logic_mouse_x = (float)(mouseX) / LOGIC_SCALE_FACTOR;
		float logic_mouse_y = (float)(WINDOW_HEIGHT_PX - mouseY) / LOGIC_SCALE_FACTOR;

	
		projectile->setInitialPosition(player->getPosition());
		projectile->moveTowards(glm::vec2(logic_mouse_x, logic_mouse_y));
	
		projectiles.push_back(projectile);
	}
}


void Scene2D::spawnEnemies() {

	for (int i = 0; i < ENEMIES_SPAWNED_PER_ROUND; i++) {

		float angle = (float)rand();
		glm::vec2 player_pos = player->getPosition();
		glm::vec2 polar_pos(cos(angle), sin(angle));

		/* Convert from angle to distance */
		polar_pos *= ENEMY_SPAWN_DISTANCE;

		int enemy_type = (rand() % 2) + 1;
		Enemy* enemy = new Enemy(enemy_type);

		enemy->setInitialPosition(player_pos + polar_pos);
		enemy->moveTowards(player_pos);

		float speedCuantifier = (float)(rand() % 3 + 1);

		enemy->x_speed *= speedCuantifier;
		enemy->y_speed *= speedCuantifier;

		enemies.push_back(enemy);
	}
}

void Scene2D::freezeScreen(glm::mat3 vis_matrix) {

	/*render player*/
	RenderMesh2D(meshes["ship"],shaders["VertexColor"],player->getModelMatrix());

	/*render enemies*/
	for (auto enemy : enemies) {
		if (enemy->isVisible())
			RenderMesh2D(meshes[enemy->getMeshName()],shaders["VertexColor"],enemy->getModelMatrix());
	}
	for (auto proj : projectiles) {
		if (proj->isVisible())
			RenderMesh2D(meshes[proj->getMeshName()], shaders["VertexColor"], proj->getModelMatrix());
	}
	/* render powerups */
	for (auto powerup : powerups) {
		powerup->computeModelMatrix(vis_matrix);

		if (powerup->isVisible())
			RenderMesh2D(meshes[powerup->getMeshName()] , shaders["VertexColor"], powerup->getModelMatrix());
	}
	/*render projectiles*/
	float tx = 16.0f;
	float ty = 8.5f;
	for (int i = 0; i < player->lives_left; i++) {
		tx -= (LIVES_SIZE + 0.1f);
		glm::mat3 model_matrix = vis_matrix;
		model_matrix *= Transform2D::Translate(tx, ty);
		RenderMesh2D(meshes["lives"], shaders["VertexColor"], model_matrix);
	}
}

void Scene2D::spawnPowerup() {

	int powerup_type = (rand() % 2 + 1);

	float x_pos = (float)(rand() % LOGIC_WINDOW_WIDTH);
	float y_pos = (float)(rand() % LOGIC_WINDOW_HEIGHT);

	Powerup* powerup = new Powerup(powerup_type);

	powerup->setCenter(origin);
	powerup->setInitialPosition(x_pos, y_pos);

	powerups.push_back(powerup);

}




