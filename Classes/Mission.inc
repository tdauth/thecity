//*******************************************************************
//Mission
//*******************************************************************
#if defined Mission_included
	#endinput
#endif
#define Mission_included
#pragma library Mission

//-- Variables --
new MISSIONS = 0;
new TIMER_MISSION[MAX_PLAYERS];

//-- Properties --
new MISSION_NAME[MAX_MISSIONS][MAX_MISSION_NAME];
new Float:MISSION_START_POSITION[MAX_MISSIONS][4];
new MISSION_TIME[MAX_MISSIONS];
new MISSION_PROFESSION[MAX_MISSIONS];
new MISSION_REWARD[MAX_MISSIONS][MAX_MISSION_REWARDS];
new MISSION_VEHICLES[MAX_MISSIONS];
new MISSION_VEHICLE[MAX_MISSIONS][MAX_MISSION_VEHICLES];
new MISSION_CHECKPOINTS[MAX_MISSIONS];
new Float:MISSION_CHECKPOINT[MAX_MISSIONS][MAX_MISSION_CHECKPOINTS][4];
