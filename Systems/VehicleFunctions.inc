//*******************************************************************
//Vehicle Functions
//*******************************************************************
#if defined VehicleFunctions_included
  	#endinput
#endif
#define VehicleFunctions_included
#pragma library VehicleFunctions

//-- Functions --
public RefreshVehicle(VehicleId)
{
    VEHICLE_USED_PLACES[VehicleId] = 0;
	VEHICLE_PETROL[VehicleId] = VEHICLE_TYPE_MAX_PETROL[VEHICLE_TYPE[VehicleId]];
	OpenVehicle(VehicleId);
	return true;
}

public OpenVehicle(VehicleId)
{
    for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
	    SetVehicleParamsForPlayer(VehicleId, I0, false, false);
	}
	return true;
}

public CloseVehicle(VehicleId)
{
    for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
	    SetVehicleParamsForPlayer(VehicleId, I0, false, true);
	}
	return true;
}

public StopVehicle(VehicleId)
{
    for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
	    if (IsPlayerInVehicle(I0, VehicleId))
	    {
	        RemovePlayerFromVehicle(I0);
		}
	}
	CloseVehicle(VehicleId);
	return true;
}

public VehicleRequiresPetrol(VehicleId)
{
	return (VehicleTypeRequiresPetrol(VEHICLE_TYPE[VehicleId]) && VEHICLE_PETROL[VehicleId] < VEHICLE_TYPE_MAX_PETROL[VEHICLE_TYPE[VehicleId]]);
}

public Float:AddVehiclePetrol(VehicleId, Float:Petrol, Add)
{
	if (Add)
	{
	    new VehicleType = VEHICLE_TYPE[VehicleId];
		VEHICLE_PETROL[VehicleId] += Petrol;
		if (VEHICLE_PETROL[VehicleId] > VEHICLE_TYPE_MAX_PETROL[VehicleType])
		{
		    VEHICLE_PETROL[VehicleId] = VEHICLE_TYPE_MAX_PETROL[VehicleType];
		}
	}
	else
	{
	    VEHICLE_PETROL[VehicleId] -= Petrol;
	    if (VEHICLE_PETROL[VehicleId] < 0)
		{
		    VEHICLE_PETROL[VehicleId] = 0;
		}
	}
	return VEHICLE_PETROL[VehicleId];
}

public VehicleUsesPetrol(VehicleId, Float:Speed)
{
	new Float:UsedPetrol = (0.001 * Speed);
	AddVehiclePetrol(VehicleId, UsedPetrol, false);
	return true;
}

public InitVehicleDataTimer()
{
    TIMER_VEHICLE_DATA = SetTimer("TimerFunctionShowVehicleData", ConvertSeconds(1), true);
	return true;
}

