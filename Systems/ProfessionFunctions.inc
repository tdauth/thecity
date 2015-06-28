//*******************************************************************
//Profession Functions
//*******************************************************************
#if defined ProfessionFunctions_included
  	#endinput
#endif
#define ProfessionFunctions_included
#pragma library ProfessionFunctions

//-- Functions --
AccountPlayerIsTargetOfAP(AccountId, AccountPlayerId, TargetAccountId, TargetAccountPlayerId)
{
    new AccountPlayerProfessionId = ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId];
	new TargetAccountPlayerProfessionId = ACCOUNT_P_PROFESSION[TargetAccountId][TargetAccountPlayerId];
	new PlayerId = ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId];
	new TargetPlayerId = ACCOUNT_P_PLAYER_ID[TargetAccountId][TargetAccountPlayerId];
	if (AccountPlayerProfessionId != -1 && TargetAccountPlayerProfessionId != -1)
	{
		if (PLAYER_USES_PROFESSION[PlayerId] && PLAYER_USES_PROFESSION[TargetPlayerId])
		{
			for (new I0 = 0; I0 < PROFESSION_TARGETS[AccountPlayerProfessionId]; I0++)
			{
				if (PROFESSION_TARGET_PROFESSION[AccountPlayerProfessionId][I0] == TargetAccountPlayerProfessionId)
				{
  					return I0;
				}
			}
		}
	}
	return -1;
}

PlayerIsTargetPlayer(PlayerId, TargetPlayerId)
{
    return AccountPlayerIsTargetOfAP(PLAYER_ACCOUNT[PlayerId], PLAYER_ACCOUNT_PLAYER[PlayerId], PLAYER_ACCOUNT[TargetPlayerId], PLAYER_ACCOUNT_PLAYER[TargetPlayerId]);
}

public CreateProfessionSelectionMenu(PlayerId)
{
    CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_PROFESSION_SELECTION, 0, "Tätigkeiten");
    SetCustomMenuHeader(PlayerId, MENU_TYPE_PROFESSION_SELECTION, "Tätigkeit - Preis");
    new MenuItemText[MAX_STRING];
	for (new I0 = 0; I0 < PROFESSIONS; I0++)
	{
	    format(MenuItemText, sizeof(MenuItemText), "%s - %d$", PROFESSION_NAME[I0], PROFESSION_PRICE[I0]);
    	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_PROFESSION_SELECTION, MenuItemText);
	}
	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_PROFESSION_SELECTION);
	return true;
}

public PlayerSelectsProfession(PlayerId, ProfessionId)
{
	if (GetPlayerMoney(PlayerId) >= PROFESSION_PRICE[ProfessionId])
	{
	    new AccountId = PLAYER_ACCOUNT[PlayerId];
	    new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
		ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId] = ProfessionId;
		new InfoMessage[MAX_STRING];
		format(InfoMessage, sizeof(InfoMessage), "%s ist nun als %s tätig.", PLAYER_NAME[PlayerId], PROFESSION_NAME[ProfessionId]);
		SendClientMessageToAllPlayers(MESSAGE_TYPE_INFO, InfoMessage);
		CreateMainMenuForPlayer(PlayerId);
	}
	else
	{
	    SendClientMessage(PlayerId, COLOUR_RED, "Die Ausbildung zu dieser Tätigkeit ist zu teuer.");
	    CreateProfessionSelectionMenu(PlayerId);
	}
	return true;
}

public CreateProfessionStartMenu(PlayerId)
{
	new AccountId = PLAYER_ACCOUNT[PlayerId];
 	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	new ProfessionId = ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId];
    CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_PROFESSION_START, 0, "Tätigkeitsstart");
	for (new I0; I0 < PROFESSION_SKINS[ProfessionId]; I0++)
	{
 		AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_PROFESSION_START, PROFESSION_SKIN_NAME[ProfessionId][I0]);
	}
	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_PROFESSION_START);
	return true;
}

