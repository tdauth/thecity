//*******************************************************************
//Objects
//*******************************************************************
#if defined Objects_included
  	#endinput
#endif
#define Objects_included
#pragma library Objects

//-- Variables --
new PROFESSION_OFFICER;
new PROFESSION_DOCTOR;
new PROFESSION_FIREMAN;
new PROFESSION_TAXI_DRIVER;
new PROFESSION_WORKER;
new PROFESSION_CRIMINAL;
new PROFESSION_GS_FAMILIES;
new PROFESSION_BALLAS;
new PROFESSION_LOS_SANTOS_VAGOS;
new PROFESSION_VARRIOS_LOS_AZTECAS;
new PROFESSION_SAN_FIERRO_RIFA;
new PROFESSION_DA_NANG_BOYS;
new PROFESSION_TRIADS;
new PROFESSION_MAFIA;
new PROFESSION_BIKERS;
new PROFESSION_SPECIAL_FORCE;
new PROFESSION_SOLDIER;
new PROFESSION_STORY_CHARACTER;

//-- Functions --
public InitMapMarkers(PlayerId)
{
    //Name, Description, Price, Money, VehicleId1, VehicleId2, VehicleId3, VehicleId4, CheckpointX, CheckpointY, CheckpointZ, CheckpointSize, ViewPositionX, ViewPositionY, ViewPositionZ, ViewTargetX, ViewTargetY, ViewTargetZ, PositionX, PositionY, PositionZ, PositionFacing, Interior
    //Camera, PositionX, PositionY, PositionZ, TargetX, TargetY, TargetZ
	//-- Los Santos --
    //International
    AddPlayerMapMarker(PlayerId, 5, 1639.3430, -2285.0547, 13.5218, 0); //Airport
	//Ocean Docks
	//Santa Maria Beach
	//Verona Beach
 	//Verdant Bluffs
 	//El Corona
 	AddPlayerMapMarker(PlayerId, 55, 1848.4888, -1856.3849, 13.3828, 0); //8 Ball
	//Willofield
	//Playa Del Seville
    //Rodeo
    //Marina
    //Market
    AddPlayerMapMarker(PlayerId, 22, 1172.9609, -1323.4269, 15.3983, 0); //Hospital
    //Conference Center
    //Commerce
    //Pershing Square
    AddPlayerMapMarker(PlayerId, 30, 1552.3413, -1675.7686, 16.1953, 0); //Police Department
    //Little-Mexico
    //Idlewood
    //Ganton
    //East Beach
    //Richman
    //Vinewood
    //Downtown Los Santos
    //Glen Park
    //Jefferson
    //East Los Santos
    //Temple
    AddPlayerMapMarker(PlayerId, 27, 1041.7582, -1021.2615, 32.1075, 0); //Mod Garage
    //Mulholland
    //Mulholland Intersection
    //Las Colinas
    //Los Flores
    //-- San Fierro --
    //-- Las Venturas --
    //-- Red County --
    //-- Flint County --
	//-- Whetstone --
	//-- Tierra Robada --
    //-- Bone County --
	return true;
}

