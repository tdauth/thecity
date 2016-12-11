//*******************************************************************
//House Functions
//*******************************************************************
#if defined HouseFunctions_included
  	#endinput
#endif
#define HouseFunctions_included
#pragma library HouseFunctions

//-- Functions --
public CreateHouseMarkersForPlayer(PlayerId)
{
	for (new I0 = 0; I0 < HOUSES; I0++)
	{
		AddPlayerMapMarker(PlayerId, 31, HOUSE_CHECKPOINT[I0][X], HOUSE_CHECKPOINT[I0][Y], HOUSE_CHECKPOINT[I0][Z], 0);
		SetupHouseVehiclesForPlayer(PlayerId, I0, false);
	}
	return true;
}

AccountPlayerHasHouse(AccountId, AccountPlayerId, HouseId)
{
	for (new I0 = 0; I0 < ACCOUNT_P_HOUSES[AccountId][AccountPlayerId]; I0++)
	{
	    if (ACCOUNT_P_HOUSE[AccountId][AccountPlayerId][I0] == HouseId)
	    {
	        return I0;
		}
	}
	return -1;
}

public SetupHouseVehiclesForPlayer(PlayerId, HouseId, Owner)
{
    for (new I0 = 0; I0 < HOUSE_VEHICLES[HouseId]; I0++)
    {
  		SetVehicleParamsForPlayer(HOUSE_VEHICLE[HouseId][I0], PlayerId, Owner, !Owner);
    }
	return true;
}

public PlayerBuysHouse(PlayerId, HouseId)
{
	//House Has No Owner
	if (HOUSE_OWNER_ACCOUNT[HouseId] == -1)
	{
	    //Player Has Enough Money
    	if (GetPlayerMoney(PlayerId) >= HOUSE_PRICE[HouseId])
    	{
    	    new AccountId = PLAYER_ACCOUNT[PlayerId];
	    	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	    	new PlayerAccountHouseId = AddAccountPlayerHouse(AccountId, AccountPlayerId, HouseId);
            //Account Player Has Not Too Many Houses
			if (PlayerAccountHouseId != -1)
	    	{
          		HOUSE_OWNER_ACCOUNT[HouseId] = AccountId;
	    	    HOUSE_OWNER_ACCOUNT_PLAYER[HouseId] = AccountPlayerId;
	    	    SetupHouseVehiclesForPlayer(PlayerId, HouseId, true);
	    	    GivePlayerMoney(PlayerId, -HOUSE_PRICE[HouseId]);
	    	    SetCameraBehindPlayer(PlayerId);
	    	    TogglePlayerControllable(PlayerId, true);
	    	    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, "Haus gekauft.");
	    	    return true;
    		}
   			//Account Player Has Too Many Houses
			else
			{
				SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie haben bereits die maximale Anzahl kaufbarer Häuser eines Spielers erreicht.");
			}
    	}
    	//Player Has Not Enough Money
    	else
    	{
    	 		SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Dieses Haus ist zu teuer.");
    	}
	}
	//House Has An Owner
	else
	{
	    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Dieses Haus gehört bereits einem Spieler.");
	}
	return false;
}

public PlayerSellsHouse(PlayerId, House)
{
    new AccountId = PLAYER_ACCOUNT[PlayerId];
   	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
   	new HouseId = ACCOUNT_P_HOUSE[AccountId][AccountPlayerId][House];
   	GivePlayerMoney(PlayerId, (HOUSE_PRICE[HouseId] / 2)); //Der halbe Preis wird zurückerstattet.
    RemoveAccountPlayerHouse(AccountId, AccountPlayerId, HouseId);
    HOUSE_OWNER_ACCOUNT[HouseId] = -1;
	HOUSE_OWNER_ACCOUNT_PLAYER[HouseId] = -1;
    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Haus verkauft.");
}

public CreateHouseMenu(PlayerId, HouseId)
{
	CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_HOUSE, HouseId, HOUSE_NAME[HouseId]);
 	SetCustomMenuHeader(PlayerId, MENU_TYPE_HOUSE, "Haus");
 	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HOUSE, "Kaufen");
 	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_HOUSE);
	return true;
}

