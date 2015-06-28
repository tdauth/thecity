//*******************************************************************
//Gang Functions
//Dynamisch
//*******************************************************************
#if defined GangFunctions_included
  	#endinput
#endif
#define GangFunctions_included
#pragma library GangFunctions

//-- Functions --
GangNameIsUsed(GangName[MAX_GANG_NAME])
{
	for (new I0 = 0; I0 < GANGS; I0++)
	{
	    if (strcmp(GANG_NAME[I0], GangName, true) == 0 && strlen(GANG_NAME[I0]) > 0)
	    {
	        return true;
	    }
	}
	return false;
}

GangContainsAccountPlayer(GangId, AccountId, AccountPlayerId)
{
	for (new I0 = 0; I0 < MAX_GANG_MEMBERS; I0++)
	{
 		if (GANG_MEMBER_ACCOUNT[GangId][I0] == AccountId && GANG_MEMBER_ACCOUNT_PLAYER[GangId][I0] == AccountPlayerId)
   		{
     		return I0;
	    }
	}
	return -1;
}

public SendGangMessage(GangId, PlayerId, Type, Message[])
{
    new AccountId, AccountPlayerId, UsedPlayerId;
    new InfoMessage[MAX_STRING];
	for (new I0; I0 < MAX_GANG_MEMBERS; I0++)
	{
	    AccountId = GANG_MEMBER_ACCOUNT[GangId][I0];
		AccountPlayerId = GANG_MEMBER_ACCOUNT_PLAYER[GangId][I0];
	    if (AccountId != -1)
	    {
	        UsedPlayerId = ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId];
	        if (PlayerId != -1)
			{
	        	format(InfoMessage, sizeof(InfoMessage), "Gang-Nachricht von %s: %s", PLAYER_NAME[PlayerId], Message);
			}
			else
			{
			    format(InfoMessage, sizeof(InfoMessage), "Gang: %s", Message);
			}
			SendClientMessageToPlayer(UsedPlayerId, Type, InfoMessage);
		}
	}
	return true;
}

public CreateGangCreationMenu(PlayerId)
{
    CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_GANG_CREATION, 0, "Gang-Farben");
    SetCustomMenuHeader(PlayerId, MENU_TYPE_GANG_CREATION, "Auswahl");
	for (new I0 = 0; I0 < MAX_GANG_USEABLE_COLOURS; I0++)
	{
	    AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_GANG_CREATION, GANG_USEABLE_COLOUR_NAME[I0]);
	}
	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_GANG_CREATION);
	return true;
}

public CreateGangMenu(PlayerId)
{
    new AccountId = PLAYER_ACCOUNT[PlayerId];
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	new GangId = ACCOUNT_P_GANG[AccountId][AccountPlayerId];
 	CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_GANG, 0, "Gang-Verwaltung");
 	if (ACCOUNT_P_GANG_RANK[AccountId][AccountPlayerId] != GANG_RANK_BOSS)
 	{
		AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_GANG, "Gang verlassen");
	}
	else if (GANG_GANG_HALL[GangId] == -1)
	{
	    AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_GANG, "Gang-Halle kaufen");
	}
	if (GANG_GANG_HALL[GangId] != -1 && !PLAYER_IS_IN_GANG_HALL[PlayerId])
	{
	    AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_GANG, "Gang-Halle betreten");
	}
	else if (GANG_GANG_HALL[GangId] != -1)
	{
	    AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_GANG, "Gang-Halle verlassen");
	}
	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_GANG);
	return true;
}

public PlayerCreatesGang(PlayerId, Colour)
{
    if (GetPlayerMoney(PlayerId) >= 1000)
    {
        new GangName[MAX_GANG_NAME];
        strcat(GangName, "Namenlos", sizeof(GangName)); //Wegen der Größe
        new GangId =  AddGang(GangName, GANG_USEABLE_COLOUR[Colour]);
		if (GangId != -1)
		{
		    new AccountId = PLAYER_ACCOUNT[PlayerId];
		    new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
		    SetAccountPlayerToGangBoss(GangId, AccountId, AccountPlayerId);
			GivePlayerMoney(PlayerId, -1000);
			CreateMainMenuForPlayer(PlayerId); //Create Menu After Settings
        	new InfoMessage[MAX_STRING];
			format(InfoMessage, sizeof(InfoMessage), "%s hat eine neue Gang gegründet.", PLAYER_NAME[PlayerId]);
			SendClientMessageToAllPlayers(MESSAGE_TYPE_INFO, InfoMessage);
			return true;
		}
		else
		{
		    SendClientMessageToAllPlayers(MESSAGE_TYPE_ERROR, "Die maximale Anzahl erstellbarer Gangs wurde bereits erreicht.");
		}
    }
    else
    {
        SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie haben zu wenig Geld, um eine Gang zu gründen. Das Gründen einer Gang kostet 1000$.");
    }
    CreateMainMenuForPlayer(PlayerId); //Create Menu After Settings
	return false;
}

