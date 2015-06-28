//*******************************************************************
//Checkpoint Functions
//*******************************************************************
#if defined CheckpointFunctions_included
  	#endinput
#endif
#define CheckpointFunctions_included
#pragma library CheckpointFunctions

//-- Functions --
public SetPlayerActiveCheckpoint(PlayerId, Checkpoint, Type)
{
	new Float:Position[4];
	//Shop Checkpoint
	if (Type == CHECKPOINT_TYPE_SHOP)
	{
	    Position[X] = SHOP_CHECKPOINT[Checkpoint][X];
        Position[Y] = SHOP_CHECKPOINT[Checkpoint][Y];
        Position[Z] = SHOP_CHECKPOINT[Checkpoint][Z];
        Position[SIZE] = SHOP_CHECKPOINT[Checkpoint][SIZE];
	}
	//House Checkpoint
	else if (Type == CHECKPOINT_TYPE_HOUSE)
	{
	    Position[X] = HOUSE_CHECKPOINT[Checkpoint][X];
        Position[Y] = HOUSE_CHECKPOINT[Checkpoint][Y];
        Position[Z] = HOUSE_CHECKPOINT[Checkpoint][Z];
        Position[SIZE] = HOUSE_CHECKPOINT[Checkpoint][SIZE];
	}
	//Death Match Checkpoint
	if (Type == CHECKPOINT_TYPE_DEATH_MATCH)
	{
	    Position[X] = DEATH_MATCH_CHECKPOINT[Checkpoint][X];
        Position[Y] = DEATH_MATCH_CHECKPOINT[Checkpoint][Y];
        Position[Z] = DEATH_MATCH_CHECKPOINT[Checkpoint][Z];
        Position[SIZE] = DEATH_MATCH_CHECKPOINT[Checkpoint][SIZE];
	}
	//Mission Checkpoint
	PLAYER_CHECKPOINT[PlayerId] = Checkpoint;
	PLAYER_CHECKPOINT_TYPE[PlayerId] = Type;
	PLAYER_CHECKPOINT_POSITION[PlayerId][X] = Position[X];
	PLAYER_CHECKPOINT_POSITION[PlayerId][Y] = Position[Y];
	PLAYER_CHECKPOINT_POSITION[PlayerId][Z] = Position[Z];
	SetPlayerCheckpoint(PlayerId, Position[X], Position[Y], Position[Z], Position[SIZE]);
	return true;
}

public InitCheckpointTimer()
{
    TIMER_CHECKPOINT = SetTimer("TimerFunctionGetCheckpoint", ConvertSeconds(1), true);
    return true;
}

