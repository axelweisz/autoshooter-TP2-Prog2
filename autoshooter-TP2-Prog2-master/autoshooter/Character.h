#pragma once
#include <vector>
#include <raylib.h>
#include "Projectile.h"
#include "Experience.h"


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
    Vector2 shootDirection;

public:
        Player(Vector2 startPos, int startHealth, int size, int level, float _speed);
};


class Enemy :public Character
{
private: 
    bool hasDroppedOrb;
public:
        Enemy(Vector2 startPos, int startHealth, int size, int level, float _speed);  

        void Move(Vector2 _direction, float _speed, std:: vector<Projectile>& projectiles);
        Experience CreateExperience();
};