public PlayerStartsProfession(PlayerId, SkinId)
{
	if (PLAYER_DEATH_MATCH[PlayerId] == -1)
	{
	    new AccountId = PLAYER_ACCOUNT[PlayerId];
	    new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	    new ProfessionId = ACCOUNT_P_PROFESSION[AccountId][AccountPlayerId];
	    if (SkinId < PROFESSION_SKINS[ProfessionId])
	    {
			PLAYER_USES_PROFESSION[PlayerId] = true;
			SetPlayerSkin(PlayerId, PROFESSION_SKIN_SKIN[ProfessionId][SkinId]);
			SavePlayerWeapons(PlayerId);
			ResetPlayerWeapons(PlayerId);
			for (new I0; I0 < 3; I0++)
			{
		    	if (PROFESSION_SKIN_WEAPON[ProfessionId][SkinId][I0] != -1)
				{
					GivePlayerWeapon(PlayerId, WEAPON_TYPE_MODEL[PROFESSION_SKIN_WEAPON[ProfessionId][SkinId][I0]], PROFESSION_SKIN_WEAPON[ProfessionId][SkinId][(I0 + 3)]);
				}
			}
 		}
		else
		{
		    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Diesen Skin gibt es nicht.");
		}
	}
	else
	{
	     SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie befinden sich in einem Death-Match.");
	}
	CreateMainMenuForPlayer(PlayerId);
	return true;
}

public PlayerEndsProfession(PlayerId)
{
	PLAYER_USES_PROFESSION[PlayerId] = false;
	new AccountId = PLAYER_ACCOUNT[PlayerId];
 	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	SetPlayerSkin(PlayerId, ACCOUNT_P_SKIN[AccountId][AccountPlayerId]);
	LoadPlayerWeapons(PlayerId);
	return true;
}

public AddProfession(Name[MAX_PROFESSION_NAME], Price)
{
	new ProfessionId = PROFESSIONS;
    if (ProfessionId < MAX_PROFESSIONS)
	{
	    PROFESSION_NAME[ProfessionId] = Name;
	    PROFESSION_PRICE[ProfessionId] = Price;
	    PROFESSION_TARGETS[ProfessionId] = 0;
	    PROFESSION_SKINS[ProfessionId] = 0;
	    PROFESSIONS++;
		return ProfessionId;
	}
	return -1;
}

public AddProfessionTarget(Experience, Money, RankPoints)
{
    new ProfessionId = (PROFESSIONS - 1);
    new ProfessionTargetId = PROFESSION_TARGETS[ProfessionId];
    if (ProfessionTargetId < MAX_PROFESSION_TARGETS)
	{
    	PROFESSION_TARGET_EXPERIENCE[ProfessionId][ProfessionTargetId] = Experience;
    	PROFESSION_TARGET_MONEY[ProfessionId][ProfessionTargetId] = Money;
    	PROFESSION_TARGET_RANK_POINTS[ProfessionId][ProfessionTargetId] = RankPoints;
    	PROFESSION_TARGETS[ProfessionId]++;
    	return ProfessionTargetId;
	}
	return -1;
}

public AddProfessionSkin(Skin, Name[MAX_PROFESSION_SKIN_NAME], Weapon1, Ammo1, Weapon2, Ammo2, Weapon3, Ammo3)
{
    new ProfessionId = (PROFESSIONS - 1);
    new ProfessionSkinId = PROFESSION_SKINS[ProfessionId];
    if (ProfessionSkinId < MAX_PROFESSION_SKINS)
	{
	    PROFESSION_SKIN_NAME[ProfessionId][ProfessionSkinId] = Name;
    	PROFESSION_SKIN_SKIN[ProfessionId][ProfessionSkinId] = Skin;
        PROFESSION_SKIN_WEAPON[ProfessionId][ProfessionSkinId][0] = Weapon1;
        PROFESSION_SKIN_WEAPON[ProfessionId][ProfessionSkinId][3] = Ammo1;
        PROFESSION_SKIN_WEAPON[ProfessionId][ProfessionSkinId][1] = Weapon2;
        PROFESSION_SKIN_WEAPON[ProfessionId][ProfessionSkinId][4] = Ammo2;
        PROFESSION_SKIN_WEAPON[ProfessionId][ProfessionSkinId][2] = Weapon3;
        PROFESSION_SKIN_WEAPON[ProfessionId][ProfessionSkinId][5] = Ammo3;
        PROFESSION_SKINS[ProfessionId]++;
		return ProfessionSkinId;
	}
	return -1;
}
