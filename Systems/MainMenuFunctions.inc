//*******************************************************************
//Main Menu Functions
//*******************************************************************
#if defined MainMenuFunctions_included
  	#endinput
#endif
#define MainMenuFunctions_included
#pragma library MainMenuFunctions

//-- Functions --
public PlayerSelectsMainMenuItem(PlayerId, MenuItem)
{
    switch (MenuItem)
	{
	    //Benutzerdaten
	    case 0:
	    {
	        CreateAccountMenuForPlayer(PlayerId);
	        new AccountId = PLAYER_ACCOUNT[PlayerId];
	    	new InfoMessage[MAX_STRING];
	    	format(InfoMessage, sizeof(InfoMessage), "~y~Benutzerdaten~n~~w~Name: %s~n~Passwort: %s~n~Email: %s~n~Land: %s~n~Beschreibung: %s~n~Spieler: %d~n~", ACCOUNT_NAME[AccountId], ACCOUNT_PASSWORD[AccountId], ACCOUNT_EMAIL[AccountId], ACCOUNT_COUNTRY[AccountId], ACCOUNT_DESCRIPTION[AccountId], ACCOUNT_PLAYERS[AccountId]);
	    	SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, InfoMessage);
	    }
	    //Spielerdaten
		case 1:
		{
	    	CreateMainMenuForPlayer(PlayerId);
	    	new AccountId = PLAYER_ACCOUNT[PlayerId];
	    	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	    	new InfoMessage[MAX_STRING];
	    	format(InfoMessage, sizeof(InfoMessage), "~y~Spielerdaten~n~~w~Name: %s~n~Stufe: %d~n~Erfahrung %d/%d~n~Kopfgeld: %d", ACCOUNT_P_NAME[AccountId][AccountPlayerId], ACCOUNT_P_LEVEL[AccountId][AccountPlayerId], ACCOUNT_P_EXPERIENCE[AccountId][AccountPlayerId], ACCOUNT_P_NEXT_LEVEL_EXPERIENCE[AccountId][AccountPlayerId], ACCOUNT_P_HEAD_MONEY[AccountId][AccountPlayerId]);
	    	SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, InfoMessage);
		}
		case 2:
		{
	    	CreateHousesMenu(PlayerId);
		}
		//Hilfe
	    case 3:
	    {
            CreateHelpMenuForPlayer(PlayerId);
	    }
		case 4:
		{
		    new AccountId = PLAYER_ACCOUNT[PlayerId];
	    	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	    	if (ACCOUNT_P_GANG[AccountId][AccountPlayerId] == -1)
	    	{
	    	    CreateGangCreationMenu(PlayerId);
	    	}
	    	else
	    	{
    	    	CreateGangMenu(PlayerId);
	    		new GangId = ACCOUNT_P_GANG[AccountId][AccountPlayerId];
    	    	new InfoMessage[MAX_STRING];
				format(InfoMessage, sizeof(InfoMessage), "~y~Gang-Daten~n~~w~Gang-Name: %s~n~Rang: %s~n~Rang-Punkte: %d", GANG_NAME[GangId], GANG_RANK_NAME[ACCOUNT_P_GANG_RANK[AccountId][AccountPlayerId]], ACCOUNT_P_GANG_RANK_POINTS[AccountId][AccountPlayerId]);
	    		SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, InfoMessage);
	    	}
		}
		case 5:
		{
		    new AccountId = PLAYER_ACCOUNT[PlayerId];
	    	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
		    if (ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId] == -1)
		    {
	    		CreateProfessionSelectionMenu(PlayerId);
			}
			else
			{
			    if (!PLAYER_USES_PROFESSION[PlayerId])
				{
					CreateProfessionStartMenu(PlayerId);
				}
				else
				{
			    	PlayerEndsProfession(PlayerId);
			    	CreateMainMenuForPlayer(PlayerId);
				}
			}
		}
		default:
		{
 			SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Dieses Menü-Objekt hat noch keine Funktion.");
		}
	}
	return true;
}

