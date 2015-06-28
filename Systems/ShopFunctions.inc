//*******************************************************************
//Shop Functions
//*******************************************************************
#if defined ShopFunctions_included
  	#endinput
#endif
#define ShopFunctions_included
#pragma library ShopFunctions

//-- Functions --
public CreateShopMarkersForPlayer(PlayerId)
{
    for (new I0 = 0; I0 <= SHOPS; I0++)
	{
		AddPlayerMapMarker(PlayerId, SHOP_TYPE_ICON[SHOP_TYPE[I0]], SHOP_CHECKPOINT[I0][X], SHOP_CHECKPOINT[I0][Y], SHOP_CHECKPOINT[I0][Z], 0);
	}
	return true;
}

public PlayerEntersShopCheckpoint(PlayerId, ShopId)
{
	new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "Sie betreten %s's %s.", SHOP_OWNER[ShopId], SHOP_TYPE_NAME[SHOP_TYPE[ShopId]]);
    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, InfoMessage);
    CreateShopTypeMenu(PlayerId, SHOP_TYPE[ShopId]);
    SetPlayerCameraPos(PlayerId, SHOP_VIEW_POSITION[ShopId][X], SHOP_VIEW_POSITION[ShopId][Y], SHOP_VIEW_POSITION[ShopId][Z]);
    SetPlayerCameraLookAt(PlayerId, SHOP_VIEW_TARGET[ShopId][X], SHOP_VIEW_TARGET[ShopId][Y], SHOP_VIEW_TARGET[ShopId][Z]);
	return true;
}

public AddShop(Owner[MAX_SHOP_OWNER], Type, Float:CheckpointX, Float:CheckpointY, Float:CheckpointZ, Float:CheckpointSize, Float:ViewPositionX, Float:ViewPositionY, Float:ViewPositionZ, Float:ViewTargetX, Float:ViewTargetY, Float:ViewTargetZ)
{
	new ShopId = SHOPS;
    if (ShopId < MAX_SHOPS)
	{
	    SHOP_OWNER[ShopId] = Owner;
	    SHOP_TYPE[ShopId] = Type;
	    SHOP_CHECKPOINT[ShopId][X] = CheckpointX;
	    SHOP_CHECKPOINT[ShopId][Y] = CheckpointY;
	    SHOP_CHECKPOINT[ShopId][Z] = CheckpointZ;
	    SHOP_CHECKPOINT[ShopId][SIZE] = CheckpointSize;
	    SHOP_VIEW_POSITION[ShopId][X] = ViewPositionX;
	    SHOP_VIEW_POSITION[ShopId][Y] = ViewPositionY;
	    SHOP_VIEW_POSITION[ShopId][Z] = ViewPositionZ;
	    SHOP_VIEW_TARGET[ShopId][X] = ViewTargetX;
	    SHOP_VIEW_TARGET[ShopId][Y] = ViewTargetY;
	    SHOP_VIEW_TARGET[ShopId][Z] = ViewTargetZ;
	    SHOPS++;
		return ShopId;
	}
	return -1;
}
