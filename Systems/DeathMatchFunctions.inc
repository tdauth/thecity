//*******************************************************************
//Death Match Functions
//*******************************************************************
#if defined DeathMatchFunctions_included
  	#endinput
#endif
#define DeathMatchFunctions_included
#pragma library DeathMatchFunctions

//-- Functions --
public CreateDMMarkersForPlayer(PlayerId)
{
	for (new I0 = 0; I0 < DEATH_MATCHES; I0++)
	{
		AddPlayerMapMarker(PlayerId, 19, DEATH_MATCH_CHECKPOINT[I0][X], DEATH_MATCH_CHECKPOINT[I0][Y], DEATH_MATCH_CHECKPOINT[I0][Z], 0);
	}
	return true;
}

public SendDeathMatchMessage(DeathMatchId, Type, Message[])
{
	for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
		if (PLAYER_DEATH_MATCH[I0] == DeathMatchId)
		{
    		SendClientMessageToPlayer(I0, Type, Message);
		}
	}
	return true;
}

public AddAccountPlayerPvPSkill(AccountId, AccountPlayerId, Value, Add)
{
	if (Add)
	{
	    ACCOUNT_P_PVP_SKILL[AccountId][AccountPlayerId] += Value;
	}
	else
	{
	    ACCOUNT_P_PVP_SKILL[AccountId][AccountPlayerId] -= Value;
	}
	new PlayerId = ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId];
	new InfoMessage[MAX_STRING];
 	format(InfoMessage, sizeof(InfoMessage), "+%d PvP-Punkte.", Value);
	GameTextForPlayer(PlayerId, InfoMessage, ConvertSeconds(6), 5);
	return ACCOUNT_P_PVP_SKILL[AccountId][AccountPlayerId];
}

public AddPlayerPvPSkill(PlayerId, Value, Add)
{
	return AddAccountPlayerPvPSkill(PLAYER_ACCOUNT[PlayerId], PLAYER_ACCOUNT_PLAYER[PlayerId], Value, Add);
}

public ShowDeathMatchPlayersForPlayer(PlayerId)
{
	for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
	    if (PLAYER_DEATH_MATCH[PlayerId] == PLAYER_DEATH_MATCH[I0])
	    {
	        if (PLAYER_DEATH_MATCH_SKIN[PlayerId] == PLAYER_DEATH_MATCH_SKIN[I0])
	        {
	            SetPlayerMarkerForPlayer(PlayerId, I0, DEATH_MATCH_SKIN_COLOUR[PLAYER_DEATH_MATCH[PlayerId]][PLAYER_DEATH_MATCH_SKIN[PlayerId]]);
	        }
	        ShowPlayerNameTagForPlayer(PlayerId, I0, true);
	    }
	}
	return true;
}

public PlayerEntersDMCheckpoint(PlayerId, DeathMatchId)
{
	if (!PLAYER_USES_PROFESSION[PlayerId])
	{
		CreateDeathMatchMenu(PlayerId, DeathMatchId);
	}
	else
	{
	    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie müssen Ihren Beruf beenden, bevor Sie an einem Death-Match teilnehmen können.");
	}
	return true;
}

public CreateDeathMatchMenu(PlayerId, DeathMatchId)
{
    CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_DEATH_MATCH, DeathMatchId, DEATH_MATCH_NAME[DeathMatchId]);
    SetCustomMenuHeader(PlayerId, MENU_TYPE_DEATH_MATCH, "Death-Match");
    if (PLAYER_DEATH_MATCH[PlayerId] != DeathMatchId)
    {
    	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_DEATH_MATCH, "Betreten");
    	//Save Data Just If Player Is Not In Death Match
    	SavePlayerState(PlayerId);
		SavePlayerWeapons(PlayerId);
	}
	else
	{
	    AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_DEATH_MATCH, "Skin wechseln");
	    AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_DEATH_MATCH, "Verlassen");
	}
	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_DEATH_MATCH);
	return true;
}

public SetupDeathMatchSkinSelection(PlayerId, DeathMatchId)
{
	PLAYER_DEATH_MATCH[PlayerId] = DeathMatchId;
	PLAYER_IS_IN_DM_SELECTION[PlayerId] = true;
	PLAYER_DEATH_MATCH_SKIN[PlayerId] = 0;
	SetPlayerInterior(PlayerId, DEATH_MATCH_INTERIOR[DeathMatchId]);
	SetPlayerPos(PlayerId, DEATH_MATCH_VIEW_TARGET[DeathMatchId][X], DEATH_MATCH_VIEW_TARGET[DeathMatchId][Y], DEATH_MATCH_VIEW_TARGET[DeathMatchId][Z]);
	SetPlayerFacingAngle(PlayerId, DEATH_MATCH_VIEW_TARGET[DeathMatchId][FACING]);
    SetPlayerSkin(PlayerId, DEATH_MATCH_SKIN[DeathMatchId][0]);
	ClearAnimations(PlayerId);
	SetPlayerCameraPos(PlayerId, DEATH_MATCH_VIEW_POSITION[DeathMatchId][X], DEATH_MATCH_VIEW_POSITION[DeathMatchId][Y], DEATH_MATCH_VIEW_POSITION[DeathMatchId][Z]);
	SetPlayerCameraLookAt(PlayerId, DEATH_MATCH_VIEW_TARGET[DeathMatchId][X], DEATH_MATCH_VIEW_TARGET[DeathMatchId][Y], DEATH_MATCH_VIEW_TARGET[DeathMatchId][Z]);
	ResetPlayerWeapons(PlayerId);
	TogglePlayerControllable(PlayerId, false);
	new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "~r~%s", DEATH_MATCH_NAME[DeathMatchId]);
	GameTextForPlayer(PlayerId, InfoMessage, ConvertSeconds(8), 4);
	SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, "~y~Death-Match-Skin-Auswahl~n~~w~Drücken Sie ~<~ oder ~>~, um den Skin zu wechseln. Drücken Sie ~k~~PED_SPRINT~, um den ausgewählten Skin zu verwenden.");
	return true;
}

