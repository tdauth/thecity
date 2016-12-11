//*******************************************************************
//Vehicle Type Functions
//*******************************************************************
#if defined VehicleTypeFunctions_included
  	#endinput
#endif
#define VehicleTypeFunctions_included
#pragma library VehicleTypeFunctions

//-- Functions --
VehicleTypeRequiresPetrol(VehicleTypeId)
{
	return(VEHICLE_TYPE_TYPE[VehicleTypeId] == VEHICLE_TYPE_TYPE_CAR || VEHICLE_TYPE_TYPE[VehicleTypeId] == VEHICLE_TYPE_TYPE_MOTORBIKE);
}

public CreateVehicleTypeForPlayer(PlayerId, VehicleTypeId)
{
	new AccountId = PLAYER_ACCOUNT[PlayerId];
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
    new Message[MAX_STRING];
	if ((ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId] == VEHICLE_TYPE_PROFESSION[VehicleTypeId] && VEHICLE_TYPE_PROFESSION[VehicleTypeId] != -1) || VEHICLE_TYPE_PROFESSION[VehicleTypeId] == -1)
	{
	    new Float:PositionX, Float:PositionY, Float:PositionZ, Float:FacingAngle;
	    GetPlayerPos(PlayerId, PositionX, PositionY, PositionZ);
	    GetPlayerFacingAngle(PlayerId, FacingAngle);
	    AddVehicle(VehicleTypeId, PositionX, PositionY, PositionZ, FacingAngle, -1, -1);
   		format(Message, sizeof(Message), "%s gekauft.", VEHICLE_TYPE_NAME[VehicleTypeId]);
		SendClientMessage(PlayerId, COLOUR_GREEN, Message);
		return true;
	}
	else
	{
	    format(Message, sizeof(Message), "Sie müssen als %s tätig sein, um dieses Fahrzeug benutzen zu können.", VEHICLE_TYPE_PROFESSION[VehicleTypeId]);
    	SendClientMessage(PlayerId, COLOUR_RED, Message);
	}
	return false;
}

public AddVehicleType(Name[MAX_VEHICLE_TYPE_NAME], Model, Price, Type, MaxPlaces, MaxPetrol, Profession)
{
	new VehicleTypeId = VEHICLE_TYPES;
    if (VehicleTypeId < MAX_VEHICLE_TYPES)
	{
    	VEHICLE_TYPE_NAME[VehicleTypeId] = Name;
    	VEHICLE_TYPE_MODEL[VehicleTypeId] = Model;
    	VEHICLE_TYPE_PRICE[VehicleTypeId] = Price;
    	VEHICLE_TYPE_TYPE[VehicleTypeId] = Type;
    	VEHICLE_TYPE_MAX_PLACES[VehicleTypeId] = MaxPlaces;
    	VEHICLE_TYPE_MAX_PETROL[VehicleTypeId] = MaxPetrol;
    	VEHICLE_TYPE_PROFESSION[VehicleTypeId] = Profession;
    	VEHICLE_TYPES++;
    	return VehicleTypeId;
	}
	return -1;
}

public GetVehicleTypeByModel(Model)
{
	for (new I0 = 0; I0 < VEHICLE_TYPES; I0++)
	{
	    if (VEHICLE_TYPE_MODEL[I0] == Model)
	    {
			return I0;
		}
	}
	
	return -1;
}

