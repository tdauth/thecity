//*******************************************************************
//Skin Functions
//*******************************************************************
#if defined SkinFunctions_included
  	#endinput
#endif
#define SkinFunctions_included
#pragma library SkinFunctions

//-- Functions --
public InitSkinPlayerClasses()
{
	for (new I0 = 0; I0 < SKINS; I0++)
	{
	    AddPlayerClass(SKIN_MODEL[I0], -783.8020, 495.5815, 1376.1953, 0.0000, 0, 0, 0, 0, 0, 0);
	}
	return true;
}

public ShowSkinInfoForPlayer(PlayerId, SkinId)
{
    SetPlayerInterior(PlayerId, 1);
    new AccountId = PLAYER_ACCOUNT[PlayerId];
    new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
    ACCOUNT_P_SKIN[AccountId][AccountPlayerId] = SKIN_MODEL[SkinId];
    new InfoMessage[MAX_STRING];
 	format(InfoMessage, sizeof(InfoMessage), "~y~Aussehen %d~n~~w~%s", (SkinId + 1), SKIN_NAME[SkinId]);
  	SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, InfoMessage);
  	return true;
}

public AddSkin(Name[MAX_SKIN_NAME], Model)
{
	new SkinId = SKINS;
    if (SkinId < MAX_SKINS)
	{
	    SKIN_NAME[SkinId] = Name;
   		SKIN_MODEL[SkinId] = Model;
   		SKINS++;
		return SkinId;
	}
	return -1;
}
