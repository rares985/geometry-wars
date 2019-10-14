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
#include "GameInfo.h"

using namespace std;

Scene2D::Scene2D()
{
}

Scene2D::~Scene2D()
{
}

void Scene2D::Init()
{
	/* Fix the camera so we can ignore the Z axis */
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	/* define the logic space and width */
	logic_space.x = 0;		
	logic_space.y = 0;		
	logic_space.width = LOGIC_WINDOW_WIDTH;	
	logic_space.height = LOGIC_WINDOW_HEIGHT;	

	background_color = black;

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

	/* Create the player object */
	player_ship = new Player();
	player_ship->setCenter(origin);
	player_ship->setMeshInfo(player_mesh, "ship");
	player_ship->setSize(PLAYER_SIZE);
	player_ship->setColor(ivory);

	player_ship->setInitialPosition(logic_space.width / 2, logic_space.height / 2);


	/* set the game variables */
	end_game = false;
	freeze_enemies = false;

	enemy_spawn_threshold = INITIAL_SPAWN_TIME;

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

}

void Scene2D::DrawScene(glm::mat3 vis_matrix, float deltaTimeSeconds)
{
	
	/* render the player's ship */

	player_ship->computeModelMatrix(vis_matrix);

	RenderMesh2D(meshes["ship"],shaders["VertexColor"],player_ship->getModelMatrix());
	

	/* Render projectiles and check for enemy-projectile collision */
	for (auto proj : projectiles) {

		float dtx = proj->x_speed * 24 * deltaTimeSeconds;
		float dty = proj->y_speed * 24 * deltaTimeSeconds;

		proj->tx += dtx;
		proj->ty += dty;

		proj->computeModelMatrix(vis_matrix);



		/* check for enemy-projectile collision */
		for (auto enemy : enemies) {

			if (proj->should_render && enemy->should_render) { /* if objects are visible(if they can collide) */
				if (checkCollision(proj,enemy)) {
					proj->should_render = false;
					if (enemy->lives_left == 1) {
						enemy->should_render = false;
						enemy->lives_left = 0;
						break; /* one projectile can damage 1 enemy only */
					}
					if (enemy->lives_left == 2) {
						enemy->shrink = true;
						enemy->mesh = meshes["shrinked_enemy_ship"];
						enemy->lives_left = 1;
						break;
					}
				}
			}
		}
		if (proj->should_render == true)
			RenderMesh2D(proj->mesh, shaders["VertexColor"], proj->getModelMatrix());
	}


	/* Render enemies and check for enemy-player collision */
	for (auto enemy : enemies) {
		
		glm::vec2 player_pos = glm::vec2(player_ship->tx, player_ship->ty);
		enemy->setMoveDirection(player_pos);

		if (enemy->shrink) { /* if the enemy is strong and has been hit, the speed doubles */
			enemy->mesh = meshes["shrinked_enemy_ship"];
			enemy->mesh_name = "shrinked_enemy_ship";
			enemy->x_speed *= 2;
			enemy->y_speed *= 2;
			enemy->setColor(firebrick);
			if (enemy->scale > 0.75f)
				enemy->scale -= (0.5f*deltaTimeSeconds) / SHRINK_ANIMATION_DURATION; /* and it shrinks over 250ms to half size */
		}

		if (!freeze_enemies) {
			float delta_tx = enemy->x_speed * deltaTimeSeconds;
			float delta_ty = enemy->y_speed * deltaTimeSeconds;
			
			enemy->tx += delta_tx;
			enemy->ty += delta_ty;

			enemy->computeModelMatrix(vis_matrix);
		}

		
		if (checkCollision(enemy, player_ship) && enemy->should_render)
		{
			if (player_ship->lives_left == 1)	{
				end_game = true;
				enemy->should_render = false;
				player_ship->lives_left--;
			}
			else if (player_ship->lives_left > 1) {
				player_ship->lives_left--;
				enemy->should_render = false;
			}
		}

		if (enemy->should_render)
				RenderMesh2D(enemy->mesh, shaders["VertexColor"], enemy->model_matrix);
	}

	for (auto powerup : powerups) {
		powerup->model_matrix = vis_matrix;
		powerup->model_matrix *= Transform2D::Translate(powerup->tx, powerup->ty);

		if (checkCollision(powerup, player_ship) && powerup->should_render) {
			if (powerup->mesh_name == "life") {
				player_ship->lives_left++;
			}
			else if (powerup->mesh_name == "freeze") {
				freeze_enemies = true;
				freeze_timer = 0;
			}
			powerup->should_render = false;
		}
		if (powerup->should_render)
			RenderMesh2D(powerup->mesh, shaders["VertexColor"], powerup->model_matrix);
	}

	float tx = 16.0f;
	float ty = 8.5f;
	for (int i = 0; i < player_ship->lives_left; i++) {
		tx -= (LIVES_SIZE + 0.1f);
		glm::mat3 model_matrix = vis_matrix;
		model_matrix *= Transform2D::Translate(tx, ty);
		RenderMesh2D(meshes["lives"], shaders["VertexColor"], model_matrix);
	}
}

void Scene2D::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		player_ship->ty += 3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_S)) {
		player_ship->ty -= 3 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_A)) {
		player_ship->tx -= 3 * deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_D)) {
		player_ship->tx += 3 * deltaTime;
	}
	glm::ivec2 mouse_pos = window->GetCursorPosition();
	float logic_mouse_x = ((float)(mouse_pos.x)) / 80;
	float logic_mouse_y = ((float)(window->GetResolution().y - mouse_pos.y)) / 80;
	float x_diff = logic_mouse_x - player_ship->tx;
	float y_diff = logic_mouse_y - player_ship->ty;
	player_ship->rotation = atan(y_diff / x_diff);
}