public ChangeDeathMatchSkin(PlayerId, DeathMatchId, Forward)
{
	new InfoMessage[MAX_STRING];
	new DeathMatchSkin;
	if (Forward)
	{
	    if (PLAYER_DEATH_MATCH_SKIN[PlayerId] != DEATH_MATCH_SKINS[DeathMatchId])
	    {
	    	PLAYER_DEATH_MATCH_SKIN[PlayerId]++;
		}
		else
		{
		    PLAYER_DEATH_MATCH_SKIN[PlayerId] = 0;
		}
	}
	else
	{
	    if (PLAYER_DEATH_MATCH_SKIN[PlayerId] != 0)
	    {
    		PLAYER_DEATH_MATCH_SKIN[PlayerId]--;
		}
		else
		{
		    PLAYER_DEATH_MATCH_SKIN[PlayerId] = (DEATH_MATCH_SKINS[DeathMatchId] - 1);
		}
	}
	DeathMatchSkin = PLAYER_DEATH_MATCH_SKIN[PlayerId];
	SetPlayerSkin(PlayerId, DEATH_MATCH_SKIN[DeathMatchId][DeathMatchSkin]);
	format(InfoMessage, sizeof(InfoMessage), "~y~Skin %d~n~~w~%s", DeathMatchSkin, DEATH_MATCH_SKIN_NAME[DeathMatchId][DeathMatchSkin]);
	SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, InfoMessage);
	return true;
}

public SelectDeathMatchSkin(PlayerId, DeathMatchId, Skin)
{
    PLAYER_IS_IN_DM_SELECTION[PlayerId] = false;
	SetPlayerPos(PlayerId, DEATH_MATCH_SKIN_POSITION[DeathMatchId][Skin][X], DEATH_MATCH_SKIN_POSITION[DeathMatchId][Skin][Y], DEATH_MATCH_SKIN_POSITION[DeathMatchId][Skin][Z]);
	SetPlayerFacingAngle(PlayerId, DEATH_MATCH_SKIN_POSITION[DeathMatchId][Skin][FACING]);
	SetCameraBehindPlayer(PlayerId);
	SetPlayerVirtualWorld(PlayerId, (MAX_PLAYERS + MAX_GANG_HALLS + DeathMatchId));
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
	ShowDeathMatchPlayersForPlayer(PlayerId);
	TogglePlayerControllable(PlayerId, true);
	new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "%s hat das Death-Match betreten (Mannschaft %d).", PLAYER_NAME[PlayerId], Skin);
	SendDeathMatchMessage(DeathMatchId, MESSAGE_TYPE_INFO, InfoMessage);
	return true;
}

public PlayerLeavesDeathMatch(PlayerId)
{
	new DeathMatchId = PLAYER_DEATH_MATCH[PlayerId];
	new Skin = PLAYER_DEATH_MATCH_SKIN[PlayerId];
    PLAYER_DEATH_MATCH[PlayerId] = -1;
    PLAYER_DEATH_MATCH_SKIN[PlayerId] = 0;
    new AccountId = PLAYER_ACCOUNT[PlayerId];
    new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	SetPlayerSkin(PlayerId, ACCOUNT_P_SKIN[AccountId][AccountPlayerId]);
	SetPlayerInterior(PlayerId, 0);
	SetPlayerPos(PlayerId, DEATH_MATCH_CHECKPOINT[DeathMatchId][X], DEATH_MATCH_CHECKPOINT[DeathMatchId][Y], DEATH_MATCH_CHECKPOINT[DeathMatchId][Z]);
	SetPlayerFacingAngle(PlayerId, 0.0000);
	SetCameraBehindPlayer(PlayerId);
	SetPlayerVirtualWorld(PlayerId, 0);
	LoadPlayerState(PlayerId);
	LoadPlayerWeapons(PlayerId);
    new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "%s hat das Death-Match verlassen (Team %d).", PLAYER_NAME[PlayerId], Skin);
	SendDeathMatchMessage(DeathMatchId, MESSAGE_TYPE_INFO, InfoMessage);
	return true;
}

