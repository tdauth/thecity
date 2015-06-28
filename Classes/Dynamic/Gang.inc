//*******************************************************************
//Gang
//Dynamisch
//*******************************************************************
#if defined Gang_included
  	#endinput
#endif
#define Gang_included
#pragma library Gang

//-- Variables --
new GANGS = 0;
new GANG_USEABLE_COLOUR[MAX_GANG_USEABLE_COLOURS] =
{
    COLOUR_RED,
    COLOUR_BLUE,
	COLOUR_GREEN,
	COLOUR_YELLOW,
	COLOUR_PINK,
	COLOUR_ORANGE,
	COLOUR_GOLD,
	COLOUR_GREY
};
new GANG_USEABLE_COLOUR_NAME[MAX_GANG_USEABLE_COLOURS][MAX_GANG_USEABLE_COLOUR_NAME] =
{
    "Rot",
    "Blau",
	"Grün",
	"Gelb",
	"Rosa",
	"Orange",
	"Golden",
	"Grau"
};
new GANG_RANK_NAME[MAX_GANG_RANKS][MAX_GANG_RANK_NAME] =
{
	"Neuling",
	"Mitglied",
	"Veteran",
	"Boss"
};


//-- Properties --
new GANG[MAX_GANGS];
new GANG_NAME[MAX_GANGS][MAX_GANG_NAME];
new GANG_COLOUR[MAX_GANGS];
new GANG_BOSS[MAX_GANGS]; //Die Nummer des Account-Mitglieds des Bosses.
new GANG_AREAS[MAX_GANGS];
new GANG_GANG_HALL[MAX_GANGS];
new GANG_MEMBERS[MAX_GANGS];
new GANG_MEMBER[MAX_GANGS][MAX_GANG_MEMBERS];
new GANG_MEMBER_ACCOUNT[MAX_GANGS][MAX_GANG_MEMBERS];
new GANG_MEMBER_ACCOUNT_PLAYER[MAX_GANGS][MAX_GANG_MEMBERS];
