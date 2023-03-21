#pragma once
#include <iostream>
#include <algorithm>

using roleName = std::string;

class Role
{
public:
	Role(const roleName& roleName, const int& startingHpMax, const int& startingDmgMax, const int& startingDef,
		const int& startingStaminaMax, const int& hpIncr, const int& dmgIncr, const int& defIncr, const int& staminaIncr) :
		roleName(roleName), startingHpMax(startingHpMax), startingDmgMax(startingDmgMax), startingDef(startingDef), 
		startingStaminaMax(startingStaminaMax), hpIncr(hpIncr), dmgIncr(dmgIncr), defIncr(defIncr), staminaIncr(staminaIncr) {};

	// Functions

	// Accessors
	inline const roleName& getRoleName() const { return roleName; };
	inline const int& getStartingHpMax() const { return startingHpMax; };
	inline const int& getStartingDmgMax() const { return startingDmgMax; };
	inline const int& getStartingDef() const { return startingDef; };
	inline const int& getStartingStaminaMax() const { return startingStaminaMax; };
	inline const int& getHpIncr() const { return hpIncr; };
	inline const int& getDmgIncr() const { return dmgIncr; };
	inline const int& getDefIncr() const { return defIncr; };
	inline const int& getStaminaIncr() const { return staminaIncr; };

protected:
	roleName roleName;
	int hpIncr;
	int dmgIncr;
	int defIncr;
	int staminaIncr;

private:
	int startingHpMax;
	int startingDmgMax;
	int startingDef;
	int startingStaminaMax;
};


