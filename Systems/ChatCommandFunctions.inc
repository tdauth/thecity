//*******************************************************************
//Chat Command Functions
//*******************************************************************
#if defined ChatCommandFunctions_included
  	#endinput
#endif
#define ChatCommandFunctions_included
#pragma library ChatCommandFunctions

//-- Functions --
PlayerChatCommandConditions(PlayerId, OtherPlayerId, Money)
{
	if (PLAYER_ACCOUNT[PlayerId] == -1)
   	{
   	    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie sind nicht angemeldet.");
   	    return false;
   	}
   	if (Money != -1)
   	{
   		if (GetPlayerMoney(PlayerId) < Money)
		{
	    	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie haben zu wenig Geld.");
	 		return false;
		}
		if (Money <= 0)
		{
		    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Der Betrag muss mehr als 0$ betragen.");
	 		return false;
		}
	}
   	if (OtherPlayerId != -1)
   	{
		if (PlayerId == OtherPlayerId)
		{
   	    	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie können nicht sich selbst als Ziel wählen.");
		    return false;
		}
		if (!IsPlayerConnected(OtherPlayerId))
		{
		    new ErrorMessage[MAX_STRING];
		    format(ErrorMessage, sizeof(ErrorMessage), "Spieler-Slot-%d ist nicht belegt.", OtherPlayerId);
		    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, ErrorMessage);
		    return false;
		}
 		if (PLAYER_ACCOUNT[PlayerId] == -1)
		{
		    new ErrorMessage[MAX_STRING];
		    format(ErrorMessage, sizeof(ErrorMessage), "Spieler %s ist nicht angemeldet.", PLAYER_NAME[OtherPlayerId]);
		    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, ErrorMessage);
		    return false;
		}
	}
	return true;
}

public CommandCreateMainMenuForPlayer(PlayerId)
{
    //General Conditions
    if (PlayerChatCommandConditions(PlayerId, -1, -1))
   	{
   	    if (PLAYER_MENU_TYPE[PlayerId] == -1)
   	    {
    		CreateMainMenuForPlayer(PlayerId);
		}
	}
	return true;
}

public ChatCommandAddPlayerHeadMoney(PlayerId, OtherPlayerId, Money)
{
    //General Conditions
    if (PlayerChatCommandConditions(PlayerId, OtherPlayerId, Money))
   	{
   	    if (PlayerIsHeadHunterOfPlayer(PlayerId, OtherPlayerId))
   	    {
   	    	if (GetPlayerHeadHunters(OtherPlayerId) < 6)
   	    	{
   	    	    new AccountId = PLAYER_ACCOUNT[PlayerId];
   	    	    new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
   	    	    new OtherAccountId = PLAYER_ACCOUNT[OtherPlayerId];
   	    	    new OtherAccountPlayerId = PLAYER_ACCOUNT_PLAYER[OtherPlayerId];
   	        	ACCOUNT_P_HEAD_HUNTER_ID[OtherAccountId][OtherAccountPlayerId][GetAccountPlayerNextHeadHS(OtherAccountId, OtherAccountPlayerId)] = AccountId;
                ACCOUNT_P_HEAD_HUNTER_PLAYER_ID[OtherAccountId][OtherAccountPlayerId][GetAccountPlayerNextHeadHS(OtherAccountId, OtherAccountPlayerId)] = AccountPlayerId;
	   			ACCOUNT_P_HEAD_MONEY[OtherAccountId][OtherAccountPlayerId] += Money;
   	        	SetPlayerWantedLevel(OtherPlayerId, (GetPlayerWantedLevel(OtherPlayerId) + 1));
                new InfoMessage[MAX_STRING];
				format(InfoMessage, sizeof(InfoMessage), "%s hat auf %s %d$ Kopfgeld gesetzt. %s's Kopfgeld beträgt %d$, die Fahndungsstufe beträgt %d.", PLAYER_NAME[PlayerId], PLAYER_NAME[OtherPlayerId], Money, PLAYER_NAME[OtherPlayerId], ACCOUNT_P_HEAD_MONEY[OtherAccountId][OtherAccountPlayerId], GetPlayerWantedLevel(OtherPlayerId));
				SendClientMessageToAllPlayers(MESSAGE_TYPE_INFO, InfoMessage);
   	    	}
   	    	else
   	    	{
   	    	    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Dieser Spieler hat bereits eine Fahndungsstufe von 6.");
   	    	}
		}
		else
		{
		    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie können auf jeden Spieler nur einmal Kopfgeld setzen.");
		}
   	}
   	return true;
}

