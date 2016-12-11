//*******************************************************************
//Interface
//*******************************************************************
#if defined Interface_included
  	#endinput
#endif
#define Interface_included
#pragma library Interface

//-- Variables --
new TIMER_TIME;
new Text:MESSAGE[MAX_PLAYERS][MAX_MESSAGE_TYPES]; // TextDraw IDs
new MESSAGE_DESTROYED[MAX_PLAYERS][MAX_MESSAGE_TYPES]; // flag which indicates if the text draw id is destroyed
new Menu:MENU[MAX_PLAYERS][MAX_MENU_TYPES];

//-- Properties --
new Float:MESSAGE_TYPE_POSITION[MAX_MESSAGE_TYPES][2] =
{
    {0.0000, 0.0000}, //Server - Speed
	{10.0000, 150.0000}, //Info
	{10.0000, 150.0000}, //Acceptance
	{180.0000, 350.0000}, //Error
	{250.0000, 20.0000}, //Speed
	{250.0000, 20.0000}, //Experience
	{180.0000, 350.0000} //Timer
};
new Float:MESSAGE_TYPE_SIZE[MAX_MESSAGE_TYPES][2] = //Y ist immer das 5-fache von X
{
    {0.0000, 0.0000}, //Server
	{0.2000, 1.0000}, //Info
	{0.2000, 1.0000}, //Acceptance
	{0.4000, 1.2000}, //Error
	{0.2000, 1.0000}, //Speed
	{0.4000, 1.2000}, //Experience
	{0.4000, 1.2000} //Timer
};
new MESSAGE_TYPE_COLOUR[MAX_MESSAGE_TYPES] =
{
	COLOUR_GREY, //Server
	COLOUR_WHITE, //Info
	COLOUR_GREEN, //Acceptance
	COLOUR_RED, //Error
	COLOUR_WHITE, //Speed
	COLOUR_GREEN,
	COLOUR_WHITE //Timer
};
new MESSAGE_TYPE_SHADOW[MAX_MESSAGE_TYPES] =
{
	0, //Server
	0, //Info
	0, //Acceptance
	0, //Error
	0, //Speed
	0, //Experience
	0 //Timer
};
new MESSAGE_TYPE_OUTLINE[MAX_MESSAGE_TYPES] =
{
	0, //Server
	0, //Info
	0, //Acceptance
	0, //Error
	0, //Speed
	0, //Experience
	0 //Timer
};
new MESSAGE_TYPE_BACKGROUND_COLOUR[MAX_MESSAGE_TYPES] =
{
	0, //Server
	0, //Info
	0, //Acceptance
	0, //Error
	0, //Speed
	0, //Experience
	0 //Timer
};
new MESSAGE_TYPE_FONT[MAX_MESSAGE_TYPES] =
{
	1, //Server
	1, //Info
	1, //Acceptance
	1, //Error
	1, //Speed
	1, //Experience
	1 //Timer
};
new MESSAGE_TYPE_USE_BOX[MAX_MESSAGE_TYPES] =
{
	false, //Server
	true, //Info
	true, //Acceptance
	false, //Error
	true, //Speed
	false, //Experience
	false //Timer
};
new Float:MESSAGE_TYPE_BOX_SIZE[MAX_MESSAGE_TYPES][2] =
{
    {0.0000, 0.0000}, //Server
	{200.0000, 800.0000}, //Info
	{200.0000, 800.0000}, //Acceptance
	{600.0000, 100.0000}, //Error
	{400.0000, 100.0000}, //Speed
	{600.0000, 100.0000}, //Experience
	{600.0000, 100.0000} //Timer
};
new MESSAGE_TYPE_BOX_COLOUR[MAX_MESSAGE_TYPES] =
{
	0, //Server
	COLOUR_BLACK, //Info
	COLOUR_BLACK, //Acceptance
	0, //Error
	COLOUR_BLACK, //Speed
	0, //Experience
	0 //Timer
};
new Float:MENU_TYPE_POSITION[MAX_MENU_TYPES][2] =
{
	{350.0000, 150.0000}, //Main Menu
	{350.0000, 150.0000}, //Account Menu
	{350.0000, 150.0000}, //Account Player Menu
	{350.0000, 150.0000}, //Help Menu
	{350.0000, 150.0000}, //Town Selection
	{350.0000, 150.0000}, //Houses
	{350.0000, 150.0000}, //House Settings
	{350.0000, 150.0000}, //Gang Creation
	{350.0000, 150.0000}, //Gang
	{350.0000, 150.0000}, //Gang Hall Selection
	{350.0000, 150.0000}, //Profession Selection
	{350.0000, 150.0000}, //Profession Start
	{350.0000, 150.0000}, //Shop
	{350.0000, 150.0000}, //House
	{350.0000, 150.0000}, //Race
	{350.0000, 150.0000}, //Death Match
	{350.0000, 150.0000} //Gang Invitation
};
new Float:MENU_TYPE_SIZE[MAX_MENU_TYPES] =
{
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
	220.0000,
    220.0000,
	220.0000
};
