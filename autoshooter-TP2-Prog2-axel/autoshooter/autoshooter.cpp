#include <iostream>
#include <raylib.h>
#include <cstdlib>
#include <ctime>

#include "GameData.h"
#include "Character.h"
#include "Projectile.h"
#include "Experience.h"
#include "Weapon.h"

using namespace std;

//data structures to contain game data
vector<Projectile> projectiles;
vector<Enemy> enemies;
vector<Experience> experienceVector;

float RandomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}


//player starts in the center (and Should stay there)
Player player = {CENTER_SCREEN, 15, MAGENTA, 1.f, 50, 1};

void Initialize() {

    InitWindow(WIDTH, HEIGHT, "AutoShooter");
    SetTargetFPS(FPS);

   
    //Enemies Spawn
    for (int i = 0; i < DESIRED_ENEMY_COUNT; i++)
    {
        Vector2 newEnemyPos = { RandomFloat(0, WIDTH), RandomFloat(0, HEIGHT) };
        enemies.push_back(Enemy{ newEnemyPos , 20, RED, 1, 10, 1.5f });
    }

    //TODO: Randomize Spawning the Enemies out of the Screen

}

void HandleInput() 
{
    // Input 
    Vector2 inputDirection = { 0.0f, 0.0f };
    if (IsKeyDown(KEY_UP) || IsKeyDown(UP))
    {
        inputDirection.y -= 1.0f;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(DOWN))
    {
        inputDirection.y += 1.0f;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(LEFT))
    {
        inputDirection.x -= 1.0f;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(RIGHT))
    {
        inputDirection.x += 1.0f;
    }

    //Normalizing the input
    float inputLength = sqrt(inputDirection.x * inputDirection.x + inputDirection.y * inputDirection.y);
    if (inputLength != 0.0f)
    {
        inputDirection.x /= inputLength;
        inputDirection.y /= inputLength;
    }

    for (auto& enemy : enemies) {
        enemy.Move(inputDirection, player.speed, projectiles);
    }

    Vector2 shootDirection = inputDirection;

    if (IsKeyPressed(SHOOT))
    {
        Vector2 shootDirection = { 0.0f, -1.0f };
        if (inputDirection.x != 0.0f || inputDirection.y != 0.0f)
        {
            shootDirection = inputDirection;
        }
        Weapon w = player.GetWeapon();
        vector<Projectile> bullets = w.m_Shoot(player.position, shootDirection);
        for (auto b : bullets) {
            projectiles.push_back(b);
        }
    }
}

void CheckCollisionEnemyPlayer() {
    for (int i = 0; i < enemies.size(); i++)
    {
        for (auto& enemy : enemies) {
            if (CheckCollisionCircles(enemy.position, enemy.size, player.position, player.size)) {
                player.health -= 1;
                //cout << "player health: " << player.health;
                enemies.erase(enemies.begin() + i);
            }
            else {
                i++;
            }
        }
    }
}

void CheckCollisionEnemyProjectile()
{
    for (auto itProjectile = projectiles.begin(); itProjectile != projectiles.end(); )
    {
        auto& projectile = *itProjectile;
        bool projectileHit = false;
        // Iterate and treat enemies
        for (auto itEnemy = enemies.begin(); itEnemy != enemies.end(); ) 
        {
            auto& enemy = *itEnemy;
            if (CheckCollisionCircles(projectile.position, projectile.size, enemy.position, enemy.size))
            {
                // Projectile hits an enemy
                enemy.health -= projectile.damage;
                cout << "enemy health: " << enemy.health << endl;
                projectileHit = true;// Mark projectile as hit
                if (enemy.health <= 0)
                {     
                    itEnemy = enemies.erase(itEnemy); // Erase the enemy/update 'itEnemy' 2 point 2 nxt elmt
                    Experience newExperience = enemy.CreateExperience();
                    experienceVector.push_back(newExperience);
                    Vector2 newEnemyPosition =
                    {
                       enemy.position.x, enemy.position.y
                    };
                    for (const Experience& experience : experienceVector) {
                        DrawCircleV(experience.position, experience.radius, experience.color);
                    }
                    // Create a new enemy and add it to the vector
                    enemies.push_back(Enemy( newEnemyPosition, 50, RED, 1, 10, 1.5f ));
                    break; //out of inner loop and goes to the next projectile in projectiles vector 
                }
                else 
                {
                    ++itEnemy; //if COLLIDE && enemy.health > 0 - check the nxt enemy
                }
                player.health += 1; // Increment player health
                break; //No need 2 continue chckng 4 enemies 4 this projectile
            }
            else {   
                ++itEnemy;//NOT COLLIDE Go2nxt enemy
            }
        }
        //
        if (projectileHit) {  
            itProjectile = projectiles.erase(itProjectile);//Erase  Projectile. Update 'itProjectile' 2 point 2  nxt elmt
        }
        else {
            ++itProjectile;//Update projectile iterator (go2nxt)
        }
    }
}

