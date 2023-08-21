#include "Character.h"
#include "Experience.h"

/********************  CHARACTER **************************/
void Character::Move(Vector2 _direction, float _speed)
{
	position.x += _direction.x * _speed;
	position.y += _direction.y * _speed;
}

void Character::Draw()
{
	DrawCircle(position.x, position.y, size, color);
}


/******************** PLAYER CHARACTER **************************/
Player::Player(Vector2 _startPos, int _size, Color _color, float _speed, int _startHealth, int _level)
{
	position = _startPos;
	size = _size;
	color = _color;
	speed = _speed;
	level = _level;
	health = _startHealth;
	weapon = Weapon();
}

Weapon Player::GetWeapon()
{
	return weapon;
}

void Player::SetWeapon(Weapon _weapon)
{
	weapon = _weapon;
}

/******************** ENEMY CHARACTER **************************/

Enemy::Enemy(Vector2 _startPos, int _size, Color _color, int _level, int _startHealth, float _speed)
{
	position = _startPos;
	size = _size;
	color = _color;
	level = _level;
	health = _startHealth;
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

