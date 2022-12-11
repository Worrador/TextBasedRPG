#include "Roles.h"

Roles::Roles() {
	//  Role			 hpMax,	dmgMax, defence, staminaMax, hpIncr, dmgIncr, defIncr, staminaIncr
	roles = {
		{Role::Warrior, { 12,	3,		2,		 10,		 2,		 1,		  1,	   3 }},
		{Role::Mage,	{ 6,	12,		0,		 5,			 1,		 3,		  1,	   1 }},
		{Role::Rouge,	{ 9,	7,		1,		 7,			 2,		 1,		  2,	   2 }},
		{Role::Ranger,	{ 8,	8,		1,		 6,			 1,		 2,		  2,	   2 }},
		{Role::Acolyte, { 6,	6,		1,		 10,		 1,		 2,		  1,	   3 }},
	};
}

