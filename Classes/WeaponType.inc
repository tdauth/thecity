//*******************************************************************
//Weapon Type
//*******************************************************************
#if defined WeaponType_included
  	#endinput
#endif
#define WeaponType_included
#pragma library WeaponType

//-- Variables --
new WEAPON_TYPES = 0;
new WEAPON_TYPE_TYPES = 0;

//-- Properties --
new WEAPON_TYPE_NAME[MAX_WEAPON_TYPES][MAX_WEAPON_TYPE_NAME];
new WEAPON_TYPE_MODEL[MAX_WEAPON_TYPES];
new WEAPON_TYPE_PRICE[MAX_WEAPON_TYPES];
new WEAPON_TYPE_TYPE[MAX_WEAPON_TYPES];
new WEAPON_TYPE_AMMO[MAX_WEAPON_TYPES];
new WEAPON_TYPE_GENERAL_AMMO[MAX_WEAPON_TYPES];
//Eigene Klasse
new WEAPON_TYPE_TYPE_NAME[MAX_WEAPON_TYPE_TYPES][MAX_WEAPON_TYPE_TYPE_NAME];
new WEAPON_TYPE_TYPE_REASONS[MAX_WEAPON_TYPES];
new WEAPON_TYPE_TYPE_REASON_ID[MAX_WEAPON_TYPE_TYPES][MAX_WEAPON_TYPE_TYPE_REASONS];
