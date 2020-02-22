#pragma once

class Ability
{
private:
	float _curHP, _maxHP;
	float _atk;
	bool _isDead;

public:
	Ability() : _curHP(0), _maxHP(0), _atk(0), _isDead(false) {};
	Ability(float curHP, float maxHP, float atk)
		: _curHP(curHP), _maxHP(maxHP), _atk(atk), _isDead(false) {};

	float GetCurrentHP() { return _curHP; }
	float GetMaxHP() { return _maxHP; }
	float GetAttackPoint() { return _atk; }

	void setHP(float value);
	void DamageHP(float value);
	void HealHP(float value);
	bool IsDead();
};

