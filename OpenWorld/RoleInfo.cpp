#include "RoleInfo.h"

RoleInfo::RoleInfo() {
	//  Role			 hpMax,	dmgMax, defence, staminaMax, hpIncr, dmgIncr, defIncr, staminaIncr
	RoleStats = {
		{Role::Warrior, { 12,	3,		2,		 10,		 2,		 1,		  1,	   3 }},
		{Role::Mage,	{ 6,	12,		0,		 5,			 1,		 3,		  1,	   1 }},
		{Role::Rouge,	{ 9,	7,		1,		 7,			 2,		 1,		  2,	   2 }},
		{Role::Ranger,	{ 8,	8,		1,		 6,			 1,		 2,		  2,	   2 }},
		{Role::Acolyte, { 6,	6,		1,		 10,		 1,		 2,		  1,	   3 }}
	};

	RoleNames = {
		{Role::Warrior, "Warrior"},
		{Role::Mage,	"Mage"},
		{Role::Rouge,	"Rouge"},
		{Role::Ranger,	"Ranger"},
		{Role::Acolyte, "Acolyte"}
	};
}

//TODO: similar for items, stats