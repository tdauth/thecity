//*******************************************************************
//Weapon Type Functions
//*******************************************************************
#if defined WeaponTypeFunctions_included
  	#endinput
#endif
#define WeaponTypeFunctions_included
#pragma library WeaponTypeFunctions

//-- Functions --
GetWeaponTypeByModel(Model)
{
	for (new I0 = 0; I0 < WEAPON_TYPES; I0++)
	{
	    if (WEAPON_TYPE_MODEL[I0] == Model)
	    {
	        return I0;
	    }
	}
	return -1;
}

GetKillReasonWeaponType(Reason)
{
	for (new I0; I0 < WEAPON_TYPE_TYPES; I0++)
	{
		for (new I1; I1 < WEAPON_TYPE_TYPE_REASONS[I0]; I1++)
		{
			if (WEAPON_TYPE_TYPE_REASON_ID[I0][I1] == Reason)
 			{
  				return I0;
			}
		}
	}
	return -1;
}

public AddAccountPlayerWeaponSkill(PlayerId, AccountId, AccountPlayerId, WeaponTypeTypeId, Value, Add)
{
	if (Add)
	{
		ACCOUNT_P_WEAPON_SKILL[AccountId][AccountPlayerId][WeaponTypeTypeId] += Value;
	}
	else
	{
	    ACCOUNT_P_WEAPON_SKILL[AccountId][AccountPlayerId][WeaponTypeTypeId] -= Value;
	}
 	new InfoMessage[MAX_STRING];
 	format(InfoMessage, sizeof(InfoMessage), "~w~+%d %s-Fertigkeit", Value, WEAPON_TYPE_TYPE_NAME[WeaponTypeTypeId]);
 	GameTextForPlayer(PlayerId, InfoMessage, ConvertSeconds(6), 5);
	return ACCOUNT_P_WEAPON_SKILL[AccountId][AccountPlayerId][WeaponTypeTypeId];
}

public AddPlayerWeaponSkill(PlayerId, WeaponTypeTypeId, Value, Add)
{
	return AddAccountPlayerWeaponSkill(PlayerId, PLAYER_ACCOUNT[PlayerId], PLAYER_ACCOUNT_PLAYER[PlayerId], WeaponTypeTypeId, Value, Add);
}

public CreateWeaponTypeForPlayer(PlayerId, WeaponTypeId, Ammo)
{
	GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WeaponTypeId], Ammo);
    new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "%s erhalten (%d Ladungen).", WEAPON_TYPE_NAME[WeaponTypeId], Ammo);
	SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, InfoMessage);
	return true;
}

public AddWeaponType(Name[MAX_WEAPON_TYPE_NAME], Model, Price, Type, Ammo, GeneralAmmo)
{
	new WeaponTypeId = WEAPON_TYPES;
    if (WeaponTypeId < MAX_WEAPON_TYPES)
	{
	    WEAPON_TYPE_NAME[WeaponTypeId] = Name;
	    WEAPON_TYPE_MODEL[WeaponTypeId] = Model;
   		WEAPON_TYPE_PRICE[WeaponTypeId] = Price;
   		WEAPON_TYPE_TYPE[WeaponTypeId] = Type;
   		WEAPON_TYPE_AMMO[WeaponTypeId] = Ammo;
   		WEAPON_TYPE_GENERAL_AMMO[WeaponTypeId] = GeneralAmmo;
   		WEAPON_TYPES++;
		return WeaponTypeId;
	}
	return -1;
}

public AddWeaponTypeType(Name[MAX_WEAPON_TYPE_TYPE_NAME])
{
    new WeaponTypeTypeId = WEAPON_TYPE_TYPES;
    if (WeaponTypeTypeId < MAX_WEAPON_TYPE_TYPES)
	{
	    WEAPON_TYPE_TYPE_NAME[WeaponTypeTypeId] = Name;
	    WEAPON_TYPE_TYPE_REASONS[WeaponTypeTypeId] = 0;
   		WEAPON_TYPE_TYPES++;
		return WeaponTypeTypeId;
	}
	return -1;
}

public AddWeaponTypeTypeReason(Id)
{
    new WeaponTypeTypeId = (WEAPON_TYPE_TYPES - 1);
    new WeaponTypeTypeReasonId = WEAPON_TYPE_TYPE_REASONS[WeaponTypeTypeId];
    if (WeaponTypeTypeReasonId < MAX_WEAPON_TYPE_TYPE_REASONS)
	{
	    WEAPON_TYPE_TYPE_REASON_ID[WeaponTypeTypeId][WeaponTypeTypeReasonId] = Id;
   		WEAPON_TYPE_TYPE_REASONS[WeaponTypeTypeId]++;
		return WeaponTypeTypeReasonId;
	}
	return -1;
}
