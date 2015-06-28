//*******************************************************************
//House
//*******************************************************************
#if defined House_included
  	#endinput
#endif
#define House_included
#pragma library House

//-- Variables --
new HOUSES = 0;
new TIMER_HOUSE;

//-- Properties --
new HOUSE_NAME[MAX_HOUSES][MAX_HOUSE_NAME];
new HOUSE_DESCRIPTION[MAX_HOUSES][MAX_HOUSE_DESCRIPTION];
new HOUSE_PRICE[MAX_HOUSES];
new HOUSE_MONEY[MAX_HOUSES];
new HOUSE_VEHICLES[MAX_HOUSES];
new HOUSE_VEHICLE[MAX_HOUSES][MAX_HOUSE_VEHICLES];
new HOUSE_OWNER_ACCOUNT[MAX_HOUSES];
new HOUSE_OWNER_ACCOUNT_PLAYER[MAX_HOUSES];
new Float:HOUSE_CHECKPOINT[MAX_HOUSES][4];
new Float:HOUSE_VIEW_POSITION[MAX_HOUSES][3];
new Float:HOUSE_VIEW_TARGET[MAX_HOUSES][3];
new HOUSE_CAMERAS[MAX_HOUSES];
new Float:HOUSE_CAMERA_POSITION[MAX_HOUSES][MAX_HOUSE_CAMERAS][3];
new Float:HOUSE_CAMERA_TARGET[MAX_HOUSES][MAX_HOUSE_CAMERAS][3];
new HOUSE_CAMERA_INTERIOR[MAX_HOUSES][MAX_HOUSE_CAMERAS];
