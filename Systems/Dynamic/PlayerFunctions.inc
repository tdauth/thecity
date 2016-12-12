//*******************************************************************
//Player Functions
//Dynamisch
//*******************************************************************
#if defined PlayerFunctions_included
  	#endinput
#endif
#define PlayerFunctions_included
#pragma library PlayerFunctions

//-- Functions --
public InitMoneyTimer()
{
	TIMER_MONEY = SetTimer("TimerFunctionGiveMoney", ConvertSeconds(10), true);
	return true;
}

public TimerFunctionGiveMoney()
{
	for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
	    if (IsPlayerConnected(I0) && PLAYER_ACCOUNT[I0] != -1)
	    {
	        GivePlayerMoney(I0, 2000);
	        SendMessageToPlayer(I0, MESSAGE_TYPE_INFO, "Mutter schickt dir 2000$.");
		}
	}
	return true;
}

public InitPlayerMiniMap(PlayerId)
{
    //ShowAreasForPlayer(PlayerId);
 	InitMapMarkers(PlayerId);
  	CreateShopMarkersForPlayer(PlayerId);
   	CreateHouseMarkersForPlayer(PlayerId);
    CreateDMMarkersForPlayer(PlayerId);
    return true;
}

PlayerExists(Name[MAX_PLAYER_NAME])
{
	for (new I0 = 0; I0 < PLAYERS; I0++)
	{
	    if (strlen(PLAYER_NAME[I0]) > 0 && strcmp(Name, PLAYER_NAME[I0], true) == 0)
	    {
	        return I0;
	    }
	}
	return -1;
}

Float:GetPlayersDistanceFromXYZ(PlayerId, Float:PointX, Float:PointY, Float:PointZ)
{
	new Float:PositionX, Float:PositionY, Float:PositionZ, Float:PointDistance;
	GetPlayerPos(PlayerId, PositionX, PositionY, PositionZ);
	PointDistance = floatsqroot(floatpower(floatsub(PositionX, PointX), 2) + floatpower(floatsub(PositionY, PointY), 2) + floatpower(floatsub(PositionZ, PointZ), 2));
	return PointDistance;
}

Float:GetPlayersLastDistanceFromXYZ(PlayerId, Float:PointX, Float:PointY, Float:PointZ)
{
	new Float:PositionX = PLAYER_LAST_POSITION[PlayerId][X];
	new Float:PositionY = PLAYER_LAST_POSITION[PlayerId][Y];
	new Float:PositionZ = PLAYER_LAST_POSITION[PlayerId][Z];
	new Float:PointDistance;
	PointDistance = floatsqroot(floatpower(floatsub(PositionX, PointX), 2) + floatpower(floatsub(PositionY, PointY), 2) + floatpower(floatsub(PositionZ, PointZ), 2));
	return PointDistance;
}

public PreloadAnimationLibrary(PlayerId, AnimationLibrary[])
{
	ApplyAnimation(PlayerId, AnimationLibrary, "null", 0.0000, false, 0, 0, 0, 0);
	return true;
}

public SavePlayerInterior(PlayerId)
{
	PLAYER_INTERIOR[PlayerId] = GetPlayerInterior(PlayerId);
	return true;
}

public LoadPlayerInterior(PlayerId)
{
	SetPlayerInterior(PlayerId, PLAYER_INTERIOR[PlayerId]);
	return true;
}

public SavePlayerState(PlayerId)
{
	GetPlayerHealth(PlayerId, PLAYER_HEALTH[PlayerId]);
	GetPlayerArmour(PlayerId, PLAYER_ARMOUR[PlayerId]);
	return true;
}

public LoadPlayerState(PlayerId)
{
    print("Load State");
    SetPlayerHealth(PlayerId, PLAYER_HEALTH[PlayerId]);
	SetPlayerArmour(PlayerId, PLAYER_ARMOUR[PlayerId]);
	return true;
}

