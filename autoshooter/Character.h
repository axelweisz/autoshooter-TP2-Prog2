#pragma once
#include <vector>
#include <raylib.h>
#include "Weapon.h"

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

class Player:public Character
{
private:
        Weapon weapon;

public:
        Player(Vector2 _startPos, int _size,  Color _color, float _speed, int _startHealth,  int level);
        Weapon GetWeapon();
        void SetWeapon(Weapon); 
};


class Enemy :public Character
{
public:
        Enemy(Vector2 _startPos, int _size, Color _color, int _level, int _startHealth, float _speed);
        
};

//Enemy(Vector2 startPos, int startHealth, int size) : position(startPos), health(startHealth), size(size) {}
