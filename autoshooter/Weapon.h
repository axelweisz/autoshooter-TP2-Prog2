#pragma once

#include <string>

#include "GameData.h"
#include "Projectile.h"

using namespace std;

class Weapon
{
//base Weapon
public:
		string name;
		float fireRate;
		float bulletSpeed;
		int bulletDamage;
		int bulletSize;
		Color bulletColor;
		vector<Projectile> bullets;

public:
	Weapon();
	Weapon(string, float, float, int, int, Color);
	virtual ~Weapon();
	virtual vector<Projectile> m_Shoot(Vector2, Vector2);
};

class MachineGun : public Weapon
{
private:
	int m_numBulletsShotAtOnce;

public:
	MachineGun();
	vector<Projectile> m_Shoot(Vector2, Vector2) override;
};