public TimerFunctionGetCheckpoint()
{
	new Float:CheckpointSenseRange = 50.0000;
 	new Float:CheckpointPosition[3] =
 	{
 	    10000.0000,
 	    10000.0000,
 	    10000.0000
 	};
 	new Float:CheckpointDistance = 100000.0000;
 	new Float:CheckingCheckpointDistance = 0.0000;
 	new MissionId;
 	new MissionCheckpoint;
	for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
	    if (PLAYER_ACCOUNT[I0] != -1)
		{
		    //Player Is Not In Death Match
		    if (PLAYER_DEATH_MATCH[I0] == -1)
		    {
				//Player Is Not In Mission
				if (PLAYER_MISSION[I0] == -1)
		    	{
		        	DisablePlayerRaceCheckpoint(I0);
					if (PLAYER_CHECKPOINT[I0] != -1)
					{
		    			CheckpointPosition[X] = PLAYER_CHECKPOINT_POSITION[I0][X];
	   					CheckpointPosition[Y] = PLAYER_CHECKPOINT_POSITION[I0][Y];
	   					CheckpointPosition[Z] = PLAYER_CHECKPOINT_POSITION[I0][Z];
		    			CheckpointDistance = GetPlayersDistanceFromXYZ(I0, CheckpointPosition[X], CheckpointPosition[Y], CheckpointPosition[Z]);
						//if (CheckpointDistance > CheckpointSenseRange)
						//{
						    //DisablePlayerCheckpoint(I0);
						//}
					}
					//Shop Checkpoints
					for (new I1 = 0; I1 <= SHOPS; I1++)
					{
			    		if (!(PLAYER_CHECKPOINT[I0] == I1 && PLAYER_CHECKPOINT_TYPE[I0] == CHECKPOINT_TYPE_SHOP))
			    		{
		    				CheckingCheckpointDistance = GetPlayersDistanceFromXYZ(I0, SHOP_CHECKPOINT[I1][X], SHOP_CHECKPOINT[I1][Y], SHOP_CHECKPOINT[I1][Z]);
	    					if (CheckingCheckpointDistance <= CheckpointSenseRange && CheckingCheckpointDistance < CheckpointDistance)
							{
								SetPlayerActiveCheckpoint(I0, I1, CHECKPOINT_TYPE_SHOP);
								break;
							}
						}
					}
					//House Checkpoints
					for (new I1 = 0; I1 <= HOUSES; I1++)
					{
			    		if (!(PLAYER_CHECKPOINT[I0] == I1 && PLAYER_CHECKPOINT_TYPE[I0] == CHECKPOINT_TYPE_HOUSE))
			    		{
		    				CheckingCheckpointDistance = GetPlayersDistanceFromXYZ(I0, HOUSE_CHECKPOINT[I1][X], HOUSE_CHECKPOINT[I1][Y], HOUSE_CHECKPOINT[I1][Z]);
	    					if (CheckingCheckpointDistance <= CheckpointSenseRange && CheckingCheckpointDistance < CheckpointDistance)
							{
								SetPlayerActiveCheckpoint(I0, I1, CHECKPOINT_TYPE_HOUSE);
								break;
							}
						}
					}
					//Death Match Checkpoints
					for (new I1 = 0; I1 <= DEATH_MATCHES; I1++)
					{
			    		if (!(PLAYER_CHECKPOINT[I0] == I1 && PLAYER_CHECKPOINT_TYPE[I0] == CHECKPOINT_TYPE_DEATH_MATCH))
			    		{
		    				CheckingCheckpointDistance = GetPlayersDistanceFromXYZ(I0, DEATH_MATCH_CHECKPOINT[I1][X], DEATH_MATCH_CHECKPOINT[I1][Y], DEATH_MATCH_CHECKPOINT[I1][Z]);
	    					if (CheckingCheckpointDistance <= CheckpointSenseRange && CheckingCheckpointDistance < CheckpointDistance)
							{
								SetPlayerActiveCheckpoint(I0, I1, CHECKPOINT_TYPE_DEATH_MATCH);
								break;
							}
						}
					}

				}
				//Player Is In Mission
				else
				{
			    	DisablePlayerCheckpoint(I0);
					MissionId = PLAYER_MISSION[I0];
					MissionCheckpoint = PLAYER_MISSION_CHECKPOINT[I0];
					//Is Not The Last Checkpoint
					if (MISSION_CHECKPOINTS[MissionId] > MissionCheckpoint)
					{
						SetPlayerRaceCheckpoint(I0, 0, MISSION_CHECKPOINT[MissionId][MissionCheckpoint][X], MISSION_CHECKPOINT[MissionId][MissionCheckpoint][Y], MISSION_CHECKPOINT[MissionId][MissionCheckpoint][Z], MISSION_CHECKPOINT[MissionId][(MissionCheckpoint + 1)][X], MISSION_CHECKPOINT[MissionId][(MissionCheckpoint + 1)][Y], MISSION_CHECKPOINT[MissionId][(MissionCheckpoint + 1)][Z], MISSION_CHECKPOINT[MissionId][MissionCheckpoint][SIZE]);
					}
					//Is The Last Checkpoint
					else
					{
				    	SetPlayerRaceCheckpoint(I0, 1, MISSION_CHECKPOINT[MissionId][MissionCheckpoint][X], MISSION_CHECKPOINT[MissionId][MissionCheckpoint][Y], MISSION_CHECKPOINT[MissionId][MissionCheckpoint][Z], 0.0000, 0.0000, 0.0000, MISSION_CHECKPOINT[MissionId][MissionCheckpoint][SIZE]);
					}
				
				}
			}
			//Player Is In Death Match
			else
			{
			    DisablePlayerCheckpoint(I0);
			}
		}
	}
}
