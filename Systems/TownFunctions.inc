//*******************************************************************
//Town Functions
//*******************************************************************
#if defined TownFunctions_included
  	#endinput
#endif
#define TownFunctions_included
#pragma library TownFunctions

//-- Functions --
GetPlayerNearestHospital(PlayerId)
{
	new TownId = -1;
	for (new I0 = 0; I0 < TOWNS; I0++)
	{
	    for (new I1 = 0; I1 < TOWNS; I1++)
	    {
	        TownId = I1;
	        if (I0 != I1)
	        {
	    		if (GetPlayersLastDistanceFromXYZ(PlayerId, TOWN_HOSPITAL_POSITION[I0][X], TOWN_HOSPITAL_POSITION[I0][Y], TOWN_HOSPITAL_POSITION[I0][Z]) < GetPlayersLastDistanceFromXYZ(PlayerId, TOWN_HOSPITAL_POSITION[I1][X], TOWN_HOSPITAL_POSITION[I1][Y], TOWN_HOSPITAL_POSITION[I1][Z]))
	    		{
	    	    	TownId = I0;
	    		}
			}
		}
	}
	return TownId;
}

public StartPlayerHospitalRespawn(PlayerId)
{
    PLAYER_RESPAWN_TIME[PlayerId] = 10000;
	TIMER_RESPAWN[PlayerId] = SetTimerEx("PlayerRespawningLoosesTime", 1000, true, "i", PlayerId);
	TogglePlayerSpectating(PlayerId, true);
	return true;
}

public PlayerRespawningLoosesTime(PlayerId)
{
	if (PLAYER_RESPAWN_TIME[PlayerId] > 0)
	{
		PLAYER_RESPAWN_TIME[PlayerId] -= 1000;
	    new Time = floatround(PLAYER_RESPAWN_TIME[PlayerId] * 0.001);
	    new InfoMessage[MAX_STRING];
		//Player Is Not In Death Match
		if (PLAYER_DEATH_MATCH[PlayerId] == -1)
	    {
			format(InfoMessage, sizeof(InfoMessage), "Noch ~r~%d~w~ Sekunden bis zum Verlassen des Krankenhauses.", Time);
		}
		//Player Is In Death Match
		else
		{
		    format(InfoMessage, sizeof(InfoMessage), "Noch ~r~%d~w~ Sekunden bis zur Neuerschaffung.", Time);
		}
		SendMessageToPlayer(PlayerId, MESSAGE_TYPE_TIMER, InfoMessage);
	    return true;
	}
	else
	{
	    PLAYER_RESPAWN_TIME[PlayerId] = 0;
    	TogglePlayerSpectating(PlayerId, false);
	    //Player Is Not In Death Match
		if (PLAYER_DEATH_MATCH[PlayerId] == -1)
	    {
	    	new TownId = GetPlayerNearestHospital(PlayerId);
			SetPlayerPos(PlayerId, TOWN_HOSPITAL_POSITION[TownId][X], TOWN_HOSPITAL_POSITION[TownId][Y], TOWN_HOSPITAL_POSITION[TownId][Z]);
	    	SetPlayerFacingAngle(PlayerId, TOWN_HOSPITAL_POSITION[TownId][FACING]);
			SetPlayerArmour(PlayerId, 0.0000);
			ResetPlayerWeapons(PlayerId);
	    	if (GetPlayerMoney(PlayerId) >= 100)
	    	{
        		GivePlayerMoney(PlayerId, -100);
			}
			else
			{
		    	GivePlayerMoney(PlayerId, -GetPlayerMoney(PlayerId));
			}
			SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, "Sie wurden im Krankenhaus verartztet.~n~Ihnen wurden Ihre Waffen, sowie etwas Geld abgenommen.");
		}
		//Player Is In Death Match
		else
		{
		    new DeathMatchId = PLAYER_DEATH_MATCH[PlayerId];
		    new Skin = PLAYER_DEATH_MATCH_SKIN[PlayerId];
		    SetPlayerPos(PlayerId, DEATH_MATCH_SKIN_POSITION[DeathMatchId][Skin][X], DEATH_MATCH_SKIN_POSITION[DeathMatchId][Skin][Y], DEATH_MATCH_SKIN_POSITION[DeathMatchId][Skin][Z]);
	    	SetPlayerFacingAngle(PlayerId, DEATH_MATCH_SKIN_POSITION[DeathMatchId][Skin][FACING]);
            SetPlayerSkin(PlayerId, DEATH_MATCH_SKIN[DeathMatchId][Skin]);
  			SetPlayerHealth(PlayerId, 100.0000);
			SetPlayerArmour(PlayerId, 100.0000);
			ResetPlayerWeapons(PlayerId);
	    	for (new I0; I0 < 3; I0++)
			{
	    		if (DEATH_MATCH_SKIN_WEAPON[DeathMatchId][Skin][I0] != -1)
				{
					GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[DEATH_MATCH_SKIN_WEAPON[DeathMatchId][Skin][I0]], DEATH_MATCH_SKIN_WEAPON[DeathMatchId][Skin][(I0 + 3)]);
				}
			}
		}
        SetCameraBehindPlayer(PlayerId);
		KillTimer(TIMER_RESPAWN[PlayerId]);
	    return false;
	}
}

