//*******************************************************************
//Gang Hall Functions
//*******************************************************************
#if defined GangHallFunctions_included
  	#endinput
#endif
#define GangHallFunctions_included
#pragma library GangHallFunctions

//-- Functions --
public CreateBuyGangHallMenu(PlayerId)
{
    CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_GANG_HALL_SELECTION, 0, "Gang-Hallen");
    SetCustomMenuHeader(PlayerId, MENU_TYPE_GANG_HALL_SELECTION, "Halle - Preis");
    new MenuItemText[MAX_STRING];
    for (new I0 = 0; I0 < GANG_HALLS; I0++)
    {
        if (GANG_HALL_OWNER[I0] == -1)
        {
            format(MenuItemText, sizeof(MenuItemText), "%s - %d$", GANG_HALL_NAME[I0], GANG_HALL_PRICE[I0]);
    		AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_GANG_HALL_SELECTION, MenuItemText);
		}
	}
    ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_GANG_HALL_SELECTION);
    return true;
}

public GangBuysGangHall(PlayerId, GangHallId)
{
	new AccountId = PLAYER_ACCOUNT[PlayerId];
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
    new GangId = ACCOUNT_P_GANG[AccountId][AccountPlayerId];
	if (GetPlayerMoney(PlayerId) >= GANG_HALL_PRICE[GangHallId])
	{
	    GANG_HALL_OWNER[GangHallId] = GangId;
	    GANG_GANG_HALL[GangId] = GangHallId;
	    new InfoMessage[MAX_STRING];
	    format(InfoMessage, sizeof(InfoMessage), "%s hat die Gang-Halle '%s' gekauft.", PLAYER_NAME[PlayerId], GANG_HALL_NAME[GangHallId]);
	    SendGangMessage(GangId, -1, MESSAGE_TYPE_ACCEPTANCE, InfoMessage);
	}
	else
	{
	    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Diese Gang-Halle ist zu teuer.");
	}
	return true;
}

public PlayerEntersGangHall(PlayerId)
{
	new AccountId = PLAYER_ACCOUNT[PlayerId];
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
    new GangId = ACCOUNT_P_GANG[AccountId][AccountPlayerId];
    new GangHallId = GANG_GANG_HALL[GangId];
    PLAYER_IS_IN_GANG_HALL[PlayerId] = true;
    SetPlayerInterior(PlayerId, GANG_HALL_INTERIOR[GangHallId]);
	SetPlayerPos(PlayerId, GANG_HALL_POSITION[GangHallId][X], GANG_HALL_POSITION[GangHallId][Y], GANG_HALL_POSITION[GangHallId][Z]);
	SetPlayerFacingAngle(PlayerId, GANG_HALL_POSITION[GangHallId][FACING]);
	SetCameraBehindPlayer(PlayerId);
	SetPlayerVirtualWorld(PlayerId, (MAX_PLAYERS + GangHallId));
    new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "%s hat die Gang-Halle betreten.", PLAYER_NAME[PlayerId]);
	SendGangMessage(GangId, -1, MESSAGE_TYPE_INFO, InfoMessage);
	return true;
}

public PlayerLeavesGangHall(PlayerId)
{
	new AccountId = PLAYER_ACCOUNT[PlayerId];
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
    new GangId = ACCOUNT_P_GANG[AccountId][AccountPlayerId];
    new GangHallId = GANG_GANG_HALL[GangId];
    PLAYER_IS_IN_GANG_HALL[PlayerId] = false;
    SetPlayerInterior(PlayerId, 0);
	SetPlayerPos(PlayerId, GANG_HALL_EXIT_POSITION[GangHallId][X], GANG_HALL_EXIT_POSITION[GangHallId][Y], GANG_HALL_EXIT_POSITION[GangHallId][Z]);
	SetPlayerFacingAngle(PlayerId, GANG_HALL_EXIT_POSITION[GangHallId][FACING]);
	SetCameraBehindPlayer(PlayerId);
	SetPlayerVirtualWorld(PlayerId, 0);
    new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "%s hat die Gang-Halle verlassen.", PLAYER_NAME[PlayerId]);
	SendGangMessage(GangId, -1, MESSAGE_TYPE_INFO, InfoMessage);
	return true;
}

public StartGangBattle(GangId, OtherGangId)
{
}

public EndGangBattle(GangId, WinerGangId)
{
}

public AddGangHall(Name[MAX_GANG_HALL_NAME], Price, Float:PositionX, Float:PositionY, Float:PositionZ, Float:PositionFacing, Interior, Float:TeamPosition1X, Float:TeamPosition1Y, Float:TeamPosition1Z, Float:TeamPosition1Facing, Float:TeamPosition2X, Float:TeamPosition2Y, Float:TeamPosition2Z, Float:TeamPosition2Facing, Float:ExitPositionX, Float:ExitPositionY, Float:ExitPositionZ, Float:ExitPositionFacing)
{
	new GangHallId = GANG_HALLS;
    if (GangHallId < MAX_GANG_HALLS)
	{
	    GANG_HALL_NAME[GangHallId] = Name;
	    GANG_HALL_PRICE[GangHallId] = Price;
	    GANG_HALL_OWNER[GangHallId] = -1;
		GANG_HALL_POSITION[GangHallId][X] = PositionX;
		GANG_HALL_POSITION[GangHallId][Y] = PositionY;
		GANG_HALL_POSITION[GangHallId][Z] = PositionZ;
		GANG_HALL_POSITION[GangHallId][FACING] = PositionFacing;
		GANG_HALL_INTERIOR[GangHallId] = Interior;
		GANG_HALL_TEAM_POSITION[GangHallId][0][X] = TeamPosition1X;
        GANG_HALL_TEAM_POSITION[GangHallId][0][Y] = TeamPosition1Y;
        GANG_HALL_TEAM_POSITION[GangHallId][0][Z] = TeamPosition1Z;
        GANG_HALL_TEAM_POSITION[GangHallId][0][FACING] = TeamPosition1Facing;
        GANG_HALL_TEAM_POSITION[GangHallId][1][X] = TeamPosition2X;
        GANG_HALL_TEAM_POSITION[GangHallId][1][Y] = TeamPosition2Y;
        GANG_HALL_TEAM_POSITION[GangHallId][1][Z] = TeamPosition2Z;
        GANG_HALL_TEAM_POSITION[GangHallId][1][FACING] = TeamPosition2Facing;
		GANG_HALL_EXIT_POSITION[GangHallId][X] = ExitPositionX;
		GANG_HALL_EXIT_POSITION[GangHallId][Y] = ExitPositionY;
		GANG_HALL_EXIT_POSITION[GangHallId][Z] = ExitPositionZ;
		GANG_HALL_EXIT_POSITION[GangHallId][FACING] = ExitPositionFacing;
		GANG_HALLS++;
		return GangHallId;
	}
	return -1;
}
