#include "Character.h"


void Character::Move(Vector2 _direction, float _speed)
{
	position.x += _direction.x * _speed;
	position.y += _direction.y * _speed;
}

void Character::SetSpeed(int _newSpeed)
{
	speed = _newSpeed;
}

Player::Player(Vector2 _startPos, int _startHealth, int _size, int _level, float _speed)
{
	position = _startPos;
	health = _startHealth;
	size = _size;
	level = _level;
	speed = _speed;
}

Enemy::Enemy(Vector2 _startPos, int _startHealth, int _size, int _level, float _speed)
{
	position = _startPos;
	health = _startHealth;
	size = _size;
	level = _level;
	speed = _speed;
	hasDroppedOrb = false;
}
	void Enemy::Move(Vector2 _direction, float _speed, std::vector<Projectile>& projectiles)
	{
		// ... existing move logic ...

		if (health <= 0 && !hasDroppedOrb)
		{
			hasDroppedOrb = true; // Mark the enemy as having dropped an orb
		}
	}
	Experience Enemy::CreateExperience()
	{
		return Experience(position, 5, ORANGE);
	}


