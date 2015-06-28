//*******************************************************************
//Town
//*******************************************************************
#if defined Town_included
  	#endinput
#endif
#define Town_included
#pragma library Town

//-- Variables --
new TOWNS = 0;
new TIMER_RESPAWN[MAX_PLAYERS];

//-- Properties --
new TOWN_NAME[MAX_TOWNS][MAX_TOWN_NAME];
new Float:TOWN_POSITION[MAX_TOWNS][4];
new Float:TOWN_HOSPITAL_POSITION[MAX_TOWNS][4];
