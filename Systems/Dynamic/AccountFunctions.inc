//*******************************************************************
//Account Functions
//Dynamisch
//*******************************************************************
#if defined AccountFunctions_included
  	#endinput
#endif
#define AccountFunctions_included
#pragma library AccountFunctions

//-- Functions --
AccountExists(Name[])
{
	for (new I0 = 0; I0 < ACCOUNTS; I0++)
	{
	    if (strlen(ACCOUNT_NAME[I0]) > 0 && strcmp(Name, ACCOUNT_NAME[I0], true) == 0)
	    {
			return I0;
	    }
	}
	return -1;
}

AccountPlayerExists(AccountId, Name[MAX_ACCOUNT_PLAYER_NAME])
{
	for (new I0 = 0; I0 < ACCOUNT_PLAYERS[AccountId]; I0++)
	{
	    if (strlen(ACCOUNT_P_NAME[AccountId][I0]) > 0 && strcmp(Name, ACCOUNT_P_NAME[AccountId][I0], true) == 0)
	    {
			return I0;
	    }
	}
	return -1;
}

AccountPlayerIsHeadHunterOfAP(AccountId, AccountPlayerId, OtherAccountId, OtherAccountPlayerId) //Account Player Is Head Hunter Of Account Player
{
    for (new I0 = 0; I0 < 6; I0++)
    {
        if (ACCOUNT_P_HEAD_HUNTER_ID[OtherAccountId][OtherAccountPlayerId][I0] == AccountId && ACCOUNT_P_HEAD_HUNTER_PLAYER_ID[OtherAccountId][OtherAccountPlayerId][I0] == AccountPlayerId)
		{
		    return true;
		}
	}
	return false;
}

GetAccountPlayerHeadHunters(AccountId, AccountPlayerId)
{
	new HeadHunters = 0;
	for (new I0 = 0; I0 < 6; I0++)
    {
        if (ACCOUNT_P_HEAD_HUNTER_ID[AccountId][AccountPlayerId][I0] != -1)
		{
		    HeadHunters++;
		}
	}
	return HeadHunters;
}

GetAccountPlayerNextHeadHS(AccountId, AccountPlayerId) //Get Account Player Next Head Hunter Slot
{
	for (new I0 = 0; I0 < 6; I0++)
    {
        if (ACCOUNT_P_HEAD_HUNTER_ID[AccountId][AccountPlayerId][I0] == -1)
		{
		    return I0;
		}
	}
	return -1;
}

ClearAccountPlayerHeadHunters(AccountId, AccountPlayerId)
{
    for (new I0 = 0; I0 < 6; I0++)
    {
        ACCOUNT_P_HEAD_HUNTER_ID[AccountId][AccountPlayerId][I0] = -1;
        ACCOUNT_P_HEAD_HUNTER_PLAYER_ID[AccountId][AccountPlayerId][I0] = -1;
	}
	ACCOUNT_P_HEAD_MONEY[AccountId][AccountPlayerId] = 0;
	new PlayerId = ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId];
	SetPlayerWantedLevel(PlayerId, 0);
	return true;
}

public GiveAccountPlayerHeadMoney(AccountId, AccountPlayerId, TargetAccountId, TargetAccountPlayerId)
{
	if (ACCOUNT_P_HEAD_MONEY[TargetAccountId][TargetAccountPlayerId] > 0)
	{
	    new PlayerId = ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId];
        new TargetPlayerId = ACCOUNT_P_PLAYER_ID[TargetAccountId][TargetAccountPlayerId];
		GivePlayerMoney(PlayerId, ACCOUNT_P_HEAD_MONEY[TargetAccountId][TargetAccountPlayerId]);
    	new InfoMessage[MAX_STRING];
    	format(InfoMessage, sizeof(InfoMessage), "%s hat für %s %d$ Kopfgeld kassiert. Damit fällt seine Fahndungsstufe wieder auf 0.", PLAYER_NAME[PlayerId], PLAYER_NAME[TargetPlayerId], ACCOUNT_P_HEAD_MONEY[TargetAccountId][TargetAccountPlayerId]);
		SendClientMessageToPlayer(TargetPlayerId, MESSAGE_TYPE_INFO, InfoMessage);
		//Clear Data After Message
		ClearAccountPlayerHeadHunters(TargetAccountId, TargetAccountPlayerId);
	}
	return true;
}

