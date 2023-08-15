#include "Projectile.h"

//Base Constructor
Projectile::Projectile()
{  
	position = { 0, 0 };
	direction = { 0,0 };
	damage = 1;
	size = 3;
	speed = 1.5f;
	color = GOLD;
}

//complete constructor
Projectile::Projectile(Vector2 _startPosition,  int _damage, int _size, Color _color)
{
	position = _startPosition;
	damage = _damage;
	size = _size;
	speed = 1.5f;
	color = _color;
}

//constructor only start pos
Projectile::Projectile(Vector2 _startPosition, Vector2 _direction)
{
	position = _startPosition;
	direction = _direction;
	damage = 1;
	size = 3;
	speed = 1.5f;
	color = RED;
}

void Projectile::Move()
{
	position.x += direction.x * speed;
	position.y += direction.y * speed;
}
