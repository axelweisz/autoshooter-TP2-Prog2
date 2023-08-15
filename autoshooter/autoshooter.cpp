#include <iostream>
#include <raylib.h>

#include "GameData.h"
#include "Character.h"
#include "Projectile.h"

using namespace std;

//data structures to contain game data
vector<Projectile> projectiles;
vector<Enemy> enemies;


//player starts in the center (and Should stay there)
Player player = { CENTER_SCREEN, 100, 15, 1, 1.5f };


void Initialize() {
    InitWindow(WIDTH, HEIGHT, "AutoShooter");
    SetTargetFPS(FPS);
  
    // Initialize game variables
    //TODO: Randomize Spawning the Enemies out of the Screen
    enemies.push_back(Enemy{ {200, 100.0f}, 50, 20, 1, 0.5f });
    enemies.push_back(Enemy{ {400, 800.0f}, 50, 20, 1, 0.5f });
    enemies.push_back(Enemy{ {600, 150.0f}, 50, 20, 1, 0.5f });
    enemies.push_back(Enemy{ {1000, 700.0f}, 50, 20, 1, 0.5f });
}

void HandleInput() {

}

int main() 
{
    Initialize();
    
    //GameLoop
    while (!WindowShouldClose()) 
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
            enemy.Move(inputDirection, player.speed);
        }

        Vector2 shootDirection = inputDirection;
        player.SetWeapon(MachineGun());

        if (IsKeyPressed(SHOOT))
        {    
            Vector2 shootDirection = { 0.0f, -1.0f };
            if (inputDirection.x != 0.0f || inputDirection.y != 0.0f)
            {
                shootDirection = inputDirection;
            }
            Weapon w = player.GetWeapon();
            vector<Projectile> bullets = w.m_Shoot(player.position, shootDirection);
            for (auto b: bullets) {
                projectiles.push_back(b);
            }   
        }
         
        //DRAWING 2 THE SCREEN
        BeginDrawing();
            ClearBackground(RAYWHITE);
            //Draw PLAYER
            DrawCircle(player.position.x, player.position.y, 20, BLUE);     
            // Draw ENEMIES
            for (Enemy& enemy : enemies) 
            {
                //we get the vector of the directon 2 the player, the enemy wil move towars the player
                Vector2 directionToPlayer = { player.position.x - enemy.position.x, player.position.y - enemy.position.y };
                //we get the lenght of the returned vector to normalize it
                float directionLength = sqrt(directionToPlayer.x * directionToPlayer.x + directionToPlayer.y * directionToPlayer.y);
                //we normalize it
                directionToPlayer.x /= directionLength;
                directionToPlayer.y /= directionLength;

                // Mettre à jour la position de l'ennemi en fonction de la direction
                float enemySpeed = 1.5f; // Vitesse de déplacement de l'ennemi
                //we update the position and render it to screen
                enemy.position.x += directionToPlayer.x * enemySpeed;
                enemy.position.y += directionToPlayer.y * enemySpeed;
                DrawCircle(enemy.position.x, enemy.position.y, enemy.size, RED);
            }

            // Draw PROJECTILES
            for (const Projectile& projectile : projectiles)
            {   
                DrawCircle(projectile.position.x, projectile.position.y, projectile.size, projectile.color);
            }

            //chck collisions ENEMY -> PLAYER
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

            //MOVE PROJECTILES and chck collisions with - ENEMY 
            for (auto itProjectile = projectiles.begin(); itProjectile != projectiles.end(); ) {
                auto& projectile = *itProjectile;
                // Move projectile
                projectile.Move();
                bool projectileHit = false;
                
                // Iterate through enemies
                for (auto itEnemy = enemies.begin(); itEnemy != enemies.end(); ) {
                    auto& enemy = *itEnemy;
                    if (CheckCollisionCircles(projectile.position, projectile.size, enemy.position, enemy.size)) {
                        // Projectile hits an enemy
                        enemy.health -= projectile.damage;
                        cout << "enemy health: " << enemy.health << endl;
                        projectileHit = true;// Mark projectile as hit
                        if (enemy.health <= 0) {
                            // Erase the enemy and update 'itEnemy' to point to the next element
                            itEnemy = enemies.erase(itEnemy);
                        }
                        else {
                            //if COLLIDE && enemy.health > 0 - check the nxt enemy
                            ++itEnemy;
                        }
                        player.health += 1; // Increment player health

                        break; // No need to continue checking other enemies for this projectile
                    }
                    else {
                        //If NOT COLLIDE Go to the next enemy
                        ++itEnemy;
                    }
                }
                if (projectileHit) {
                    // Erase the projectile and update 'itProjectile' to point to the next element
                    itProjectile = projectiles.erase(itProjectile);
                }
                else {
                    // Go to the next projectile
                    ++itProjectile;
                }
            }


            /************* DRAW UI********************************/
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