public GiveAccountPlayerExperience(AccountId, AccountPlayerId, Experience)
{
	new PlayerId = ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId];
	//Player Level Is Not 20
	if (ACCOUNT_P_LEVEL[AccountId][AccountPlayerId] > 20)
	{
		new NewExperience = (ACCOUNT_P_EXPERIENCE[AccountId][AccountPlayerId] + Experience);
		new InfoMessage[MAX_STRING];
		format(InfoMessage, sizeof(InfoMessage), "Sie erhalten +%d Erfahrung.", Experience);
		SendMessageToPlayer(PlayerId, MESSAGE_TYPE_EXPERIENCE, InfoMessage);
		for (new I0 = 0; I0 < 200; I0++)
		{
			//No Level Up
			if (NewExperience < ACCOUNT_P_NEXT_LEVEL_EXPERIENCE[AccountId][AccountPlayerId])
			{
	    		ACCOUNT_P_EXPERIENCE[AccountId][AccountPlayerId] += Experience;
				break;
			}
			//Experience Is Higher Than Experience You Need For Level 20
			else if (ACCOUNT_P_LEVEL[AccountId][AccountPlayerId] == 19 && NewExperience > ACCOUNT_P_NEXT_LEVEL_EXPERIENCE[AccountId][AccountPlayerId])
			{
	    		ACCOUNT_P_LEVEL[AccountId][AccountPlayerId] = 20;
	    		ACCOUNT_P_EXPERIENCE[AccountId][AccountPlayerId] = 2000;
				SendMessageToPlayer(PlayerId, MESSAGE_TYPE_EXPERIENCE, "Sie sind auf Stufe 20 aufgestiegen.");
				break;
			}
			//General Level Up
			else
			{
		    	ACCOUNT_P_LEVEL[AccountId][AccountPlayerId]++;
		    	ACCOUNT_P_EXPERIENCE[AccountId][AccountPlayerId] = (NewExperience - ACCOUNT_P_NEXT_LEVEL_EXPERIENCE[AccountId][AccountPlayerId]);
				NewExperience = (NewExperience - ACCOUNT_P_NEXT_LEVEL_EXPERIENCE[AccountId][AccountPlayerId]);
		    	ACCOUNT_P_NEXT_LEVEL_EXPERIENCE[AccountId][AccountPlayerId] = (ACCOUNT_P_LEVEL[AccountId][AccountPlayerId] * 100);
		    	format(InfoMessage, sizeof(InfoMessage), "Sie sind auf Stufe %d aufgestiegen.", ACCOUNT_P_LEVEL[AccountId][AccountPlayerId]);
				SendMessageToPlayer(PlayerId, MESSAGE_TYPE_EXPERIENCE, InfoMessage);
			}
		}
	}
	return true;
}

GetAccountPlayerKillType(AccountId, AccountPlayerId, KillerAccountId, KillerAccountPlayerId)
{
    new PlayerId = ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId];
    new KillerId = ACCOUNT_P_PLAYER_ID[KillerAccountId][KillerAccountPlayerId];
	//Player Kills Another Player Of His Profession
	if (ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId] == ACCOUNT_P_PROFESSION[KillerAccountId][KillerAccountPlayerId] && ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId] != -1 && ACCOUNT_P_PROFESSION[KillerAccountId][KillerAccountPlayerId] != -1)
	{
	    if (PLAYER_USES_PROFESSION[PlayerId] && PLAYER_USES_PROFESSION[KillerId])
	    {
	    	return KILL_TYPE_PROFESSION;
		}
	}
	//Player Kills A Gang Member Of His Gang
	else if (ACCOUNT_P_GANG[AccountId][AccountPlayerId] == ACCOUNT_P_GANG[KillerAccountId][KillerAccountPlayerId] && ACCOUNT_P_GANG[AccountId][AccountPlayerId] != -1 && ACCOUNT_P_GANG[KillerAccountId][KillerAccountPlayerId] != -1)
	{
	    return KILL_TYPE_GANG;
	}
	//Player Kills A Profession Target
	else if (AccountPlayerIsTargetOfAP(KillerAccountId, KillerAccountPlayerId, AccountId, AccountPlayerId))
	{
	    return KILL_TYPE_PROFESSION_TARGET;
	}
	//Player Kills A General Enemy
	return KILL_TYPE_ENEMY;
}