public PlayerJoinsGang(PlayerId, GangId)
{
    new InfoMessage[MAX_STRING];
    format(InfoMessage, sizeof(InfoMessage), "%s ist ein Ihrer Gang beigetreten.", PLAYER_NAME[PlayerId]);
    SendGangMessage(GangId, -1, MESSAGE_TYPE_ACCEPTANCE, InfoMessage);
	//Player Joins After Message
	new AccountId = PLAYER_ACCOUNT[PlayerId];
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	AddGangMember(GangId, AccountId, AccountPlayerId);
    format(InfoMessage, sizeof(InfoMessage), "~g~Gang-Einladung~n~~w~Sie sind nun ein Mitglied der Gang '%s'. Gehen Sie ins Hauptmenü, um Ihre Gang-Daten zu betrachten.", GANG_NAME[GangId]);
    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, InfoMessage);
    return true;
}

public PlayerLeavesGang(PlayerId, GangId)
{
    new AccountId = PLAYER_ACCOUNT[PlayerId];
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	new GangMemberId = GangContainsAccountPlayer(GangId, AccountId, AccountPlayerId);
	RemoveGangMember(GangId, GangMemberId);
    new InfoMessage[MAX_STRING];
    format(InfoMessage, sizeof(InfoMessage), "%s hat Ihre Gang verlassen.", PLAYER_NAME[PlayerId]);
    SendGangMessage(GangId, -1, MESSAGE_TYPE_ERROR, InfoMessage);
	format(InfoMessage, sizeof(InfoMessage), "~g~Gang~n~~w~Sie haben die Gang '%s' verlassen.", GANG_NAME[GangId]);
    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, InfoMessage);
    return true;
}

public SetAccountPlayerToGangBoss(GangId, AccountId, AccountPlayerId)
{
    new GangMemberId = GangContainsAccountPlayer(GangId, AccountId, AccountPlayerId);
    //Wenn der Spieler kein Mitglied der Gang ist, wird er einfach hinzugefügt.
    if (GangMemberId == -1)
    {
        GangMemberId = AddGangMember(GangId, AccountId, AccountPlayerId);
    }
    GANG_BOSS[GangId] = GangMemberId;
	ACCOUNT_P_GANG_RANK[AccountId][AccountPlayerId] = GANG_RANK_BOSS;
	ACCOUNT_P_GANG_RANK_POINTS[AccountId][AccountPlayerId] = 100;
	return false;
}

GetNextFreeGangId()
{
    if (GANGS < MAX_GANGS)
	{
	    return GANGS;
	}
	else
	{
	    for (new I0 = 0; I0 < MAX_GANGS; I0++)
	    {
	        if (!GANG[I0]) //Da Wert nicht unbedingt auf false gesetzt worden ist
	        {
	            return I0;
	        }
	    }
	}
	return -1;
}

//Setzt alle Gang-Werte zurück.
ClearGang(GangId, Copy, FirstClear = false) //Benötigt selbst kein FirstClear aber ClearGangMember
{
    GANG[GangId] = false;
    GANG_NAME[GangId] = "";
	GANG_COLOUR[GangId] = -1;
	GANG_BOSS[GangId] = -1; //Die Nummer des Account-Mitglieds des Bosses.
	GANG_AREAS[GangId] = 0;
	GANG_GANG_HALL[GangId] = -1;
	GANG_MEMBERS[GangId] = 0;
	for (new I0 = 0; I0 < MAX_GANG_MEMBERS; I0++)
    {
        ClearGangMember(GangId, I0, Copy, FirstClear);
    }
    return true;
}

public AddGang(Name[MAX_GANG_NAME], Colour)
{
    new GangId = GetNextFreeGangId();
    if (GangId != -1)
	{
	    ClearGang(GangId, false);
	    GANG[GangId] = true;
   		GANG_NAME[GangId] = Name;
		GANG_COLOUR[GangId] = Colour;
		GANGS++;
		return GangId;
	}
	return -1;
}

public CopyGang(GangId, CopiedGangId)
{
    GANG[GangId] = GANG[CopiedGangId];
    GANG_NAME[GangId] = GANG_NAME[CopiedGangId];
	GANG_COLOUR[GangId] = GANG_COLOUR[CopiedGangId];
	GANG_BOSS[GangId] = GANG_BOSS[CopiedGangId]; //Die Nummer des Account-Mitglieds des Bosses.
	GANG_AREAS[GangId] = GANG_AREAS[CopiedGangId];
	GANG_GANG_HALL[GangId] = GANG_GANG_HALL[CopiedGangId];
	GANG_MEMBERS[GangId] = GANG_MEMBERS[CopiedGangId];
	for (new I0 = 0; I0 < MAX_GANG_MEMBERS; I0++)
    {
        //Durch Funktion ersetzen.
        GANG_MEMBER_ACCOUNT[GangId][I0] = GANG_MEMBER_ACCOUNT[CopiedGangId][I0];
		GANG_MEMBER_ACCOUNT_PLAYER[GangId][I0] = GANG_MEMBER_ACCOUNT_PLAYER[CopiedGangId][I0];
    }
    return true;
}

