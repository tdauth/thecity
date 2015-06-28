//*******************************************************************
//Constants
//*******************************************************************
#if defined Constants_included
  	#endinput
#endif
#define Constants_included
#pragma library Constants

//-- Account --
#define MAX_ACCOUNTS                                100
#define MAX_ACCOUNT_NAME                            8
#define MAX_ACCOUNT_PASSWORD                        8
#define MAX_ACCOUNT_EMAIL                           22
#define MAX_ACCOUNT_COUNTRY                         2
#define MAX_ACCOUNT_DESCRIPTION                     22
#define MAX_ACCOUNT_PLAYERS                         4
#define MAX_ACCOUNT_PLAYER_NAME                     22
#define MAX_ACCOUNT_PLAYER_HOUSES                   4
//-- Area --
#define MAX_AREAS                              		150
#define MAX_AREA_NAME                              	44
//-- Checkpoint --
#define CHECKPOINT_TYPE_SHOP                        0
#define CHECKPOINT_TYPE_HOUSE                       1
#define CHECKPOINT_TYPE_MISSION                     3
#define CHECKPOINT_TYPE_DEATH_MATCH                 4
//-- Database --
//-- Death Match --
#define MAX_DEATH_MATCHES                           50
#define MAX_DEATH_MATCH_NAME                        22
#define MAX_DEATH_MATCH_SKINS                       4
#define MAX_DEATH_MATCH_SKIN_NAME                   22
//-- Emoticon --
#define MAX_EMOTICONS                             	100
#define MAX_EMOTICON_COMMAND                      	22
#define MAX_EMOTICON_LIBARY             			22
#define MAX_EMOTICON_ANIMATION                    	22
#define MAX_EMOTICON_TEXT                          	36
//-- Gang --
#define MAX_GANGS                                   100
#define MAX_GANG_NAME                               12
#define MAX_GANG_USEABLE_COLOURS                    8
#define MAX_GANG_USEABLE_COLOUR_NAME                12
#define MAX_GANG_RANKS                              4
#define MAX_GANG_RANK_NAME                          12
#define MAX_GANG_AREAS                              8
#define MAX_GANG_MEMBERS                           	20
#define GANG_RANK_NOOB                              0
#define GANG_RANK_MEMBER                            1
#define GANG_RANK_VETERAN                           2
#define GANG_RANK_BOSS                              3
//-- Gang Hall --
#define MAX_GANG_HALLS                             	8
#define MAX_GANG_HALL_NAME                         	22
//-- House --
#define MAX_HOUSES                                  100
#define MAX_HOUSE_NAME                              22
#define MAX_HOUSE_DESCRIPTION                       256
#define MAX_HOUSE_VEHICLES                          4
#define MAX_HOUSE_CAMERAS                           6
//-- Interface --
//Colours
#define COLOUR_GREY 								0xAFAFAFAA
#define COLOUR_GREEN 								0x33AA33AA
#define COLOUR_RED 									0xAA3333AA
#define COLOUR_YELLOW 								0xFFFF00AA
#define COLOUR_WHITE 								0xFFFFFFAA
#define COLOUR_BLUE 								0x0000BBAA
#define COLOUR_LIGHTBLUE 							0x33CCFFAA
#define COLOUR_ORANGE 								0xFF9900AA
#define COLOUR_LIME 								0x10F441AA
#define COLOUR_MAGENTA 								0xFF00FFFF
#define COLOUR_NAVY 								0x000080AA
#define COLOUR_AQUA 								0xF0F8FFAA
#define COLOUR_CRIMSON 								0xDC143CAA
#define COLOUR_FLBLUE 								0x6495EDAA
#define COLOUR_BISQUE 								0xFFE4C4AA
#define COLOUR_BLACK 								0x000000AA
#define COLOUR_CHARTREUSE 							0x7FFF00AA
#define COLOUR_BROWN 								0XA52A2AAA
#define COLOUR_CORAL 								0xFF7F50AA
#define COLOUR_GOLD 								0xB8860BAA
#define COLOUR_GREENYELLOW 							0xADFF2FAA
#define COLOUR_INDIGO 								0x4B00B0AA
#define COLOUR_IVORY 								0xFFFF82AA
#define COLOUR_LAWNGREEN 							0x7CFC00AA
#define COLOUR_SEAGREEN 							0x20B2AAAA
#define COLOUR_LIMEGREEN 							0x32CD32AA
#define COLOUR_MIDNIGHTBLUE 						0X191970AA
#define COLOUR_MAROON 								0x800000AA
#define COLOUR_OLIVE 								0x808000AA
#define COLOUR_ORANGERED 							0xFF4500AA
#define COLOUR_PINK 								0xFFC0CBAA
#define COLOUR_SPRINGGREEN 							0x00FF7FAA
#define COLOUR_TOMATO 								0xFF6347AA
#define COLOUR_YELLOWGREEN 							0x9ACD32AA
#define COLOUR_MEDIUMAQUA 							0x83BFBFAA
#define COLOUR_MEDIUMMAGENTA 						0x8B008BAA
//Keys
#define KEY_MAIN_MENU                           	1
#define KEY_START_MISSION                           512
#define KEY_CHANGE_DM_SKIN_NEXT                     8192 //16384
#define KEY_CHANGE_DM_SKIN_LAST                     16384 //65408
#define KEY_SELECT_DM_SKIN                     		4
#define KEY_CANCEL_EMOTICON                         8
//Message Types
#define MAX_MESSAGE_TYPES                           7
#define MESSAGE_TYPE_SERVER             			0
#define MESSAGE_TYPE_INFO             				1
#define MESSAGE_TYPE_ACCEPTANCE                     2
#define MESSAGE_TYPE_ERROR                          3
#define MESSAGE_TYPE_SPEED                          4
#define MESSAGE_TYPE_EXPERIENCE                     5
#define MESSAGE_TYPE_TIMER                          6
//Menu Types
#define MAX_MENU_TYPES                              17
#define MENU_TYPE_MAIN_MENU                    		0
#define MENU_TYPE_ACCOUNT_MENU                      1
#define MENU_TYPE_ACCOUNT_PLAYER_MENU               2
#define MENU_TYPE_HELP_MENU                         3
#define MENU_TYPE_TOWN_SELECTION                    4
#define MENU_TYPE_HOUSES                            5
#define MENU_TYPE_HOUSE_SETTINGS                    6
#define MENU_TYPE_GANG_CREATION                  	7
#define MENU_TYPE_GANG                              8
#define MENU_TYPE_GANG_HALL_SELECTION               9
#define MENU_TYPE_PROFESSION_SELECTION              10
#define MENU_TYPE_PROFESSION_START                	11
#define MENU_TYPE_SHOP                              12
#define MENU_TYPE_HOUSE                             13
#define MENU_TYPE_RACE                              14
#define MENU_TYPE_DEATH_MATCH                   	15
#define MENU_TYPE_GANG_INVITATION                   16
//-- Mission --
#define MAX_MISSIONS                                100
#define MAX_MISSION_NAME                            22
#define MAX_MISSION_VEHICLES                        6
#define MAX_MISSION_CHECKPOINTS                     50
#define MAX_MISSION_REWARDS                         2 //Experience, Money
#define MISSION_REWARD_EXPERIENCE                   0
#define MISSION_REWARD_MONEY                   		1
//-- Player --
#define MAX_PLAYER_HOUSES                           4
#define MAX_PLAYER_MAP_MARKERS						100
//-- Profession --
#define MAX_PROFESSIONS                             100
#define MAX_PROFESSION_NAME                         22
#define MAX_PROFESSION_TARGETS                      4
#define MAX_PROFESSION_SKINS                      	7
#define MAX_PROFESSION_SKIN_NAME                    22
//-- Shop --
#define MAX_SHOPS                                   100
#define MAX_SHOP_OWNER                              22
//-- Shop Type --
#define MAX_SHOP_TYPES                              2
#define MAX_SHOP_TYPE_NAME                          28
#define MAX_SHOP_TYPE_OBJECTS                       10
#define MAX_SHOP_TYPE_OBJECT_NAME                   22
#define SHOP_TYPE_OBJECT_TYPE_WEAPON                0
#define SHOP_TYPE_OBJECT_TYPE_VEHICLE               1
#define SHOP_TYPE_OBJECT_TYPE_HEALTH                2
#define SHOP_TYPE_OBJECT_TYPE_ARMOUR                3
#define SHOP_TYPE_OBJECT_TYPE_PETROL                4
//-- Skin --
#define MAX_SKINS                                 	34
#define MAX_SKIN_NAME                              	12
//-- Town --
#define MAX_TOWNS                                  	1
#define MAX_TOWN_NAME                               22
//-- Vehicle --
//-- Vehicle Type --
#define MAX_VEHICLE_TYPES                           70
#define MAX_VEHICLE_TYPE_NAME                       44
#define MAX_VEHICLE_TYPE_TYPES                      7
#define VEHICLE_TYPE_TYPE_CAR                       0
#define VEHICLE_TYPE_TYPE_MOTORBIKE                 1
#define VEHICLE_TYPE_TYPE_BIKE                      2
#define VEHICLE_TYPE_TYPE_BOAT                      3
#define VEHICLE_TYPE_TYPE_HELICOPTER                4
#define VEHICLE_TYPE_TYPE_PLANE                     5
#define VEHICLE_TYPE_TYPE_TRAIN                     6
#define VEHICLE_TYPE_POLICE_LS                      0
#define VEHICLE_TYPE_POLICE_SF                      1
#define VEHICLE_TYPE_POLICE_LV                     	2
#define VEHICLE_TYPE_POLICE_RC                      3
#define VEHICLE_TYPE_FBI_RANCHER                   	4
#define VEHICLE_TYPE_FBI_TRUCK                      5
#define VEHICLE_TYPE_ENFORCER                     	6
#define VEHICLE_TYPE_ARMOURED                    	7
#define VEHICLE_TYPE_FIRE_ENGINE                   	8
#define VEHICLE_TYPE_AMBULANCE                     	9
#define VEHICLE_TYPE_PATRIOT                     	10
#define VEHICLE_TYPE_BARRACKS                  		11
#define VEHICLE_TYPE_BAGGAGE                  		12
#define VEHICLE_TYPE_STRETCH                  		13
#define VEHICLE_TYPE_BROADWAY                  		14
#define VEHICLE_TYPE_TRACTOR                 		15
#define VEHICLE_TYPE_COMBINE                    	16
#define VEHICLE_TYPE_BULLDOZER                 		17
#define VEHICLE_TYPE_TAXI                 			18
#define VEHICLE_TYPE_TRUCK                          19
#define VEHICLE_TYPE_SENTINEL                		20
#define VEHICLE_TYPE_CHEETAH                 		21
#define VEHICLE_TYPE_INFERNUS                 		22
#define VEHICLE_TYPE_COMET                 			23
#define VEHICLE_TYPE_WASHINGTON                 	24
#define VEHICLE_TYPE_ADMIRAL                 		25
#define VEHICLE_TYPE_STALLION                 		26
#define VEHICLE_TYPE_YANKEE                 		27
#define VEHICLE_TYPE_RUMPO                 			28
#define VEHICLE_TYPE_GREENWOOD                      29
#define VEHICLE_TYPE_LANDSTALKER                   	30
#define VEHICLE_TYPE_VOODO                 			31
#define VEHICLE_TYPE_SLAMVAN 						32 //Slamvan 0.2
#define VEHICLE_TYPE_CLOVER 						33 //Clover
#define VEHICLE_TYPE_SUNRISE						34 //Sunrise
#define VEHICLE_TYPE_MONSTERTRUCK					35 //Monstertruck
#define VEHICLE_TYPE_VIRGO							36 //Virgo
#define VEHICLE_TYPE_BUS 							37 //Bus
#define VEHICLE_TYPE_WALTON							38 //Walton
#define VEHICLE_TYPE_POLICE_PCJ600                  39
#define VEHICLE_TYPE_PIZZABOY                       40
#define VEHICLE_TYPE_SANCHEZ                   		41
#define VEHICLE_TYPE_PCJ600                   		42
#define VEHICLE_TYPE_FREEWAY                 		43
#define VEHICLE_TYPE_FCR900							44 //FCR 900 0.2
#define VEHICLE_TYPE_NRG500							45 //NGR 500
#define VEHICLE_TYPE_BMX                 			46
#define VEHICLE_TYPE_BIKE							47 //Bike 0.2
#define VEHICLE_TYPE_DINGHY                         48
#define VEHICLE_TYPE_TROPIC                         49
#define VEHICLE_TYPE_LAUNCH							50 //Launch 0.2
#define VEHICLE_TYPE_JATMAX							51 //Jatmax
#define VEHICLE_TYPE_POLICE_MAVERICK                52
#define VEHICLE_TYPE_HUNTER                         53
#define VEHICLE_TYPE_LEVITHAN                       54
#define VEHICLE_TYPE_RAINDANCE                      55
#define VEHICLE_TYPE_MAVERICK                       56
#define VEHICLE_TYPE_SEASPARROW                     57
#define VEHICLE_TYPE_SPARROW						58 //Sparrow 0.2
#define VEHICLE_TYPE_HYDRA                          59
#define VEHICLE_TYPE_ANDROMEDA                      60
#define VEHICLE_TYPE_SHAMAL                         61
#define VEHICLE_TYPE_DODO                           62
#define VEHICLE_TYPE_RUSTLER						63 //Rustler 0.2
#define VEHICLE_TYPE_NEVADA							64 //Nevada
#define VEHICLE_TYPE_STUNT							65 //Stunt
#define VEHICLE_TYPE_TRAM							66 //Tram 0.2
#define VEHICLE_TYPE_X1								67 //?
#define VEHICLE_TYPE_X2								68 //?
#define VEHICLE_TYPE_X3								69 //?
//-- Weapon --
#define MAX_WEAPONS                            		100
//-- Weapon Type --
#define MAX_WEAPON_TYPES                            41
#define MAX_WEAPON_TYPE_NAME                        28
#define MAX_WEAPON_TYPE_TYPES                      	10
#define MAX_WEAPON_TYPE_TYPE_NAME                   22
#define MAX_WEAPON_TYPE_TYPE_REASONS                23
#define WEAPON_TYPE_TYPE_MEELE                      0
#define WEAPON_TYPE_TYPE_PISTOL                     1
#define WEAPON_TYPE_TYPE_SHOTGUN                    2
#define WEAPON_TYPE_TYPE_MICRO_SMG                  3
#define WEAPON_TYPE_TYPE_SMG                        4
#define WEAPON_TYPE_TYPE_MG                         5
#define WEAPON_TYPE_TYPE_RIFLE                      6
#define WEAPON_TYPE_TYPE_HEAVY_WEAPON               7
#define WEAPON_TYPE_TYPE_PROJECTILE                 8
#define WEAPON_TYPE_TYPE_CANNON                     9
#define WEAPON_TYPE_BRASSNUCKLE                     0
#define WEAPON_TYPE_KNIFE                          	1
#define WEAPON_TYPE_NITESTICK                       2
#define WEAPON_TYPE_BASEBALL_BAT                    3
#define WEAPON_TYPE_KATANA                          4
#define WEAPON_TYPE_GOLF_CLUB                       5
#define WEAPON_TYPE_SHOVEL                          6
#define WEAPON_TYPE_POOL_CUE                        7
#define WEAPON_TYPE_CHAINSAW                        8
#define WEAPON_TYPE_DILDO_1                         9
#define WEAPON_TYPE_DILDO_2                         10
#define WEAPON_TYPE_VIBRATOR_1                      11
#define WEAPON_TYPE_VIBRATOR_2                      12
#define WEAPON_TYPE_FLOWERS                         13
#define WEAPON_TYPE_CANE                            14
#define WEAPON_TYPE_SPRAY_PAINT                     15
#define WEAPON_TYPE_FIRE_EXTINGUISHER               16
#define WEAPON_TYPE_CAMERA                          17
#define WEAPON_TYPE_PARACHUTE                       18
#define WEAPON_TYPE_9MM                            	19
#define WEAPON_TYPE_SILENCED_9MM                    20
#define WEAPON_TYPE_DESERT_EAGLE                    21
#define WEAPON_TYPE_SHOTGUN							22
#define WEAPON_TYPE_SAWED_OFF_SHOTGUN 				23
#define WEAPON_TYPE_SPASS12       					24
#define WEAPON_TYPE_UZI                             25
#define WEAPON_TYPE_TEC9                         	26
#define WEAPON_TYPE_MP5                         	27
#define WEAPON_TYPE_M4                         		28
#define WEAPON_TYPE_AK47                         	29
#define WEAPON_TYPE_RIFLE                         	30
#define WEAPON_TYPE_SNIPER                         	31
#define WEAPON_TYPE_RPG                         	32
#define WEAPON_TYPE_STINGER_ROCKET_LAUNCHER         33
#define WEAPON_TYPE_FLAMETHROWER                    34
#define WEAPON_TYPE_MINIGUN                         35
#define WEAPON_TYPE_HAND_GRENADE                    36
#define WEAPON_TYPE_TEAR_GAS                        37
#define WEAPON_TYPE_MOLOTOV                        	38
#define WEAPON_TYPE_SATCHEL_CARGES                  39
#define WEAPON_TYPE_EXPLOSION                       40