public AccountRegister(PlayerId, Name[MAX_STRING], Password[MAX_STRING], Email[MAX_STRING], Country[MAX_STRING])
{
 	//Player Is Not Logged In
	if (PLAYER_ACCOUNT[PlayerId] == -1)
	{
  		//Name Has The Right Length
		if (strlen(Name) <= MAX_ACCOUNT_NAME && strlen(Name) > 0)
		{
	    	//Password Has The Right Length
	    	if (strlen(Password) <= MAX_ACCOUNT_PASSWORD && strlen(Password) > 0)
			{
		    	//Email Has The Right Length
		    	if (strlen(Email) <= MAX_ACCOUNT_EMAIL && strlen(Email) > 0)
				{
			    	//Email Contains @
			    	if (strfind(Email, "@", true) != -1)
			    	{
			    	    //Country Has The Right Length
		    			if (strlen(Country) <= MAX_ACCOUNT_COUNTRY && strlen(Country) > 0)
						{
			        		//Account Does Not Exist
							if (AccountExists(Name) == -1)
							{
							    new NewName[MAX_ACCOUNT_NAME];
								strcat(NewName, Name, sizeof(NewName));
								//format(NewName, sizeof(NewName), "%s", Name);
							    new NewPassword[MAX_ACCOUNT_PASSWORD];
							    strcat(NewPassword, Password, sizeof(NewPassword));
							    //format(NewPassword, sizeof(NewPassword), "%s", Name);
							    new NewEmail[MAX_ACCOUNT_EMAIL];
							    strcat(NewEmail, Email, sizeof(NewEmail));
							    //format(NewEmail, sizeof(NewEmail), "%s", Name);
							    new NewCountry[MAX_ACCOUNT_COUNTRY];
							    strcat(NewCountry, Country, sizeof(NewCountry));
							    //format(NewCountry, sizeof(NewCountry), "%s", Name);
					    		new AccountId = AddAccount(PlayerId, NewName, NewPassword, NewEmail, NewCountry, "Empty");
								//Server Has Not Enough Accounts
								if (AccountId != -1)
					    		{
									new AccountPlayerName[MAX_ACCOUNT_PLAYER_NAME];
					    		    format(AccountPlayerName, sizeof(AccountPlayerName), "%s", PLAYER_NAME[PlayerId]); //Wegen der maximalen Stringgröße
				    		 		new AccountPlayerId = AddAccountPlayer(AccountId, PlayerId, AccountPlayerName);
									PLAYER_ACCOUNT[PlayerId] = AccountId;
									PLAYER_ACCOUNT_PLAYER[PlayerId] = AccountPlayerId;
									ShowSkinInfoForPlayer(PlayerId, 0);
					    			SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, "Benutzerkonto wurde erfolgreich erstellt.");
					    			SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, "Sie wurden automatisch angemeldet.");
					    			SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, "Wählen Sie nun Ihr Aussehen und Ihre Startstadt.");
									return true;
								}
								//Server Has Enough Accounts
								else
								{
								    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Die maximale Anzahl erstellbarer Benutzer wurde bereits erreicht.");
								}
							}
							//Account Exists
							else
							{
 								SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Benutzer existiert bereits.");
							}
						}
						//Country Has Not The Right Length
		    			else
						{
						    new ErrorMessage[MAX_STRING];
		    				format(ErrorMessage, sizeof(ErrorMessage), "(Maximal %d Zeichen)", MAX_ACCOUNT_COUNTRY);
		    				SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Das Landeskürzel ist zu kurz oder zu lang.");
		   					SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, ErrorMessage);
						}
					}
					//Email Does Not Contain @
					else
					{
		    			SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "E-Mail-Addresse ungültig - Enthält kein '@'.");
					}
            	}
            	//Email Has Not The Right Length
				else
				{
				    new ErrorMessage[MAX_STRING];
					format(ErrorMessage, sizeof(ErrorMessage), "(Maximal %d Zeichen)", MAX_ACCOUNT_EMAIL);
		    		SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "E-Mail-Addresse ist zu kurz oder zu lang.");
		   			SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, ErrorMessage);
				}
			}
        	//Password Has Not The Right Length
			else
			{
			    new ErrorMessage[MAX_STRING];
				format(ErrorMessage, sizeof(ErrorMessage), "(Maximal %d Zeichen)", MAX_ACCOUNT_PASSWORD);
		    	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Passwort ist zu kurz oder zu lang.");
		    	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, ErrorMessage);
			}
		}
		//Name Has Not The Right Length
		else
		{
		    new ErrorMessage[MAX_STRING];
	    	format(ErrorMessage, sizeof(ErrorMessage), "(Maximal %d Zeichen)", MAX_ACCOUNT_NAME);
	    	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Benutzername ist zu kurz oder zu lang.");
	    	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, ErrorMessage);
		}
	}
    //Player Is Logged In
	else
	{
	    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie sind bereits angemeldet.");
	}
	return false;
}