int main() 
{
    Initialize(); 
    //GameLoop
    int maxExperience = 10; // Set the maximum experience needed to level up
    int currentExperience = 0; // Initialize player's current experience
    float blueBarMaxLength = 200.0f; // Maximum length of the blue bar
    float blueBarLength = 0.0f; // Initialize the blue bar length
    while (!WindowShouldClose()) 
    {   
        HandleInput();
        //DRAWING 2 THE SCREEN
        BeginDrawing();
            ClearBackground(RAYWHITE);
            //Draw PLAYER
            player.Draw();
            //Draw  And Move ENEMIES
            for (Enemy& enemy : enemies) 
            {
                //we get the vector of the directon 2 the player, the enemy wil move towars the player
                Vector2 directionToPlayer = { player.position.x - enemy.position.x, player.position.y - enemy.position.y };
                //we get the lenght of the returned vector to normalize it
                float directionLength = sqrt(directionToPlayer.x * directionToPlayer.x + directionToPlayer.y * directionToPlayer.y);
                //we normalize it
                directionToPlayer.x /= directionLength;
                directionToPlayer.y /= directionLength;
                enemy.Draw();
                enemy.Move(directionToPlayer, enemy.speed, projectiles);
            }
            //Draw and  Move projectile
            for (Projectile& prjctl : projectiles)
            {
                prjctl.Draw();
                prjctl.Move();
            }
            for (auto it = experienceVector.begin(); it != experienceVector.end(); )
            {
                auto& experience = *it;
                // Calculate direction to the player
                Vector2 directionToPlayer = { player.position.x - experience.position.x, player.position.y - experience.position.y };
                float directionLength = sqrt(directionToPlayer.x * directionToPlayer.x + directionToPlayer.y * directionToPlayer.y);
                directionToPlayer.x /= directionLength;
                directionToPlayer.y /= directionLength;

                // Update position of experience orb
                float experienceSpeed = 5.0f; // Speed at which experience orbs move towards the player
                experience.position.x += directionToPlayer.x * experienceSpeed;
                experience.position.y += directionToPlayer.y * experienceSpeed;

                // Check if experience orb has reached the player
                if (CheckCollisionCircles(experience.position, experience.radius, player.position, player.size))
                {
                    // Add 1 experience to the player
                    currentExperience += 1;
                    blueBarLength = 0.0f; // Reset the blue bar length
                    it = experienceVector.erase(it);
                }
                else
                {
                    // Move on to the next experience or b
                    ++it;
                }
            }
            //chck collisions ENEMY -> PLAYER
            CheckCollisionEnemyPlayer();
            //Chck collisions PROJECTILES/ENEMY 
            CheckCollisionEnemyProjectile();

            /************************** DRAW UI ************************************/
            DrawRectangle(10, 10, player.health * 2, 20, GREEN); // Health bar
            DrawRectangle(10, 40, player.level * 50, 20, BLUE);  // Experience bar

        EndDrawing();

        if (IsKeyPressed(CHEAT))
        {
            player.level + 5;
        }
   
    }

    CloseWindow();

    return 0;
}
