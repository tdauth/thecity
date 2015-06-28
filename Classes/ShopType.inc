//*******************************************************************
//Shop Type
//*******************************************************************
#if defined ShopType_included
  	#endinput
#endif
#define ShopType_included
#pragma library ShopType

//-- Variables --
new SHOP_TYPES = 0;

//-- Properties --
new SHOP_TYPE_NAME[MAX_SHOP_TYPES][MAX_SHOP_TYPE_NAME];
new SHOP_TYPE_ICON[MAX_SHOP_TYPES];
new SHOP_TYPE_OBJECTS[MAX_SHOP_TYPES];
new SHOP_TYPE_OBJECT_NAME[MAX_SHOP_TYPES][MAX_SHOP_TYPE_OBJECTS][MAX_SHOP_TYPE_OBJECT_NAME];
new SHOP_TYPE_OBJECT_PRICE[MAX_SHOP_TYPES][MAX_SHOP_TYPE_OBJECTS];
new SHOP_TYPE_OBJECT_TYPE[MAX_SHOP_TYPES][MAX_SHOP_TYPE_OBJECTS];
new SHOP_TYPE_OBJECT_ID[MAX_SHOP_TYPES][MAX_SHOP_TYPE_OBJECTS];