public AccountLogin(PlayerId, AccountName[], Password[], AccountPlayerName[])
{
	//Player Is Not Logged In
	if (PLAYER_ACCOUNT[PlayerId] == -1)
	{
	    new AccountId = AccountExists(AccountName);
		//Account Exists
		if (AccountId != -1)
		{
	    	//Password Is Right
	    	if (strcmp(Password, ACCOUNT_PASSWORD[AccountId], true) == 0)
	    	{
	    	    new NewAccountPlayerName[MAX_ACCOUNT_PLAYER_NAME]; //Wegen der korrekten Größe
	    	    format(NewAccountPlayerName, sizeof(NewAccountPlayerName), "%s", AccountPlayerName);
	    	    new AccountPlayerId = AccountPlayerExists(AccountId, NewAccountPlayerName);
	    	    //Account Player Exists
	    	    if (AccountPlayerId != -1)
	    	    {
	    	        PLAYER_ACCOUNT[PlayerId] = AccountId;
					PLAYER_ACCOUNT_PLAYER[PlayerId] = AccountPlayerId;
	    	        SpawnPlayer(PlayerId);
	    	        SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, "Sie haben sich erfolgreich angemeldet.");
	        		SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, "Ihre Spielerdaten wurden geladen.");
	        		return true;
				}
				//Account Player Does Not Exist
				else
				{
				    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Spieler existiert nicht.");
				}
			}
	    	//Password Is Wrong
	    	else
	    	{
	        	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Falsches Passwort.");
	    	}
		}
		//Account Does Not Exist
		else
		{
	    	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Benutzer existiert nicht.");
		}
	}
	//Player Is Logged In
	else
	{
	    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie sind bereits angemeldet.");
	}
	return false;
}

public AccountRegisterPlayer(PlayerId, AccountId, AccountPlayerName[])
{
	//Name Has The Right Length
	if (strlen(AccountPlayerName) <= MAX_ACCOUNT_PLAYER_NAME && strlen(AccountPlayerName) > 0)
	{
	    new NewAccountPlayerName[MAX_ACCOUNT_PLAYER_NAME]; //Wegen der korrekten Größe
	    format(NewAccountPlayerName, sizeof(NewAccountPlayerName), "%s", AccountPlayerName);
	    //Account Player Does Not Exist
	    if (AccountPlayerExists(AccountId, NewAccountPlayerName) == -1)
	    {
    		new AccountPlayerId = AddAccountPlayer(AccountId, PlayerId, NewAccountPlayerName);
    		//Account Has Not Enough Players
    		if (AccountPlayerId != -1)
    		{
    		    new InfoMessage[MAX_STRING];
    		    format(InfoMessage, sizeof(InfoMessage), "Sie haben Ihrem Benutzer den Spieler '%s' hinzugefügt.", AccountPlayerName);
      			SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, InfoMessage);
      			return true;
			}
	    	//Account Has Enough Players
	    	else
	    	{
	        	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Die maximale Anzahl erstellbarer Spieler wurde bereits erreicht..");
	    	}
		}
		//Account Player Exists
		else
		{
	    	SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Spielername wird bereits verwendet.");
		}
	}
	//Name Has Not The Right Length
	else
	{
	    new ErrorMessage[MAX_STRING];
        format(ErrorMessage, sizeof(ErrorMessage), "(Maximal %d Zeichen)", MAX_ACCOUNT_PLAYER_NAME);
		SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Spielername ist zu kurz oder zu lang.");
 		SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, ErrorMessage);
	}
	return false;
}

GetNextFreeAccountId()
{
    if (ACCOUNTS < MAX_ACCOUNTS)
	{
	    return ACCOUNTS;
	}
	else
	{
	    for (new I0 = 0; I0 < MAX_ACCOUNTS; I0++)
	    {
	        if (!ACCOUNT[I0]) //Da Wert nicht unbedingt auf false gesetzt worden ist
	        {
	            return I0;
	        }
	    }
	}
	return -1;
}

//Setzt alle Account-Werte zurück.
//ACHTUNG: Spieler-Daten auch überprüfen und ändern.
ClearAccount(AccountId, Copy, FirstClear = false)
{
	if (!FirstClear)
	{
	    if (!Copy) //Diese Daten dürfen nur gecleared werden, wenn sie davor nicht kopiert wurden
		{
	    	if (ACCOUNT_PLAYER_ID[AccountId] != -1)
			{
		    	PLAYER_ACCOUNT[ACCOUNT_PLAYER_ID[AccountId]] = -1;
			}
		}
	}
    ACCOUNT[AccountId] = false;
    ACCOUNT_PLAYER_ID[AccountId] = -1;
	ACCOUNT_NAME[AccountId] = "";
	ACCOUNT_PASSWORD[AccountId] = "";
	ACCOUNT_EMAIL[AccountId] = "";
	ACCOUNT_COUNTRY[AccountId] = "";
	ACCOUNT_DESCRIPTION[AccountId] = "";
	ACCOUNT_PLAYERS[AccountId] = 0;
	for (new I0 = 0; I0 < MAX_ACCOUNT_PLAYERS; I0++)
    {
        ClearAccountPlayer(AccountId, I0, Copy, FirstClear);
    }
    return true;
}