public TimerFunctionShowVehicleData()
{
	for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
	    //Player Is Logged In
	    if (PLAYER_ACCOUNT[I0] != -1 && GetPlayerState(I0) != PLAYER_STATE_WASTED && GetPlayerState(I0) !=  PLAYER_STATE_SPECTATING)
	    {
	        new Float:PositionX, Float:PositionY, Float:PositionZ, Float:Facing;
			GetPlayerPos(I0, PositionX, PositionY, PositionZ);
			GetPlayerFacingAngle(I0, Facing);
	        //Player Is Driver
	    	if (GetPlayerState(I0) == PLAYER_STATE_DRIVER)
			{
			    new VehicleId = GetPlayerVehicleID(I0);
			    new VehicleType = VEHICLE_TYPE[VehicleId];
			    new RequiresPetrol = VehicleTypeRequiresPetrol(VehicleType);
			    //Vehicle Requires Petrol
				if (RequiresPetrol)
				{
					//Vehicle Has No Petrol
					if (VEHICLE_PETROL[VehicleId] == 0.0000)
                	{
                    	StopVehicle(VehicleId);
                    	SendMessageToPlayer(I0, MESSAGE_TYPE_SPEED, "Der Tank des Fahrzeugs ist leer.");
                	}
				}
				new AccountId = PLAYER_ACCOUNT[I0];
				new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[I0];
				//Player Has Vehicle Data Showing Activated And Vehicle Has Patrol
	    		if (ACCOUNT_P_SHOW_VEHICLE_DATA[AccountId][AccountPlayerId])
	    		{
					new Float:Distance = GetPlayersDistanceFromXYZ(I0, PLAYER_LAST_POSITION[I0][X], PLAYER_LAST_POSITION[I0][Y], PLAYER_LAST_POSITION[I0][Z]);
					new Name[MAX_VEHICLE_TYPE_NAME];
					Name = VEHICLE_TYPE_NAME[VehicleType];
					new UsedPlaces = VEHICLE_USED_PLACES[VehicleId];
					new MaxPlaces = VEHICLE_TYPE_MAX_PLACES[VehicleType];
					new Speed = floatround(Distance * 3.6);
                    new Float:HealthValue;
					GetVehicleHealth(VehicleId, HealthValue);
					new State = floatround(HealthValue * 0.1);
					new InfoMessage[MAX_STRING];
					format(InfoMessage, sizeof(InfoMessage),"~y~%s~n~~w~Plätze: %d/%d~n~Zustand: %d Prozent~n~Geschwindigkeit: %d Kmh", Name, UsedPlaces, MaxPlaces, State, Speed);
					//Vehicle Requires Petrol
					if (RequiresPetrol)
					{
					    new Petrol;
						new MaxPetrol;
						Petrol = floatround(VEHICLE_PETROL[VehicleId]);
						MaxPetrol = floatround(VEHICLE_TYPE_MAX_PETROL[VEHICLE_TYPE[VehicleId]]);
						VehicleUsesPetrol(VehicleId, Speed);
						format(InfoMessage, sizeof(InfoMessage),"%s~n~Tank: %d/%d L", InfoMessage, Petrol, MaxPetrol);
					}
					//Player Is In Mission
					if (PLAYER_MISSION[I0] != -1)
					{
					    new Time = floatround(PLAYER_MISSION_TIME[I0] * 0.001);
					    new Checkpoints = ((MISSION_CHECKPOINTS[PLAYER_MISSION[I0]] + 1) - PLAYER_MISSION_CHECKPOINT[I0]);
						format(InfoMessage, sizeof(InfoMessage), "%s~n~Verbleibende Zeit: %d Sekunden~n~Verbleibende Checkpoints: %d", InfoMessage, Time, Checkpoints);
					}
					SendMessageToPlayer(I0, MESSAGE_TYPE_SPEED, InfoMessage);
	    		}
	    		//Player Is No Driver and message has not been destroyed yet
	    		else if (!MESSAGE_DESTROYED[I0][MESSAGE_TYPE_SPEED])
	    		{
	    		    DestroySendedMessageForPlayer(I0, MESSAGE_TYPE_SPEED);
	    		}
			}
			PLAYER_LAST_POSITION[I0][X] = PositionX;
			PLAYER_LAST_POSITION[I0][Y] = PositionY;
			PLAYER_LAST_POSITION[I0][Z] = PositionZ;
			PLAYER_LAST_POSITION[I0][FACING] = Facing;
		}
	}
}

public AddVehicle(Type, Float:PositionX, Float:PositionY, Float:PositionZ, Float:Facing, Colour0, Colour1)
{
	new VehicleId = VEHICLES;
    if (VehicleId < MAX_VEHICLES)
	{
    	VEHICLE_TYPE[VehicleId] = Type;
    	RefreshVehicle(VehicleId);
    	VEHICLES++;
    	return AddStaticVehicle(VEHICLE_TYPE_MODEL[Type], PositionX, PositionY, PositionZ, Facing, Colour0, Colour1);
	}
	return 0; //Vehicles beginnen mit 1, trotzdem wird die Anzahl von 0 aus gezählt
}