public SavePlayerWeapons(PlayerId)
{
	for (new I0; I0 < 13; I0++)
	{
	    GetPlayerWeaponData(PlayerId, I0, PLAYER_WEAPON[PlayerId][I0], PLAYER_AMMO[PlayerId][I0]);
	}
	ResetPlayerWeapons(PlayerId);
	return true;
}

public LoadPlayerWeapons(PlayerId)
{
	print("Load Weapons");
	ResetPlayerWeapons(PlayerId);
	for (new I0; I0 < 13; I0++)
	{
	    if (PLAYER_WEAPON[PlayerId][I0] != -1)
	    {
			GivePlayerWeapon(PlayerId, PLAYER_WEAPON[PlayerId][I0], PLAYER_AMMO[PlayerId][I0]);
		}
	}
	return true;
}

public Float:AddPlayerHealth(PlayerId, Float:Health, Add)
{
	new Float:PlayerHealth;
	GetPlayerHealth(PlayerId, PlayerHealth);
	if (Add)
	{
		SetPlayerHealth(PlayerId, (PlayerHealth + Health));
	}
	else
	{
	    SetPlayerHealth(PlayerId, (PlayerHealth - Health));
	}
	GetPlayerHealth(PlayerId, PlayerHealth);
	return PlayerHealth;
}

public Float:AddPlayerArmour(PlayerId, Float:Armour, Add)
{
    new Float:PlayerArmour;
	GetPlayerArmour(PlayerId, PlayerArmour);
	if (Add)
	{
		SetPlayerHealth(PlayerId, (PlayerArmour + Armour));
	}
	else
	{
	    SetPlayerHealth(PlayerId, (PlayerArmour - Armour));
	}
	GetPlayerArmour(PlayerId, PlayerArmour);
	return PlayerArmour;
}

public SetupPlayerForLogin(PlayerId)
{
	SetPlayerInterior(PlayerId, 1);
	SetPlayerCameraPos(PlayerId, -784.0707, 498.6585, 1376.1953);
	SetPlayerCameraLookAt(PlayerId, -783.8020, 495.5815, 1376.1953);
	TogglePlayerClock(PlayerId, true);
	return true;
}

public PlayerSelectsSkin(PlayerId, SkinId)
{
	if (PLAYER_ACCOUNT[PlayerId] == -1)
	{
		SetupPlayerForLogin(PlayerId);
	}
	else
	{
	    new AccountId = PLAYER_ACCOUNT[PlayerId];
	    new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	    ACCOUNT_P_SKIN[AccountId][AccountPlayerId] = SkinId;
	    ShowSkinInfoForPlayer(PlayerId, SkinId);
	}
	return true;
}

PlayerIsHeadHunterOfPlayer(PlayerId, OtherPlayerId)
{
    return AccountPlayerIsHeadHunterOfAP(PLAYER_ACCOUNT[PlayerId], PLAYER_ACCOUNT_PLAYER[PlayerId], PLAYER_ACCOUNT[OtherPlayerId], PLAYER_ACCOUNT_PLAYER[OtherPlayerId]);
}

GetPlayerHeadHunters(PlayerId)
{
	return GetAccountPlayerHeadHunters(PLAYER_ACCOUNT[PlayerId], PLAYER_ACCOUNT_PLAYER[PlayerId]);
}

GetPlayerNextHeadHunterSlot(PlayerId)
{
	return GetAccountPlayerNextHeadHS(PLAYER_ACCOUNT[PlayerId], PLAYER_ACCOUNT_PLAYER[PlayerId]);
}

public GivePlayerHeadMoney(PlayerId, TargetPlayerId)
{
	GiveAccountPlayerHeadMoney(PLAYER_ACCOUNT[PlayerId], PLAYER_ACCOUNT_PLAYER[PlayerId], PLAYER_ACCOUNT[TargetPlayerId], PLAYER_ACCOUNT_PLAYER[TargetPlayerId]);
	return true;
}

