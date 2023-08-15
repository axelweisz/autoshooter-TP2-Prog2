#include "Projectile.h"

//Base Constructor
Projectile::Projectile()
{  
	position = { 0, 0 };
	direction = { 0,0 };
	damage = 10;
	size = 3;
	speed = 2.0f;
	color = GOLD;
}

//complete constructor
Projectile::Projectile(Vector2 _startPosition, Vector2 _direction, int _damage, int _size, float _speed,  Color _color)
{
	position = _startPosition;
	direction = _direction;
	damage = _damage;
	size = _size;
	speed = _speed;
	color = _color;
}

//constructor  start pos and direction


void Projectile::Move()
{
	position.x += direction.x * speed;
	position.y += direction.y * speed;
}