public CreateTownMenu(PlayerId)
{
    CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_TOWN_SELECTION, 0, "Start-Städte");
    SetCustomMenuHeader(PlayerId, MENU_TYPE_TOWN_SELECTION, "Auswahl");
	for (new I0 = 0; I0 < TOWNS; I0++)
    {
    	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_TOWN_SELECTION, TOWN_NAME[I0]);
	}
	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_TOWN_SELECTION);
	return true;
}

public PlayerChoosesTown(PlayerId, TownId)
{
	new AccountId = PLAYER_ACCOUNT[PlayerId];
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	ACCOUNT_P_TOWN[AccountId][AccountPlayerId] = TownId;
	TogglePlayerControllable(PlayerId, true);
	SpawnPlayerInTown(PlayerId, TownId);
	new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "~y~Start-Stadt-Auswahl~n~~g~Sie haben %s zu Ihrer Start-Stadt gewählt.~n~~w~Drücken Sie ~k~~PED_ANSWER_PHONE~ , um ins Hauptmenü zu gelangen.~n~Drücken Sie ~k~~TOGGLE_SUBMISSIONS~, um eine Mission in einem Fahrzeug zu starten.", TOWN_NAME[TownId]);
    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, InfoMessage);
	return true;
}

public SpawnPlayerInTown(PlayerId, TownId)
{
	SetPlayerInterior(PlayerId, 0);
    SetPlayerPos(PlayerId, TOWN_POSITION[TownId][X], TOWN_POSITION[TownId][Y], TOWN_POSITION[TownId][Z]);
	SetPlayerFacingAngle(PlayerId, TOWN_POSITION[TownId][FACING]);
	SetCameraBehindPlayer(PlayerId);
 	InitPlayerMiniMap(PlayerId);
    GivePlayerMoney(PlayerId, 2000);
    new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "~w~Willkommen in~n~~y~%s", TOWN_NAME[TownId]);
	GameTextForPlayer(PlayerId, InfoMessage, ConvertSeconds(10), 4);
	return true;
}

public AddTown(Name[MAX_TOWN_NAME], Float:PositionX, Float:PositionY, Float:PositionZ, Float:PositionFacing, Float:HospitalPositionX, Float:HospitalPositionY, Float:HospitalPositionZ, Float:HospitalPositionFacing)
{
	new TownId = TOWNS;
    if (TownId < MAX_TOWNS)
	{
	    TOWN_NAME[TownId] = Name;
   		TOWN_POSITION[TownId][X] = PositionX;
   		TOWN_POSITION[TownId][Y] = PositionY;
   		TOWN_POSITION[TownId][Z] = PositionZ;
   		TOWN_POSITION[TownId][FACING] = PositionFacing;
   		TOWN_HOSPITAL_POSITION[TownId][X] = HospitalPositionX;
   		TOWN_HOSPITAL_POSITION[TownId][Y] = HospitalPositionY;
   		TOWN_HOSPITAL_POSITION[TownId][Z] = HospitalPositionZ;
   		TOWN_HOSPITAL_POSITION[TownId][FACING] = HospitalPositionFacing;
   		TOWNS++;
		return TownId;
	}
	return -1;
}