public ChatCommandPlayerGivesPM(PlayerId, OtherPlayerId, Money) //ChatCommandPlayerGivesPlayerMoney
{
	//General Conditions
    if (PlayerChatCommandConditions(PlayerId, OtherPlayerId, Money))
   	{
	    GivePlayerMoney(PlayerId, -Money);
	    GivePlayerMoney(OtherPlayerId, Money);
	    new InfoMessage[MAX_STRING];
	    format(InfoMessage, sizeof(InfoMessage), "%s gibt Ihnen %d$.", PLAYER_NAME[PlayerId], Money);
		SendClientMessageToPlayer(OtherPlayerId, MESSAGE_TYPE_INFO, InfoMessage);
	}
	return true;
}

public ChatCommandPlayerSetsGangName(PlayerId, GangName[MAX_GANG_NAME])
{
	//General Conditions
    if (PlayerChatCommandConditions(PlayerId, -1, -1))
   	{
   	    new AccountId = PLAYER_ACCOUNT[PlayerId];
   	    new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
   	    //Account Player Has Gang
	    if (ACCOUNT_P_GANG[AccountId][AccountPlayerId] != -1)
	    {
	        //Account Player Is The Boss
	        if (ACCOUNT_P_GANG_RANK[AccountId][AccountPlayerId] == GANG_RANK_BOSS)
	        {
	            new GangId = ACCOUNT_P_GANG[AccountId][AccountPlayerId];
	            //Gang Name Is Not The Old
	            if (strcmp(GANG_NAME[GangId], GangName, true) != 0)
	            {
	                //Gang Name Is Not Used
	            	if (!GangNameIsUsed(GangName))
					{
						//Gang Name Has The Right Length
	            		if (strlen(GangName) <= MAX_GANG_NAME && strlen(GangName) > 0)
	            		{
            				new OldName[MAX_GANG_NAME];
            				OldName = GANG_NAME[GangId];
            				GANG_NAME[GangId] = GangName;
                            new InfoMessage[MAX_STRING];
							format(InfoMessage, sizeof(InfoMessage), "Die Gang '%s' heißt nun '%s'.", OldName, GangName);
							SendClientMessageToAllPlayers(MESSAGE_TYPE_INFO, InfoMessage);
						}
						//Gang Name Has Not The Right Length
						else
						{
				    		new ErrorMessage[MAX_STRING];
				    		format(ErrorMessage, sizeof(ErrorMessage), "(Maximal %d Zeichen)", MAX_GANG_NAME);
    						SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Der Gang-Name ist zu kurz oder zu lang.");
   							SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, ErrorMessage);
						}
					}
					//Gang Name Is Used
					else
					{
					    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Dieser Gang-Name wird bereits verwendet.");
					}
				}
				//Gang Name Is The Old
				else
				{
				    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Dieser Gang-Name entspricht Ihrem derzeitigen Gang-Namen.");
				}
			}
			//Account Player Is No Boss
	        else
	        {
	            SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie müssen den Rang 'Boss' haben, um den Namen Ihrer Gang ändern zu können.");
	        }
		}
		//Account Player Has No Gang
		else
		{
		    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie befinden sich in keiner Gang.");
		}
	}
	return true;
}

public ChatCommandInvitePlayerInGang(PlayerId, OtherPlayerId)
{
	//General Conditions
    if (PlayerChatCommandConditions(PlayerId, OtherPlayerId, -1))
   	{
   	    new AccountId = PLAYER_ACCOUNT[PlayerId];
   	    new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
   	    new GangId = ACCOUNT_P_GANG[AccountId][AccountPlayerId];
   	    //Account Player Has Gang
	    if (ACCOUNT_P_GANG[AccountId][AccountPlayerId] != -1)
	    {
	        //Account Player Is The Boss
	        if (ACCOUNT_P_GANG_RANK[AccountId][AccountPlayerId] == GANG_RANK_BOSS)
	        {
	            new OtherAccountId = PLAYER_ACCOUNT[OtherPlayerId];
   	    		new OtherAccountPlayerId = PLAYER_ACCOUNT_PLAYER[OtherPlayerId];
	            //Other Account Player Has No Gang
	            if (ACCOUNT_P_GANG[OtherAccountId][OtherAccountPlayerId] == -1)
	            {
					CreateCustomMenuForPlayer(OtherPlayerId, MENU_TYPE_GANG_INVITATION, GangId, "Gang-Einladung");
	            	AddCustomMenuItemForPlayer(OtherPlayerId, MENU_TYPE_GANG_INVITATION, "Annehmen");
					ShowCustomMenuForPlayer(OtherPlayerId, MENU_TYPE_GANG_INVITATION);
                    new InfoMessage[MAX_STRING];
					format(InfoMessage, sizeof(InfoMessage), "Sie erhalten eine Einladung der Gang '%s'. Wenn Sie die Einladung annehmen, sind Sie ein Mitglied der Gang.", GANG_NAME[GangId]);
					SendMessageToPlayer(OtherPlayerId, MESSAGE_TYPE_INFO, "~g~Gang-Einladung~n~~w~");
				}
				//Other Account Player Has A Gang
				else
				{
				    new ErrorMessage[MAX_STRING];
		    		format(ErrorMessage, sizeof(ErrorMessage), "%s befindet sich bereits in einer Gang.", PLAYER_NAME[OtherPlayerId]);
				    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, ErrorMessage);
				}
			}
			//Account Player Is No Boss
	        else
	        {
	            SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie müssen den Rang 'Boss' haben, um den einen Spieler in Ihre Gang einladen zu können.");
	        }
		}
		//Account Player Has No Gang
		else
		{
		    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie befinden sich in keiner Gang.");
		}
	}
	return true;
}