public AddAccount(PlayerId, Name[MAX_ACCOUNT_NAME], Password[MAX_ACCOUNT_PASSWORD], Email[MAX_ACCOUNT_EMAIL], Country[MAX_ACCOUNT_COUNTRY], Description[MAX_ACCOUNT_DESCRIPTION])
{
    new AccountId = GetNextFreeAccountId();
    if (AccountId != -1)
	{
	    ClearAccount(AccountId, false);
	    ACCOUNT[AccountId] = true;
	    ACCOUNT_PLAYER_ID[AccountId] = PlayerId;
   		ACCOUNT_NAME[AccountId] = Name;
		ACCOUNT_PASSWORD[AccountId] = Password;
		ACCOUNT_EMAIL[AccountId] = Email;
		ACCOUNT_COUNTRY[AccountId] = Country;
		ACCOUNT_DESCRIPTION[AccountId] = Description;
		PLAYER_ACCOUNT[PlayerId] = AccountId; //Spielerdaten
		ACCOUNTS++;
		return AccountId;
	}
	return -1;
}

//ACHTUNG: Spieler-Daten auch überprüfen und ändern.
public CopyAccount(AccountId, CopiedAccountId)
{
    if (ACCOUNT_PLAYER_ID[CopiedAccountId] != -1)
	{
	    PLAYER_ACCOUNT[ACCOUNT_PLAYER_ID[CopiedAccountId]] = AccountId;
	}
    ACCOUNT[AccountId] = ACCOUNT[CopiedAccountId];
    ACCOUNT_PLAYER_ID[AccountId] = ACCOUNT_PLAYER_ID[CopiedAccountId];
	ACCOUNT_NAME[AccountId] = ACCOUNT_NAME[CopiedAccountId];
	ACCOUNT_PASSWORD[AccountId] = ACCOUNT_PASSWORD[CopiedAccountId];
	ACCOUNT_EMAIL[AccountId] = ACCOUNT_EMAIL[CopiedAccountId];
	ACCOUNT_COUNTRY[AccountId] = ACCOUNT_COUNTRY[CopiedAccountId];
	ACCOUNT_DESCRIPTION[AccountId] = ACCOUNT_DESCRIPTION[CopiedAccountId];
	ACCOUNT_PLAYERS[AccountId] = ACCOUNT_PLAYERS[CopiedAccountId];
	for (new I0 = 0; I0 < MAX_ACCOUNT_PLAYERS; I0++)
 	{
  		CopyAccountPlayer(AccountId, I0, CopiedAccountId, I0);
    }
    return true;
}

//Verschiebt den letzten Account an die Position des entfernten Accounts und setzt den Wert der Account-Anzahl herunter.
public RemoveAccount(AccountId)
{
    ClearAccount(AccountId, false);
    if ((AccountId + 1) != ACCOUNTS)
	{
		CopyAccount(AccountId, (ACCOUNTS - 1));
		ClearAccount((ACCOUNTS - 1), true);
	}
	ACCOUNTS--;
	return true;
}

GetNextFreeAccountPlayerId(AccountId)
{
    if (ACCOUNT_PLAYERS[AccountId] < MAX_ACCOUNT_PLAYERS)
	{
	    return ACCOUNT_PLAYERS[AccountId];
	}
	else
	{
	    for (new I0 = 0; I0 < MAX_ACCOUNT_PLAYERS; I0++)
	    {
	        if (!ACCOUNT_PLAYER[AccountId][I0]) //Da Wert nicht unbedingt auf false gesetzt worden ist
	        {
	            return I0;
	        }
	    }
	}
	return -1;
}

