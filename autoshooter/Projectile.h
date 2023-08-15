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
    Projectile(Vector2 _startPosition,  int _damage, int _size, Color _color);
    Projectile(Vector2 _startPosition, Vector2 _direction);

public:
    Vector2 GetPosition() {  return position; }
    void Move();
};

