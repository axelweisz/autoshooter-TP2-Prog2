#pragma once
#include <vector>
#include <raylib.h>
#include "Weapon.h"
#include "Experience.h"

class Character
{
public:
    Vector2 position;
    int size;
    Color color;
    int level;
    float speed;
    int health;

public:
    void Move(Vector2 _direction, float _speed);
    void Draw();
};

class Player : public Character
{
private:
    Weapon weapon;

public:
    Player(Vector2 _startPos, int _size, Color _color, float _speed, int _startHealth, int _level);
    Weapon GetWeapon();
    void SetWeapon(Weapon _weapon);
};

class Enemy : public Character
{
private:
    bool hasDroppedOrb;

public:
    Enemy(Vector2 _startPos, int _size, Color _color, int _level, int _startHealth, float _speed);

    void Move(Vector2 _direction, float _speed, std::vector<Projectile>& projectiles);
    Experience CreateExperience();
};
