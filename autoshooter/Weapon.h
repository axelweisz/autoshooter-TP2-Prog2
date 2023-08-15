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
		vector<Projectile> bullets;

public:
	Weapon();
	Weapon(string, float);
	virtual ~Weapon();
	virtual vector<Projectile> m_Shoot(Vector2, Vector2);
};

class MachineGun : public Weapon
{
private:
	int m_numOfBulletsShot;

public:
	MachineGun();
	vector<Projectile> m_Shoot(Vector2, Vector2) override;
};