public GivePlayerExperience(PlayerId, Experience)
{
	GiveAccountPlayerExperience(PLAYER_ACCOUNT[PlayerId], PLAYER_ACCOUNT_PLAYER[PlayerId], Experience);
}

GetPlayerKillType(PlayerId, KillerId)
{
	return GetAccountPlayerKillType(PLAYER_ACCOUNT[PlayerId], PLAYER_ACCOUNT_PLAYER[PlayerId], PLAYER_ACCOUNT[KillerId], PLAYER_ACCOUNT_PLAYER[KillerId]);
}

public PlayerDies(PlayerId, KillerId, Reason)
{
	SendDeathMessage(KillerId, PlayerId, Reason);
	//Player Has A Killer
	if (KillerId != INVALID_PLAYER_ID)
	{
	    //Player Is Not In Death Match
	    if (PLAYER_DEATH_MATCH[PlayerId] == -1)
	    {
			new KillType = GetPlayerKillType(PlayerId, KillerId);
			//Player Kills Another Player Of His Profession
			if (KillType == KILL_TYPE_PROFESSION)
			{
	    		GivePlayerMoney(KillerId, -1000);
	    		SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, "Ihr Mörder verliert 1000$.");
	    		SendMessageToPlayer(KillerId, MESSAGE_TYPE_ERROR, "Sie verlieren 1000$.");
                new ErrorMessage[MAX_STRING];
				format(ErrorMessage, sizeof(ErrorMessage), "%s hat einen Arbeitskollegen erschossen (%s).", PLAYER_NAME[KillerId], PLAYER_NAME[PlayerId]);
	    		SendClientMessageToAllPlayers(MESSAGE_TYPE_ERROR, ErrorMessage);
			}
			//Player Kills A Gang Member Of His Gang
			else if (KillType == KILL_TYPE_GANG)
			{
			    new KillerAccountId = PLAYER_ACCOUNT[KillerId];
			    new KillerAccountPlayerId = PLAYER_ACCOUNT_PLAYER[KillerId];
	    		ACCOUNT_P_GANG_RANK_POINTS[KillerAccountId][KillerAccountPlayerId] -= 100;
	    		GivePlayerMoney(KillerId, -10000);
	    		SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, "Ihr Mörder verliert 10.000$. Sein Gang-Rang sinkt um 100 Punkte.");
	    		SendMessageToPlayer(KillerId, MESSAGE_TYPE_ERROR, "Sie verlieren 10.000$. Ihr Gang-Rang sinkt um 100 Punkte.");
                new ErrorMessage[MAX_STRING];
				format(ErrorMessage, sizeof(ErrorMessage), "%s hat ein Gang-Mitglied erschossen (%s).", PLAYER_NAME[KillerId], PLAYER_NAME[PlayerId]);
	    		SendClientMessageToAllPlayers(MESSAGE_TYPE_ERROR, ErrorMessage);
			}
			//Player Kills A Profession Target
			else if (KillType == KILL_TYPE_PROFESSION_TARGET)
			{
			    new KillerAccountId = PLAYER_ACCOUNT[KillerId];
			    new KillerAccountPlayerId = PLAYER_ACCOUNT_PLAYER[KillerId];
	    		new KillerProfessionId = ACCOUNT_P_PROFESSION[KillerAccountId][KillerAccountPlayerId];
	    		new ProfessionTargetId = PlayerIsTargetPlayer(KillerId, PlayerId);
				GivePlayerExperience(KillerId, PROFESSION_TARGET_EXPERIENCE[KillerProfessionId][ProfessionTargetId]);
	    		GivePlayerMoney(KillerId, PROFESSION_TARGET_MONEY[KillerProfessionId][ProfessionTargetId]);
            	GivePlayerHeadMoney(KillerId, PlayerId);
				ACCOUNT_P_PROFESSION_RPS[KillerAccountId][KillerAccountPlayerId] += PROFESSION_TARGET_RANK_POINTS[KillerProfessionId][ProfessionTargetId];
                new InfoMessage[MAX_STRING];
				format(InfoMessage, sizeof(InfoMessage), "Sie erhalten %d Erfahrung und %d$. Ihr Berufsrang steigt um %d Punkte.", PROFESSION_TARGET_EXPERIENCE[KillerProfessionId][ProfessionTargetId], PROFESSION_TARGET_MONEY[KillerProfessionId][ProfessionTargetId], PROFESSION_TARGET_RANK_POINTS[KillerProfessionId][ProfessionTargetId]);
	    		SendMessageToPlayer(KillerId, MESSAGE_TYPE_ACCEPTANCE, InfoMessage);
			}
			//Player Kills A General Enemy
			else if (KillType == KILL_TYPE_ENEMY)
			{
			    new PlayerAccountId = PLAYER_ACCOUNT[PlayerId];
			    new PlayerAccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	    		GivePlayerExperience(KillerId, ACCOUNT_P_LEVEL[PlayerAccountId][PlayerAccountPlayerId]);
	    		GivePlayerMoney(KillerId, 100);
            	GivePlayerHeadMoney(KillerId, PlayerId);
                new InfoMessage[MAX_STRING];
				format(InfoMessage, sizeof(InfoMessage), "Sie erhalten %d Erfahrung und 100$.", ACCOUNT_P_LEVEL[PlayerAccountId][PlayerAccountPlayerId]);
	    		SendMessageToPlayer(KillerId, MESSAGE_TYPE_ACCEPTANCE, InfoMessage);
			}
		}
		//Player Is In Death Match
		else
		{
		    PlayerKillsDeathMatchPlayer(PlayerId, KillerId);
		    return true;
		}
	}
	//Player Uses Profession
	if (PLAYER_USES_PROFESSION[PlayerId])
	{
	    PlayerEndsProfession(PlayerId);
	}
	//Player Has Mission
	if (PLAYER_MISSION[PlayerId] != -1)
	{
	    PlayerFailsMission(PlayerId, PLAYER_MISSION[PlayerId]);
	}
	StartPlayerHospitalRespawn(PlayerId);
	new WeaponType;
	WeaponType = GetKillReasonWeaponType(Reason);
	if (WeaponType != -1)
	{
		AddPlayerWeaponSkill(KillerId, WeaponType, 1, true);
	}
	return true;
}

