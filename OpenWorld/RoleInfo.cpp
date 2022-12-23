#include "RoleInfo.h"

RoleInfo::RoleInfo() {
	//  Role			 hpMax,	dmgMax, defence, staminaMax, hpIncr, dmgIncr, defIncr, staminaIncr
	RoleStats = {
		{"Warrior", { 12,	4,		2,		 10,		 2,		 1,		  1,	   3 }},
		{"Mage",	{ 6,	12,		0,		 5,			 1,		 3,		  1,	   1 }},
		{"Rouge",	{ 9,	7,		1,		 7,			 2,		 1,		  2,	   2 }},
		{"Ranger",	{ 8,	8,		1,		 6,			 1,		 2,		  2,	   2 }},
		{"Acolyte", { 6,	6,		1,		 10,		 1,		 2,		  1,	   3 }}
	};
}

//TODO: similar for items, stats