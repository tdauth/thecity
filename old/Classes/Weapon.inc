//*******************************************************************
//Weapon
//*******************************************************************
#if defined Weapon_included
  	#endinput
#endif
#define Weapon_included
#pragma library Weapon

//-- Variables --
new WEAPONS = 0; //Pickups beginnen mit 0

//-- Properties --
new WEAPON_TYPE[MAX_WEAPONS];
new WEAPON_AMMO[MAX_WEAPONS];
