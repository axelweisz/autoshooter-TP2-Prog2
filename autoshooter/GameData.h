#pragma once
#include <string>
#include <vector>
#include <raylib.h>
using namespace std;

//GLOBAL CONSTS
//interaction sdfasdfsda
const char UP = 'W';
const char DOWN = 'S';
const char RIGHT = 'D';
const char LEFT = 'A';
const char CHEAT = '5';

//Numeric value settings
const char SHOOT = 32;
const float playerSpeed = 5.0f;
const int DESIRED_ENEMY_COUNT = 4;


//Window data
const int WIDTH = 1280;
const int HEIGHT = 800;
const int FPS = 60;
const Vector2 CENTER_SCREEN = { WIDTH / 2, (int)HEIGHT / 2 };
const string GAME_NAME = "AutoShooter";