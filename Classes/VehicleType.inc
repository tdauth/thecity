//*******************************************************************
//Vehicle Type
//*******************************************************************
#if defined VehicleType_included
  	#endinput
#endif
#define VehicleType_included
#pragma library VehicleType

//-- Variables --
new VEHICLE_TYPES = 0;

//-- Properties --
new VEHICLE_TYPE_NAME[MAX_VEHICLE_TYPES][MAX_VEHICLE_TYPE_NAME];
new VEHICLE_TYPE_MODEL[MAX_VEHICLE_TYPES];
new VEHICLE_TYPE_PRICE[MAX_VEHICLE_TYPES];
new VEHICLE_TYPE_TYPE[MAX_VEHICLE_TYPES];
new VEHICLE_TYPE_MAX_PLACES[MAX_VEHICLE_TYPES];
new Float:VEHICLE_TYPE_MAX_PETROL[MAX_VEHICLE_TYPES];
new VEHICLE_TYPE_PROFESSION[MAX_VEHICLE_TYPES];
