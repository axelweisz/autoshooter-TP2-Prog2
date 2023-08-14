#include <raylib.h>
#include <iostream>
#include <vector>

//GLOBAL CONSTS
//interaction
const char UP = 'W';
const char DOWN = 'S';
const char RIGHT = 'D';
const char LEFT = 'A';
const char CHEAT = '5';
//Numeric value settings
const char SHOOT = 32;
const float playerSpeed = 5.0f;
float shootSpeed = 10.0f;
//Window data
const int screenWidth = 1280;
const int screenHeight = 800;

//STRUCTS (Characters)
struct Player 
{
    Vector2 position;
    int health;
    int size;
    int level; 
};

struct Enemy 
{
    Vector2 position;
    int health;
    int size;
    Enemy(Vector2 startPos, int startHealth, int size) : position(startPos), health(startHealth), size(size) {}
};

struct Projectile 
{
    Vector2 position;
    Vector2 velocity;
    int damage;
    int size;
    Color color;
};

//data structures to contain game data
std::vector<Projectile> projectiles;
std::vector<Enemy> enemies;

int main() 
{

    InitWindow(screenWidth, screenHeight, "Autoshooter");
    SetTargetFPS(60);

    //player starts in the center (and Should stay there)
    Player player = { { screenWidth / 2, screenHeight / 2 }, 100, 15, 1 };

    // Initialize game variables
    //TODO: Randomize Spawning the Enemies out of the Screen
    enemies.push_back(Enemy{ {600, 300.0f}, 50, 15 });
    enemies.push_back(Enemy{ {1000, 800.0f}, 50, 25 });
    enemies.push_back(Enemy{ {150.0f, 150.0f}, 50, 15 });
    enemies.push_back(Enemy{ {50.0f, 300.0f}, 50, 15 });



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
        float playerSpeed = 2.0f; 

        //TODO: Create random enemies?
        for (auto& enemy : enemies) {
             enemy.position.x += inputDirection.x * playerSpeed;
             enemy.position.y += inputDirection.y * playerSpeed;
        }
      //  player.position.x += inputDirection.x * playerSpeed;
      //  player.position.y += inputDirection.y * playerSpeed;

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
        //The Line Below was intantiating etra circles besides projectiles
        //projectiles.push_back({ player.position, shootDirection, 10 });
        if (IsKeyPressed(CHEAT)) 
        {
            player.level + 5;
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
                float enemySpeed = 3.0f; // Vitesse de déplacement de l'ennemi
                //we update the position and render it to screen
                enemy.position.x += directionToPlayer.x * enemySpeed;
                enemy.position.y += directionToPlayer.y * enemySpeed;
                DrawCircle(enemy.position.x, enemy.position.y, enemy.size, RED);
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
                        if (enemy.health <= 0) {
                            it = enemies.erase(it);  // Erase the enemy and update 'it' to point to the next element
                            break; //out of inner loop and goes to the next projectile in projectiles vector 
                        }
                        else {
                            ++it; //go 2  nxt enemy - if enemy.health > 0 
                        }
                        //TO DO - ADD POINTS TO THE PLAYER
                        //TO DO - XPs are instantiated here I guess

                    }
                    else {
                        ++it;  //go nxt enemy - if ENEMY NOT COLLIDED
                    }
                }
            }


        // Draw UI
        DrawRectangle(10, 10, player.health * 2, 20, GREEN); // Health bar
        DrawRectangle(10, 40, player.level * 50, 20, BLUE);  // Experience bar

        // End UI drawing
        EndDrawing();
    }

    CloseWindow();

    return 0;
}