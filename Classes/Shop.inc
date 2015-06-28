//*******************************************************************
//Shop
//*******************************************************************
#if defined Shop_included
  	#endinput
#endif
#define Shop_included
#pragma library Shop

//-- Variables --
new SHOPS = 0;

//-- Properties --
new SHOP_OWNER[MAX_SHOPS][MAX_SHOP_OWNER];
new SHOP_TYPE[MAX_SHOPS];
new Float:SHOP_CHECKPOINT[MAX_SHOPS][4];
new Float:SHOP_VIEW_POSITION[MAX_SHOPS][3];
new Float:SHOP_VIEW_TARGET[MAX_SHOPS][3];