//Setzt alle AccountPlayer-Werte zurück.
//ACHTUNG: Spieler-Daten auch überprüfen und ändern.
ClearAccountPlayer(AccountId, AccountPlayerId, Copy, FirstClear = false)
{
	if (!FirstClear)
	{
	    if (!Copy) //Diese Daten dürfen nur gecleared werden, wenn sie davor nicht kopiert wurden
		{
			//Player wird dadurch auch ausgeloggt
	    	if (ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId] != -1)
			{
		    	PLAYER_ACCOUNT_PLAYER[ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId]] = -1;
			}
			//AccountPlayer verlässt die Gang.
			if (ACCOUNT_P_GANG[AccountId][AccountPlayerId] != -1)
			{
		    	RemoveGangMember(ACCOUNT_P_GANG[AccountId][AccountPlayerId], ACCOUNT_P_GANG_MEMBER[AccountId][AccountPlayerId]);
			}
		}
	}
    ACCOUNT_PLAYER[AccountId][AccountPlayerId] = false;
    ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId] = -1;
	ACCOUNT_P_NAME[AccountId][AccountPlayerId] = "";
	ACCOUNT_P_TOWN[AccountId][AccountPlayerId] = -1;
	ACCOUNT_P_SKIN[AccountId][AccountPlayerId] = -1;
	ACCOUNT_P_HEAD_MONEY[AccountId][AccountPlayerId] = 0;
	new I0;
	for (I0 = 0; I0 < 6; I0++)
	{
 		ACCOUNT_P_HEAD_HUNTER_ID[AccountId][AccountPlayerId][I0] = -1;
 		ACCOUNT_P_HEAD_HUNTER_PLAYER_ID[AccountId][AccountPlayerId][I0] = -1;
	}
	ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId] = -1;
	for (I0 = 0; I0 < MAX_ACCOUNT_PLAYER_HOUSES; I0++)
	{
		ClearAccountPlayerHouse(AccountId, AccountPlayerId, I0, Copy, FirstClear);
	}
	ACCOUNT_P_GANG[AccountId][AccountPlayerId] = -1;
	ACCOUNT_P_GANG_MEMBER[AccountId][AccountPlayerId] = -1;
    ACCOUNT_P_GANG_RANK[AccountId][AccountPlayerId] = -1;
	//Rank Data
	ACCOUNT_P_LEVEL[AccountId][AccountPlayerId] = 0;
	ACCOUNT_P_EXPERIENCE[AccountId][AccountPlayerId] = 0;
	ACCOUNT_P_NEXT_LEVEL_EXPERIENCE[AccountId][AccountPlayerId] = 500;
    for (I0 = 0; I0 < MAX_VEHICLE_TYPE_TYPES; I0++)
	{
		ACCOUNT_P_VEHICLE_SKILL[AccountId][AccountPlayerId][I0] = 0;
	}
	for (I0 = 0; I0 < MAX_WEAPON_TYPE_TYPES; I0++)
	{
		ACCOUNT_P_WEAPON_SKILL[AccountId][AccountPlayerId][I0] = 0;
	}
	ACCOUNT_P_PVP_SKILL[AccountId][AccountPlayerId] = 0;
	ACCOUNT_P_PROFESSION_RPS[AccountId][AccountPlayerId] = 0;
	ACCOUNT_P_GANG_RANK_POINTS[AccountId][AccountPlayerId] = 0;
	//Settings
    ACCOUNT_P_SHOW_VEHICLE_DATA[AccountId][AccountPlayerId] = true;
    return true;
}

public AddAccountPlayer(AccountId, PlayerId, Name[MAX_ACCOUNT_PLAYER_NAME])
{
    new AccountPlayerId = GetNextFreeAccountPlayerId(AccountId);
    if (AccountPlayerId != -1)
    {
        ClearAccountPlayer(AccountId, AccountPlayerId, false);
        ACCOUNT_PLAYER[AccountId][AccountPlayerId] = true;
		ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId] = PlayerId;
		ACCOUNT_P_NAME[AccountId][AccountPlayerId] = Name;
		PLAYER_ACCOUNT_PLAYER[PlayerId] = AccountPlayerId; //Spielerdaten
		ACCOUNT_PLAYERS[AccountId]++;
    	return AccountPlayerId;
	}
	return -1;
}