GetNextFreePlayerId()
{
    if (PLAYERS < MAX_PLAYERS)
	{
	    return PLAYERS;
	}
	else
	{
	    for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	    {
	        if (!PLAYER[I0]) //Da Wert nicht unbedingt auf false gesetzt worden ist
	        {
	            return I0;
	        }
	    }
	}
	return -1;
}

//Setzt alle Player-Werte zurück.
//ACHTUNG: Account-Daten zurücksetzen.
ClearPlayer(PlayerId, Copy, FirstClear = false)
{
	if (!FirstClear)
	{
		if (!Copy) //Diese Daten dürfen nur gecleared werden, wenn sie davor nicht kopiert wurden
		{
		    new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	    	if (AccountPlayerId != -1)
			{
			    new AccountId = PLAYER_ACCOUNT[PlayerId];
		    	ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId] = -1; //Zuletzt hier. Wichtig: Diese Daten müssen auch beim Kopieren mitgeändert werden.
			}
		}
	}
	PLAYER[PlayerId] = false;
    PLAYER_ACCOUNT[PlayerId] = -1;
	PLAYER_ACCOUNT_PLAYER[PlayerId] = -1;
	PLAYER_NAME[PlayerId] = "";
	PLAYER_USES_PROFESSION[PlayerId] = false;
	PLAYER_RESPAWN_TIME[PlayerId] = 0;
	PLAYER_MISSION[PlayerId] = -1;
	PLAYER_MISSION_TIME[PlayerId] = 0;
	PLAYER_MISSION_CHECKPOINT[PlayerId] = 0;
	PLAYER_IS_IN_HOUSE[PlayerId] = false;
	PLAYER_IS_IN_GANG_HALL[PlayerId] = false;
	PLAYER_DEATH_MATCH[PlayerId] = -1;
	PLAYER_IS_IN_DM_SELECTION[PlayerId] = false;
	PLAYER_DEATH_MATCH_SKIN[PlayerId] = 0;
	PLAYER_PLAYS_EMOTICON[PlayerId] = false;
	PLAYER_EMOTICON_TIMER[PlayerId] = -1;
	PLAYER_CHECKPOINT[PlayerId] = -1;
	PLAYER_CHECKPOINT_TYPE[PlayerId] = -1;
	new I0;
	for (I0 = 0; I0 < 3; I0++)
	{
		PLAYER_CHECKPOINT_POSITION[PlayerId][I0] = 100000.0000;
	}
	for (I0 = 0; I0 < 4; I0++)
	{
		PLAYER_LAST_POSITION[PlayerId][I0] = 0.0000;
    }
	PLAYER_MENU_TYPE[PlayerId] = -1;
	PLAYER_MENU[PlayerId] = -1;
	PLAYER_MAP_MARKERS[PlayerId] = 0; //Dadurch wird die Anzahl der MapMarker auf 0 gesetzt, wodurch wieder neue erzeugt werden können
	//Save Data
	PLAYER_INTERIOR[PlayerId] = 0;
	PLAYER_HEALTH[PlayerId] = 0.0000;
	PLAYER_ARMOUR[PlayerId] = 0.0000;
	for (I0 = 0; I0 < 13; I0++)
	{
	    PLAYER_WEAPON[PlayerId][I0] = -1;
		PLAYER_AMMO[PlayerId][I0] = 0;
	}
    return true;
}