public InitAreas()
{
	//Name, Float:MinX, Float:MinY, Float:MinZ, Float:MaxX, Float:MaxY, Float:MaxZ
    //-- Los Santos --
    //International
    AddArea("International", 1249.6000, -2394.3000, -89.0000, 1852.0000, -2179.2000, 110.9000);
    AddArea("International", 1852.0000, -2394.3000, -89.0000, 2089.0000, -2179.2000, 110.9000);
    AddArea("International", 1382.7000, -2730.8000, -89.0000, 2201.8000, -2394.3000, 110.9000);
    AddArea("International", 1974.6000, -2394.3000, -39.0000, 2089.0000, -2256.5000, 60.9000);
    AddArea("International", 1400.9000, -2669.2000, -39.0000, 2189.8000, -2597.2000, 60.9000);
    AddArea("International", 2051.6000, -2597.2000, -39.0000, 2152.4000, -2394.3000, 60.9000);
	//Ocean Docks
	AddArea("Ocean Docks", 2373.7000, -2697.0000, -89.0000, 2809.2000, -2330.4000, 110.9000);
	AddArea("Ocean Docks", 2201.8000, -2418.3000, -89.0000, 2324.0000, -2095.0000, 110.9000);
	AddArea("Ocean Docks", 2324.0000, -2302.3000, -89.0000, 2703.5000, -2145.1000, 110.9000);
	AddArea("Ocean Docks", 2089.0000, -2394.3000, -89.0000, 2201.8000, -2235.8000, 110.9000);
	AddArea("Ocean Docks", 2201.8000, -2730.8000, -89.0000, 2324.0000, -2418.3000, 110.9000);
	AddArea("Ocean Docks", 2703.5000, -2302.3000, -89.0000, 2959.3000, -2126.9000, 110.9000);
	AddArea("Ocean Docks", 2324.0000, -2145.1000, -89.0000, 2703.5000, -2059.2000, 110.9000);
	//Santa Maria Beach
	AddArea("Santa Maria Beach", 342.6000, -2173.2000,  -89.0000, 647.7000, -1684.6000, 110.9000);
	AddArea("Santa Maria Beach", 72.6000, -2173.2000, -89.0000, 342.6000, -1684.6000, 110.9000);
	//Verona Beach
	AddArea("Verona Beach", 647.7000, -2173.2000, -89.0000, 930.2000, -1804.2000, 110.9000);
	AddArea("Verona Beach", 930.2000, -2006.7000, -89.0000, 1073.2000, -1804.2000, 110.9000);
	AddArea("Verona Beach", 851.4000, -1804.2000, -89.0000, 1046.1000, -1577.5000, 110.9000);
	AddArea("Verona Beach", 1161.5000, -1722.2000, -89.0000, 1323.9000, -1577.5000, 110.9000);
	AddArea("Verona Beach", 1046.1000, -1722.2000, -89.0000, 1161.5000, -1577.5000, 110.9000);
 	//Verdant Bluffs
 	AddArea("Verdant Bluffs", 930.2000, -2488.4000, -89.0000, 1249.6000, -2006.7000, 110.9000);
 	AddArea("Verdant Bluffs", 1073.2000, -2006.7000, -89.0000, 1249.6000, -1842.2000, 110.9000);
 	AddArea("Verdant Bluffs", 1249.6000, -2179.2000, -89.0000, 1692.6000, -1842.2000, 110.9000);
 	//El Corona
 	AddArea("El Corona", 1812.6000, -2179.2000, -89.0000, 1970.6000, -1852.8000, 110.9000);
 	AddArea("El Corona", 1692.6000, -2179.2000, -89.0000, 1812.6000, -1842.2000, 110.9000);
	//Willofield
	AddArea("Willofield", 1970.6000, -2179.2000, -89.0000, 2089.0000, -1852.8000, 110.9000);
	AddArea("Willofield", 2089.0000, -2235.8000, -89.0000, 2201.8000, -1989.9000, 110.9000);
	AddArea("Willofield", 2089.0000, -1989.9000, -89.0000, 2324.0000, -1852.8000, 110.9000);
	AddArea("Willofield", 2201.8000, -2095.0000, -89.0000, 2324.0000, -1989.9000, 110.9000);
	AddArea("Willofield", 2541.7000, -1941.4000, -89.0000, 2703.5000, -1852.8000, 110.9000);
	AddArea("Willofield", 2324.0000, -2059.2000, -89.0000, 2541.7000, -1852.8000, 110.9000);
	AddArea("Willofield", 2541.7000, -2059.2000, -89.0000, 2703.5000, -1941.4000, 110.9000);
	//Playa Del Seville
	AddArea("Playa Del Seville", 2703.5000, -2126.9000, -89.0000, 2959.3000, -1852.8000, 110.9000);
    //Rodeo
    AddArea("Rodeo", 72.6000, -1684.6000, -89.0000, 225.1000, -1544.1000, 110.9000);
    AddArea("Rodeo", 72.6000, -1544.1000, -89.0000, 225.1000, -1404.9000, 110.9000);
    AddArea("Rodeo", 225.1000, -1684.6000, -89.0000, 312.8000, -1501.9000, 110.9000);
    AddArea("Rodeo", 225.1000, -1501.9000, -89.0000, 334.5000, -1369.6000, 110.9000);
    AddArea("Rodeo", 334.5000, -1501.9000, -89.0000, 422.6000, -1406.0000, 110.9000);
    AddArea("Rodeo", 312.8000, -1684.6000, -89.0000, 422.6000, -1501.9000, 110.9000);
    AddArea("Rodeo", 422.6000, -1684.6000, -89.0000, 558.0000, -1570.2000, 110.9000);
    AddArea("Rodeo", 558.0000, -1684.6000, -89.0000, 647.5000, -1384.9000, 110.9000);
    AddArea("Rodeo", 466.2000, -1570.2000, -89.0000, 558.0000, -1385.0000, 110.9000);
    AddArea("Rodeo", 422.6000, -1570.2000, -89.0000, 466.2000, -1406.0000, 110.9000);
    AddArea("Rodeo", 466.2000, -1385.0000, -89.0000, 647.5000, -1235.0000, 110.9000);
    AddArea("Rodeo", 334.5000, -1406.0000, -89.0000, 466.2000, -1292.0000, 110.9000);
    //Marina
    AddArea("Marina", 647.7000, -1804.2000, -89.0000, 851.4000, -1577.5000, 110.9000);
    AddArea("Marina", 647.7000, -1577.5000, -89.0000, 807.9000, -1416.2000, 110.9000);
    AddArea("Marina", 807.9000, -1577.5000, -89.0000, 926.9000, -1416.2000, 110.9000);
    //Market
    AddArea("Market", 787.4000, -1416.2000, -89.0000, 1072.6000, -1310.2000, 110.9000);
    AddArea("Market", 952.6000, -1310.2000, -89.0000, 1072.6000, -1130.8000, 110.9000);
    AddArea("Market", 1072.6000, -1416.2000, -89.0000, 1370.8000, -1130.8000, 110.9000);
    AddArea("Market", 926.9000, -1577.5000, -89.0000, 1370.8000, -1416.2000, 110.9000);
    //Conference Center
    AddArea("Conference Center", 1046.1000, -1804.2000, -89.0000, 1323.9000, -1722.2000, 110.9000);
    AddArea("Conference Center", 1073.2000, -1842.2000, -89.0000, 1323.9000, -1804.2000, 110.9000);
    //Commerce
    AddArea("Commerce", 1323.9000, -1842.2000, -89.0000, 1701.9000, -1722.2000, 110.9000);
    AddArea("Commerce", 1323.9000, -1722.2000, -89.0000, 1440.9000, -1577.5000, 110.9000);
    AddArea("Commerce", 1370.8000, -1577.5000, -89.0000, 1463.9000, -1384.9000, 110.9000);
    AddArea("Commerce", 1463.9000, -1577.5000, -89.0000, 1667.9000, -1430.8000, 110.9000);
    AddArea("Commerce", 1583.5000, -1722.2000, -89.0000, 1758.9000, -1577.5000, 110.9000);
    AddArea("Commerce", 1667.9000, -1577.5000, -89.0000, 1812.6000, -1430.8000, 110.9000);
    //Pershing Square
    AddArea("Pershing Square", 1440.9000, -1722.2000, -89.0000, 1583.5000, -1577.5000, 110.9000);
    //Little-Mexico
    AddArea("Little-Mexico", 1701.9000, -1842.2000, -89.0000, 1812.6000, -1722.2000, 110.9000);
    AddArea("Little-Mexico", 1758.9000, -1722.2000, -89.0000, 1812.6000, -1577.5000, 110.9000);
    //Idlewood
    AddArea("Idlewood", 1812.6000, -1852.8000, -89.0000, 1971.6000, -1742.3000, 110.9000);
    AddArea("Idlewood", 1812.6000, -1742.3000, -89.0000, 1951.6000, -1602.3000, 110.9000);
    AddArea("Idlewood", 1951.6000, -1742.3000, -89.0000, 2124.6000, -1602.3000, 110.9000);
    AddArea("Idlewood", 1812.6000, -1602.3000, -89.0000, 2124.6000, -1449.6000, 110.9000);
    AddArea("Idlewood", 2124.6000, -1742.3000, -89.0000, 2222.5000, -1494.0000, 110.9000);
    AddArea("Idlewood", 1971.6000, -1852.8000, -89.0000, 2222.5000, -1742.3000, 110.9000);
    //Ganton
    AddArea("Ganton", 2222.5000, -1852.8000, -89.0000, 2632.8000, -1722.3000, 110.9000);
    AddArea("Ganton", 2222.5000, -1722.3000, -89.0000, 2632.8000, -1628.5000, 110.9000);
    //East Beach
    AddArea("East Beach", 2632.8000, -1852.8000, -89.0000, 2959.3000, -1668.1000, 110.9000);
    AddArea("East Beach", 2632.8000, -1668.1000, -89.0000, 2747.7000, -1393.4000, 110.9000);
    AddArea("East Beach", 2747.7000, -1668.1000, -89.0000, 2959.3000, -1498.6000, 110.9000);
    AddArea("East Beach", 2747.7000, -1498.6000, -89.0000, 2959.3000, -1120.0000, 110.9000);
    //Richman
    AddArea("Richman", 647.5000, -1118.2000, -89.0000, 787.4000, -954.6000, 110.9000);
    AddArea("Richman", 647.5000, -954.6000, -89.0000, 768.6000, -860.6000, 110.9000);
    AddArea("Richman", 225.1000, -1369.6000, -89.0000, 334.5000, -1292.0000, 110.9000);
    AddArea("Richman", 225.1000, -1292.0000, -89.0000, 466.2000, -1235.0000, 110.9000);
    AddArea("Richman", 72.6000, -1404.9000, -89.0000, 225.1000, -1235.0000, 110.9000);
    AddArea("Richman", 72.6000, -1235.0000, -89.0000, 321.3000, -1008.1000, 110.9000);
    AddArea("Richman", 321.3000, -1235.0000, -89.0000, 647.5000, -1044.0000, 110.9000);
    AddArea("Richman", 321.3000, -1044.0000, -89.0000, 647.5000, -860.6000, 110.9000);
    AddArea("Richman", 321.3000, -860.6000, -89.0000, 687.8000, -768.0000, 110.9000);
    AddArea("Richman", 321.3000, -768.0000, -89.0000, 700.7000, -674.8000, 110.9000);
    //Vinewood
    AddArea("Vinewood", 787.4000, -1310.2000, -89.0000, 952.6000, -1130.8000, 110.9000);
    AddArea("Vinewood", 787.4000, -1130.8000, -89.0000, 952.6000, -954.6000, 110.9000);
    AddArea("Vinewood", 647.5000, -1227.2000, -89.0000, 787.4000, -1118.2000, 110.9000);
    AddArea("Vinewood", 647.7000, -1416.2000, -89.0000, 787.4000, -1227.2000, 110.9000);
    //Downtown Los Santos
    AddArea("Downtown Los Santos", 1463.9000, -1430.8000, -89.0000, 1724.7000, -1290.8000, 110.9000);
    AddArea("Downtown Los Santos", 1724.7000, -1430.8000, -89.0000, 1812.6000, -1250.9000, 110.9000);
    AddArea("Downtown Los Santos", 1463.9000, -1290.8000, -89.0000, 1724.7000, -1150.8000, 110.9000);
    AddArea("Downtown Los Santos", 1370.8000, -1384.9000, -89.0000, 1463.9000, -1170.8000, 110.9000);
    AddArea("Downtown Los Santos", 1724.7000, -1250.9000, -89.0000, 1812.6000, -1150.8000, 110.9000);
    AddArea("Downtown Los Santos", 1370.8000, -1170.8000, -89.0000, 1463.9000, -1130.8000, 110.9000);
    AddArea("Downtown Los Santos", 1378.3000, -1130.8000, -89.0000, 1463.9000, -1026.3000, 110.9000);
    AddArea("Downtown Los Santos", 1391.0000, -1026.3000, -89.0000, 1463.9000, -926.9000, 110.9000);
    AddArea("Downtown Los Santos", 1507.5000, -1385.2000, 110.9000, 1582.5000, -1325.3000, 335.9000);
    //Glen Park
    AddArea("Glen Park", 1812.6000, -1449.6000, -89.0000, 1996.9000, -1350.7000, 110.9000);
    AddArea("Glen Park", 1812.6000, -1100.8000, -89.0000, 1994.3000, -973.3000, 110.9000);
    AddArea("Glen Park", 1812.6000, -1350.7000, -89.0000, 2056.8000, -1100.8000, 110.9000);
    //Jefferson
    AddArea("Jefferson", 1996.9000, -1449.6000, -89.0000, 2056.8000, -1350.7000, 110.9000);
    AddArea("Jefferson", 2124.6000, -1494.0000, -89.0000, 2266.2000, -1449.6000, 110.9000);
    AddArea("Jefferson", 2056.8000, -1372.0000, -89.0000, 2281.4000, -1210.7000, 110.9000);
    AddArea("Jefferson", 2056.8000, -1210.7000, -89.0000, 2185.3000, -1126.3000, 110.9000);
    AddArea("Jefferson", 2185.3000, -1210.7000, -89.0000, 2281.4000, -1154.5000, 110.9000);
    AddArea("Jefferson", 2056.8000, -1449.6000, -89.0000, 2266.2000, -1372.0000, 110.9000);
    //East Los Santos
    AddArea("East Los Santos", 2421.0000, -1628.5000, -89.0000, 2632.8000, -1454.3000, 110.9000);
    AddArea("East Los Santos", 2222.5000, -1628.5000, -89.0000, 2421.0000, -1494.0000, 110.9000);
    AddArea("East Los Santos", 2266.2000, -1494.0000, -89.0000, 2381.6000, -1372.0000, 110.9000);
    AddArea("East Los Santos", 2381.6000, -1494.0000, -89.0000, 2421.0000, -1454.3000, 110.9000);
    AddArea("East Los Santos", 2281.4000, -1372.0000, -89.0000, 2381.6000, -1135.0000, 110.9000);
    AddArea("East Los Santos", 2381.6000, -1454.3000, -89.0000, 2462.1000, -1135.0000, 110.9000);
    AddArea("East Los Santos", 2462.1000, -1454.3000, -89.0000, 2581.7000, -1135.0000, 110.9000);
    //Temple
    AddArea("Temple", 1252.3000, -1130.8000, -89.0000, 1378.3000, -1026.3000, 110.9000);
    AddArea("Temple", 1252.3000, -1026.3000, -89.0000, 1391.0000, -926.9000, 110.9000);
    AddArea("Temple", 1252.3000, -926.9000, -89.0000, 1357.0000, -910.1000, 110.9000);
    AddArea("Temple", 952.6000, -1130.8000, -89.0000, 1096.4000, -937.1000, 110.9000);
    AddArea("Temple", 1096.4000, -1130.8000, -89.0000, 1252.3000, -1026.3000, 110.9000);
    AddArea("Temple", 1096.4000, -1026.3000, -89.0000, 1252.3000, -910.1000, 110.9000);
    //Mulholland
    AddArea("Mulholland", 1414.0000, -768.0000, -89.0000, 1667.6000, -452.4000, 110.9000);
    AddArea("Mulholland", 1281.1000, -452.4000, -89.0000, 1641.1000, -290.9000, 110.9000);
    AddArea("Mulholland", 1269.1000, -768.0000, -89.0000, 1414.0000, -452.4000, 110.9000);
    AddArea("Mulholland", 1357.0000, -926.9000, -89.0000, 1463.9000, -768.0000, 110.9000);
    AddArea("Mulholland", 1318.1000, -910.1000, -89.0000, 1357.0000, -768.0000, 110.9000);
    AddArea("Mulholland", 1169.1000, -910.1000, -89.0000, 1318.1000, -768.0000, 110.9000);
    AddArea("Mulholland", 768.6000, -954.6000, -89.0000, 952.6000, -860.6000, 110.9000);
    AddArea("Mulholland", 687.8000, -860.6000, -89.0000, 911.8000, -768.0000, 110.9000);
    AddArea("Mulholland", 737.5000, -768.0000, -89.0000, 1142.2000, -674.8000, 110.9000);
    AddArea("Mulholland", 1096.4000, -910.1000, -89.0000, 1169.1000, -768.0000, 110.9000);
    AddArea("Mulholland", 952.6000, -937.1000, -89.0000, 1096.4000, -860.6000, 110.9000);
    AddArea("Mulholland", 911.8000, -860.6000, -89.0000, 1096.4000, -768.0000, 110.9000);
    AddArea("Mulholland", 861.0000, -674.8000, -89.0000, 1156.5000, -600.8000, 110.9000);
    //Mulholland Intersection
    AddArea("Mulholland Intersection", 1463.9000, -1150.8000, -89.0000, 1812.6000, -768.0000, 110.9000);
    //Las Colinas
    AddArea("Las Colinas", 1994.3000, -1100.8000, -89.0000, 2056.8000, -920.8000, 110.9000);
    AddArea("Las Colinas", 2056.8000, -1126.3000, -89.0000, 2126.8000, -920.8000, 110.9000);
    AddArea("Las Colinas", 2185.3000, -1154.5000, -89.0000, 2281.4000, -934.4000, 110.9000);
    AddArea("Las Colinas", 2126.8000, -1126.3000, -89.0000, 2185.3000, -934.4000, 110.9000);
    AddArea("Las Colinas", 2747.7000, -1120.0000, -89.0000, 2959.3000, -945.0000, 110.9000);
    AddArea("Las Colinas", 2632.7000, -1135.0000, -89.0000, 2747.7000, -945.0000, 110.9000);
    AddArea("Las Colinas", 2281.4000, -1135.0000, -89.0000, 2632.7000, -945.0000, 110.9000);
    //Los Flores
    AddArea("Los Flores", 2581.7000, -1454.3000, -89.0000, 2632.8000, -1393.4000, 110.9000);
    AddArea("Los Flores", 2581.7000, -1393.4000, -89.0000, 2747.7000, -1135.0000, 110.9000);
    //-- San Fierro --
    //-- Las Venturas --
    //-- Red County --
    AddArea("Red County", -1213.9000, -768.0000, -242.9000, 2997.0000, 596.3000, 900.0000);
    //-- Flint County --
    AddArea("Flint County", -1213.9000, -2892.9000, -242.9000, 44.6000, -768.0000, 900.0000);
	//-- Whetstone --
	AddArea("Whetstone", -2997.4000, -2892.9000, -242.9000, -1213.9000, -1115.5000, 900.0000);
	//-- Tierra Robada --
	AddArea("Tierra Robada", -2997.4000, 1659.6000, -242.9000, -480.5000, 2993.8000, 900.0000);
	AddArea("Tierra Robada", -1213.9000, 596.3000, -242.9000, -480.5000, 1659.6000, 900.0000);
    //-- Bone County --
    AddArea("Bone County", -480.5000, 596.3000, -242.9000, 869.4000, 2993.8000, 900.0000);
    //AddArea("Sperrgebiet", 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000);
	return true;
}