public CopyAccountPlayer(AccountId, AccountPlayerId, CopiedAccountId, CopiedAccountPlayerId)
{
    //Spielerdaten ändern
    if (ACCOUNT_P_PLAYER_ID[CopiedAccountId][CopiedAccountPlayerId] != -1)
	{
	    PLAYER_ACCOUNT_PLAYER[ACCOUNT_P_PLAYER_ID[CopiedAccountId][CopiedAccountPlayerId]] = AccountPlayerId;
	}
	//Gang-Daten ändern
	if (ACCOUNT_P_GANG[AccountId][AccountPlayerId] != -1)
	{
		GANG_MEMBER_ACCOUNT_PLAYER[ACCOUNT_P_GANG[CopiedAccountId][CopiedAccountPlayerId]][ACCOUNT_P_GANG_MEMBER[CopiedAccountId][CopiedAccountPlayerId]] = AccountPlayerId;
	}
    ACCOUNT_PLAYER[AccountId][AccountPlayerId] = ACCOUNT_PLAYER[CopiedAccountId][CopiedAccountPlayerId];
    ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId] = ACCOUNT_P_PLAYER_ID[CopiedAccountId][CopiedAccountPlayerId];
	ACCOUNT_P_NAME[AccountId][AccountPlayerId] = ACCOUNT_P_NAME[CopiedAccountId][CopiedAccountPlayerId];
	ACCOUNT_P_TOWN[AccountId][AccountPlayerId] = ACCOUNT_P_TOWN[CopiedAccountId][CopiedAccountPlayerId];
	ACCOUNT_P_SKIN[AccountId][AccountPlayerId] = ACCOUNT_P_SKIN[CopiedAccountId][CopiedAccountPlayerId];
	ACCOUNT_P_HEAD_MONEY[AccountId][AccountPlayerId] = ACCOUNT_P_HEAD_MONEY[CopiedAccountId][CopiedAccountPlayerId];
	new I0;
	for (I0 = 0; I0 < 6; I0++)
	{
 		ACCOUNT_P_HEAD_HUNTER_ID[AccountId][AccountPlayerId][I0] = ACCOUNT_P_HEAD_HUNTER_ID[CopiedAccountId][CopiedAccountPlayerId][I0];
 		ACCOUNT_P_HEAD_HUNTER_PLAYER_ID[AccountId][AccountPlayerId][I0] = ACCOUNT_P_HEAD_HUNTER_PLAYER_ID[CopiedAccountId][CopiedAccountPlayerId][I0];
	}
	ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId] = ACCOUNT_P_PROFESSION[CopiedAccountId][CopiedAccountPlayerId];
    ACCOUNT_P_HOUSES[AccountId][AccountPlayerId] = ACCOUNT_P_HOUSES[CopiedAccountId][CopiedAccountPlayerId];
	for (I0 = 0; I0 < MAX_ACCOUNT_PLAYER_HOUSES; I0++)
	{
		 CopyAccountPlayerHouse(AccountId, AccountPlayerId, I0, CopiedAccountId, CopiedAccountPlayerId, I0);
	}
	ACCOUNT_P_GANG[AccountId][AccountPlayerId] = ACCOUNT_P_GANG[CopiedAccountId][CopiedAccountPlayerId];
    ACCOUNT_P_GANG_MEMBER[AccountId][AccountPlayerId] = ACCOUNT_P_GANG_MEMBER[CopiedAccountId][CopiedAccountPlayerId];
	ACCOUNT_P_GANG_RANK[AccountId][AccountPlayerId] = ACCOUNT_P_GANG_RANK[CopiedAccountId][CopiedAccountPlayerId];
	//Rank Data
	ACCOUNT_P_LEVEL[AccountId][AccountPlayerId] = ACCOUNT_P_LEVEL[CopiedAccountId][CopiedAccountPlayerId];
	ACCOUNT_P_EXPERIENCE[AccountId][AccountPlayerId] = ACCOUNT_P_EXPERIENCE[CopiedAccountId][CopiedAccountPlayerId];
	ACCOUNT_P_NEXT_LEVEL_EXPERIENCE[AccountId][AccountPlayerId] = ACCOUNT_P_NEXT_LEVEL_EXPERIENCE[CopiedAccountId][CopiedAccountPlayerId];
    for (I0 = 0; I0 < MAX_VEHICLE_TYPE_TYPES; I0++)
	{
		ACCOUNT_P_VEHICLE_SKILL[AccountId][AccountPlayerId][I0] = ACCOUNT_P_VEHICLE_SKILL[CopiedAccountId][CopiedAccountPlayerId][I0];
	}
	for (I0 = 0; I0 < MAX_WEAPON_TYPE_TYPES; I0++)
	{
		ACCOUNT_P_WEAPON_SKILL[AccountId][AccountPlayerId][I0] = ACCOUNT_P_WEAPON_SKILL[CopiedAccountId][CopiedAccountPlayerId][I0];
	}
	ACCOUNT_P_PVP_SKILL[AccountId][AccountPlayerId] = ACCOUNT_P_PVP_SKILL[CopiedAccountId][CopiedAccountPlayerId];
	ACCOUNT_P_PROFESSION_RPS[AccountId][AccountPlayerId] = ACCOUNT_P_PROFESSION_RPS[CopiedAccountId][CopiedAccountPlayerId];
	ACCOUNT_P_GANG_RANK_POINTS[AccountId][AccountPlayerId] = ACCOUNT_P_GANG_RANK_POINTS[CopiedAccountId][CopiedAccountPlayerId];
	//Settings
    ACCOUNT_P_SHOW_VEHICLE_DATA[AccountId][AccountPlayerId] = ACCOUNT_P_SHOW_VEHICLE_DATA[CopiedAccountId][CopiedAccountPlayerId];
	return true;
}