public PlayerEntersHouseCheckpoint(PlayerId, HouseId)
{
    new AccountId = PLAYER_ACCOUNT[PlayerId];
   	new PlayerAccountId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	if (AccountPlayerHasHouse(AccountId, PlayerAccountId, HouseId) == -1)
    {
		SetPlayerCameraPos(PlayerId, HOUSE_VIEW_POSITION[HouseId][X], HOUSE_VIEW_POSITION[HouseId][Y], HOUSE_VIEW_POSITION[HouseId][Z]);
		SetPlayerCameraLookAt(PlayerId, HOUSE_VIEW_TARGET[HouseId][X], HOUSE_VIEW_TARGET[HouseId][Y], HOUSE_VIEW_TARGET[HouseId][Z]);
		CreateHouseMenu(PlayerId, HouseId);
	}
    new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "~y~%s~n~~w~Preis: %d$~n~Einnahmen (Alle 10 Minuten): %d~n~Kameras: %d~n~%s", HOUSE_NAME[HouseId], HOUSE_PRICE[HouseId], HOUSE_MONEY[HouseId], (HOUSE_CAMERAS[HouseId] + 1), HOUSE_DESCRIPTION[HouseId]);
	SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, InfoMessage);
	return true;
}

public CreateHousesMenu(PlayerId)
{
    new AccountId = PLAYER_ACCOUNT[PlayerId];
   	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	if (ACCOUNT_P_HOUSES[AccountId][AccountPlayerId] > 0)
	{
    	CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_HOUSES, 0, "Häuser-Liste");
    	new House;
    	new MenuItemText[MAX_STRING];
    	for (new I0 = 0; I0 < MAX_ACCOUNT_PLAYER_HOUSES; I0++)
		{
		    House = ACCOUNT_P_HOUSE[AccountId][AccountPlayerId][I0];
	    	if (House != -1)
	    	{
	        	format(MenuItemText, sizeof(MenuItemText), "%s", HOUSE_NAME[House]);
    			AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HOUSES, MenuItemText);
			}
		}
		ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_HOUSES);
	}
	else
	{
	    CreateMainMenuForPlayer(PlayerId);
	    SendClientMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie besitzen keine Häuser.");
	}
	return true;
}

public CreateHouseSettingsMenu(PlayerId, House)
{
    new AccountId = PLAYER_ACCOUNT[PlayerId];
   	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
	new HouseId = ACCOUNT_P_HOUSE[AccountId][AccountPlayerId][House];

	PLAYER_MENU_HOUSE[PlayerId] = House;
	CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_HOUSE_SETTINGS, House, HOUSE_NAME[HouseId]);
	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HOUSE_SETTINGS, "Haus verkaufen");
	new MenuItemText[MAX_STRING];
	for (new I0 = 0; I0 < HOUSE_CAMERAS[HouseId]; I0++)
	{
    	format(MenuItemText, sizeof(MenuItemText), "Kamera %d", I0);
		AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HOUSE_SETTINGS, MenuItemText);
	}
	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_HOUSE_SETTINGS);

	return true;
}

public CreateHouseSellingMenu(PlayerId)
{
	new HouseId = PLAYER_MENU_HOUSE[PlayerId];
	CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_HOUSE_SELLING, HouseId, HOUSE_NAME[HouseId]);
	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HOUSE_SELLING, "OK");
	AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_HOUSE_SELLING, "Abbrechen");
	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_HOUSE_SELLING);

	return true;
}

public ShowHouseCameraForPlayer(PlayerId, House, Camera)
{
    new AccountId = PLAYER_ACCOUNT[PlayerId];
   	new AccountPlayerId = PLAYER_ACCOUNT_PLAYER[PlayerId];
    new HouseId = ACCOUNT_P_HOUSE[AccountId][AccountPlayerId][House];
    SavePlayerInterior(PlayerId);
	SetPlayerInterior(PlayerId, HOUSE_CAMERA_INTERIOR[HouseId][Camera]);
	SetPlayerCameraPos(PlayerId, HOUSE_CAMERA_POSITION[HouseId][Camera][X], HOUSE_CAMERA_POSITION[HouseId][Camera][Y], HOUSE_CAMERA_POSITION[HouseId][Camera][Z]);
	SetPlayerCameraLookAt(PlayerId, HOUSE_CAMERA_TARGET[HouseId][Camera][X], HOUSE_CAMERA_TARGET[HouseId][Camera][Y], HOUSE_CAMERA_TARGET[HouseId][Camera][Z]);
    TogglePlayerControllable(PlayerId, false);
    CreateHouseSettingsMenu(PlayerId, House);
    return true;
}

public InitHouseTimer()
{
    TIMER_HOUSE = SetTimer("TimerFunctionDivideHouseMoney", ConvertSeconds(600), true); //Eine 0 mehr!
	return true;
}

