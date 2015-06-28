//*******************************************************************
//Area Functions
//*******************************************************************
#if defined AreaFunctions_included
  	#endinput
#endif
#define AreaFunctions_included
#pragma library AreaFunctions

//-- Functions --
public CreateAreaGangZones()
{
    for (new I0 = 0; I0 < AREAS; I0++)
	{
	    GangZoneCreate(AREA_POSITION[I0][MIN_X], AREA_POSITION[I0][MIN_Y], AREA_POSITION[I0][MIN_X], AREA_POSITION[I0][MIN_Y]);
	    new Colour;
	    if (AREA_OWNING_GANG[I0] == -1)
	    {
	        Colour = COLOUR_BLACK;
		}
		else
		{
		    Colour = GANG_COLOUR[AREA_OWNING_GANG[I0]];
		}
		GangZoneShowForAll(I0, Colour);
	}
	return true;
}

public ShowAreasForPlayer(PlayerId)
{
    for (new I0 = 0; I0 < AREAS; I0++)
	{
	    new Colour;
	    if (AREA_OWNING_GANG[I0] == -1)
	    {
	        Colour = COLOUR_BLACK;
		}
		else
		{
		    Colour = GANG_COLOUR[AREA_OWNING_GANG[I0]];
		}
		GangZoneShowForPlayer(PlayerId, I0, Colour);
	}
	return true;
}

PlayerIsInArea(PlayerId, AreaId)
{
	new Float:PositionX, Float:PositionY, Float:PositionZ;
	GetPlayerPos(PlayerId, PositionX, PositionY, PositionZ);
	//Player Is In Area
	return (PositionX >= AREA_POSITION[AreaId][MIN_X] && PositionY >= AREA_POSITION[AreaId][MIN_Y] && PositionZ >= AREA_POSITION[AreaId][MIN_Z] && PositionX <= AREA_POSITION[AreaId][MAX_X] && PositionY <= AREA_POSITION[AreaId][MAX_Y] && PositionZ <= AREA_POSITION[AreaId][MAX_Z]);
}

GetPlayerArea(PlayerId)
{
	for (new I0 = 0; I0 < AREAS; I0++)
	{
	    if (PlayerIsInArea(PlayerId, I0))
	    {
	        return I0;
	    }
	}
	return -1;
}

public FlashAreaForGang(GangId, AreaId, Colour)
{
    new AccountId, AccountPlayerId, PlayerId;
	for (new I0 = 0; I0 < MAX_GANG_MEMBERS; I0++)
	{
	    AccountId = GANG_MEMBER_ACCOUNT[GangId][I0];
	    if (AccountId != -1)
	    {
			AccountPlayerId = GANG_MEMBER_ACCOUNT_PLAYER[GangId][I0];
			PlayerId = ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId];
	        GangZoneFlashForPlayer(PlayerId, AreaId, Colour);
	    }
	}
	return true;
}

public StopFlashingAreaForGang(GangId, AreaId)
{
    new AccountId, AccountPlayerId, PlayerId;
	for (new I0 = 0; I0 < MAX_GANG_MEMBERS; I0++)
	{
	    AccountId = GANG_MEMBER_ACCOUNT[GangId][I0];
	    if (AccountId != -1)
		{
			AccountPlayerId = GANG_MEMBER_ACCOUNT_PLAYER[GangId][I0];
			PlayerId = ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId];
   			GangZoneStopFlashForPlayer(PlayerId, AreaId);
	    }
	}
	return true;
}

public StartAreaConquest(PlayerId, AreaId)
{
	//Area Has No Owning Gang
	if (AREA_OWNING_GANG[AreaId] == -1)
	{
	    new AccountId = PLAYER_ACCOUNT[PlayerId];
		new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
    	new GangId = ACCOUNT_P_GANG[AccountId][AccountPlayerId];
	    if (GANG_AREAS[GangId] < MAX_GANG_AREAS)
	    {
	    	AREA_OWNING_GANG[AreaId] = GangId;
	    	GANG_AREAS[GangId]++;
			GangZoneShowForAll(AreaId, GANG_COLOUR[GangId]);
			FlashAreaForGang(GangId, AreaId, COLOUR_BLACK);
        	SetTimerEx("StopFlashingAreaForGang", ConvertSeconds(6), false, "ii", GangId, AreaId);
        	new InfoMessage[MAX_STRING];
			format(InfoMessage, sizeof(InfoMessage), "%s hat das Gebiet %s für seine Gang eingenommen.", PLAYER_NAME[PlayerId], AREA_NAME[AreaId]);
			SendGangMessage(GangId, -1, MESSAGE_TYPE_ACCEPTANCE, InfoMessage);
			if (GANG_AREAS[GangId] == MAX_GANG_AREAS)
			{
			    SendGangMessage(GangId, -1, MESSAGE_TYPE_INFO, "Damit wurde die maximale Anzahl der eroberbaren Gebiete erreicht.");
			}
		}
	}
	//Area Has An Owning Gang
	else
	{
	}
	return true;
}

public InitAreaTimer()
{
    TIMER_AREA = SetTimer("TimerFunctionAreaConquest", ConvertSeconds(1), true);
    return true;
}

public TimerFunctionAreaConquest()
{
	for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
	    if (PLAYER_ACCOUNT[I0] != -1)
	    {
	        new AccountId = PLAYER_ACCOUNT[I0];
			new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[I0];
	        if (ACCOUNT_P_GANG[AccountId][AccountPlayerId] != -1)
	        {
	            if (PLAYER_DEATH_MATCH[I0] == -1)
	            {
	            	new AreaId = GetPlayerArea(I0);
	            	if (AreaId != -1)
	            	{
	            		if (AREA_OWNING_GANG[AreaId] != ACCOUNT_P_GANG[AccountId][AccountPlayerId])
	            		{
	                    	StartAreaConquest(I0, AreaId);
	            		}
					}
				}
	    	}
		}
	}
}

public AddArea(Name[MAX_AREA_NAME], Float:MinX, Float:MinY, Float:MinZ, Float:MaxX, Float:MaxY, Float:MaxZ)
{
	new AreaId = AREAS;
    if (AreaId < MAX_AREAS)
	{
   		AREA_NAME[AreaId] = Name;
		AREA_POSITION[AreaId][MIN_X] = MinX;
		AREA_POSITION[AreaId][MIN_Y] = MinY;
		AREA_POSITION[AreaId][MIN_Z] = MinZ;
		AREA_POSITION[AreaId][MAX_X] = MaxX;
		AREA_POSITION[AreaId][MAX_Y] = MaxY;
		AREA_POSITION[AreaId][MAX_Z] = MaxZ;
		AREA_OWNING_GANG[AreaId] = -1;
		AREAS++;
		return AreaId;
	}
	return -1;
}