//Verschiebt den letzten AccountPlayer an die Position des entfernten AccountPlayers und setzt den Wert der AccountPlayer-Anzahl herunter.
public RemoveAccountPlayer(AccountId, AccountPlayerId)
{
    ClearAccountPlayer(AccountId, AccountPlayerId, false);
	if ((AccountPlayerId + 1) != ACCOUNT_PLAYERS[AccountId])
	{
	    CopyAccountPlayer(AccountId, AccountPlayerId, AccountId, (ACCOUNT_PLAYERS[AccountId] - 1));
	    ClearAccountPlayer(AccountId, (ACCOUNT_PLAYERS[AccountId] - 1), true);
	}
	ACCOUNT_PLAYERS[AccountId]--;
	//Account wird aufgelöst.
	if (ACCOUNT_PLAYERS[AccountId] == 0)
	{
	    RemoveAccount(AccountId);
	}
	return true;
}

GetNextFreeAccountPlayerHouseId(AccountId, AccountPlayerId)
{
    if (ACCOUNT_P_HOUSES[AccountId][AccountPlayerId] < MAX_ACCOUNT_PLAYER_HOUSES)
	{
	    return ACCOUNT_P_HOUSES[AccountId][AccountPlayerId];
	}
	else
	{
	    for (new I0 = 0; I0 < MAX_ACCOUNT_PLAYER_HOUSES; I0++)
	    {
	        if (ACCOUNT_P_HOUSE[AccountId][AccountPlayerId][I0] != -1)
	        {
	            return I0;
	        }
	    }
	}
	return -1;
}

//Setzt alle AccountPlayerHouse-Werte zurück.
//ACHTUNG: Spieler-Daten auch überprüfen und ändern.
ClearAccountPlayerHouse(AccountId, AccountPlayerId, AccountPlayerHouseId, Copy, FirstClear = false) //Kein FirstClear benötigt, da keine Daten verändert werden, auch kein Copy benötigt, halte es nur bereit
{
	if (!FirstClear)
	{
	    if (!Copy)
	    {
	        new HouseId = ACCOUNT_P_HOUSE[AccountId][AccountPlayerId][AccountPlayerHouseId];
	        if (HouseId != -1)
	        {
    			HOUSE_OWNER_ACCOUNT[HouseId] = -1;
    			HOUSE_OWNER_ACCOUNT_PLAYER[HouseId] = -1;
			}
		}
	}
	ACCOUNT_P_HOUSE[AccountId][AccountPlayerId][AccountPlayerHouseId] = -1; //Kein Boolean sondern die Id
    return true;
}

public AddAccountPlayerHouse(AccountId, AccountPlayerId, HouseId)
{
    new AccountPlayerHouseId = GetNextFreeAccountPlayerHouseId(AccountId, AccountPlayerId);
    if (AccountPlayerHouseId != -1)
    {
        ClearAccountPlayerHouse(AccountId, AccountPlayerId, AccountPlayerHouseId, false);
        ACCOUNT_P_HOUSE[AccountId][AccountPlayerId][AccountPlayerHouseId] = HouseId;
		ACCOUNT_P_HOUSES[AccountId][AccountPlayerId]++;
    	return AccountPlayerHouseId;
	}
	return -1;
}

public CopyAccountPlayerHouse(AccountId, AccountPlayerId, AccountPlayerHouseId, CopiedAccountId, CopiedAccountPlayerId, CopiedAccountPlayerHouseId)
{
    ACCOUNT_P_HOUSE[AccountId][AccountPlayerId][AccountPlayerHouseId] = ACCOUNT_P_HOUSE[CopiedAccountId][CopiedAccountPlayerId][CopiedAccountPlayerHouseId];
	return true;
}

public RemoveAccountPlayerHouse(AccountId, AccountPlayerId, AccountPlayerHouseId)
{
    ClearAccountPlayerHouse(AccountId, AccountPlayerId, AccountPlayerHouseId, false);
	if ((AccountPlayerHouseId + 1) != ACCOUNT_P_HOUSES[AccountId][AccountPlayerId])
	{
	    CopyAccountPlayerHouse(AccountId, AccountPlayerId, AccountPlayerHouseId, AccountId, AccountPlayerId, (ACCOUNT_P_HOUSES[AccountId][AccountPlayerId] - 1));
	    ClearAccountPlayerHouse(AccountId, AccountPlayerId, (ACCOUNT_P_HOUSES[AccountId][AccountPlayerId] - 1), true);
	}
	ACCOUNT_P_HOUSES[AccountId][AccountPlayerId]--;
	return true;
}

public ClearAllAccounts() //Muss am Anfang des Modes ausgeführt werden und cleared alle Accounts das erste Mal - Damit werden auch alle Unterklassen des Accounts gecleared
{
	for (new I0 = 0; I0 < MAX_ACCOUNTS; I0++)
	{
		ClearAccount(I0, false, true);
	}
	return true;
}