public InitSkins()
{
	//Name, Model
    AddSkin("Skin 1", 2);
    AddSkin("Skin 2", 7);
    AddSkin("Skin 3", 9);
    AddSkin("Skin 4", 10);
    AddSkin("Skin 5", 12);
    AddSkin("Skin 6", 13);
    AddSkin("Skin 7", 14);
    AddSkin("Skin 8", 15);
    AddSkin("Skin 9", 17);
    AddSkin("Skin 10", 18);
    AddSkin("Skin 11", 19);
    AddSkin("Skin 12", 20);
    AddSkin("Skin 13", 21);
    AddSkin("Skin 14", 22);
    AddSkin("Skin 15", 23);
    AddSkin("Skin 16", 24);
    AddSkin("Skin 17", 25);
    AddSkin("Skin 18", 26);
    AddSkin("Skin 19", 28);
    AddSkin("Skin 20", 29);
    AddSkin("Skin 21", 30);
    AddSkin("Skin 22", 31);
    AddSkin("Skin 23", 32);
    AddSkin("Skin 24", 33);
    AddSkin("Skin 25", 34);
    AddSkin("Skin 26", 35);
    AddSkin("Skin 27", 36);
    AddSkin("Skin 28", 37);
    AddSkin("Skin 29", 38);
    AddSkin("Skin 30", 39);
    AddSkin("Skin 31", 40);
    AddSkin("Skin 32", 41);
    AddSkin("Skin 33", 43);
    AddSkin("Skin 34", 44);
	return true;
}

public InitTowns()
{
	//Name, PositionX, PositionY, PositionZ, PositionFacing, HospitalPositionX, HospitalPositionY, HospitalPositionZ, HospitalPositionFacing
	AddTown("Los Santos", 1685.9139, -2241.7817, 13.5469, 180.0000, 1172.9609, -1323.4269, 15.3983, 270.0000);
	return true;
}

