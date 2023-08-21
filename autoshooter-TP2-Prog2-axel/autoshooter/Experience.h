#pragma once
#include <raylib.h>

class Experience
{
public:
    Vector2 position;
    float radius;
    Color color;

    Experience(Vector2 _position, float _radius, Color _color);
};

