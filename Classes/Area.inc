//*******************************************************************
//Area
//Nicht dynamisch, alle Areas werden am Anfang definiert.
//*******************************************************************
#if defined Area_included
  	#endinput
#endif
#define Area_included
#pragma library Area

//-- Variables --
new AREAS = 0;
new TIMER_AREA;

//-- Properties --
new AREA_NAME[MAX_AREAS][MAX_AREA_NAME];
new Float:AREA_POSITION[MAX_AREAS][6];
new AREA_OWNING_GANG[MAX_AREAS];
