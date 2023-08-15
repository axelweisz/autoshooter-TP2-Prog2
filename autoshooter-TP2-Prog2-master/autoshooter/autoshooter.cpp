#include <iostream>
#include <raylib.h>
#include <cstdlib>
#include <ctime>

#include "GameData.h"
#include "Character.h"
#include "Projectile.h"
#include "Experience.h"

using namespace std;

const int DESIRED_ENEMY_COUNT = 4;

// Initialize the random number generator


// Function to generate a random float between min and max
float RandomFloat(float min, float max) 
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

//data structures to contain game data
vector<Projectile> projectiles;
vector<Enemy> enemies;
vector<Experience> experienceVector;

//player starts in the center (and Should stay there)
Player player = { CENTER_SCREEN, 100, 15, 1, 1.5f };

void Initialize() {
    InitWindow(WIDTH, HEIGHT, GAME_NAME.c_str());
    SetTargetFPS(FPS);
  
    // Initialize game variables
    //TODO: Randomize Spawning the Enemies out of the Screen
    enemies.push_back(Enemy{ {600, 300.0f}, 50, 15, 1, 1.5f });
    enemies.push_back(Enemy{ {1000, 800.0f}, 50, 25, 1, 1.5f });
    enemies.push_back(Enemy{ {150.0f, 150.0f}, 50, 15, 1, 1.5f });
    enemies.push_back(Enemy{ {50.0f, 300.0f}, 50, 15, 1, 1.5f });

}


void HandleInput() {

}

int main() 
{
    srand(static_cast<unsigned int>(time(nullptr)));
    Initialize();
    int maxExperience = 10; // Set the maximum experience needed to level up
    int currentExperience = 0; // Initialize player's current experience
    float blueBarMaxLength = 200.0f; // Maximum length of the blue bar
    float blueBarLength = 0.0f; // Initialize the blue bar length
    //Interaction
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

        //We use the normalized input to move the Player (we move everybody elsse, not the player)
       

        //TODO: Character Move Method?
        for (auto& enemy : enemies) {
             enemy.position.x += inputDirection.x * playerSpeed;
             enemy.position.y += inputDirection.y * playerSpeed;
            enemy.Move(inputDirection, player.speed, projectiles);
        }


        if (IsKeyPressed(SHOOT)) 
        {
            Vector2 shootDirection = { 0.0f, -1.0f };
            if (inputDirection.x != 0.0f || inputDirection.y != 0.0f) 
            {
                shootDirection = inputDirection; 
            }
            float shootSpeed = 10.0f; 
            Projectile p = { player.position, shootDirection, 10, 5,  GREEN };
            projectiles.push_back(p);
        }

        Vector2 shootDirection = inputDirection;
        float shootSpeed = 10.0f;
     

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
                float enemySpeed = 3.0f; // Vitesse de déplacement de l'ennemi
                //we update the position and render it to screen
                enemy.position.x += directionToPlayer.x * enemySpeed;
                enemy.position.y += directionToPlayer.y * enemySpeed;
                DrawCircle(enemy.position.x, enemy.position.y, enemy.size, RED);
            }
            int currentEnemyCount = enemies.size();
            if (currentEnemyCount < DESIRED_ENEMY_COUNT) {
                int enemiesToSpawn = DESIRED_ENEMY_COUNT - currentEnemyCount;

                for (int i = 0; i < enemiesToSpawn; ++i) {
                    // Calculate a random edge for spawning (1 = top, 2 = right, 3 = bottom, 4 = left)
                    int randomEdge = rand() % 4 + 1;

                    // Calculate random position on the chosen edge
                    Vector2 newEnemyPosition;
                    if (randomEdge == 1) {
                        newEnemyPosition = { RandomFloat(0, WIDTH), 0 };
                    }
                    else if (randomEdge == 2) {
                        newEnemyPosition = { WIDTH, RandomFloat(0, HEIGHT) };
                    }
                    else if (randomEdge == 3) {
                        newEnemyPosition = { RandomFloat(0, WIDTH), HEIGHT };
                    }
                    else if (randomEdge == 4) {
                        newEnemyPosition = { 0, RandomFloat(0, HEIGHT) };
                    }

                    // Create and add a new enemy to the vector
                    enemies.push_back(Enemy{ {newEnemyPosition}, 50, 15, 1, 1.5f });
                }
            }
            // Draw PROJECTILES
            for (const Projectile& projectile : projectiles)
            {
                DrawCircle(projectile.position.x, projectile.position.y, 5, GREEN);
            }

            //chck collisions ENEMY -> PLAYER
            for (int i = 0; i < enemies.size(); i++)
            {
                for (auto& enemy : enemies) {
                    if (CheckCollisionCircles(enemy.position, enemy.size, player.position, player.size)) {
                        player.health -= 1;
                        std::cout << "player health: " << player.health;
                        enemies.erase(enemies.begin() + i);
                        enemy.Move(inputDirection, player.speed, projectiles);
                    }
                }
            }
            //move projs
            //and chck collisions PROJECTIBLE - ENEMY 
            for (auto& projectile : projectiles) {
                //move projectible
                projectile.position.x += projectile.velocity.x * shootSpeed;
                projectile.position.y += projectile.velocity.y * shootSpeed;

                //enemies.begins gets the first item. 
                //.end() returns an index out of reach, thus the condition  it != enemies.end()
                for (auto it = enemies.begin(); it != enemies.end(); ) {
                    auto& enemy = *it; 
                    if (CheckCollisionCircles(projectile.position, projectile.size, enemy.position, enemy.size)) {
                        // Projectile hit an enemy
                        enemy.health -= projectile.damage; 
                        if (enemy.health <= 0) 
                        {
                            it = enemies.erase(it);
                            Experience newExperience = enemy.CreateExperience();
                            experienceVector.push_back(newExperience);
                            Vector2 newEnemyPosition = 
                            {
                               enemy.position.x, enemy.position.y 
                            };
                            for (const Experience& experience : experienceVector) {
                                DrawCircleV(experience.position,    experience.radius,  experience.color);
                            }
                            // Create a new enemy and add it to the vector
                            enemies.push_back(Enemy{ newEnemyPosition, 50, 15, 1, 1.5f });
                            break; //out of inner loop and goes to the next projectile in projectiles vector 
                        }
                        else 
                        {
                            ++it; //go 2  nxt enemy - if enemy.health > 0 
                        }
                    }
                    else
                    {
                        ++it;  //go nxt enemy - if ENEMY NOT COLLIDED
                    }
                }
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

        // Draw UI
        DrawRectangle(10, 10, player.health * 2, 20, GREEN); // Health bar
        DrawRectangle(10, 40, blueBarLength, 20, BLUE); // experience bar
        blueBarLength = static_cast<float>(currentExperience) / maxExperience * blueBarMaxLength;
        if (currentExperience >= maxExperience)
        {
            player.level += 1;
            currentExperience -= maxExperience;
            blueBarLength = 0.0f; // Reset blue bar length
        }

        
        
        // End UI drawing
        EndDrawing();

        //The Line Below was intantiating etra circles besides projectiles
     //projectiles.push_back({ player.position, shootDirection, 10 });
        if (IsKeyPressed(CHEAT))
        {
            player.level + 5;
        }
    }

    CloseWindow();

    return 0;
}
