#include "Projectile.h"

Projectile::Projectile(Vector2 _startPosition, Vector2 _direction, int _damage, int _size, Color _color)
{
	position = _startPosition;
	velocity = _direction;
	damage = _damage;
	size = _size;
	color = _color;
}