public CreateMainMenuForPlayer(PlayerId)
{
	new AccountId = PLAYER_ACCOUNT[PlayerId];
	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	if (ACCOUNT_P_TOWN[AccountId][AccountPlayerId] != -1)
	{
    	CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_MAIN_MENU, 0, "Hauptmenü");
    	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_MAIN_MENU, "Benutzerdaten"); //Neu
    	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_MAIN_MENU, "Spielerdaten");
    	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_MAIN_MENU, "Häuser");
    	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_MAIN_MENU, "Hilfe"); //Neu
		//Gang
		if (ACCOUNT_P_GANG[AccountId][AccountPlayerId] == -1)
    	{
    	    AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_MAIN_MENU, "Gang gründen");
    	}
    	else
    	{
    		AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_MAIN_MENU, "Gang verwalten");
		}
		//Profession
		if (ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId] == -1)
		{
    		AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_MAIN_MENU, "Beruf wählen");
		}
		else
		{
		    if (!PLAYER_USES_PROFESSION[PlayerId])
			{
				AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_MAIN_MENU, "Beruf starten");
			}
			else
			{
			    AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_MAIN_MENU, "Beruf beenden");
			}
		}
		ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_MAIN_MENU);
		return true;
	}
	else
	{
	    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie müssen zunächst eine Startstadt wählen.");
	}
	return false;
}

public PlayerSelectsHelpMenuItem(PlayerId, MenuItem)
{
    CreateHelpMenuForPlayer(PlayerId);
    switch (MenuItem)
	{
	    default:
		{
	    	SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Dieses Menü-Objekt hat noch keine Funktion.");
		}
	}
	return true;
}

public CreateHelpMenuForPlayer(PlayerId)
{
    CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_HELP_MENU, 0, "Hilfe");
   	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HELP_MENU, "Spielmodus");
   	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HELP_MENU, "Steuerung");
   	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HELP_MENU, "Benutzer");
   	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HELP_MENU, "Spieler");
   	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HELP_MENU, "Gangs");
   	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HELP_MENU, "Berufe");
   	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HELP_MENU, "Missionen");
   	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HELP_MENU, "Mitwirkende");
   	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_HELP_MENU);
	return true;
}

public PlayerSelectsAccountMenuItem(PlayerId, MenuItem)
{
    new AccountId = PLAYER_ACCOUNT[PlayerId];
    CreateAPMenuForPlayer(PlayerId, AccountId, MenuItem);
	return true;
}

public CreateAccountMenuForPlayer(PlayerId)
{
    new AccountId = PLAYER_ACCOUNT[PlayerId];
	if (ACCOUNT_PLAYERS[AccountId] > 0)
	{
	    CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_ACCOUNT_MENU, 0, "Benutzerdaten");
	    for (new I0 = 0; I0 < ACCOUNT_PLAYERS[AccountId]; I0 ++)
	    {
	        AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_ACCOUNT_MENU, ACCOUNT_P_NAME[AccountId][I0]);
	    }
		//Später noch einfügen, dass man Benutzer gescheit verwalten kann.
	   	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_ACCOUNT_MENU);
 	}
 	else
 	{
 		SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Ihr Benutzer hat keine Spieler.");
 	}
	return true;
}

public PlayerSelectsAPMenuItem(PlayerId) //PlayerSelectsAccountPlayerMenuItem
{
    CreateMainMenuForPlayer(PlayerId);
    new AccountId = PLAYER_ACCOUNT[PlayerId];
    new AccountPlayerId = PLAYER_MENU[PlayerId];
    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, "Spieler gelöscht.");
    if (PLAYER_ACCOUNT_PLAYER[PlayerId] == AccountPlayerId) //Muss davor ausgeführt werden
    {
        SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie wurden vom Server gekickt, da Sie Ihren derzeitigen Spieler gelöscht haben.");
        Kick(PlayerId);

    }
    RemoveAccountPlayer(AccountId, AccountPlayerId);
	return true;
}

public CreateAPMenuForPlayer(PlayerId, AccountId, AccountPlayerId) //CreateAccountPlayerMenuForPlayer
{
    CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_ACCOUNT_PLAYER_MENU, AccountPlayerId, ACCOUNT_P_NAME[AccountId][AccountPlayerId]);
   	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_ACCOUNT_PLAYER_MENU, "Löschen");
   	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_ACCOUNT_PLAYER_MENU);
   	return true;
}
