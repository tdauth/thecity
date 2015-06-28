//*******************************************************************
//Mission Functions
//*******************************************************************
#if defined MissionFunctions_included
	#endinput
#endif
#define MissionFunctions_included
#pragma library MissionFunctions

//-- Functions --
PlayerIsInMissionVehicle(PlayerId, VehicleId)
{
	new AccountId = PLAYER_ACCOUNT[PlayerId];
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	for (new I0 = 0; I0 < MISSIONS; I0++)
	{
		for (new I1 = 0; I1 < MISSION_VEHICLES[I0]; I1++)
		{
			if (VEHICLE_TYPE[VehicleId] == MISSION_VEHICLE[I0][I1])
			{
				if (ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId] == MISSION_PROFESSION[I0] && PLAYER_USES_PROFESSION[PlayerId])
 				{
					return I0;
  				}
			}
		}
	}
	return -1;
}

public PlayerEntersMissionVehicle(PlayerId)
{
    GameTextForPlayer(PlayerId, "~y~Mission~n~~w~Drücken Sie ~k~~TOGGLE_SUBMISSIONS~, um eine Mission zu beginnen.", ConvertSeconds(46), 3);
	return true;
}

public PlayerStartsMission(PlayerId)
{
	//Player Has No Mission
	if (PLAYER_MISSION[PlayerId] == -1)
	{
	    if  (GetPlayerState(PlayerId) == PLAYER_STATE_DRIVER)
	    {
	        new MissionId = PlayerIsInMissionVehicle(PlayerId, GetPlayerVehicleID(PlayerId));
	    	if (MissionId != -1)
	    	{
    			PLAYER_MISSION[PlayerId] = MissionId;
    			PLAYER_MISSION_TIME[PlayerId] = MISSION_TIME[MissionId];
    			PLAYER_MISSION_CHECKPOINT[PlayerId] = 0;
    			SetVehiclePos(GetPlayerVehicleID(PlayerId), MISSION_START_POSITION[MissionId][X], MISSION_START_POSITION[MissionId][Y], MISSION_START_POSITION[MissionId][Z]);
    			SetVehicleZAngle(GetPlayerVehicleID(PlayerId), MISSION_START_POSITION[MissionId][FACING]);
    			SetCameraBehindPlayer(PlayerId);
    			TIMER_MISSION[PlayerId] = SetTimerEx("MissionLosesTime", ConvertSeconds(1), true, "ii", PlayerId, MissionId);
    			new InfoMessage[MAX_STRING];
    			format(InfoMessage, sizeof(InfoMessage), "Sie beginnen die Mission '%s'.", MISSION_NAME[MissionId]);
    			GameTextForPlayer(PlayerId, InfoMessage, ConvertSeconds(4), 3);
    			return true;
			}
		}
	}
	//Player Has A Mission
	else
	{
	    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie befinden sich bereits in einer Mission.");
	}
	return false;
}

public MissionLosesTime(PlayerId, MissionId)
{
	if (PLAYER_MISSION_TIME[PlayerId] > 0)
	{
		PLAYER_MISSION_TIME[PlayerId] = (PLAYER_MISSION_TIME[PlayerId] - ConvertSeconds(1));
	    return true;
	}
	else
	{
	    PlayerFailsMission(PlayerId, MissionId);
	    return false;
	}
}

public PlayerFailsMission(PlayerId, MissionId)
{
    PLAYER_MISSION[PlayerId] = -1;
    KillTimer(TIMER_MISSION[PlayerId]);
    GameTextForPlayer(PlayerId, "~r~Mission fehlgeschlagen", ConvertSeconds(6), 6);
    return true;
}

public PlayerCompletesMission(PlayerId, MissionId)
{
    PLAYER_MISSION[PlayerId] = -1;
    KillTimer(TIMER_MISSION[PlayerId]);
    GivePlayerExperience(PlayerId, MISSION_REWARD[MissionId][MISSION_REWARD_EXPERIENCE]);
	GivePlayerMoney(PlayerId, MISSION_REWARD[MissionId][MISSION_REWARD_MONEY]);
	new InfoMessage[MAX_STRING];
    format(InfoMessage, sizeof(InfoMessage), "~y~Mission erfüllt:~n~~w~+%d Erfahrung~n~+%d$", MISSION_REWARD[MissionId][MISSION_REWARD_EXPERIENCE], MISSION_REWARD[MissionId][MISSION_REWARD_MONEY]);
	GameTextForPlayer(PlayerId, InfoMessage, ConvertSeconds(6), 6);
	return true;
}

public AddMission(Name[MAX_MISSION_NAME], Float:StartPositionX, Float:StartPositionY, Float:StartPositionZ, Float:StartPositionFacing, Time, Profession, RewardExperience, RewardMoney)
{
	new MissionId = MISSIONS;
    if (MissionId < MAX_MISSIONS)
	{
    	MISSION_NAME[MissionId] = Name;
		MISSION_START_POSITION[MissionId][X] = StartPositionX;
		MISSION_START_POSITION[MissionId][Y] = StartPositionY;
		MISSION_START_POSITION[MissionId][Z] = StartPositionZ;
		MISSION_START_POSITION[MissionId][FACING] = StartPositionFacing;
		MISSION_TIME[MissionId] = ConvertSeconds(Time);
		MISSION_PROFESSION[MissionId] = Profession;
		MISSION_REWARD[MissionId][MISSION_REWARD_EXPERIENCE] = RewardExperience;
		MISSION_REWARD[MissionId][MISSION_REWARD_MONEY] = RewardMoney;
		MISSION_VEHICLES[MissionId] = 0;
		MISSION_CHECKPOINTS[MissionId] = 0;
		MISSIONS++;
    	return MissionId;
	}
	return -1;
}

public AddMissionVehicle(VehicleType)
{
    new MissionId = (MISSIONS - 1);
    new MissionVehicleId = MISSION_VEHICLES[MissionId];
	if (MissionVehicleId < MAX_MISSION_VEHICLES)
	{
	    MISSION_VEHICLE[MissionId][MissionVehicleId] = VehicleType;
        MISSION_VEHICLES[MissionId]++;
		return MissionVehicleId;
	}
	return -1;
}

public AddMissionCheckpoint(Float:PositionX, Float:PositionY, Float:PositionZ, Float:PositionSize)
{
    new MissionId = (MISSIONS - 1);
    new MissionCheckpointId = MISSION_CHECKPOINTS[MissionId];
    if (MissionCheckpointId < MAX_MISSION_CHECKPOINTS)
	{
    	MISSION_CHECKPOINT[MissionId][MissionCheckpointId][X] = PositionX;
    	MISSION_CHECKPOINT[MissionId][MissionCheckpointId][Y] = PositionY;
    	MISSION_CHECKPOINT[MissionId][MissionCheckpointId][Z] = PositionZ;
    	MISSION_CHECKPOINT[MissionId][MissionCheckpointId][SIZE] = PositionSize;
    	MISSION_CHECKPOINTS[MissionId]++;
		return MissionCheckpointId;
	}
	return -1;
}
