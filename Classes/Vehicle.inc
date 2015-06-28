//*******************************************************************
//Vehicle
//*******************************************************************
#if defined Vehicle_included
  	#endinput
#endif
#define Vehicle_included
#pragma library Vehicle

//-- Variables --
new VEHICLES = 0; //Vehicles beginnen mit 1
new TIMER_VEHICLE_DATA;
//#define MAX_VEHICLES                        		700

//-- Properties --
new VEHICLE_TYPE[MAX_VEHICLES];
new VEHICLE_USED_PLACES[MAX_VEHICLES];
new Float:VEHICLE_PETROL[MAX_VEHICLES];
