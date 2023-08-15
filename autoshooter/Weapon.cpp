#include "Weapon.h"
#include "GameData.h"
/******************** BASE WEAPON **************************/
Weapon::Weapon()
{ 
		name = "Base Weapon";
		bulletSpeed = 2.0f;
		fireRate = 1.0f;
		bulletSpeed = 2.0f;
		bulletDamage = 5;
		bulletSize = 5;
		bulletColor = GRAY;
}

Weapon::Weapon(string _name, float _fireRate, float _bulletSpeed, int _bulletDamage, int _bulletSize, Color _color)
{
	name = _name;
	fireRate = _fireRate;
	bulletSpeed = _bulletSpeed;
	bulletDamage = _bulletDamage;
	bulletSize = _bulletSize;
	bulletColor = _color;
}

Weapon::~Weapon()
{
}

vector<Projectile> Weapon::m_Shoot(Vector2 _pos, Vector2 _dir)
{ 
	Projectile p = Projectile(_pos, _dir, bulletDamage, bulletSize, bulletSpeed, bulletColor);
	bullets.push_back(Projectile(p));
	return bullets;
}


/******************** MACHINE GUN **************************/


MachineGun::MachineGun()
{
	m_numBulletsShotAtOnce = 6;
}

vector<Projectile>  MachineGun::m_Shoot(Vector2 _pos, Vector2 _startDir)
{
	float angle = 60 * PI / 180;
	for (int i = 0; i < m_numBulletsShotAtOnce; i++)
	{
		Vector2 rotatedVec;
		rotatedVec.x = _startDir.x * cos(angle * i) - _startDir.y * sin(angle * i);
		rotatedVec.y = _startDir.x * sin(angle * i) - _startDir.y * cos(angle * i);
		Projectile p = Projectile(_pos, rotatedVec, bulletDamage, bulletSize, bulletSpeed, bulletColor);
		bullets.push_back(p);
	}
	return bullets;
}
