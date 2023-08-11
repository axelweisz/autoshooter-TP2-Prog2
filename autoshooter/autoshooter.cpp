#include <raylib.h>
#include <iostream>
#include <vector>

const char UP = 'W';
const char DOWN = 'S';
const char RIGHT = 'D';
const char LEFT = 'A';
const char CHEAT = '5';
const char SHOOT = 32;

const float playerSpeed = 5.0f;
float shootSpeed = 10.0f;

struct Player 
{
    Vector2 position;
    int health;
    int level;
};

struct Enemy 
{
    Vector2 position;
    int health;
    Enemy(Vector2 startPos, int startHealth) : position(startPos), health(startHealth) {}
};

struct Projectile 
{
    Vector2 position;
    Vector2 velocity;
    int damage;
};

std::vector<Projectile> projectiles;
std::vector<Enemy> enemies;

int main() 
{
    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Autoshooter");

    Player player = { { screenWidth / 2, screenHeight / 2 }, 100, 1 };

    // Initialize game variables
    enemies.push_back(Enemy{ {200.0f, 200.0f}, 50 });
    SetTargetFPS(60);

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
        float inputLength = sqrt(inputDirection.x * inputDirection.x + inputDirection.y * inputDirection.y);
        if (inputLength != 0.0f)
        {
            inputDirection.x /= inputLength;
            inputDirection.y /= inputLength;
        }

        // normalized input
        float playerSpeed = 5.0f; 
        player.position.x += inputDirection.x * playerSpeed;
        player.position.y += inputDirection.y * playerSpeed;

        if (IsKeyPressed(SHOOT)) 
        {
            
            Vector2 shootDirection = { 0.0f, -1.0f };
            if (inputDirection.x != 0.0f || inputDirection.y != 0.0f) 
            {
                shootDirection = inputDirection; 
            }

            float shootSpeed = 10.0f; 
            projectiles.push_back({ player.position, shootDirection, 10 });
        }
        Vector2 shootDirection = inputDirection;
        float shootSpeed = 10.0f;
        projectiles.push_back({ player.position, shootDirection, 10 });
        if (IsKeyPressed(CHEAT)) 
        {
            player.level + 5;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircle(player.position.x, player.position.y, 20, BLUE);

        // Draw enemies
        for (const Enemy& enemy : enemies) 
        {
            DrawCircle(enemy.position.x, enemy.position.y, 15, RED);
        }

        // Draw projectiles
        for (const Projectile& projectile : projectiles) 
        {
            DrawCircle(projectile.position.x, projectile.position.y, 5, GREEN);
        }
        for (size_t i = 0; i < projectiles.size(); ++i) {
            auto& projectile = projectiles[i];
            projectile.position.x += projectile.velocity.x * shootSpeed;
            projectile.position.y += projectile.velocity.y * shootSpeed;

            // Check for collision with enemies
            for (auto& enemy : enemies) {
                if (CheckCollisionCircles(projectile.position, 5, enemy.position, 15)) {
                    // Projectile hit an enemy
                    projectiles.erase(projectiles.begin() + i); // Remove projectile
                    enemy.health -= projectile.damage; // Decrease enemy health
                    break; // Exit enemy loop since the projectile hit
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