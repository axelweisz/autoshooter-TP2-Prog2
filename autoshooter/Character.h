#pragma once
#include <vector>
#include <raylib.h>

#include "Weapon.h"

class Character
{
public:
        Vector2 position;
        int health;
        int size;
        int level;
        float speed;
       
public:
    void Move(Vector2 _direction, float _speed);  
    void SetSpeed(int);
};

class Player:public Character
{
private:
    Weapon weapon;

public:
        Player(Vector2 startPos, int startHealth, int size, int level, float _speed);
        Weapon GetWeapon();
        void SetWeapon(Weapon); 
};


class Enemy :public Character
{

public:
        Enemy(Vector2 startPos, int startHealth, int size, int level, float _speed);
};

//Enemy(Vector2 startPos, int startHealth, int size) : position(startPos), health(startHealth), size(size) {}