public TimerFunctionDivideHouseMoney()
{
	new AccountId, AccountPlayerId, PlayerId;
	new InfoMessage[MAX_STRING];
	for (new I0 = 0; I0 < HOUSES; I0++)
	{
 		AccountId = HOUSE_OWNER_ACCOUNT[I0];
        if (AccountId != -1)
        {
			AccountPlayerId = HOUSE_OWNER_ACCOUNT_PLAYER[I0];
			PlayerId = ACCOUNT_P_PLAYER_ID[AccountId][AccountPlayerId];
        	GivePlayerMoney(PlayerId, HOUSE_MONEY[I0]);
        	format(InfoMessage, sizeof(InfoMessage), "Ihr Haus bringt Ihnen %d$ ein.", HOUSE_MONEY[I0]);
        	SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ACCEPTANCE, InfoMessage);
		}
	}
	return true;
}

public AddHouse(Name[MAX_HOUSE_NAME], Description[MAX_HOUSE_DESCRIPTION], Price, Money, Float:CheckpointX, Float:CheckpointY, Float:CheckpointZ, Float:CheckpointSize, Float:ViewPositionX, Float:ViewPositionY, Float:ViewPositionZ, Float:ViewTargetX, Float:ViewTargetY, Float:ViewTargetZ)
{
	new HouseId = HOUSES;
	if (HouseId < MAX_HOUSES)
	{
		HOUSE_NAME[HouseId] = Name;
		HOUSE_DESCRIPTION[HouseId] = Description;
		HOUSE_PRICE[HouseId] = Price;
		HOUSE_MONEY[HouseId] = Money;
		HOUSE_VEHICLES[HouseId] = 0;
		HOUSE_OWNER_ACCOUNT[HouseId] = -1;
		HOUSE_OWNER_ACCOUNT_PLAYER[HouseId] = -1;
		HOUSE_CHECKPOINT[HouseId][X] = CheckpointX;
		HOUSE_CHECKPOINT[HouseId][Y] = CheckpointY;
		HOUSE_CHECKPOINT[HouseId][Z] = CheckpointZ;
		HOUSE_CHECKPOINT[HouseId][SIZE] = CheckpointSize;
		HOUSE_VIEW_POSITION[HouseId][X] = ViewPositionX;
		HOUSE_VIEW_POSITION[HouseId][Y] = ViewPositionY;
		HOUSE_VIEW_POSITION[HouseId][Z] = ViewPositionZ;
		HOUSE_VIEW_TARGET[HouseId][X] = ViewTargetX;
		HOUSE_VIEW_TARGET[HouseId][Y] = ViewTargetY;
		HOUSE_VIEW_TARGET[HouseId][Z] = ViewTargetZ;
		HOUSE_VEHICLES[HouseId] = 0;
		HOUSE_CAMERAS[HouseId] = 0;
		HOUSES++;
		return HouseId;
	}
	return -1;
}

public AddHouseVehicle(VehicleId)
{
	new HouseId = (HOUSES - 1);
	new HouseVehicleId = HOUSE_VEHICLES[HouseId];
    if (HouseVehicleId < MAX_HOUSE_VEHICLES)
	{
    	HOUSE_VEHICLE[HouseId][HouseVehicleId] = VehicleId;
    	HOUSE_VEHICLES[HouseId]++;
    	return HouseVehicleId;
	}
	return -1;
}

public AddHouseCamera(Float:PositionX, Float:PositionY, Float:PositionZ, Float:TargetX, Float:TargetY, Float:TargetZ, Interior)
{
	new HouseId = (HOUSES - 1);
	new HouseCameraId = HOUSE_CAMERAS[HouseId];
    if (HouseCameraId < MAX_HOUSE_CAMERAS)
	{
    	HOUSE_CAMERA_POSITION[HouseId][HouseCameraId][X] = PositionX;
    	HOUSE_CAMERA_POSITION[HouseId][HouseCameraId][Y] = PositionY;
    	HOUSE_CAMERA_POSITION[HouseId][HouseCameraId][Z] = PositionZ;
    	HOUSE_CAMERA_TARGET[HouseId][HouseCameraId][X] = TargetX;
    	HOUSE_CAMERA_TARGET[HouseId][HouseCameraId][Y] = TargetY;
    	HOUSE_CAMERA_TARGET[HouseId][HouseCameraId][Z] = TargetZ;
    	HOUSE_CAMERA_INTERIOR[HouseId][HouseCameraId] = Interior;
    	HOUSE_CAMERAS[HouseId]++;
    	return HouseCameraId;
	}
	return -1;
}