public PlayerKillsDeathMatchPlayer(PlayerId, KillerId)
{
	//Kill
	if (PLAYER_DEATH_MATCH_SKIN[PlayerId] != PLAYER_DEATH_MATCH_SKIN[KillerId])
	{
	    GivePlayerMoney(KillerId, 200);
	    AddPlayerPvPSkill(KillerId, 1, true);
	    SendMessageToPlayer(KillerId, MESSAGE_TYPE_ACCEPTANCE, "Kill: +200$");
	}
	//Team Kill
	else
	{
	    GivePlayerMoney(KillerId, -400);
    	SendMessageToPlayer(KillerId, MESSAGE_TYPE_ERROR, "Team-Kill: -400$");
	}
	SetupDeathMatchSkinSelection(PlayerId, PLAYER_DEATH_MATCH[PlayerId]); //TESTEN
	return true;
}

public AddDeathMatch(Name[MAX_DEATH_MATCH_NAME], Float:CheckpointX, Float:CheckpointY, Float:CheckpointZ, Float:CheckpointSize, Float:ViewPositionX, Float:ViewPositionY, Float:ViewPositionZ, Float:ViewTargetX, Float:ViewTargetY, Float:ViewTargetZ, Float:ViewTargetFacing, Interior)
{
	new DeathMatchId = DEATH_MATCHES;
    if (DeathMatchId < MAX_DEATH_MATCHES)
	{
		DEATH_MATCH_NAME[DeathMatchId]= Name;
		DEATH_MATCH_CHECKPOINT[DeathMatchId][X] = CheckpointX;
		DEATH_MATCH_CHECKPOINT[DeathMatchId][Y] = CheckpointY;
		DEATH_MATCH_CHECKPOINT[DeathMatchId][Z] = CheckpointZ;
		DEATH_MATCH_CHECKPOINT[DeathMatchId][SIZE] = CheckpointSize;
		DEATH_MATCH_VIEW_POSITION[DeathMatchId][X] = ViewPositionX;
		DEATH_MATCH_VIEW_POSITION[DeathMatchId][Y] = ViewPositionY;
		DEATH_MATCH_VIEW_POSITION[DeathMatchId][Z] = ViewPositionZ;
		DEATH_MATCH_VIEW_TARGET[DeathMatchId][X] = ViewTargetX;
		DEATH_MATCH_VIEW_TARGET[DeathMatchId][Y] = ViewTargetY;
		DEATH_MATCH_VIEW_TARGET[DeathMatchId][Z] = ViewTargetZ;
		DEATH_MATCH_VIEW_TARGET[DeathMatchId][FACING] = ViewTargetFacing;
		DEATH_MATCH_INTERIOR[DeathMatchId] = Interior;
		DEATH_MATCH_SKINS[DeathMatchId]= 0;
		DEATH_MATCHES++;
		return DeathMatchId;
	}
	return -1;
}

public AddDeathMatchSkin(Skin, Name[MAX_DEATH_MATCH_SKIN_NAME], Colour, Weapon1, Ammo1, Weapon2, Ammo2, Weapon3, Ammo3, Float:PositionX, Float:PositionY, Float:PositionZ, Float:PositionFacing)
{
	new DeathMatchId = (DEATH_MATCHES - 1);
	new DeathMatchSkinId = DEATH_MATCH_SKINS[DeathMatchId];
	if (DeathMatchSkinId < MAX_DEATH_MATCH_SKINS)
	{
	    DEATH_MATCH_SKIN[DeathMatchId][DeathMatchSkinId] = Skin;
        DEATH_MATCH_SKIN_NAME[DeathMatchId][DeathMatchSkinId] = Name;
        DEATH_MATCH_SKIN_COLOUR[DeathMatchId][DeathMatchSkinId] = Colour;
        DEATH_MATCH_SKIN_WEAPON[DeathMatchId][DeathMatchSkinId][0] = Weapon1;
        DEATH_MATCH_SKIN_WEAPON[DeathMatchId][DeathMatchSkinId][3] = Ammo1;
        DEATH_MATCH_SKIN_WEAPON[DeathMatchId][DeathMatchSkinId][1] = Weapon2;
        DEATH_MATCH_SKIN_WEAPON[DeathMatchId][DeathMatchSkinId][4] = Ammo2;
        DEATH_MATCH_SKIN_WEAPON[DeathMatchId][DeathMatchSkinId][2] = Weapon3;
        DEATH_MATCH_SKIN_WEAPON[DeathMatchId][DeathMatchSkinId][5] = Ammo3;
        DEATH_MATCH_SKIN_POSITION[DeathMatchId][DeathMatchSkinId][X] = PositionX;
        DEATH_MATCH_SKIN_POSITION[DeathMatchId][DeathMatchSkinId][Y] = PositionY;
        DEATH_MATCH_SKIN_POSITION[DeathMatchId][DeathMatchSkinId][Z] = PositionZ;
        DEATH_MATCH_SKIN_POSITION[DeathMatchId][DeathMatchSkinId][FACING] = PositionFacing;
        DEATH_MATCH_SKINS[DeathMatchId]++;
		return DeathMatchSkinId;
	}
	return -1;
}