void Scene2D::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		
		GameObject* projectile = new GameObject();
		projectile->setCenter(origin);
		projectile->setMeshInfo(meshes["projectile"], "projectile");
		projectile->setSize(PROJECTILE_SIZE);
		projectile->setColor(yellow);

		projectile->tx = player_ship->tx;
		projectile->ty = player_ship->ty;

		float logic_mouse_x = ((float)(mouseX)) / 80;
		float logic_mouse_y = ((float)(window->GetResolution().y - mouseY)) / 80;
		glm::vec2 mouse_pos = glm::vec2(logic_mouse_x, logic_mouse_y);
		
		
		projectile->setMoveDirection(mouse_pos);
	

		projectiles.push_back(projectile);
	}

}


void Scene2D::spawnEnemies() {
		srand((unsigned int)time_elapsed);
		for (int i = 0; i < 3; i++) {


			float angle = (float)rand();
			float px = player_ship->tx;
			float py = player_ship->ty;
			float radius = ENEMY_SPAWN_DISTANCE;
			float x = cos(angle)*radius;
			float y = sin(angle)*radius;


			GameObject* enemy;

			int lives_count = (rand() % 2) + 1;
			glm::vec3 color;
			std::string mesh_name;

			if (lives_count == 1) {
				mesh_name = "weak_enemy_ship";
				color = deepskyblue;
			}
			else {
				mesh_name = "strong_enemy_ship";
				color = gold;
			}
			enemy = new GameObject();
			enemy->setCenter(origin);
			enemy->setMeshInfo(meshes[mesh_name], mesh_name);
			enemy->setSize(DEFAULT_ENEMY_SIZE);
			enemy->setColor(color);

			enemy->initial_lives = lives_count;
			enemy->lives_left = enemy->initial_lives;

			enemy->tx = px + x;
			enemy->ty = py + y;

			glm::vec2 player_pos = glm::vec2(player_ship->tx, player_ship->ty);
			enemy->setMoveDirection(player_pos);
			float speedCuantifier = (float)(rand() % 3 + 1);
			enemy->x_speed *= speedCuantifier;
			enemy->y_speed *= speedCuantifier;


			enemies.push_back(enemy);
		}
}

void Scene2D::eraseInvisibleEntities() {
	std::vector<GameObject*>::iterator projectile;
	for (projectile = std::begin(projectiles); projectile != std::end(projectiles); ++projectile) {
		if (!(*projectile)->should_render)
			projectiles.erase(projectile);
	}
	std::vector<GameObject*>::iterator enemy;
	for (projectile = std::begin(enemies); projectile != std::end(enemies); ++enemy) {
		if (!(*enemy)->should_render)
			enemies.erase(enemy);
	}
}

bool Scene2D::checkCollision(GameObject* first, GameObject* second) {
	float xdist = first->tx - second->tx;
	float ydist = first->ty - second->ty;
	float abs_dist = xdist*xdist + ydist*ydist;
	float radii_dist = (first->getSize() + second->getSize()) * (first->getSize() + second->getSize());
	return (abs_dist <= radii_dist);
}

void Scene2D::freezeScreen(glm::mat3 vis_matrix) {

	/*render player*/
	RenderMesh2D(meshes["ship"],shaders["VertexColor"],player_ship->model_matrix);
	/*render enemies*/
	for (auto enemy : enemies) {
		if (enemy->should_render)
			RenderMesh2D(meshes[enemy->mesh_name],shaders["VertexColor"],enemy->model_matrix);
	}
	for (auto proj : projectiles) {
		if (proj->should_render)
			RenderMesh2D(meshes[proj->mesh_name], shaders["VertexColor"], proj->model_matrix);
	}
	/* render powerups */
	for (auto powerup : powerups) {
		powerup->model_matrix = vis_matrix;
		powerup->model_matrix *= Transform2D::Translate(powerup->tx, powerup->ty);
		if (powerup->should_render)
			RenderMesh2D(powerup->mesh, shaders["VertexColor"], powerup->model_matrix);
	}
	/*render projectiles*/
	float tx = 16.0f;
	float ty = 8.5f;
	for (int i = 0; i < player_ship->lives_left; i++) {
		tx -= (LIVES_SIZE + 0.1f);
		glm::mat3 model_matrix = vis_matrix;
		model_matrix *= Transform2D::Translate(tx, ty);
		RenderMesh2D(meshes["lives"], shaders["VertexColor"], model_matrix);
	}
}

void Scene2D::spawnPowerup() {

	int powerup_type = (rand() % 2 + 1);
	float x_pos = (float)(rand() % 16);
	float y_pos = (float)(rand() % 9);

	glm::vec3 color;
	std::string mesh_name;
	float size = 0.0f;

	if (powerup_type == 1) {
		mesh_name = "life";
		color = forestgreen;
		size = LIFE_POWERUP_SIZE;

	}
	if (powerup_type == 2) {
		mesh_name = "freeze";
		color = darkcyan;
		size = FREEZE_POWERUP_SIZE;
	}
	GameObject* powerup = new GameObject();
	powerup->setCenter(origin);
	powerup->setMeshInfo(meshes[mesh_name], mesh_name);
	powerup->setSize(size);
	powerup->setColor(color);

	powerup->tx = x_pos;
	powerup->ty = y_pos;

	powerups.push_back(powerup);


}



