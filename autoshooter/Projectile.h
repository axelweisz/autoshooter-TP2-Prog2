#pragma once
#include <raylib.h>

class Projectile
{
public:
    Vector2 position;
    Vector2 velocity;
    int damage;
    int size;
    Color color;

public:
    Projectile(Vector2 _startPosition, Vector2 _direction, int _damage, int _size, Color _color);

public:
    Vector2 GetPosition() {  return position; }


};

