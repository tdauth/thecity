//*******************************************************************
//Weapon Functions
//*******************************************************************
#if defined WeaponFunctions_included
  	#endinput
#endif
#define WeaponFunctions_included
#pragma library WeaponFunctions

//-- Functions --
public AddWeapon(Model, Type, Ammo, Float:PositionX, Float:PositionY, Float:PositionZ)
{
	new WeaponId = WEAPONS;
    if (WeaponId < MAX_WEAPONS)
	{
    	WEAPON_TYPE[WeaponId] = Type;
    	WEAPON_AMMO[WeaponId] = Ammo;
    	//AddStaticPickup(WEAPON_TYPE_MODEL[Type], 8, PositionX, PositionY, PositionZ);
    	WEAPONS++;
    	return AddStaticPickup(WEAPON_TYPE_MODEL[Type], 8, PositionX, PositionY, PositionZ);
	}
	return -1; //Weapons (Pickups beginnen mit 0???
}
