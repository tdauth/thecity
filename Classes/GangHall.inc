//*******************************************************************
//Gang Hall
//*******************************************************************
#if defined GangHall_included
  	#endinput
#endif
#define GangHall_included
#pragma library GangHall

//-- Variables --
new GANG_HALLS = 0;

//-- Properties --
new GANG_HALL_NAME[MAX_GANG_HALLS][MAX_GANG_HALL_NAME];
new GANG_HALL_PRICE[MAX_GANG_HALLS];
new GANG_HALL_OWNER[MAX_GANG_HALLS];
new Float:GANG_HALL_POSITION[MAX_GANG_HALLS][4];
new GANG_HALL_INTERIOR[MAX_GANG_HALLS];
new Float:GANG_HALL_TEAM_POSITION[MAX_GANG_HALLS][2][4];
new Float:GANG_HALL_EXIT_POSITION[MAX_GANG_HALLS][4];