//Verschiebt die letzte Gang an die Position der entfernten Gang und setzt den Wert der Gang-Anzahl herunter.
public RemoveGang(GangId)
{
    ClearGang(GangId, false);
    if ((GangId + 1) != GANGS)
	{
		CopyGang(GangId, (GANGS - 1));
		ClearGang((GANGS - 1), true);
	}
	GANGS--;
	return true;
}

GetNextFreeGangMemberId(GangId)
{
    if (GANG_MEMBERS[GangId] < MAX_GANG_MEMBERS)
	{
	    return GANG_MEMBERS[GangId];
	}
	else
	{
	    for (new I0 = 0; I0 < MAX_GANG_MEMBERS; I0++)
	    {
	        if (!GANG_MEMBER[GangId][I0]) //Da Wert nicht unbedingt auf false gesetzt worden ist
	        {
	            return I0;
	        }
	    }
	}
	return -1;
}

//Setzt alle GangMember-Werte zurück.
//ACHTUNG: AccountPlayer-Daten auch überprüfen und ändern.
ClearGangMember(GangId, GangMemberId, Copy, FirstClear = false)
{
	if (!FirstClear)
	{
		if (!Copy)
		{
			new AccountId = GANG_MEMBER_ACCOUNT[GangId][GangMemberId];
			new AccountPlayerId = GANG_MEMBER_ACCOUNT_PLAYER[GangId][GangMemberId];
			//AccountPlayer verlässt die Gang
			if (AccountId != -1 && AccountPlayerId != -1)
			{
		    	ACCOUNT_P_GANG[AccountId][AccountPlayerId] = -1;
		    	ACCOUNT_P_GANG_MEMBER[AccountId][AccountPlayerId] = -1;
		    	ACCOUNT_P_GANG_RANK[AccountId][AccountPlayerId] = -1;
				ACCOUNT_P_GANG_RANK_POINTS[AccountId][AccountPlayerId] = 0;
			}
		}
	}
    GANG_MEMBER[GangId][GangMemberId] = false;
	GANG_MEMBER_ACCOUNT[GangId][GangMemberId] = -1;
	GANG_MEMBER_ACCOUNT_PLAYER[GangId][GangMemberId] = -1;
	return true;
}

public AddGangMember(GangId, AccountId, AccountPlayerId)
{
    new GangMemberId = GetNextFreeGangMemberId(GangId);
    if (GangMemberId != -1)
    {
        ClearGangMember(GangId, GangMemberId, false);
        GANG_MEMBER[GangId][GangMemberId] = true;
		GANG_MEMBER_ACCOUNT[GangId][GangMemberId] = AccountId;
		GANG_MEMBER_ACCOUNT_PLAYER[GangId][GangMemberId] = AccountPlayerId;
		ACCOUNT_P_GANG[AccountId][AccountPlayerId] = GangId; //AccountPlayer-Daten
    	ACCOUNT_P_GANG_MEMBER[AccountId][AccountPlayerId] = GangMemberId; //AccountPlayer-Daten
		GANG_MEMBERS[GangId]++;
    	return GangMemberId;
	}
	return -1;
}

public CopyGangMember(GangId, GangMemberId, CopiedGangId, CopiedGangMemberId)
{
    GANG_MEMBER[GangId][GangMemberId] = GANG_MEMBER[CopiedGangId][CopiedGangMemberId];
	GANG_MEMBER_ACCOUNT[GangId][GangMemberId] = GANG_MEMBER_ACCOUNT[CopiedGangId][CopiedGangMemberId];
	GANG_MEMBER_ACCOUNT_PLAYER[GangId][GangMemberId] = GANG_MEMBER_ACCOUNT_PLAYER[CopiedGangId][CopiedGangMemberId];
	return true;
}

//Verschiebt das letzte GangMember an die Position des entfernten GangMembers und setzt den Wert der GangMember-Anzahl herunter.
public RemoveGangMember(GangId, GangMemberId)
{
    ClearGangMember(GangId, GangMemberId, false);
	if ((GangMemberId + 1) != GANG_MEMBERS[GangId])
	{
	    CopyGangMember(GangId, GangMemberId, GangId, (GANG_MEMBERS[GangId] - 1));
	    ClearGangMember(GangId, (GANG_MEMBERS[GangId] - 1), true);
	}
	GANG_MEMBERS[GangId]--;
	//Gang wird aufgelöst.
	if (GANG_MEMBERS[GangId] == 0)
	{
	    RemoveGang(GangId);
	}
	return true;
}

public ClearAllGangs() //Muss am Anfang des Modes ausgeführt werden und cleared alle Gangs das erste Mal - Damit werden auch alle Unterklassen der Gang gecleared
{
	for (new I0 = 0; I0 < MAX_GANGS; I0++)
	{
		ClearGang(I0, false, true);
	}
	return true;
}