public CommandExit(PlayerId)
{
	//General Conditions
    if (PlayerChatCommandConditions(PlayerId, -1, -1))
   	{
   	    //Player Is In Death Match
	    if (PLAYER_DEATH_MATCH[PlayerId] != -1)
	    {
	        //Player Is Not In Death Match Selection
	        if (!PLAYER_IS_IN_DM_SELECTION[PlayerId])
	        {
         		 CreateDeathMatchMenu(PlayerId, PLAYER_DEATH_MATCH[PlayerId]);
			}
			//Player Is In Death Match Selection
	        else
	        {
	            SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie befinden sich noch in der Skin-Auswahl.");
	        }
		}
		//Player Is Not In Death Match
		else
		{
		    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie befinden sich in keinem Death-Match.");
		}
	}
	return true;
}

public CommandPlayPlayerEmoticon(PlayerId, Emoticon[])
{
	//General Conditions
	if (PlayerChatCommandConditions(PlayerId, -1, -1))
	{
	    if (!PLAYER_PLAYS_EMOTICON[PlayerId])
	    {
    		for (new I0 = 0; I0 < EMOTICONS; I0++)
    		{
    			if (strcmp(Emoticon, EMOTICON_COMMAND[I0], true) == 0)
    			{
    		    	PlayerMakesEmoticon(PlayerId, I0);
					return true;
    			}
			}
		}
	}
	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Unbekannter Befehl.");
	return false;
}

public CommandTurnPlayerToAdmin(PlayerId)
{
	//General Conditions
	if (PlayerChatCommandConditions(PlayerId, -1, -1))
	{
	    //Player Is Admin
    	if (IsPlayerAdmin(PlayerId))
		{
		    SetPlayerSkin(PlayerId, 0);
		    SetPlayerHealth(PlayerId, 100.0000);
            SetPlayerArmour(PlayerId, 100.0000);
            GivePlayerMoney(PlayerId, 99999999);
			ResetPlayerWeapons(PlayerId);
		    GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WEAPON_TYPE_BRASSNUCKLE], 9999999);
            GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WEAPON_TYPE_KNIFE], 9999999);
            GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WEAPON_TYPE_DESERT_EAGLE], 9999999);
            GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WEAPON_TYPE_SPASS12], 9999999);
            GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WEAPON_TYPE_MP5], 9999999);
            GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WEAPON_TYPE_M4], 9999999);
            GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WEAPON_TYPE_SNIPER], 9999999);
            GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WEAPON_TYPE_RPG], 9999999);
            GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WEAPON_TYPE_MINIGUN], 9999999);
            GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[WEAPON_TYPE_SATCHEL_CARGES], 9999999);
            SetPlayerSpecialAction(PlayerId, SPECIAL_ACTION_USEJETPACK);
		}
		//Player Is Not Admin
		else
		{
		    SendClientMessageToAllPlayers(MESSAGE_TYPE_ERROR, "Sie sind kein Administrator.");
		}
	}
	return true;
}

public SavePlayerChatLogData(PlayerId, Data[])
{
    new FileName[MAX_STRING];
    new Line[MAX_STRING];
    new Year, Month, Day;
    new Hour, Minute, Second;
    getdate(Year, Month, Day);
    gettime(Hour, Minute, Second);
	format(FileName, MAX_STRING, "ChatLog[%d.%d.%d].txt", Day, Month, Year);
	format(Line, MAX_STRING, "%s[%d:%d:%d]: %s\n", PLAYER_NAME[PlayerId], Hour, Minute, Second, Data);
	new File:LogFile;
	LogFile = fopen(FileName, io_read | io_append);
	
	if (LogFile)
	{
	    fwrite(LogFile, Line);
	    fclose(LogFile);
	}

    return true;
}