public InitVehicleTypes()
{
	//Name, Model, Price, Type, MaxPlaces, MaxPetrol, Profession
	//Cars
	AddVehicleType("Los-Santos-Polizeiauto", 		596, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("San-Fierro-Polizeiauto", 		597, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Las-Venturas-Polizeiauto", 		598, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Gelände-Polizeiauto", 			599, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("FBI-Rancher", 					490, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("FBI-Truck", 					528, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Enforcer", 						427, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Geldtransporter", 				428, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Feuerwehrwagen", 				544, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Krankenwagen", 					416, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Patriot", 						470, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Barracks", 						433, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Baggage", 						485, 0, VEHICLE_TYPE_TYPE_CAR, 1, 100, -1);
	AddVehicleType("Stretch", 						409, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Broadway", 						575, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Traktor", 						610, 0, VEHICLE_TYPE_TYPE_CAR, 1, 100, -1);
	AddVehicleType("Mähdrescher", 					532, 0, VEHICLE_TYPE_TYPE_CAR, 1, 100, -1);
	AddVehicleType("Bulldozer", 					486, 0, VEHICLE_TYPE_TYPE_CAR, 1, 100, -1);
	AddVehicleType("Taxi", 							420, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Linerunner", 					403, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Sentinel", 						405, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Cheetah", 						415, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Infernus", 						411, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Comet", 						480, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Washington", 					421, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Admiral", 						445, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Stallion", 						439, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Yankee", 						456, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Rumpo", 						440, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Greenwood", 					492, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Landstalker", 					400, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Voodo", 						412, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Slamvan", 						535, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1); //0.2
	AddVehicleType("Clover", 						542, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Sunrise", 						550, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Monstertruck", 					444, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	AddVehicleType("Virgo", 						491, 0, VEHICLE_TYPE_TYPE_CAR, 4, 100, -1);
	AddVehicleType("Bus", 							431, 0, VEHICLE_TYPE_TYPE_CAR, 6, 100, -1);
	AddVehicleType("Walton", 						478, 0, VEHICLE_TYPE_TYPE_CAR, 2, 100, -1);
	//Motorbikes
	AddVehicleType("Polizei-PCJ-600", 				523, 0, VEHICLE_TYPE_TYPE_MOTORBIKE, 2, 100, -1);
	AddVehicleType("Pizzaboy", 						448, 0, VEHICLE_TYPE_TYPE_MOTORBIKE, 2, 100, -1);
	AddVehicleType("Sanchez", 						468, 0, VEHICLE_TYPE_TYPE_MOTORBIKE, 2, 100, -1);
	AddVehicleType("PCJ-600", 						461, 0, VEHICLE_TYPE_TYPE_MOTORBIKE, 2, 100, -1);
	AddVehicleType("Freeway", 						463, 0, VEHICLE_TYPE_TYPE_MOTORBIKE, 2, 100, -1);
	AddVehicleType("FCR-900", 						521, 0, VEHICLE_TYPE_TYPE_MOTORBIKE, 2, 100, -1); //0.2
	AddVehicleType("NRG-500", 						522, 0, VEHICLE_TYPE_TYPE_MOTORBIKE, 2, 100, -1);
	//Bikes
	AddVehicleType("BMX", 							481, 0, VEHICLE_TYPE_TYPE_BIKE, 1, 100, -1);
	AddVehicleType("Bike", 							509, 0, VEHICLE_TYPE_TYPE_BIKE, 1, 100, -1); //0.2
	//Boats
	AddVehicleType("Schlauchboot", 					473, 0, VEHICLE_TYPE_TYPE_BOAT, 2, 100, -1);
	AddVehicleType("Tropic", 						454, 0, VEHICLE_TYPE_TYPE_BOAT, 1, 100, -1);
	AddVehicleType("Launch", 						595, 0, VEHICLE_TYPE_TYPE_BOAT, 1, 100, -1); //0.2
	AddVehicleType("Jatmax",						493, 0, VEHICLE_TYPE_TYPE_BOAT, 2, 100, -1);
	//Helicopters
	AddVehicleType("Polizei-Maverick", 				497, 0, VEHICLE_TYPE_TYPE_HELICOPTER, 4, 100, -1);
	AddVehicleType("Hunter", 						425, 0, VEHICLE_TYPE_TYPE_HELICOPTER, 1, 100, -1);
	AddVehicleType("Leviathn", 						417, 0, VEHICLE_TYPE_TYPE_HELICOPTER, 1, 100, -1);
	AddVehicleType("Raindance", 					563, 0, VEHICLE_TYPE_TYPE_HELICOPTER, 2, 100, -1);
	AddVehicleType("Maverick", 						487, 0, VEHICLE_TYPE_TYPE_HELICOPTER, 4, 100, -1);
	AddVehicleType("Seasparrow", 					447, 0, VEHICLE_TYPE_TYPE_HELICOPTER, 2, 100, -1);
	AddVehicleType("Sparrow", 						469, 0, VEHICLE_TYPE_TYPE_HELICOPTER, 2, 100, -1); //0.2
	//Planes
	AddVehicleType("Hydra", 						520, 0, VEHICLE_TYPE_TYPE_PLANE, 1, 100, -1);
	AddVehicleType("Andromeda", 					592, 0, VEHICLE_TYPE_TYPE_PLANE, 1, 100, -1);
	AddVehicleType("Shamal", 						519, 0, VEHICLE_TYPE_TYPE_PLANE, 1, 100, -1);
	AddVehicleType("Dodo", 							593, 0, VEHICLE_TYPE_TYPE_PLANE, 2, 100, -1);
	AddVehicleType("Rustler",						476, 0, VEHICLE_TYPE_TYPE_PLANE, 1, 100, -1); //0.2
	AddVehicleType("Nevada", 						553, 0, VEHICLE_TYPE_TYPE_PLANE, 1, 100, -1);
	AddVehicleType("Stunt", 						513, 0, VEHICLE_TYPE_TYPE_PLANE, 1, 100, -1);
	//Trains
	AddVehicleType("Straßenbahn", 					449, 0, VEHICLE_TYPE_TYPE_TRAIN, 10, 100, -1); //0.2
	AddVehicleType("?", 							537, 0, VEHICLE_TYPE_TYPE_TRAIN, 10, 100, -1);
	AddVehicleType("?",								538, 0, VEHICLE_TYPE_TYPE_TRAIN, 10, 100, -1);
	AddVehicleType("?", 							569, 0, VEHICLE_TYPE_TYPE_TRAIN, 10, 100, -1);
	return true;
}

public InitVehicles()
{
	//Type, PositionX, PositionY, PositionZ, Facing, Colour0, Colour1
	//--Los Santos--
    //International
    AddVehicle(VEHICLE_TYPE_TAXI, 1670.3711, -2248.9944, 13.3860, 90.0000, -1, -1); //Taxi
    AddVehicle(VEHICLE_TYPE_TAXI, 1663.0160, -2249.2808, 13.1633, 90.0000, -1, -1); //Taxi
    AddVehicle(VEHICLE_TYPE_TAXI, 1713.6833, -2249.1399, 13.1815, 90.0000, -1, -1); //Taxi
    AddVehicle(VEHICLE_TYPE_TAXI, 1669.1349, -2260.4917, 13.2062, 127.2915, -1, -1); //Taxi
    AddVehicle(VEHICLE_TYPE_SENTINEL, 1560.2263, -2254.2881, 13.2684, 90.0000, -1, -1); //Sentinel
    AddVehicle(VEHICLE_TYPE_CLOVER, 1552.7882, -2211.7656, 13.2757, 0.0000, -1, -1); //Clover
    AddVehicle(VEHICLE_TYPE_GREENWOOD, 1536.5004, -2212.0127, 13.2763, 180.0000, -1, -1); //Greenwood
    AddVehicle(VEHICLE_TYPE_STALLION, 1515.4817, -2211.4873, 13.2744, 0.0000, -1, -1); //Stallion
    AddVehicle(VEHICLE_TYPE_SUNRISE, 1508.9436, -2211.5518, 13.2720, 0.0000, -1, -1); //Sunrise
    AddVehicle(VEHICLE_TYPE_NRG500, 1486.6431, -2211.5596, 13.2679, 0.0000, -1, -1); //NRG 500
    AddVehicle(VEHICLE_TYPE_WALTON, 1560.3623, -2312.2944, 13.2676, 270.0000, -1, -1); //Walton
    AddVehicle(VEHICLE_TYPE_VIRGO, 1560.5142, -2325.1299, 13.2695, 270.0000, -1, -1); //Virgo
    AddVehicle(VEHICLE_TYPE_ADMIRAL, 1560.5043, -2335.1182, 13.2689, 90.0000, -1, -1); //Admiral
    AddVehicle(VEHICLE_TYPE_RUMPO, 1556.3088, -2360.6660, 13.2757, 180.0000, -1, -1); //Rump
    AddVehicle(VEHICLE_TYPE_LANDSTALKER, 1533.0657, -2361.1648, 13.2743, 0.0000, -1, -1); //Landstalker
    AddVehicle(VEHICLE_TYPE_COMET, 1508.8591, -2361.2207, 13.2724, 0.0000, -1, -1); //Comet
    AddVehicle(VEHICLE_TYPE_SLAMVAN, 1454.5303, -2347.9583, 13.2680, 0.0000, -1, -1); //Slamvan
    AddVehicle(VEHICLE_TYPE_SENTINEL, 1451.2201, -2347.8337, 13.2698, 0.0000, -1, -1); //Sentinel
    AddVehicle(VEHICLE_TYPE_BROADWAY, 1438.1528, -2347.8057, 13.2677, 180.0000, -1, -1); //Broadway
    AddVehicle(VEHICLE_TYPE_SUNRISE, 1398.1323, -2365.1807, 13.2668, 180.0000, -1, -1); //Sunrise
    AddVehicle(VEHICLE_TYPE_STALLION, 1365.4855, -2365.5635, 13.2668, 270.0000, -1, -1); //Stallion
    AddVehicle(VEHICLE_TYPE_YANKEE, 1365.2352, -2337.1421, 13.2682, 270.0000, -1, -1); //Yankee
    AddVehicle(VEHICLE_TYPE_VOODO, 1365.1487, -2334.1643, 13.2694, 90.0000, -1, -1); //Voodo
    AddVehicle(VEHICLE_TYPE_VIRGO, 1365.1696, -2316.1519, 13.2682, 270.0000, -1, -1); //Virgo
    AddVehicle(VEHICLE_TYPE_CLOVER, 1391.7639, -2313.5103, 13.2681, 0.0000, -1, -1); //Clover
    AddVehicle(VEHICLE_TYPE_BIKE, 1675.2601, -2370.2014, 13.2654, 270.0000, -1, -1); //Bike
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1779.5592, -2331.8870, 13.1885, 180.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1792.0298, -2332.6570, 13.1822, 270.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_AMBULANCE, 1583.3491, -2285.0132, 13.2623, 0.0000, -1, -1); //Ambulance
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1595.5721, -2240.7075, 13.2736, 0.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_BIKE, 1608.5963, -2274.7322, 13.2399, 180.0000, -1, -1); //Bike
    AddVehicle(VEHICLE_TYPE_BMX, 1616.7656, -2276.2666, 13.2330, 270.0000, -1, -1); //BMX
    AddVehicle(VEHICLE_TYPE_BUS, 1539.7130, -2310.4421, 13.2661, 180.0000, -1, -1); //Bus
    AddVehicle(VEHICLE_TYPE_BUS, 1424.3235, -2363.0422, 13.3225, 270.0000, -1, -1); //Bus
    AddVehicle(VEHICLE_TYPE_GREENWOOD, 1411.0883, -2347.8340, 13.3181,180.0000, -1, -1); //Greenwood
    AddVehicle(VEHICLE_TYPE_PCJ600, 1404.7679, -2330.8625, 13.3260, 180.0000, -1, -1); //PCJ 600
    AddVehicle(VEHICLE_TYPE_SUNRISE, 1401.3392, -2330.8684, 13.3261, 0.0000, -1, -1); //Sunrise
    AddVehicle(VEHICLE_TYPE_MAVERICK, 1958.0753, -2643.2769, 13.7178, 0.0000, -1, -1); //Maverick
    AddVehicle(VEHICLE_TYPE_MAVERICK, 1973.2926, -2642.9802, 13.7228, 0.0000, -1, -1); //Maverick
    AddVehicle(VEHICLE_TYPE_MAVERICK, 1986.8037, -2642.2649, 13.5469, 0.0000, -1, -1); //Maverick
    AddVehicle(VEHICLE_TYPE_ANDROMEDA, 2038.2365, -2494.1038, 13.1480, 90.0000, -1, -1); //Andromeda
    AddVehicle(VEHICLE_TYPE_SHAMAL, 1554.0203, -2631.7712, 14.4693, 0.0000, -1, -1); //Shamal
    AddVehicle(VEHICLE_TYPE_SHAMAL, 1525.7642, -2631.2559, 14.4685, 0.0000, -1, -1); //Shamal
    AddVehicle(VEHICLE_TYPE_SHAMAL, 1499.2665, -2630.6621, 13.5469, 0.0000, -1, -1); //Shamal
    //Ocean Docks
	//Santa Maria Beach
	//Verona Beach
 	//Verdant Bluffs
 	AddVehicle(VEHICLE_TYPE_GREENWOOD, 1662.8031, -2111.7715, 13.3252, 270.0000, -1, -1); //Greenwood
 	AddVehicle(VEHICLE_TYPE_VOODO, 1695.6638, -2141.3176, 13.3263, 90.0000, -1, -1); //Voodo
 	AddVehicle(VEHICLE_TYPE_SLAMVAN, 1747.5055, -2081.4224, 13.3347, 0.0000, -1, -1); //Slamvan
 	AddVehicle(VEHICLE_TYPE_BIKE, 1786.1587, -2125.1729, 13.5469, 270.0000, -1, -1); //Bike
 	AddVehicle(VEHICLE_TYPE_FREEWAY, 1809.6106, -2095.4373, 13.5469, 0.0000, -1, -1); //Freeway
	AddVehicle(VEHICLE_TYPE_RAINDANCE, 1116.1652, -2023.9308, 74.5092, 180.0000, -1, -1); //Raindance
	AddVehicle(VEHICLE_TYPE_STRETCH, 1248.6471, -2043.1094, 59.5495, 270.0000, 0, 0); //Black Stretch
	AddVehicle(VEHICLE_TYPE_SENTINEL, 1275.8636, -2038.2396, 59.0299, 90.0000, 0, 0); //Black Sentinel
	AddVehicle(VEHICLE_TYPE_SENTINEL, 1275.8969, -2035.5332, 58.8939, 90.0000, 0, 0); //Black Sentinel
	AddVehicle(VEHICLE_TYPE_STRETCH, 1276.8378, -2015.6171, 58.7391, 0.0000, 0, 0); //Black Stretch
	AddVehicle(VEHICLE_TYPE_POLICE_LS, 1246.3464, -2026.7452, 59.6913, 270.0000, -1, -1); //Los Santos Police Car
	AddVehicle(VEHICLE_TYPE_POLICE_LS, 1245.8882, -2023.9542, 59.5506, 90.0000, -1, -1); //Los Santos Police Car
	//El Corona
	//Willofield
	//Playa Del Seville
    //Rodeo
    //Marina
    //Market
    AddVehicle(VEHICLE_TYPE_AMBULANCE, 1190.2617, -1332.5568, 13.5690, 180.0000, -1, -1); //Ambulance
    AddVehicle(VEHICLE_TYPE_AMBULANCE, 1147.0475, -1350.1648, 13.6280, 180.0000, -1, -1); //Ambulance
    AddVehicle(VEHICLE_TYPE_AMBULANCE, 1144.5028, -1311.3098, 13.6465, 90.0000, -1, -1); //Ambulance
    AddVehicle(VEHICLE_TYPE_AMBULANCE, 1144.1191, -1303.8887, 13.6387, 90.0000, -1, -1); //Ambulance
    //Conference Center
    //Commerce
    AddVehicle(VEHICLE_TYPE_STALLION, 1648.4962, -1721.0918, 20.4772, 270.0000, -1, -1); //Stallion
	AddVehicle(VEHICLE_TYPE_GREENWOOD, 1670.3870, -1719.4589, 20.4844, 0.0000, -1, -1); //Greenwood
	AddVehicle(VEHICLE_TYPE_ADMIRAL, 1672.3376, -1707.8557, 20.4844, 90.0000, -1, -1); //Admiral
	AddVehicle(VEHICLE_TYPE_LANDSTALKER, 1672.2875, -1703.3910, 20.4844, 90.0000, -1, -1); //Landstalker
	AddVehicle(VEHICLE_TYPE_PCJ600, 1645.4845, -1696.1078, 20.4600, 270.0000, -1, -1); //PCJ 600
	AddVehicle(VEHICLE_TYPE_FREEWAY, 1645.4845, -1696.1078, 20.4600, 270.0000, -1, -1); //Freeway
    AddVehicle(VEHICLE_TYPE_SENTINEL, 1499.3171, -1487.4539, 13.5524, 180.0000, -1, -1); //Sentinel
	AddVehicle(VEHICLE_TYPE_WASHINGTON, 1511.4849, -1485.8947, 13.5508, 270.0000, -1, -1); //Washington
	AddVehicle(VEHICLE_TYPE_LANDSTALKER, 1521.2889, -1502.8789, 13.5547, 0.0000, -1, -1); //Landstalker
    AddVehicle(VEHICLE_TYPE_FBI_RANCHER, 1507.8854, -1751.4948, 13.5469, 180.0000, -1, -1); //FBI Rancher
	AddVehicle(VEHICLE_TYPE_SENTINEL, 1455.0243, -1750.6353, 13.5469, 0.0000, 0, 0); //Black Sentinel
	AddVehicle(VEHICLE_TYPE_FBI_RANCHER, 1407.0245, -1800.3021, 13.5469, 90.0000, -1, -1); //FBI Rancher
	AddVehicle(VEHICLE_TYPE_FBI_RANCHER, 1407.0508, -1792.9808, 13.5469, 90.0000, -1, -1); //FBI Rancher
	AddVehicle(VEHICLE_TYPE_ENFORCER, 1408.2721, -1780.6451, 13.5469, 0.0000, -1, -1); //Enforcer
	AddVehicle(VEHICLE_TYPE_FBI_TRUCK, 1554.7969, -1793.5983, 13.5469, 270.0000, -1, -1); //FBI Truck
    AddVehicle(VEHICLE_TYPE_FBI_TRUCK, 1555.1666, -1789.0660, 13.5469, 270.0000, -1, -1); //FBI Truck
    AddVehicle(VEHICLE_TYPE_ENFORCER, 1549.6038, -1771.4739, 13.5469, 270.0000, -1, -1); //Enforcer
    //Pershing Square
	AddVehicle(VEHICLE_TYPE_POLICE_LS, 1530.4833, -1644.4636, 5.6123, 180.0000, -1, -1); //Los Santos Police Car
	AddVehicle(VEHICLE_TYPE_POLICE_LS, 1534.6205, -1644.7362, 5.6111, 180.0000, -1, -1); //Los Santos Police Car
	AddVehicle(VEHICLE_TYPE_POLICE_LS, 1602.1212, -1695.7866, 5.6110, 270.0000, -1, -1); //Los Santos Police Car
	AddVehicle(VEHICLE_TYPE_POLICE_LS, 1529.3235, -1683.5609, 5.6119, 90.0000, -1, -1); //Los Santos Police Car
	AddVehicle(VEHICLE_TYPE_SENTINEL, 1564.9846, -1711.2965, 5.6109, 0.0000, -1, -1); //Sentinel
	AddVehicle(VEHICLE_TYPE_POLICE_LS, 1601.6823, -1683.8691, 5.6124, 90.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1601.8087, -1687.6761, 5.6089, 90.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1592.9950, -1606.0215, 13.1094, 180.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1596.4111, -1605.5631, 13.1444, 0.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1555.2758, -1606.0461, 13.3828, 180.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1560.2649, -1606.0535, 13.1044, 180.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1565.9717, -1605.9940, 13.1041, 180.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1570.4695, -1606.0879, 13.1041, 180.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_ENFORCER, 1604.7206, -1628.5928, 13.5162, 0.0000, -1, -1); //Enforcer
    AddVehicle(VEHICLE_TYPE_POLICE_MAVERICK, 1517.6246, -1653.1888, 13.5392, 180.0000, -1, -1); //Police Maverick
    AddVehicle(VEHICLE_TYPE_POLICE_LS, 1539.1902, -1693.6447, 13.5469, 0.0000, -1, -1); //Los Santos Police Car
    AddVehicle(VEHICLE_TYPE_POLICE_PCJ600, 1541.5620, -1665.0200, 13.5528, 90.0000, -1, -1); //Police PCJ 600
    AddVehicle(VEHICLE_TYPE_POLICE_PCJ600, 1541.9049, -1660.8546, 13.5535, 90.0000, -1, -1); //Police PCJ 600
    //Little-Mexico
    AddVehicle(VEHICLE_TYPE_YANKEE, 1732.5609, -1749.4478, 13.6946, 180.0000, -1, -1); //Yankee
	AddVehicle(VEHICLE_TYPE_STRETCH, 1795.4769, -1811.4662, 13.1103, 270.0000, -1, -1); //Stretch
	AddVehicle(VEHICLE_TYPE_YANKEE, 1773.6316, -1691.6869, 13.4322, 180.0000, -1, -1); //Yankee
	AddVehicle(VEHICLE_TYPE_RUMPO, 1782.1404, -1692.3258, 13.4538, 180.0000, -1, -1); //Rumpo
	AddVehicle(VEHICLE_TYPE_RUMPO, 1807.1053, -1699.3168, 13.5464, 0.0000, -1, -1); //Rumpo
    //Idlewood
    AddVehicle(VEHICLE_TYPE_STRETCH, 1826.9764, -1653.2554, 13.5469, 0.0000, -1, -1); //Stretch
    AddVehicle(VEHICLE_TYPE_STRETCH, 1911.7198, -1650.1871, 13.3664, 180.0000, -1, -1); //Stretch
    AddVehicle(VEHICLE_TYPE_INFERNUS, 1912.9202, -1688.0942, 13.3934, 270.0000, -1, -1); //Infernus
    AddVehicle(VEHICLE_TYPE_COMET, 1912.9063, -1695.2736, 13.3931, 270.0000, -1, -1); //Comet
    AddVehicle(VEHICLE_TYPE_CHEETAH, 1912.8938, -1702.7794, 13.3945, 270.0000, -1, -1); //Cheetah
    AddVehicle(VEHICLE_TYPE_BROADWAY, 1911.3481, -1725.7162, 13.3575, 180.0000, -1, -1); //Broadway
    //Ganton
    //East Beach
    AddVehicle(VEHICLE_TYPE_LANDSTALKER, 2706.7275, -1843.2268, 9.3904, 339.7137, -1, -1); //Landstalker
	AddVehicle(VEHICLE_TYPE_COMET, 2715.4780, -1846.2919, 9.2978, 159.5335, -1, -1); //Comet
	AddVehicle(VEHICLE_TYPE_BROADWAY, 2742.3586, -1875.0513, 9.5350, 0.0000, -1, -1); //Broadway
	AddVehicle(VEHICLE_TYPE_WASHINGTON, 2767.1348, -1875.9606, 9.6356, 180.0000, -1, -1); //Washington
	AddVehicle(VEHICLE_TYPE_GREENWOOD, 2775.6223, -1840.7766, 9.6717, 22.3293, -1, -1); //Greenwood
	AddVehicle(VEHICLE_TYPE_LANDSTALKER, 2810.1162, -1822.6460, 9.8202, 270.0000, -1, -1); //Landstalker
	AddVehicle(VEHICLE_TYPE_RUMPO, 2825.7175, -1713.8022, 9.9030, 255.2369, -1, -1); //Rumpo
	AddVehicle(VEHICLE_TYPE_ADMIRAL, 2827.6738, -1709.2706, 9.9018, 259.5576, -1, -1); //Admiral
	AddVehicle(VEHICLE_TYPE_STALLION, 2822.6057, -1672.4908, 9.8546, 0.0000, -1, -1); //Stallion
	AddVehicle(VEHICLE_TYPE_TAXI, 2797.3320, -1671.9769, 9.8040, 0.0000, -1, -1); //Taxi
	AddVehicle(VEHICLE_TYPE_SENTINEL, 2656.6316, -1701.3701, 9.2089, 90.0000, -1, -1); //Sentinel
	AddVehicle(VEHICLE_TYPE_GREENWOOD, 2817.8054, -1452.8832, 15.9087, 270.0000, -1, -1); //Greenwood
	AddVehicle(VEHICLE_TYPE_YANKEE, 2818.3340, -1428.4021, 16.3349, 0.0000, -1, -1); //Yankee
	AddVehicle(VEHICLE_TYPE_GREENWOOD, 2792.0146, -1430.4363, 19.9620, 90.0000, -1, -1); //Greenwood
	AddVehicle(VEHICLE_TYPE_BROADWAY, 2817.0645, -1457.2007, 20.2188, 270.0000, -1, -1); //Broadway
	AddVehicle(VEHICLE_TYPE_TAXI, 2818.9385, -1441.0734, 20.2188, 0.0000, -1, -1); //Taxi
	AddVehicle(VEHICLE_TYPE_INFERNUS, 2803.5007, -1428.0167, 19.9018, 0.0000, -1, -1); //Infernus
	AddVehicle(VEHICLE_TYPE_STALLION, 2817.7014, -1461.8860, 27.9358, 270.0000, -1, -1); //Stallion
    AddVehicle(VEHICLE_TYPE_VOODO, 2816.6558, -1430.1339, 24.1875, 360.0000, -1, -1); //Voodo
    AddVehicle(VEHICLE_TYPE_RUMPO, 2797.8052, -1427.1819, 28.1563, 270.0000, -1, -1); //Rumpo
    AddVehicle(VEHICLE_TYPE_LANDSTALKER, 2817.6597, -1445.2469, 28.1563, 270.0000, -1, -1); //Landstalker
    AddVehicle(VEHICLE_TYPE_BROADWAY, 2817.5298, -1458.4392, 32.1250, 270.0000, -1, -1); //Broadway
    AddVehicle(VEHICLE_TYPE_FREEWAY, 2816.2927, -1428.5522, 32.1250, 0.0000, -1, -1); //Freeway
    AddVehicle(VEHICLE_TYPE_PCJ600, 2813.1404, -1427.9099, 32.1250, 0.0000, -1, -1); //PCJ 600
    AddVehicle(VEHICLE_TYPE_VOODO, 2815.3398, -1461.3910, 36.0882, 270.0000, -1, -1); //Voodo
    AddVehicle(VEHICLE_TYPE_GREENWOOD, 2816.5676, -1455.7477, 36.0938, 270.0000, -1, -1); //Greenwood
    AddVehicle(VEHICLE_TYPE_SANCHEZ, 2815.4348, -1429.6841, 36.0938, 0.0000, -1, -1); //Sanchez
    AddVehicle(VEHICLE_TYPE_ADMIRAL, 2811.8188, -1429.2314, 36.0938, 0.0000, -1, -1); //Admiral
    AddVehicle(VEHICLE_TYPE_WASHINGTON, 2792.9531, -1432.5525, 36.0938, 90.0000, -1, -1); //Washington
    AddVehicle(VEHICLE_TYPE_STALLION, 2816.6528, -1451.0070, 40.0625, 270.0000, -1, -1); //Stallion
    AddVehicle(VEHICLE_TYPE_VOODO, 2813.3955, -1430.1212, 40.0625, 0.0000, -1, -1); //Voodo
    AddVehicle(VEHICLE_TYPE_SENTINEL, 2815.5647, -1429.7836, 40.0625, 0.0000, -1, -1); //Sentinel
    //Richman
    //Vinewood
    //Downtown Los Santos
    AddVehicle(VEHICLE_TYPE_MAVERICK, 1545.2195, -1353.4800, 329.4740, 90.0000, -1, -1); //Maverick
    AddVehicle(VEHICLE_TYPE_LANDSTALKER, 1597.9718, -1324.8159, 17.4728, 0.0000, -1, -1); //Landstalker
	AddVehicle(VEHICLE_TYPE_ADMIRAL, 1502.8937, -1323.7520, 13.9239, 270.0000, -1, -1); //Admrial
	AddVehicle(VEHICLE_TYPE_WASHINGTON, 1503.1013, -1326.8649, 13.9116, 270.0000, -1, -1); //Washington
	AddVehicle(VEHICLE_TYPE_SENTINEL, 1502.7839, -1329.9807, 13.9039, 270.0000, -1, -1); //Sentinel
	AddVehicle(VEHICLE_TYPE_INFERNUS, 1502.8948, -1333.1876, 13.7334, 270.0000, -1, -1); //Infernus
	AddVehicle(VEHICLE_TYPE_COMET, 1501.4458, -1357.4072, 13.8258, 180.0000, -1, -1); //Comet
    //Glen Park
    //Jefferson
    AddVehicle(VEHICLE_TYPE_BROADWAY, 2205.3987, -1160.6458, 25.7350, 270.0000, -1, -1); //Broadway
    AddVehicle(VEHICLE_TYPE_SENTINEL, 2228.8569, -1173.2418, 25.7266, 90.0000, -1, -1); //Sentinel
    AddVehicle(VEHICLE_TYPE_BROADWAY, 2238.0281, -1146.8916, 25.7969, 80.9932, -1, -1); //Broadway
    AddVehicle(VEHICLE_TYPE_STRETCH, 2205.8269, -1177.1563, 25.3315, 270.0000, -1, -1); //Stretch
    //East Los Santos
    //Temple
    //Mulholland
    //Mulholland Intersection
    //Las Colinas
    AddVehicle(VEHICLE_TYPE_SANCHEZ, 1997.1050, -1092.3336, 24.7948, 76.4686, -1, -1); //Sanchez
    AddVehicle(VEHICLE_TYPE_BMX, 1953.0685, -1119.1069, 26.8359, 90.0000, -1, -1); //BMX
    AddVehicle(VEHICLE_TYPE_BMX, 1936.3289, -1116.6875, 26.4531, 180.0000, -1, -1); //BMX
    AddVehicle(VEHICLE_TYPE_VOODO, 2077.2632, -974.8956, 49.7020, 80.0000, -1, -1); //Voodo
    AddVehicle(VEHICLE_TYPE_STALLION, 2193.3284, -1057.2145, 48.1650, 225.0000, -1, -1); //Stallion
    AddVehicle(VEHICLE_TYPE_BROADWAY, 2193.3284, -1057.2145, 48.1650, 225.0000, -1, -1); //Broadway
    AddVehicle(VEHICLE_TYPE_VOODO, 2278.5063, -1109.6521, 37.9766, 157.1732, -1, -1); //Voodo
    AddVehicle(VEHICLE_TYPE_BMX, 2291.0901, -1048.4482, 49.5156, 334.5216, -1, -1); //BMX
    AddVehicle(VEHICLE_TYPE_BMX, 2197.2920, -1104.4503, 25.1664, 244.8607, -1, -1); //BMX
    //Los Flores
    //--San Fierro--
    //--Las Venturas--
    //--Red County--
    //--Flint County--
	//--Whetstone--
    AddVehicle(VEHICLE_TYPE_SANCHEZ, -1453.3964, -1547.8192, 101.7578, 90.0000, 0, 0); //Black Sanchez
    AddVehicle(VEHICLE_TYPE_SANCHEZ, -1462.5223, -1564.0818, 101.7578, 31.3570, 0, 0); //Black Sanchez
    AddVehicle(VEHICLE_TYPE_TRACTOR, -1415.6198, -1541.2661, 101.7208, 270.0000, -1, -1); //Tractor
    AddVehicle(VEHICLE_TYPE_STRETCH, -1446.4480, -1500.2825, 101.5578, 180.0000, 0, 0); //Black Stretch
    AddVehicle(VEHICLE_TYPE_SENTINEL, -1407.6486, -1479.8547, 101.7790, 21.9803, 0, 0); //Black Sentinel
    AddVehicle(VEHICLE_TYPE_SENTINEL, -1409.1006, -1464.4491, 101.3718, 180.0000, 0, 0); //Black Sentinel
    AddVehicle(VEHICLE_TYPE_SANCHEZ, -1428.8105, -1461.6260, 101.6640, 270.0000, 0, 0); //Black Sanchez
    AddVehicle(VEHICLE_TYPE_SANCHEZ, -1428.0750, -1464.3359, 101.6732, 270.0000, 0, 0); //Black Sanchez
    AddVehicle(VEHICLE_TYPE_MAVERICK, -1459.7290, -1460.2300, 101.7578, 180.0000, 0, 33); //Black Maverick
	//--Tierra Robada--
    //--Bone County--
	AddVehicle(VEHICLE_TYPE_PATRIOT, 220.3935, 1920.6572, 17.6345, 180.0000, -1, -1); //Patriot
    AddVehicle(VEHICLE_TYPE_PATRIOT, 211.0884, 1920.8020, 17.6351, 180.0000, -1, -1); //Patriot
    AddVehicle(VEHICLE_TYPE_PATRIOT, 202.5714, 1920.7163, 17.6352, 180.0000, -1, -1); //Patriot
    AddVehicle(VEHICLE_TYPE_PATRIOT, 193.7732, 1920.4568, 17.6314, 180.0000, -1, -1); //Patriot
    AddVehicle(VEHICLE_TYPE_BARRACKS, 181.7327, 1937.3770, 17.9246, 90.0000, -1, -1); //Barracks
    AddVehicle(VEHICLE_TYPE_BARRACKS, 151.4475, 1827.9044, 17.6481, 90.0000, -1, -1); //Barracks
    AddVehicle(VEHICLE_TYPE_BARRACKS, 152.3484, 1806.4818, 18.0773, 0.0000, -1, -1); //Barracks
    AddVehicle(VEHICLE_TYPE_PATRIOT, 210.9567, 1816.8423, 18.0773, 270.0000, -1, -1); //Patriot
    AddVehicle(VEHICLE_TYPE_BARRACKS, 146.0546, 1933.1017, 19.2301, 68.9691, -1, -1); //Barracks
    AddVehicle(VEHICLE_TYPE_BARRACKS, 127.5684, 1932.9077, 19.2499, 180.0000, -1, -1); //Barracks
	AddVehicle(VEHICLE_TYPE_HUNTER, 336.5463, 1853.9818, 17.8087, 90.0000, -1, -1); //Hunter
    AddVehicle(VEHICLE_TYPE_HUNTER, 335.3385, 1869.0436, 17.6904, 90.0000, -1, -1); //Hunter
    AddVehicle(VEHICLE_TYPE_HYDRA, 275.9253, 1956.9890, 17.6406, 270.0000, -1, -1); //Hydra
    AddVehicle(VEHICLE_TYPE_HYDRA, 274.3188, 1988.7749, 17.6406, 270.0000, -1, -1); //Hydra
    AddVehicle(VEHICLE_TYPE_HYDRA, 274.8241, 2024.0774, 17.6406, 270.0000, -1, -1); //Hydra
    AddVehicle(VEHICLE_TYPE_LEVITHAN, 234.2631, 1989.3975, 18.5161, 163.3571, -1, -1); //Leviathn
    AddVehicle(VEHICLE_TYPE_BARRACKS, 215.2736, 1989.0736, 17.6406, 211.0457, -1, -1); //Barracks
    AddVehicle(VEHICLE_TYPE_MAVERICK, 233.1604, 2019.0559, 17.6479, 270.0000, 0, 0); //Black Maverick
    //Test
    //AddVehicle(1, 1684.6003, -2258.9709, 13.6087, 74.0000, -1, -1); //Maverick
	return true;
}

public InitWeaponTypes()
{
	//Name, Model, Price, Type, Ammo, GeneralAmmo
	//-- Weapon Types --
	//Meeles
    AddWeaponType("Schlagring", 				1, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Messer", 					4, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Schlagstock", 				3, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Baseball-Schläger", 			5, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Katana", 					8, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Golf-Schläger", 				2, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Schaufel", 					6, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Pool-Stock", 				7, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Chainsaw", 					9, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Dildo 1", 					10, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Dildo 2", 					11, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Vibrator 1", 				12, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Vibrator 2", 				13, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Blumen", 					14, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Gehstock", 					15, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    AddWeaponType("Sprühdose", 					41, 100, WEAPON_TYPE_TYPE_MEELE, 500, 500);
    AddWeaponType("Feuerlöscher", 				42, 100, WEAPON_TYPE_TYPE_MEELE, 500, 500);
    AddWeaponType("Kamera", 					43, 100, WEAPON_TYPE_TYPE_MEELE, 50, 50);
    AddWeaponType("Fallschirm", 				46, 100, WEAPON_TYPE_TYPE_MEELE, 0, 0);
    //Pistoles
    AddWeaponType("9mm", 						22, 100, WEAPON_TYPE_TYPE_PISTOL, 24, 24);
    AddWeaponType("9mm mit Schalldämpfer", 		23, 100, WEAPON_TYPE_TYPE_PISTOL, 12, 12);
    AddWeaponType("Desert Eagle", 				24, 100, WEAPON_TYPE_TYPE_PISTOL, 7, 7);
    //Shotguns
    AddWeaponType("Schrotflinte", 				25, 100, WEAPON_TYPE_TYPE_SHOTGUN, 10, 10);
    AddWeaponType("Abgesägte Schrotflinte", 	26, 100, WEAPON_TYPE_TYPE_SHOTGUN, 4, 4);
    AddWeaponType("Spass12", 					27, 100, WEAPON_TYPE_TYPE_SHOTGUN, 7, 7);
    //Micro SMGs
    AddWeaponType("Uzi", 						28, 100, WEAPON_TYPE_TYPE_MICRO_SMG, 100, 100);
    AddWeaponType("Tec9", 						32, 100, WEAPON_TYPE_TYPE_MICRO_SMG, 100, 100);
    //SMGs
    AddWeaponType("MP5", 						29, 100, WEAPON_TYPE_TYPE_SMG, 100, 100);
    //MGs
    AddWeaponType("M4", 						31, 100, WEAPON_TYPE_TYPE_MG, 50, 50);
    AddWeaponType("AK47", 						30, 100, WEAPON_TYPE_TYPE_MG, 30, 30);
    //Rifles
    AddWeaponType("Jagdgewehr", 				33, 100, WEAPON_TYPE_TYPE_RIFLE, 20, 20);
    AddWeaponType("Scharfschützengewehr", 		34, 100, WEAPON_TYPE_TYPE_RIFLE, 10, 10);
    //Heavy Weapons
    AddWeaponType("RPG", 						35, 100, WEAPON_TYPE_TYPE_HEAVY_WEAPON, 1, 1);
    AddWeaponType("Stinger-Raketenwerfer", 		36, 100, WEAPON_TYPE_TYPE_HEAVY_WEAPON, 1, 1);
    AddWeaponType("Flammenwerfer", 				37, 100, WEAPON_TYPE_TYPE_HEAVY_WEAPON, 100, 100);
    AddWeaponType("Minigun", 					38, 100, WEAPON_TYPE_TYPE_HEAVY_WEAPON, 500, 500);
    //Projectiles
    AddWeaponType("Handgranate", 				16, 100, WEAPON_TYPE_TYPE_PROJECTILE, 1, 1);
    AddWeaponType("Tränengas", 					17, 100, WEAPON_TYPE_TYPE_PROJECTILE, 1, 1);
    AddWeaponType("Molotov", 					18, 100, WEAPON_TYPE_TYPE_PROJECTILE, 1, 1);
    AddWeaponType("Rucksackbombe", 				39, 100, WEAPON_TYPE_TYPE_PROJECTILE, 1, 1);
    //Cannon
    AddWeaponType("Explosion", 					-1, 100, WEAPON_TYPE_TYPE_CANNON, 0, 0);
    //Name
    //Weapon Type Types
    AddWeaponTypeType("Nahkampf");
    AddWeaponTypeTypeReason(0);
    AddWeaponTypeTypeReason(1);
    AddWeaponTypeTypeReason(2);
    AddWeaponTypeTypeReason(3);
    AddWeaponTypeTypeReason(4);
    AddWeaponTypeTypeReason(5);
    AddWeaponTypeTypeReason(6);
    AddWeaponTypeTypeReason(7);
    AddWeaponTypeTypeReason(8);
    AddWeaponTypeTypeReason(9);
    AddWeaponTypeTypeReason(10);
    AddWeaponTypeTypeReason(11);
    AddWeaponTypeTypeReason(12);
    AddWeaponTypeTypeReason(13);
    AddWeaponTypeTypeReason(14);
    AddWeaponTypeTypeReason(15);
    AddWeaponTypeTypeReason(41);
    AddWeaponTypeTypeReason(42);
    AddWeaponTypeTypeReason(43);
    AddWeaponTypeTypeReason(44);
    AddWeaponTypeTypeReason(45);
    AddWeaponTypeTypeReason(46);
    AddWeaponTypeTypeReason(47);
    AddWeaponTypeType("Pistolen");
    AddWeaponTypeTypeReason(22);
    AddWeaponTypeTypeReason(23);
    AddWeaponTypeTypeReason(24);
    AddWeaponTypeType("Schrotflinten");
    AddWeaponTypeTypeReason(25);
    AddWeaponTypeTypeReason(26);
    AddWeaponTypeTypeReason(27);
    AddWeaponTypeType("Micro-SMG");
    AddWeaponTypeTypeReason(28);
    AddWeaponTypeTypeReason(32);
    AddWeaponTypeType("SMG");
    AddWeaponTypeTypeReason(29);
    AddWeaponTypeType("Maschinengewehr");
    AddWeaponTypeTypeReason(30);
    AddWeaponTypeTypeReason(31);
    AddWeaponTypeType("Gewehr");
    AddWeaponTypeTypeReason(33);
    AddWeaponTypeTypeReason(34);
    AddWeaponTypeType("Schwere-Waffen");
    AddWeaponTypeTypeReason(35);
    AddWeaponTypeTypeReason(36);
    AddWeaponTypeTypeReason(37);
    AddWeaponTypeTypeReason(38);
    AddWeaponTypeType("Geschoss");
    AddWeaponTypeTypeReason(16);
    AddWeaponTypeTypeReason(17);
    AddWeaponTypeTypeReason(18);
    AddWeaponTypeTypeReason(39);
    AddWeaponTypeType("Kanonen");
    AddWeaponTypeTypeReason(19);
    AddWeaponTypeTypeReason(20);
    AddWeaponTypeTypeReason(21);
	return true;
}

public InitWeapons()
{
	//Model, Type, Ammo, PositionX, PositionY, PositionZ
    //-- Los Santos --
    //International
    //Ocean Docks
	//Santa Maria Beach
	//Verona Beach
 	//Verdant Bluffs
 	//El Corona
	//Willofield
	//Playa Del Seville
    //Rodeo
    //Marina
    //Market
    //Conference Center
    //Commerce
    //Pershing Square
    //Little-Mexico
    //Idlewood
    //Ganton
    //East Beach
    //Richman
    //Vinewood
    //Downtown Los Santos
    //Glen Park
    //Jefferson
    //East Los Santos
    //Temple
    //Mulholland
    //Mulholland Intersection
    //Las Colinas
    //Los Flores
    //-- San Fierro --
    //-- Las Venturas --
    //-- Red County --
    //-- Flint County --
	//-- Whetstone --
	//-- Tierra Robada --
    //-- Bone County --
    return true;
}

public InitProfessions()
{
	//Name, Price
	//Experience, Money, RankPoints
	//Skin, Name, Weapon1, Ammo1, Weapon2, Ammo2, Weapon3, Ammo3
	//Officer
    PROFESSION_OFFICER = AddProfession("Polizist", 6000);
    AddProfessionSkin(280, "LS-Polizist", WEAPON_TYPE_NITESTICK, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_SHOTGUN, 999999);
    AddProfessionSkin(281, "SF-Polizist", WEAPON_TYPE_NITESTICK, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_SHOTGUN, 999999);
    AddProfessionSkin(282, "LV-Polizist", WEAPON_TYPE_NITESTICK, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_SHOTGUN, 999999);
    AddProfessionSkin(283, "Land-Polizist", WEAPON_TYPE_NITESTICK, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_SHOTGUN, 999999);
    AddProfessionSkin(288, "Wüsten-Polizist", WEAPON_TYPE_NITESTICK, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_SHOTGUN, 999999);
    AddProfessionSkin(284, "Mottorrad-Polizist", WEAPON_TYPE_NITESTICK, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_MP5, 999999);
    //Doctor
    PROFESSION_DOCTOR = AddProfession("Arzt", 6000);
    AddProfessionSkin(274, "LS-Sanitäter", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(276, "SF-Sanitäter", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(275, "LV-Sanitäter", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(70, "Arzt", -1, 0, -1, 0, -1, 0);
    //Fireman
    PROFESSION_FIREMAN = AddProfession("Feuerwehrmann", 6000);
    AddProfessionSkin(277, "LS-Feuerwehrmann", WEAPON_TYPE_FIRE_EXTINGUISHER, 999999, -1, 0, -1, 0);
    AddProfessionSkin(279, "SF-Feuerwehrmann", WEAPON_TYPE_FIRE_EXTINGUISHER, 999999, -1, 0, -1, 0);
    AddProfessionSkin(278, "LV-Feuerwehrmann", WEAPON_TYPE_FIRE_EXTINGUISHER, 999999, -1, 0, -1, 0);
    //Taxi Driver
    PROFESSION_TAXI_DRIVER = AddProfession("Taxi-Fahrer", 3000);
    //Worker
    PROFESSION_WORKER = AddProfession("Arbeiter", 5000);
    AddProfessionSkin(27, "Bauarbeiter", WEAPON_TYPE_SHOVEL, 0, -1, 0, -1, 0);
    AddProfessionSkin(16, "Straßenarbeiter 1", WEAPON_TYPE_SHOVEL, 0, -1, 0, -1, 0);
    AddProfessionSkin(260, "Straßenarbeiter 2", WEAPON_TYPE_SHOVEL, 0, -1, 0, -1, 0);
    AddProfessionSkin(153, "Architekt", WEAPON_TYPE_CAMERA, 999999, -1, 0, -1, 0);
    //Criminal
    PROFESSION_CRIMINAL = AddProfession("Verbrecher", 3000);
    //Grove Street Families
    PROFESSION_GS_FAMILIES = AddProfession("Grove Street Families", 6000);
    AddProfessionSkin(105, "Gang-Mitglied 1", WEAPON_TYPE_SPRAY_PAINT, 999999, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_TEC9, 999999);
    AddProfessionSkin(106, "Gang-Mitglied 2", WEAPON_TYPE_SPRAY_PAINT, 999999, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_TEC9, 999999);
    AddProfessionSkin(107, "Gang-Mitglied 3", WEAPON_TYPE_SPRAY_PAINT, 999999, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_TEC9, 999999);
	//Ballas
    PROFESSION_BALLAS = AddProfession("Ballas", 6000);
    AddProfessionSkin(102, "Gang-Mitglied 1", WEAPON_TYPE_BASEBALL_BAT, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_TEC9, 999999);
    AddProfessionSkin(103, "Gang-Mitglied 2", WEAPON_TYPE_BASEBALL_BAT, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_TEC9, 999999);
    AddProfessionSkin(104, "Gang-Mitglied 3", WEAPON_TYPE_BASEBALL_BAT, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_TEC9, 999999);
    //Los Santos Vagos
    PROFESSION_LOS_SANTOS_VAGOS = AddProfession("Los Santos Vagos", 6000);
    AddProfessionSkin(108, "Gang-Mitglied 1", WEAPON_TYPE_BASEBALL_BAT, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_SAWED_OFF_SHOTGUN, 999999);
    AddProfessionSkin(109, "Gang-Mitglied 2", WEAPON_TYPE_BASEBALL_BAT, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_SAWED_OFF_SHOTGUN, 999999);
    AddProfessionSkin(110, "Gang-Mitglied 3", WEAPON_TYPE_BASEBALL_BAT, 0, WEAPON_TYPE_9MM, 999999, WEAPON_TYPE_SAWED_OFF_SHOTGUN, 999999);
    //Varrios Los Aztecas
    PROFESSION_VARRIOS_LOS_AZTECAS = AddProfession("Varrios Los Aztecas", 6000);
    AddProfessionSkin(114, "Gang-Mitglied 1", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(115, "Gang-Mitglied 2", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(116, "Gang-Mitglied 3", -1, 0, -1, 0, -1, 0);
    //San Fierro Rifa
    PROFESSION_SAN_FIERRO_RIFA = AddProfession("San Fierro Rifa", 6000);
    AddProfessionSkin(173, "Gang-Mitglied 1", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(174, "Gang-Mitglied 2", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(175, "Gang-Mitglied 3", -1, 0, -1, 0, -1, 0);
    //Da Nang Boys
    PROFESSION_DA_NANG_BOYS = AddProfession("Da Nang Boys", 6000);
    AddProfessionSkin(121, "Gang-Mitglied 1", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(122, "Gang-Mitglied 2", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(123, "Gang-Mitglied 3", -1, 0, -1, 0, -1, 0);
    //Triads
    PROFESSION_TRIADS = AddProfession("Triaden", 6000);
    AddProfessionSkin(117, "Gang-Mitglied 1", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(118, "Gang-Mitglied 2", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(120, "Gang-Mitglied 3", -1, 0, -1, 0, -1, 0);
    //Mafia
    PROFESSION_MAFIA = AddProfession("Mafia", 6000);
    AddProfessionSkin(124, "Handlanger 1", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(125, "Handlanger 2", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(126, "Handlanger 3", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(127, "Auftragsmörder", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(111, "Leibwächter 1", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(112, "Leibwächter 2", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(113, "Boss", -1, 0, -1, 0, -1, 0);
    //Bikers
    PROFESSION_BIKERS = AddProfession("Biker", 6000);
    AddProfessionSkin(247, "Gang-Mitglied 1", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(248, "Gang-Mitglied 2", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(254, "Gang-Mitglied 3", -1, 0, -1, 0, -1, 0);
    AddProfessionSkin(100, "Boss", -1, 0, -1, 0, -1, 0);
    //Special Force
    PROFESSION_SPECIAL_FORCE = AddProfession("Spezialeinheit", 12000);
    AddProfessionSkin(285, "SWAT", WEAPON_TYPE_NITESTICK, 0, WEAPON_TYPE_MP5, 999999, WEAPON_TYPE_TEAR_GAS, 999999);
    AddProfessionSkin(286, "FBI-Agent", WEAPON_TYPE_DESERT_EAGLE, 999999, WEAPON_TYPE_SPASS12, 999999, WEAPON_TYPE_MP5, 999999);
    AddProfessionSkin(165, "CIA-Agent 1", WEAPON_TYPE_SILENCED_9MM, 999999, WEAPON_TYPE_MP5, 999999, WEAPON_TYPE_SATCHEL_CARGES, 999999);
    AddProfessionSkin(166, "CIA-Agent 2", WEAPON_TYPE_SILENCED_9MM, 999999, WEAPON_TYPE_MP5, 999999, WEAPON_TYPE_SATCHEL_CARGES, 999999);
    //Soldier
    PROFESSION_SOLDIER = AddProfession("Soldat", 12000);
    AddProfessionSkin(287, "Infanterist", WEAPON_TYPE_KNIFE, 0, WEAPON_TYPE_M4, 999999, WEAPON_TYPE_HAND_GRENADE, 999999);
	AddProfessionSkin(287, "Scharfschütze", WEAPON_TYPE_KNIFE, 0, WEAPON_TYPE_SILENCED_9MM, 999999, WEAPON_TYPE_SNIPER, 999999);
	AddProfessionSkin(287, "Luftabwehr", WEAPON_TYPE_KNIFE, 0, WEAPON_TYPE_STINGER_ROCKET_LAUNCHER, 999999, WEAPON_TYPE_PARACHUTE, 0);
	AddProfessionSkin(179, "Offizier", WEAPON_TYPE_KNIFE, 0, WEAPON_TYPE_DESERT_EAGLE, 999999, WEAPON_TYPE_M4, 999999);
	//Story Character
    PROFESSION_STORY_CHARACTER = AddProfession("Geschichts-Charakter", 20000);
	return true;
}

public InitMissions()
{
	//Name, StartPositionX, StartPositionY, StartPositionZ, StartPositionFacing, Time, Profession, RewardExperience, RewardMoney
	//VehicleType - MissionVehicle
	//Checkpoint, PositionX, PositionY, PositionZ, PositionSize - MissionCheckpoint
	//-- Los Santos --
    //International
    AddMission("Zum Polizei-Revier", 1615.5913, -2319.2029, 13.1587, 90.0000, 360, PROFESSION_OFFICER, 20, 80);
    AddMissionVehicle(VEHICLE_TYPE_TAXI);
    AddMissionCheckpoint(1558.4065, -2286.7942, 13.1616, 5.0000);
    AddMissionCheckpoint(1474.6317, -2225.2744, 13.1621, 5.0000);
    AddMissionCheckpoint(1425.0150, -2194.2832, 15.8759, 5.0000);
    AddMissionCheckpoint(1264.0092, -2245.9946, 15.3505, 5.0000);
    AddMissionCheckpoint(1329.9380, -2276.6587, 13.1692, 5.0000);
    AddMissionCheckpoint(1320.2133, -2403.7180, 13.0555, 5.0000);
    AddMissionCheckpoint(1274.6570, -2446.8127, 8.0833, 5.0000);
    AddMissionCheckpoint(1042.8273, -2111.2336, 12.7129, 5.0000);
    AddMissionCheckpoint(1088.6290, -1853.1049, 13.1644, 5.0000);
    AddMissionCheckpoint(1236.5339, -1852.8767, 13.1617, 5.0000);
    AddMissionCheckpoint(1345.3632, -1860.3901, 13.1613, 5.0000);
    AddMissionCheckpoint(1389.1195, -1843.6769, 13.1637, 5.0000);
    AddMissionCheckpoint(1408.6409, -1733.1289, 13.1647, 5.0000);
    AddMissionCheckpoint(1469.1028, -1732.9673, 13.1623, 5.0000);
    AddMissionCheckpoint(1535.1417, -1673.4390, 13.1629, 5.0000);
	//Ocean Docks
	//Santa Maria Beach
	//Verona Beach
 	//Verdant Bluffs
 	//El Corona
	//Willofield
	//Playa Del Seville
    //Rodeo
    //Marina
    //Market
    //Conference Center
    //Commerce
    //Pershing Square
    //Little-Mexico
    //Idlewood
    //Ganton
    //East Beach
    //Richman
    //Vinewood
    //Downtown Los Santos
    //Glen Park
    //Jefferson
    //East Los Santos
    //Temple
    //Mulholland
    //Mulholland Intersection
    //Las Colinas
    //Los Flores
    //-- San Fierro --
    //-- Las Venturas --
    //-- Red County --
    //-- Flint County --
	//-- Whetstone --
	//-- Tierra Robada --
    //-- Bone County --
    return true;
}

public InitShopTypes()
{
	//Name, Icon
	//Name, Price, Type, Id
    //-- Los Santos --
    //Souvenir-Geschäft
    AddShopType("Souvenir-Geschäft", 38);
    AddShopTypeObject("Blumen", 20, SHOP_TYPE_OBJECT_TYPE_WEAPON, WEAPON_TYPE_FLOWERS);
    AddShopTypeObject("Blumen", 30, SHOP_TYPE_OBJECT_TYPE_WEAPON, WEAPON_TYPE_SPRAY_PAINT);
    AddShopTypeObject("Blumen", 50, SHOP_TYPE_OBJECT_TYPE_WEAPON, WEAPON_TYPE_CAMERA);
    AddShopTypeObject("Blumen", 150, SHOP_TYPE_OBJECT_TYPE_WEAPON, WEAPON_TYPE_PARACHUTE);
    //Tankstelle
    AddShopType("Tankstelle", 51);
    AddShopTypeObject("1 Liter", 1, SHOP_TYPE_OBJECT_TYPE_PETROL, 1);
    AddShopTypeObject("5 Liter", 5, SHOP_TYPE_OBJECT_TYPE_PETROL, 5);
    AddShopTypeObject("10 Liter", 10, SHOP_TYPE_OBJECT_TYPE_PETROL, 10);
    AddShopTypeObject("50 Liter", 50, SHOP_TYPE_OBJECT_TYPE_PETROL, 50);
    //-- San Fierro --
    //-- Las Venturas --
    //-- Red County --
    //-- Flint County --
	//-- Whetstone --
	//-- Tierra Robada --
    //-- Bone County --
	return true;
}

public InitShops()
{
	//Owner, Type, CheckpointX, CheckpointY, CheckpointZ, CheckpointSize, ViewPositionX, ViewPositionY, ViewPositionZ, ViewTargetX, ViewTargetY, ViewTargetZ
    //-- Los Santos --
    //International
    AddShop("Oli", 0, 1685.6531, -2334.1960, 13.5469, 3.0000, 1685.5219, -2329.3389, 13.5469, 1685.6531, -2334.1960, 13.5469);
    //Ocean Docks
	//Santa Maria Beach
	//Verona Beach
 	//Verdant Bluffs
 	//El Corona
	//Willofield
	//Playa Del Seville
    //Rodeo
    //Marina
    //Market
    //Conference Center
    //Commerce
    //Pershing Square
    //Little-Mexico
    //Idlewood
    AddShop("Oli", 1, 1944.7417, -1773.3329, 13.3906, 5.0000, 1944.7417, -1773.3329, 13.3906, 1944.7417, -1773.3329, 13.3906);
    //Ganton
    //East Beach
    //Richman
    //Vinewood
    //Downtown Los Santos
    //Glen Park
    //Jefferson
    //East Los Santos
    //Temple
    //Mulholland
    //Mulholland Intersection
    //Las Colinas
    //Los Flores
    //-- San Fierro --
    //-- Las Venturas --
    //-- Red County --
    //-- Flint County --
	//-- Whetstone --
	//-- Tierra Robada --
    //-- Bone County --
    return true;
}

public InitHouses()
{
	//Name, Description, Price, Money, CheckpointX, CheckpointY, CheckpointZ, CheckpointSize, ViewPositionX, ViewPositionY, ViewPositionZ, ViewTargetX, ViewTargetY, ViewTargetZ
	//VehicleId - HouseVehicle
	//PositionX, PositionY, PositionZ, TargetX, TargetY, TargetZ, Interior - HouseCamera
	//-- Los Santos --
    //International
	//Ocean Docks
	//Santa Maria Beach
	//Verona Beach
 	//Verdant Bluffs
 	//El Corona
	//Willofield
	//Playa Del Seville
    //Rodeo
    //Marina
    //Market
    //Conference Center
    //Commerce
    //Pershing Square
    //Little-Mexico
    //Idlewood
    //Ganton
    //East Beach
    //Richman
    //Vinewood
    //Downtown Los Santos
    //Glen Park
    //Jefferson
	AddHouse("Bordell", "Ein großes Bordell mit Hubschrauber und Auto.", 2000000, 2000, 2230.5142, -1159.9054, 25.8194, 4.0000, 2220.4336, -1133.2054, 25.6250, 2216.8599, -1180.2552, 29.7971);
    AddHouseVehicle(AddVehicle(VEHICLE_TYPE_BROADWAY, 2228.2144, -1163.0769, 25.6428, 270.0000, -1, -1)); //Broadway
	AddHouseVehicle(AddVehicle(VEHICLE_TYPE_SPARROW, 2195.4160, -1173.8026, 33.5313, 0.0000, -1, -1)); //Sparrow
	//East Los Santos
    //Temple
    //Mulholland
    AddHouse("Maddogs Villa", "Eine große Villa mit fantastischem Ausblick auf Los Santos.", 6000000, 10000, 1301.2543, -802.6722, 84.1406, 4.0000, 1279.1090, -855.6321, 97.2725, 1276.6158, -788.2546, 96.9662);
    AddHouseVehicle(AddVehicle(VEHICLE_TYPE_MAVERICK, 1291.5063, -787.8284, 96.4554, 180.0000, -1, -1)); //Maverick
    AddHouseVehicle(AddVehicle(VEHICLE_TYPE_STRETCH, 1252.5272, -809.6781, 84.1406, 90.0000, -1, -1)); //Stretch
	AddHouseCamera(1258.6748, -788.3049, 92.0313, 1256.1550, -783.4768, 92.0302, 0);
    AddHouseCamera(1297.6394, -810.4351, 84.1406, 1302.4576, -800.8644, 84.1406, 0);
    AddHouseCamera(1356.7308, -849.8791, 54.4910, 1369.8580, -846.5010, 43.9772, 0);
    AddHouseCamera(1251.1343, -789.5239, 89.9030, 1245.8744, -767.2453, 92.0635, 0);
    AddHouseCamera(1268.8489, -812.2648, 84.1406, 1288.0323, -829.5942, 83.1406, 0);
    AddHouseCamera(1276.6973, -788.1629, 96.9662, 1223.7605, -824.4244, 87.0065, 0);
    //Mulholland Intersection
    //Las Colinas
    //Los Flores
    //-- San Fierro --
    //-- Las Venturas --
    //-- Red County --
    //-- Flint County --
	//-- Whetstone --
	//-- Tierra Robada --
    //-- Bone County --
	return true;
}

public InitGangHalls()
{
    //Name, Price, Float:PositionX, Float:PositionY, Float:PositionZ, Float:PositionFacing, Interior, Float:TeamPosition1X, Float:TeamPosition1Y, Float:TeamPosition1Z, Float:TeamPosition1Facing, Float:TeamPosition2X, Float:TeamPosition2Y, Float:TeamPosition2Z, Float:TeamPosition2Facing, Float:ExitPositionX, Float:ExitPositionY, Float:ExitPositionZ, Float:ExitPositionFacing
	//-- Los Santos --
    //International
	//Ocean Docks
	//Santa Maria Beach
	//Verona Beach
 	//Verdant Bluffs
 	//El Corona
	//Willofield
	//Playa Del Seville
    //Rodeo
    //Marina
    //Market
    //Conference Center
    //Commerce
    //Pershing Square
    //Little-Mexico
    //Idlewood
    //Ganton
    //East Beach
    //Richman
    //Vinewood
    //Downtown Los Santos
    //Glen Park
    //Jefferson
    //East Los Santos
    AddGangHall("Crackhöhle", 20000000, 2542.9314, -1318.9672, 1031.4219, 90.0000, 2, 2556.9226, -1288.8007, 1060.9844, 270.0000, 2542.9314, -1318.9672, 1031.4219, 90.0000, 2519.2219, -1281.2832, 34.8516, 90.0000);
	AddWeapon(349, WEAPON_TYPE_SHOTGUN, 220, 2574.9409,-1282.1533,1060.9844);
	AddWeapon(356, WEAPON_TYPE_M4, 220, 2581.1750, -1284.7113, 1065.3573);
	//Temple
    //Mulholland
    AddGangHall("Maddogs Villa", 15000000, 1299.2085, -794.3455,1084.0078, 352.9400, 2, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 1309.2233, -815.1431, 77.1528, 225.0203);
    //Mulholland Intersection
    //Las Colinas
    //Los Flores
    //-- San Fierro --
    //-- Las Venturas --
    //-- Red County --
    //-- Flint County --
	//-- Whetstone --
	//-- Tierra Robada --
    //-- Bone County --
	return true;
}

public InitDeathMatches()
{
    //Name, CheckpointX, CheckpointY, CheckpointZ, CheckpointSize, ViewPositionX, ViewPositionY, ViewPositionZ, ViewTargetX, ViewTargetY, ViewTargetZ, ViewTargetFacing, Interior
    //Skin, Name, Colour, Weapon1, Ammo1, Weapon2, Ammo2, Weapon3, Ammo3, PositionX, PositionY, PositionZ, PositionFacing
	//-- Los Santos --
    //International
	//Ocean Docks
	//Santa Maria Beach
	//Verona Beach
 	//Verdant Bluffs
 	//El Corona
	//Willofield
	//Playa Del Seville
	AddDeathMatch("Los-Santos-Stadion", 2746.9363, -1828.2908, 11.8478, 3.0000, -1423.6820, 938.3299, 1036.5422, -1423.9554, 929.2668, 1036.3986, 0.0000, 15);
    AddDeathMatchSkin(280, "Polizei", 				COLOUR_BLUE, 	WEAPON_TYPE_NITESTICK, 		0, 			WEAPON_TYPE_9MM, 			999999, 	WEAPON_TYPE_SHOTGUN, 			999999, 	-1399.6414, 957.5759, 1026.0811, 2.6025);
    AddDeathMatchSkin(105, "Grove Street Families", COLOUR_GREEN, 	WEAPON_TYPE_SPRAY_PAINT, 	999999, 	WEAPON_TYPE_9MM, 			999999, 	WEAPON_TYPE_TEC9, 				999999, 	-1462.3217, 1020.1063, 1026.9017, 53.6763);
    AddDeathMatchSkin(102, "Ballas", 				COLOUR_PINK, 	WEAPON_TYPE_BASEBALL_BAT, 	0, 			WEAPON_TYPE_9MM, 			999999, 	WEAPON_TYPE_TEC9, 				999999, 	-1343.6918, 1032.4675, 1028.7202, 253.8749);
    AddDeathMatchSkin(108, "Los Santos Vagos", 		COLOUR_YELLOW, 	WEAPON_TYPE_BASEBALL_BAT, 	0, 			WEAPON_TYPE_9MM, 			999999, 	WEAPON_TYPE_SAWED_OFF_SHOTGUN, 	999999, 	-1468.0383, 955.2559, 1031.7684, 77.7799);
    //Rodeo
    //Marina
    //Market
    //Conference Center
    //Commerce
    //Pershing Square
    //Little-Mexico
    //Idlewood
    //Ganton
    //East Beach
    //Richman
    //Vinewood
    //Downtown Los Santos
    //Glen Park
    //Jefferson
    //East Los Santos
    //Temple
    //Mulholland
    //Mulholland Intersection
    //Las Colinas
    //Los Flores
    //-- San Fierro --
    //-- Las Venturas --
    //-- Red County --
    //-- Flint County --
	//-- Whetstone --
	//-- Tierra Robada --
    //-- Bone County --
	return true;
}

public InitEmoticons()
{
    AddEmoticon("/besoffen", "PED", "WALK_DRUNK", "ist besoffen", 4.0000, true);
    AddEmoticon("/bedrohen", "PED", "ARRESTGun", "bedroht jemanden mit seiner Waffe", 4.0000, false);
    AddEmoticon("/lachen", "RAPPING", "Laugh_01", "lacht", 5.0000, false);
    AddEmoticon("/umsehen", "SHOP", "ROB_Shifty", "sieht sich nach Polizisten um", 8.0000, false);
    AddEmoticon("/platzieren", "BOMBER", "BOM_Plant", "platziert etwas", 6.0000, false);
    AddEmoticon("/ueberfallen", "SHOP", "ROB_Loop_Threat", "überfällt jemanden.", 6.0000, false);
    AddEmoticon("/wichsen", "PAULNMAC", "wank_loop", "wichst", 4.0000, true);
    AddEmoticon("/verhaften", "POLICE", "plc_drgbst_01", "verhaftet jemanden", 10.0000, false);
    AddEmoticon("/verhaftet", "POLICE", "crm_drgbst_01", "wird verhaftet", 10.0000, false);
    AddEmoticon("/verletzt", "SWEET", "Sweet_injuredloop", "ist verletzt", 4.0000, true);
    AddEmoticon("/rauchen", "SMOKING", "F_smklean_loop", "raucht", 4.0000, true);
    AddEmoticon("/schaun", "COP_AMBIENT", "Coplook_loop", "schaut", 4.0000, true);
    AddEmoticon("/hinlegen", "BEACH", "bather", "legt sich hin", 4.0000, true);
    AddEmoticon("/decken", "ped", "cower", "deckt sich", 4.0000, false);
    AddEmoticon("/uebergeben", "FOOD", "EAT_Vomit_P", "übergibt sich", 6.0000, false);
    AddEmoticon("/essen", "FOOD", "EAT_Burger", "isst", 4.0000, true);
    AddEmoticon("/winken", "KISSING", "BD_GF_Wave", "winkt", 8.0000, false);
    AddEmoticon("/handeln", "DEALER", "DEALER_DEAL", "handelt", 4.0000, true);
    AddEmoticon("/kuessen", "KISSING", "Playa_Kiss_02", "küsst jemanden", 6.0000, false);
    AddEmoticon("/crack", "CRACK", "crckdeth2", "stirbt an einer Überdosis Crack", 6.0000, false);
    AddEmoticon("/pissen", "PAULNMAC", "Piss_in", "pisst", 8.0000, false);
    AddEmoticon("/sitzen", "BEACH", "ParkSit_M_loop", "setzt sich hin", 4.0000, true);
    AddEmoticon("/beleidigen", "ped", "fucku", "beleidigt jemanden", 6.0000, false);
    AddEmoticon("/unterhalten", "PED", "IDLE_CHAT", "unterhält sich", 4.0000, true);
	return true;
}

