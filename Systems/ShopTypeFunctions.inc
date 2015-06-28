//*******************************************************************
//Shop Type Functions
//*******************************************************************
#if defined ShopTypeFunctions_included
  	#endinput
#endif
#define ShopTypeFunctions_included
#pragma library ShopTypeFunctions

//-- Functions --
public CreateShopTypeMenu(PlayerId, ShopTypeId)
{
 	CreateCustomMenuForPlayer(PlayerId, MENU_TYPE_SHOP, ShopTypeId, SHOP_TYPE_NAME[ShopTypeId]);
 	SetCustomMenuHeader(PlayerId, MENU_TYPE_SHOP, "Laden");
    SetCustomMenuHeader(PlayerId, MENU_TYPE_SHOP, "Objekt - Preis");
    new MenuItemText[MAX_STRING];
	for (new I0 = 0; I0 < SHOP_TYPE_OBJECTS[ShopTypeId]; I0++)
	{
		format(MenuItemText, sizeof(MenuItemText), "%s - %d$", SHOP_TYPE_OBJECT_NAME[ShopTypeId][I0], SHOP_TYPE_OBJECT_PRICE[ShopTypeId][I0]);
		AddCustomMenuItemForPlayer(PlayerId, MENU_TYPE_SHOP, MenuItemText);
	}
	ShowCustomMenuForPlayer(PlayerId, MENU_TYPE_SHOP);
	return true;
}

public PlayerBuysShopTypeObject(PlayerId, ShopTypeObjectId)
{
	new ShopTypeId = PLAYER_MENU[PlayerId];
	new ShopId = PLAYER_CHECKPOINT[PlayerId];
	if (GetPlayerMoney(PlayerId) >= SHOP_TYPE_OBJECT_PRICE[ShopTypeId][ShopTypeObjectId])
	{
	    switch (SHOP_TYPE_OBJECT_TYPE[ShopTypeId][ShopTypeObjectId])
	    {
			case SHOP_TYPE_OBJECT_TYPE_WEAPON:
			{
			    GivePlayerMoney(PlayerId, -SHOP_TYPE_OBJECT_PRICE[ShopTypeId][ShopTypeObjectId]);
				CreateWeaponTypeForPlayer(PlayerId, SHOP_TYPE_OBJECT_ID[ShopTypeId][ShopTypeObjectId], WEAPON_TYPE_AMMO[SHOP_TYPE_OBJECT_ID[ShopTypeId][ShopTypeObjectId]]);
                return true;
			}
			case SHOP_TYPE_OBJECT_TYPE_VEHICLE:
			{
			    GivePlayerMoney(PlayerId, -SHOP_TYPE_OBJECT_PRICE[ShopTypeId][ShopTypeObjectId]);
				CreateVehicleTypeForPlayer(PlayerId, SHOP_TYPE_OBJECT_ID[ShopTypeId][ShopTypeObjectId]);
				return true;
			}
			case SHOP_TYPE_OBJECT_TYPE_HEALTH:
			{
			    GivePlayerMoney(PlayerId, -SHOP_TYPE_OBJECT_PRICE[ShopTypeId][ShopTypeObjectId]);
			    AddPlayerHealth(PlayerId, float(SHOP_TYPE_OBJECT_ID[ShopTypeId][ShopTypeObjectId]), true);
                return true;
			}
			case SHOP_TYPE_OBJECT_TYPE_ARMOUR:
			{
			    GivePlayerMoney(PlayerId, -SHOP_TYPE_OBJECT_PRICE[ShopTypeId][ShopTypeObjectId]);
			    AddPlayerArmour(PlayerId, float(SHOP_TYPE_OBJECT_ID[ShopTypeId][ShopTypeObjectId]), true);
                return true;
			}
			case SHOP_TYPE_OBJECT_TYPE_PETROL:
			{
			    if (GetPlayerState(PlayerId) == PLAYER_STATE_DRIVER)
			    {
			        new VehicleId = GetPlayerVehicleID(PlayerId);
			        if (VehicleRequiresPetrol(VehicleId))
			        {
			            GivePlayerMoney(PlayerId, -SHOP_TYPE_OBJECT_PRICE[ShopTypeId][ShopTypeObjectId]);
			    		AddVehiclePetrol(GetPlayerVehicleID(PlayerId), float(SHOP_TYPE_OBJECT_ID[ShopTypeId][ShopTypeObjectId]), true);
                        return true;
					}
					else
					{
					    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Ihr Fahrzeug benötigt kein Benzin.");
					}
				}
				else
				{
				    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Sie müssen Fahrer eines Fahrzeugs sein, um tanken zu können.");
				}
			}
			case SHOP_TYPE_OBJECT_TYPE_ACTION:
			{
			    SetPlayerSpecialAction(PlayerId, SHOP_TYPE_OBJECT_ID[ShopTypeId][ShopTypeObjectId]);
			    return true;
			}
			default:
			{
			    SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Unbekannter Ladentyp.");
			}
		}
		CreateShopTypeMenu(PlayerId, ShopTypeId);
		SetPlayerCameraPos(PlayerId, SHOP_VIEW_POSITION[ShopId][X], SHOP_VIEW_POSITION[ShopId][Y], SHOP_VIEW_POSITION[ShopId][Z]);
    	SetPlayerCameraLookAt(PlayerId, SHOP_VIEW_TARGET[ShopId][X], SHOP_VIEW_TARGET[ShopId][Y], SHOP_VIEW_TARGET[ShopId][Z]);
	}
	else
	{
		SendMessageToPlayer(PlayerId, MESSAGE_TYPE_ERROR, "Dieses Objekt ist zu teuer.");
	}
	return false;
}

public AddShopType(Name[MAX_SHOP_TYPE_NAME], Icon)
{
	new ShopTypeId = SHOP_TYPES;
    if (ShopTypeId < MAX_SHOP_TYPES)
	{
	    SHOP_TYPE_NAME[ShopTypeId] = Name;
	    SHOP_TYPE_ICON[ShopTypeId] = Icon;
	    SHOP_TYPE_OBJECTS[ShopTypeId] = 0;
	    SHOP_TYPES++;
		return ShopTypeId;
	}
	return -1;
}

public AddShopTypeObject(Name[MAX_SHOP_TYPE_OBJECT_NAME], Price, Type, Id)
{
    new ShopTypeId = (SHOP_TYPES - 1);
    new ShopTypeObjectId = SHOP_TYPE_OBJECTS[ShopTypeId];
	if (ShopTypeObjectId < MAX_SHOP_TYPES)
	{
	    SHOP_TYPE_OBJECT_NAME[ShopTypeId][ShopTypeObjectId] = Name;
	    SHOP_TYPE_OBJECT_PRICE[ShopTypeId][ShopTypeObjectId] = Price;
	    SHOP_TYPE_OBJECT_TYPE[ShopTypeId][ShopTypeObjectId] = Type;
	    SHOP_TYPE_OBJECT_ID[ShopTypeId][ShopTypeObjectId] = Id;
        SHOP_TYPE_OBJECTS[ShopTypeId]++;
		return ShopTypeObjectId;
	}
	return -1;
}

