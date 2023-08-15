#include "Weapon.h"
#include "GameData.h"
/******************** BASE WEAPON **************************/
Weapon::Weapon()
{ 
		name = "Base Weapon";
		fireRate = 1.0f;
}

Weapon::Weapon(string _name, float _fireRate)
{
	name = _name;
	fireRate = _fireRate;
}

Weapon::~Weapon()
{
}

vector<Projectile> Weapon::m_Shoot(Vector2 _pos, Vector2 _dir)
{
	bullets.push_back(Projectile(_pos, _dir));
	return bullets;
}

MachineGun::MachineGun()
{
	m_numOfBulletsShot = 6;
}

vector<Projectile>  MachineGun::m_Shoot(Vector2 _pos, Vector2 _startDir)
{
	float angle = 60 * PI / 180;
	for (int i = 0; i < m_numOfBulletsShot; i++)
	{
		Vector2 rotatedVec;
		rotatedVec.x = _startDir.x * cos(angle * i) - _startDir.y * sin(angle * i);
		rotatedVec.y = _startDir.x * sin(angle * i) - _startDir.y * cos(angle * i);
		Projectile p = Projectile(_pos, rotatedVec);
		bullets.push_back(p);
	}
	return bullets;
}
