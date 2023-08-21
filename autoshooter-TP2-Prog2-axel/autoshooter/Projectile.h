#pragma once
#include <raylib.h>

class Projectile
{
public:
    Vector2 position;
    Vector2 direction;
    int damage;
    int size;
    float speed;
    Color color;

public:
    Projectile();
    Projectile(
        Vector2 _startPosition, 
        Vector2 _direction, 
        int _damage, 
        int _size, 
        float _speed,
        Color _color
    );

public:
    void Move();
    void Draw();
};