public AddPlayer(AccountId, AccountPlayerId, Name[MAX_PLAYER_NAME])
{
    new PlayerId = GetNextFreePlayerId();
    if (PlayerId != -1)
	{
	    ClearPlayer(PlayerId, false);
	    PLAYER[PlayerId] = true;
		PLAYER_ACCOUNT[PlayerId] = AccountId;
		PLAYER_ACCOUNT_PLAYER[PlayerId] = AccountPlayerId;
		PLAYER_NAME[PlayerId] = Name;
		PLAYERS++;
		return PlayerId;
	}
	return -1;
}

public CopyPlayer(PlayerId, CopiedPlayerId)
{
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[CopiedPlayerId];
    if (AccountPlayerId != -1)
	{
	    new AccountId = PLAYER_ACCOUNT[CopiedPlayerId];
	    ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId] = PlayerId; //Muss mitgeändert werden, PlayerId stimmt!
	}
    PLAYER[PlayerId] = PLAYER[CopiedPlayerId];
    PLAYER_ACCOUNT[PlayerId] = PLAYER_ACCOUNT[CopiedPlayerId];
	PLAYER_ACCOUNT_PLAYER[PlayerId] = PLAYER_ACCOUNT_PLAYER[CopiedPlayerId];
	PLAYER_NAME[PlayerId] = PLAYER_NAME[CopiedPlayerId];
	PLAYER_USES_PROFESSION[PlayerId] = PLAYER_USES_PROFESSION[CopiedPlayerId];
	PLAYER_RESPAWN_TIME[PlayerId] = PLAYER_RESPAWN_TIME[CopiedPlayerId];
	PLAYER_MISSION[PlayerId] = PLAYER_MISSION[CopiedPlayerId];
	PLAYER_MISSION_TIME[PlayerId] = PLAYER_MISSION_TIME[CopiedPlayerId];
	PLAYER_MISSION_CHECKPOINT[PlayerId] = PLAYER_MISSION_CHECKPOINT[CopiedPlayerId];
	PLAYER_IS_IN_HOUSE[PlayerId] = PLAYER_IS_IN_HOUSE[CopiedPlayerId];
	PLAYER_IS_IN_GANG_HALL[PlayerId] = PLAYER_IS_IN_GANG_HALL[CopiedPlayerId];
	PLAYER_DEATH_MATCH[PlayerId] = PLAYER_DEATH_MATCH[CopiedPlayerId];
	PLAYER_IS_IN_DM_SELECTION[PlayerId] = PLAYER_IS_IN_DM_SELECTION[CopiedPlayerId];
	PLAYER_DEATH_MATCH_SKIN[PlayerId] = PLAYER_DEATH_MATCH_SKIN[CopiedPlayerId];
	PLAYER_PLAYS_EMOTICON[PlayerId] = PLAYER_PLAYS_EMOTICON[CopiedPlayerId];
	PLAYER_EMOTICON_TIMER[PlayerId] = PLAYER_EMOTICON_TIMER[CopiedPlayerId];
	PLAYER_CHECKPOINT[PlayerId] = PLAYER_CHECKPOINT[CopiedPlayerId];
	PLAYER_CHECKPOINT_TYPE[PlayerId] = PLAYER_CHECKPOINT_TYPE[CopiedPlayerId];
	new I0;
	for (I0 = 0; I0 < 3; I0++)
	{
		PLAYER_CHECKPOINT_POSITION[PlayerId][I0] = PLAYER_CHECKPOINT_POSITION[CopiedPlayerId][I0];
	}
	for (I0 = 0; I0 < 4; I0++)
	{
		PLAYER_LAST_POSITION[PlayerId][I0] = PLAYER_LAST_POSITION[CopiedPlayerId][I0];
    }
	PLAYER_MENU_TYPE[PlayerId] = PLAYER_MENU_TYPE[CopiedPlayerId];
	PLAYER_MENU[PlayerId] = PLAYER_MENU[CopiedPlayerId];
	PLAYER_MAP_MARKERS[PlayerId] = PLAYER_MAP_MARKERS[CopiedPlayerId];
	//Save Data
	PLAYER_INTERIOR[PlayerId] = PLAYER_INTERIOR[CopiedPlayerId];
	PLAYER_HEALTH[PlayerId] = PLAYER_HEALTH[CopiedPlayerId];
	PLAYER_ARMOUR[PlayerId] = PLAYER_ARMOUR[CopiedPlayerId];
	for (I0 = 0; I0 < 13; I0++)
	{
	    PLAYER_WEAPON[PlayerId][I0] = PLAYER_WEAPON[CopiedPlayerId][I0];
		PLAYER_AMMO[PlayerId][I0] = PLAYER_AMMO[CopiedPlayerId][I0];
	}
    return true;
}

//Verschiebt den letzten Player an die Position des entfernten Players und setzt den Wert der Player-Anzahl herunter.
public RemovePlayer(PlayerId)
{
    ClearPlayer(PlayerId, false);
    if ((PlayerId + 1) != PLAYERS)
	{
		CopyPlayer(PlayerId, (PLAYERS - 1));
		ClearPlayer((PLAYERS - 1), true);
	}
	PLAYERS--;
	return true;
}

//Map Marker beginnen mit 1
public AddPlayerMapMarker(PlayerId, Icon, Float:PositionX, Float:PositionY, Float:PositionZ, Colour)
{
    if ((PLAYER_MAP_MARKERS[PlayerId] + 1) <= MAX_PLAYER_MAP_MARKERS)
	{
    	PLAYER_MAP_MARKERS[PlayerId]++;
    	return SetPlayerMapIcon(PlayerId, PLAYER_MAP_MARKERS[PlayerId], PositionX, PositionY, PositionZ, Icon, Colour);
	}
	return 0;
}

public ClearAllPlayers() //Muss am Anfang des Modes ausgeführt werden und cleared alle Spieler das erste Mal
{
	for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
		ClearPlayer(I0, false, true);
	}
	return true;
}
