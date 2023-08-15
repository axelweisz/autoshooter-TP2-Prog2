#pragma once
#include <string>

//GLOBAL CONSTS
//interaction
const char UP = 'W';
const char DOWN = 'S';
const char RIGHT = 'D';
const char LEFT = 'A';
const char CHEAT = '5';
//Numeric value settings
const char SHOOT = 32;
const float playerSpeed = 1.0f;
float shootSpeed = 10.0f;

//Window data
std::string GAME_NAME = "AutoShooter";
const int WIDTH = 1280;
const int HEIGHT = 800;
const int FPS = 60;
Vector2 CENTER_SCREEN = { WIDTH / 2, HEIGHT / 2 };