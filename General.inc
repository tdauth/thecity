//*******************************************************************
//General
//*******************************************************************
#if defined General_included
  	#endinput
#endif
#define General_included
#pragma library General

//-- General Including --
#include <a_samp> //Include dieser Datei muss vor allem anderen stattfinden - Sonst kommen unerklrärliche Kompilierungsfehler.
//Plugins

//-- Variables --
//Path Constants
#define PATH_ACCOUNTS                           	"TC/ServerData/Accounts/"
#define PATH_PLAYERS                           		"TC/ServerData/Players/"
#define PATH_LANGUAGE                               "TC/Language.txt"
//General Constants
#define MAX_STRING                                  256
#define GENERAL_MESSAGE_TIME                        5000
#define SMALL_MESSAGE_TIME                        	1000
#define X                                           0
#define Y                                           1
#define Z                                           2
#define FACING                                      3
#define SIZE                                      	3
#define MIN_X                                       0
#define MIN_Y                                       1
#define MIN_Z                                       2
#define MAX_X                                       3
#define MAX_Y                                       4
#define MAX_Z                                       5
#define KILL_TYPE_PROFESSION                 		0
#define KILL_TYPE_GANG                    			1
#define KILL_TYPE_PROFESSION_TARGET          		2
#define KILL_TYPE_ENEMY                     		3

//-- Constants Including --
#include "Constants"

//-- Class Including --
#include "Classes\Dynamic\Account"
#include "Classes\Area"
#include "Classes\ChatCommand"
#include "Classes\Checkpoint"
#include "Classes\DeathMatch"
#include "Classes\Emoticon"
#include "Classes\Dynamic\Gang"
#include "Classes\GangHall"
#include "Classes\House"
#include "Classes\Interface"
#include "Classes\MainMenu"
#include "Classes\Mission"
#include "Classes\Profession"
#include "Classes\Shop"
#include "Classes\ShopType"
#include "Classes\Skin"
#include "Classes\Town"
#include "Classes\Vehicle"
#include "Classes\VehicleType"
#include "Classes\Weapon"
#include "Classes\WeaponType"
#include "Classes\Dynamic\Player" //Muss nach unten, da die Klasse Konstanten aus VehicleType und WeaponType benötigt

//-- Function Definition --
//Events
/*
forward OnGameModeInit();
forward OnGameModeExit();
forward OnRconCommand(CommandText[]);
forward OnObjectMoved(ObjectId);
forward OnPlayerObjectMoved(PlayerId, ObjectId);
forward OnPlayerConnect(PlayerId);
forward OnPlayerDisconnect(PlayerId);
forward OnPlayerSpawn(PlayerId);
forward OnPlayerDeath(PlayerId, KillerId, Reason);
forward OnPlayerText(PlayerId, Text[]);
forward OnPlayerCommandText(PlayerId, CommandText[]);
forward OnPlayerInfoChange(PlayerId);
forward OnPlayerRequestClass(PlayerId, SkinId);
forward OnPlayerStateChange(PlayerId, NewState, OldState);
forward OnPlayerPrivmsg(PlayerId, RecieverId, Message[]);
forward OnPlayerTeamPrivMsg(PlayerId, Message[]);
forward OnPlayerRequestSpawn(PlayerId);
forward OnPlayerPickUpPickup(PlayerId, PickupId);
forward OnPlayerSelectedMenuRow(PlayerId, Row);
forward OnPlayerExitedMenu(PlayerId);
forward OnPlayerKeyStateChange(PlayerId, NewKeys, OldKeys);
forward OnPlayerInteriorChange(PlayerId, NewInteriorId, OldInteriorId);
forward OnPlayerEnterCheckpoint(PlayerId);
forward OnPlayerLeaveCheckpoint(PlayerId);
forward OnPlayerEnterRaceCheckpoint(PlayerId);
forward OnPlayerLeaveRaceCheckpoint(PlayerId);
forward OnVehicleSpawn(VehicleId);
forward OnVehicleDeath(VehicleId, KillerId);
forward OnPlayerEnterVehicle(PlayerId, VehicleId, IsPassenger);
forward OnPlayerExitVehicle(PlayerId, VehicleId);
forward OnVehicleMod(VehicleId, ComponentId);
forward OnVehiclePaintjob(VehicleId, PaintjobId);
forward OnVehicleRespray(VehicleId, Colour1, Colour2);
*/
//Account Functions
forward AccountExists(Name[]);
forward AccountPlayerExists(AccountId, Name[MAX_ACCOUNT_PLAYER_NAME]);
forward AccountPlayerIsHeadHunterOfAP(AccountId, AccountPlayerId, OtherAccountId, OtherAccountPlayerId);
forward GetAccountPlayerHeadHunters(AccountId, AccountPlayerId);
forward GetAccountPlayerNextHeadHS(AccountId, AccountPlayerId);
forward ClearAccountPlayerHeadHunters(AccountId, AccountPlayerId);
forward GiveAccountPlayerHeadMoney(AccountId, AccountPlayerId, TargetAccountId, TargetAccountPlayerId);
forward GiveAccountPlayerExperience(AccountId, AccountPlayerId, Experience);
forward GetAccountPlayerKillType(AccountId, AccountPlayerId, KillerAccountId, KillerAccountPlayerId);
forward AccountRegister(PlayerId, Name[MAX_STRING], Password[MAX_STRING], Email[MAX_STRING], Country[MAX_STRING]);
forward AccountLogin(PlayerId, AccountName[], Password[], AccountPlayerName[]);
forward AccountRegisterPlayer(PlayerId, AccountId, AccountPlayerName[]);
forward GetNextFreeAccountId();
forward ClearAccount(AccountId, Copy, FirstClear = false);
forward AddAccount(PlayerId, Name[MAX_ACCOUNT_NAME], Password[MAX_ACCOUNT_PASSWORD], Email[MAX_ACCOUNT_EMAIL], Country[MAX_ACCOUNT_COUNTRY], Description[MAX_ACCOUNT_DESCRIPTION]);
forward CopyAccount(AccountId, CopiedAccountId);
forward RemoveAccount(AccountId);
forward GetNextFreeAccountPlayerId(AccountId);
forward ClearAccountPlayer(AccountId, AccountPlayerId, Copy, FirstClear = false);
forward AddAccountPlayer(AccountId, PlayerId, Name[MAX_ACCOUNT_PLAYER_NAME]);
forward CopyAccountPlayer(AccountId, AccountPlayerId, CopiedAccountId, CopiedAccountPlayerId);
forward RemoveAccountPlayer(AccountId, AccountPlayerId);
forward GetNextFreeAccountPlayerHouseId(AccountId, AccountPlayerId);
forward ClearAccountPlayerHouse(AccountId, AccountPlayerId, AccountPlayerHouseId, Copy, FirstClear = false);
forward AddAccountPlayerHouse(AccountId, AccountPlayerId, HouseId);
forward CopyAccountPlayerHouse(AccountId, AccountPlayerId, AccountPlayerHouseId, CopiedAccountId, CopiedAccountPlayerId, CopiedAccountPlayerHouseId);
forward RemoveAccountPlayerHouse(AccountId, AccountPlayerId, AccountPlayerHouseId);
forward ClearAllAccounts();
//Area Functions
forward CreateAreaGangZones();
forward ShowAreasForPlayer(PlayerId);
forward PlayerIsInArea(PlayerId, AreaId);
forward GetPlayerArea(PlayerId);
forward FlashAreaForGang(GangId, AreaId, Colour);
forward StopFlashingAreaForGang(GangId, AreaId);
forward StartAreaConquest(PlayerId, AreaId);
forward InitAreaTimer();
forward TimerFunctionAreaConquest();
forward AddArea(Name[MAX_AREA_NAME], Float:MinX, Float:MinY, Float:MinZ, Float:MaxX, Float:MaxY, Float:MaxZ);
//Chat Command Functions
forward PlayerChatCommandConditions(PlayerId, OtherPlayerId, Money);
forward CommandCreateMainMenuForPlayer(PlayerId);
forward ChatCommandAddPlayerHeadMoney(PlayerId, OtherPlayerId, Money);
forward ChatCommandPlayerGivesPM(PlayerId, OtherPlayerId, Money);
forward ChatCommandPlayerSetsGangName(PlayerId, GangName[MAX_GANG_NAME]);
forward ChatCommandInvitePlayerInGang(PlayerId, OtherPlayerId);
forward CommandExit(PlayerId);
forward CommandPlayPlayerEmoticon(PlayerId, Emoticon[]);
forward CommandTurnPlayerToAdmin(PlayerId);
forward SavePlayerChatLogData(PlayerId, Data[]);
//Checkpoint Functions
forward SetPlayerActiveCheckpoint(PlayerId, Checkpoint, Type);
forward InitCheckpointTimer();
forward TimerFunctionGetCheckpoint();
//Death Match Functions
forward CreateDMMarkersForPlayer(PlayerId);
forward SendDeathMatchMessage(DeathMatchId, Type, Message[]);
forward AddAccountPlayerPvPSkill(AccountId, AccountPlayerId, Value, Add);
forward AddPlayerPvPSkill(PlayerId, Value, Add);
forward ShowDeathMatchPlayersForPlayer(PlayerId);
forward PlayerEntersDMCheckpoint(PlayerId, DeathMatchId);
forward CreateDeathMatchMenu(PlayerId, DeathMatchId);
forward SetupDeathMatchSkinSelection(PlayerId, DeathMatchId);
forward ChangeDeathMatchSkin(PlayerId, DeathMatchId, Forward);
forward SelectDeathMatchSkin(PlayerId, DeathMatchId, Skin);
forward PlayerLeavesDeathMatch(PlayerId);
forward PlayerKillsDeathMatchPlayer(PlayerId, KillerId);
forward AddDeathMatch(Name[MAX_DEATH_MATCH_NAME], Float:CheckpointX, Float:CheckpointY, Float:CheckpointZ, Float:CheckpointSize, Float:ViewPositionX, Float:ViewPositionY, Float:ViewPositionZ, Float:ViewTargetX, Float:ViewTargetY, Float:ViewTargetZ, Float:ViewTargetFacing, Interior);
forward AddDeathMatchSkin(Skin, Name[MAX_DEATH_MATCH_SKIN_NAME], Colour, Weapon1, Ammo1, Weapon2, Ammo2, Weapon3, Ammo3, Float:PositionX, Float:PositionY, Float:PositionZ, Float:PositionFacing);
//Emoticon Functions
forward PreloadEmoticonLibraries(PlayerId);
forward PlayerMakesEmoticon(PlayerId, EmoticonId);
forward ResetPlayerEmoticon(PlayerId);
forward AddEmoticon(Command[MAX_EMOTICON_COMMAND], Libary[MAX_EMOTICON_LIBARY], Animation[MAX_EMOTICON_ANIMATION], Text[MAX_EMOTICON_TEXT], Float:Time, Loop);
//Gang Functions
forward GangNameIsUsed(GangName[MAX_GANG_NAME]);
forward GangContainsAccountPlayer(GangId, AccountId, AccountPlayerId);
forward SendGangMessage(GangId, PlayerId, Type, Message[]);
forward CreateGangCreationMenu(PlayerId);
forward CreateGangMenu(PlayerId);
forward PlayerCreatesGang(PlayerId, Colour);
forward PlayerJoinsGang(PlayerId, GangId);
forward PlayerLeavesGang(PlayerId, GangId);
forward SetAccountPlayerToGangBoss(GangId, AccountId, AccountPlayerId);
forward GetNextFreeGangId();
forward ClearGang(GangId, Copy, FirstClear = false);
forward AddGang(Name[MAX_GANG_NAME], Colour);
forward CopyGang(GangId, CopiedGangId);
forward RemoveGang(GangId);
forward GetNextFreeGangMemberId(GangId);
forward ClearGangMember(GangId, GangMemberId, Copy, FirstClear = false);
forward AddGangMember(GangId, AccountId, AccountPlayerId);
forward CopyGangMember(GangId, GangMemberId, CopiedGangId, CopiedGangMemberId);
forward RemoveGangMember(GangId, GangMemberId);
forward ClearAllGangs();
//Gang Hall Functions
forward CreateBuyGangHallMenu(PlayerId);
forward GangBuysGangHall(PlayerId, GangHallId);
forward PlayerEntersGangHall(PlayerId);
forward PlayerLeavesGangHall(PlayerId);
forward StartGangBattle(GangId, OtherGangId);
forward EndGangBattle(GangId, WinerGangId);
forward AddGangHall(Name[MAX_GANG_HALL_NAME], Price, Float:PositionX, Float:PositionY, Float:PositionZ, Float:PositionFacing, Interior, Float:TeamPosition1X, Float:TeamPosition1Y, Float:TeamPosition1Z, Float:TeamPosition1Facing, Float:TeamPosition2X, Float:TeamPosition2Y, Float:TeamPosition2Z, Float:TeamPosition2Facing, Float:ExitPositionX, Float:ExitPositionY, Float:ExitPositionZ, Float:ExitPositionFacing);
//General Functions
forward FixString(const String[]);
forward StringIsNumeric(const String[]);
forward Strtok(const String[], &Index);
forward ConvertSeconds(Seconds);
//House Functions
forward CreateHouseMarkersForPlayer(PlayerId);
forward AccountPlayerHasHouse(AccountId, AccountPlayerId, HouseId);
forward SetupHouseVehiclesForPlayer(PlayerId, HouseId, Owner);
forward PlayerBuysHouse(PlayerId, HouseId);
forward PlayerSellsHouse(PlayerId, House);
forward CreateHouseMenu(PlayerId, HouseId);
forward PlayerEntersHouseCheckpoint(PlayerId, HouseId);
forward CreateHousesMenu(PlayerId);
forward CreateHouseSettingsMenu(PlayerId, House);
forward CreateHouseSellingMenu(PlayerId);
forward ShowHouseCameraForPlayer(PlayerId, House, Camera);
forward InitHouseTimer();
forward TimerFunctionDivideHouseMoney();
forward AddHouse(Name[MAX_HOUSE_NAME], Description[MAX_HOUSE_DESCRIPTION], Price, Money, Float:CheckpointX, Float:CheckpointY, Float:CheckpointZ, Float:CheckpointSize, Float:ViewPositionX, Float:ViewPositionY, Float:ViewPositionZ, Float:ViewTargetX, Float:ViewTargetY, Float:ViewTargetZ);
forward AddHouseVehicle(VehicleId);
forward AddHouseCamera(Float:PositionX, Float:PositionY, Float:PositionZ, Float:TargetX, Float:TargetY, Float:TargetZ, Interior);
//Interface Functions
forward InitTimeTimer();
forward InitPlayerMessages();
forward TimerFunctionSetTime();
forward SendMessageToPlayer(PlayerId, Type, Message[]);
forward SendTimedMessageToPlayer(PlayerId, Time, Type, Message[]);
forward DestroySendedMessageForPlayer(PlayerId, Type);
forward SendClientMessageToPlayer(PlayerId, Type, Message[]);
forward SendClientMessageToAllPlayers(Type, Message[]);
forward CreateCustomMenuForPlayer(PlayerId, Type, Menu, Title[]);
forward DestroyAllCustomMenuesForPlayer(PlayerId);
forward SetCustomMenuHeader(PlayerId, Type, Header[]);
forward ShowCustomMenuForPlayer(PlayerId, Type);
forward AddCustomMenuItemForPlayer(PlayerId, Type, Text[]);
//Main Menu Functions
forward PlayerSelectsMainMenuItem(PlayerId, MenuItem);
forward CreateMainMenuForPlayer(PlayerId);
forward PlayerSelectsAccountMenuItem(PlayerId, MenuItem);
forward CreateAccountMenuForPlayer(PlayerId);
forward PlayerSelectsAPMenuItem(PlayerId);
forward CreateAPMenuForPlayer(PlayerId, AccountId, AccountPlayerId);
forward PlayerSelectsHelpMenuItem(PlayerId, MenuItem);
forward CreateHelpMenuForPlayer(PlayerId);
//Mission Functions
forward PlayerIsInMissionVehicle(PlayerId, VehicleId);
forward PlayerEntersMissionVehicle(PlayerId);
forward PlayerStartsMission(PlayerId);
forward MissionLosesTime(PlayerId, MissionId);
forward PlayerFailsMission(PlayerId, MissionId);
forward PlayerCompletesMission(PlayerId, MissionId);
forward AddMission(Name[MAX_MISSION_NAME], Float:StartPositionX, Float:StartPositionY, Float:StartPositionZ, Float:StartPositionFacing, Time, Profession, RewardExperience, RewardMoney);
forward AddMissionVehicle(VehicleType);
forward AddMissionCheckpoint(Float:PositionX, Float:PositionY, Float:PositionZ, Float:PositionSize);
//Objects
forward InitMapMarkers(PlayerId);
forward InitAreas();
forward InitSkins();
forward InitTowns();
forward InitVehicleTypes();
forward InitVehicles();
forward InitWeaponTypes();
forward InitWeapons();
forward InitProfessions();
forward InitMissions();
forward InitShopTypes();
forward InitShops();
forward InitHouses();
forward InitGangHalls();
forward InitDeathMatches();
forward InitEmoticons();
//Player Functions
forward InitMoneyTimer();
forward TimerFunctionGiveMoney();
forward InitPlayerMiniMap(PlayerId);
forward PlayerExists(Name[MAX_PLAYER_NAME]);
forward Float:GetPlayersDistanceFromXYZ(PlayerId, Float:PointX, Float:PointY, Float:PointZ);
forward Float:GetPlayersLastDistanceFromXYZ(PlayerId, Float:PointX, Float:PointY, Float:PointZ);
forward PreloadAnimationLibrary(PlayerId, AnimationLibrary[]);
forward SavePlayerInterior(PlayerId);
forward LoadPlayerInterior(PlayerId);
forward SavePlayerState(PlayerId);
forward LoadPlayerState(PlayerId);
forward SavePlayerWeapons(PlayerId);
forward LoadPlayerWeapons(PlayerId);
forward Float:AddPlayerHealth(PlayerId, Float:Health, Add);
forward Float:AddPlayerArmour(PlayerId, Float:Armour, Add);
forward SetupPlayerForLogin(PlayerId);
forward PlayerSelectsSkin(PlayerId, SkinId);
forward PlayerIsHeadHunterOfPlayer(PlayerId, OtherPlayerId);
forward GetPlayerHeadHunters(PlayerId);
forward GetPlayerNextHeadHunterSlot(PlayerId);
forward GivePlayerHeadMoney(PlayerId, TargetPlayerId);
forward GivePlayerExperience(PlayerId, Experience);
forward GetPlayerKillType(PlayerId, KillerId);
forward PlayerDies(PlayerId, KillerId, Reason);
forward GetNextFreePlayerId();
forward ClearPlayer(PlayerId, Copy, FirstClear = false);
forward AddPlayer(AccountId, AccountPlayerId, Name[MAX_PLAYER_NAME]);
forward CopyPlayer(PlayerId, CopiedPlayerId);
forward RemovePlayer(PlayerId);
forward AddPlayerMapMarker(PlayerId, Icon, Float:PositionX, Float:PositionY, Float:PositionZ, Colour);
forward ClearAllPlayers();
//Profession Functions
forward AccountPlayerIsTargetOfAP(AccountId, AccountPlayerId, TargetAccountId, TargetAccountPlayerId);
forward PlayerIsTargetPlayer(PlayerId, TargetPlayerId);
forward CreateProfessionSelectionMenu(PlayerId);
forward PlayerSelectsProfession(PlayerId, ProfessionId);
forward CreateProfessionStartMenu(PlayerId);
forward PlayerStartsProfession(PlayerId, SkinId);
forward PlayerEndsProfession(PlayerId);
forward AddProfession(Name[MAX_PROFESSION_NAME], Price);
forward AddProfessionTarget(Experience, Money, RankPoints);
forward AddProfessionSkin(Skin, Name[MAX_PROFESSION_SKIN_NAME], Weapon1, Ammo1, Weapon2, Ammo2, Weapon3, Ammo3);
//Shop Functions
forward CreateShopMarkersForPlayer(PlayerId);
forward PlayerEntersShopCheckpoint(PlayerId, ShopId);
forward AddShop(Owner[MAX_SHOP_OWNER], Type, Float:CheckpointX, Float:CheckpointY, Float:CheckpointZ, Float:CheckpointSize, Float:ViewPositionX, Float:ViewPositionY, Float:ViewPositionZ, Float:ViewTargetX, Float:ViewTargetY, Float:ViewTargetZ);
//Shop Type Functions
forward CreateShopTypeMenu(PlayerId, ShopTypeId);
forward PlayerBuysShopTypeObject(PlayerId, ShopTypeObjectId);
forward AddShopType(Name[MAX_SHOP_TYPE_NAME], Icon);
forward AddShopTypeObject(Name[MAX_SHOP_TYPE_OBJECT_NAME], Price, Type, Id);
//Skin Functions
forward InitSkinPlayerClasses();
forward ShowSkinInfoForPlayer(PlayerId, SkinId);
forward AddSkin(Name[MAX_SKIN_NAME], Model);
//Town Functions
forward GetPlayerNearestHospital(PlayerId);
forward StartPlayerHospitalRespawn(PlayerId);
forward PlayerRespawningLoosesTime(PlayerId);
forward CreateTownMenu(PlayerId);
forward PlayerChoosesTown(PlayerId, TownId);
forward SpawnPlayerInTown(PlayerId, TownId);
forward  AddTown(Name[MAX_TOWN_NAME], Float:PositionX, Float:PositionY, Float:PositionZ, Float:PositionFacing, Float:HospitalPositionX, Float:HospitalPositionY, Float:HospitalPositionZ, Float:HospitalPositionFacing);
//Vehicle Functions
forward RefreshVehicle(VehicleId);
forward OpenVehicle(VehicleId);
forward CloseVehicle(VehicleId);
forward StopVehicle(VehicleId);
forward VehicleRequiresPetrol(VehicleId);
forward Float:AddVehiclePetrol(VehicleId, Float:Petrol, Add);
forward VehicleUsesPetrol(VehicleId, Float:Speed);
forward InitVehicleDataTimer();
forward TimerFunctionShowVehicleData();
forward AddVehicle(Type, Float:PositionX, Float:PositionY, Float:PositionZ, Float:Facing, Colour0, Colour1);
//Vehicle Type Functions
forward VehicleTypeRequiresPetrol(VehicleTypeId);
forward CreateVehicleTypeForPlayer(PlayerId, VehicleTypeId);
forward AddVehicleType(Name[MAX_VEHICLE_TYPE_NAME], Model, Price, Type, MaxPlaces, MaxPetrol, Profession);
forward GetVehicleTypeByModel(Model);
//Weapon Functions
forward AddWeapon(Model, Type, Ammo, Float:PositionX, Float:PositionY, Float:PositionZ);
//Weapon Type Functions
forward GetWeaponTypeByModel(Model);
forward GetKillReasonWeaponType(Reason);
forward AddAccountPlayerWeaponSkill(PlayerId, AccountId, AccountPlayerId, WeaponTypeTypeId, Value, Add);
forward AddPlayerWeaponSkill(PlayerId, WeaponTypeTypeId, Value, Add);
forward CreateWeaponTypeForPlayer(PlayerId, WeaponTypeId, Ammo);
forward AddWeaponType(Name[MAX_WEAPON_TYPE_NAME], Model, Price, Type, Ammo, GeneralAmmo);
forward AddWeaponTypeType(Name[MAX_WEAPON_TYPE_TYPE_NAME]);
forward AddWeaponTypeTypeReason(Id);

//-- Functions --
FixString(const String[]) //String soll eigentlich ein direkter Link auf die Variable sein  - &String, funktioniert aber nicht im Compiler
{
	new I0;
	new FixedString[MAX_STRING];
	new TargetIndex;
	TargetIndex = 0;
	// Copy for safety
	strcat(FixedString, String, sizeof(FixedString));
	//General Fix
	for (I0 = 0; I0 < strlen(String) && TargetIndex < MAX_STRING; I0++, TargetIndex++)
	{
		//German Fix
	    if (String[I0] == 'ä')
	    {
	        FixedString[TargetIndex] = 'a';
	        TargetIndex++;
	        
	        if (TargetIndex == MAX_STRING)
	        {
	            break;
     		}
	        
     		FixedString[TargetIndex] = 'e';
	    }
	    else if (String[I0] == 'ö')
	    {
	        FixedString[TargetIndex] = 'o';
	        TargetIndex++;

	        if (TargetIndex == MAX_STRING)
	        {
	            break;
     		}
	        
	        FixedString[TargetIndex] = 'e';
	    }
	    else if (String[I0] == 'ü')
	    {
	        FixedString[TargetIndex] = 'u';
	        TargetIndex++;

	        if (TargetIndex == MAX_STRING)
	        {
	            break;
     		}
	        
	        FixedString[TargetIndex] = 'e';
	    }
	    else if (String[I0] == 'ß')
	    {
	        FixedString[TargetIndex] = 's';
	        TargetIndex++;

	        if (TargetIndex == MAX_STRING)
	        {
	            break;
     		}
     		
	        FixedString[TargetIndex] = 's';
	    }
     	else if (String[I0] == '@')
	    {
	        FixedString[TargetIndex] = 'a';
	        TargetIndex++;

	        if (TargetIndex == MAX_STRING)
	        {
	            break;
     		}

	        FixedString[TargetIndex] = 't';
	    }
		else if (String[I0] == 0)
		{
			FixedString[TargetIndex] = 0;
			
			break;
		}
		else if (String[I0] < 0)
	    {
	        FixedString[TargetIndex] += 256;
	    }
	    else
	    {
	        FixedString[TargetIndex] = String[I0];
	    }
	}

	return FixedString;
}

StringIsNumeric(const String[])
{
	for (new I0 = 0; I0 < strlen(String); I0++)
	{
	    if (String[I0] > '9' || String[I0] < '0')
		{
			return false;
		}
	}
	return true;
}

Strtok(const String[], &Index)
{
	new Length = strlen(String);
	while ((Index < Length) && (String[Index] <= ' '))
	{
		Index++;
	}
	new Offset = Index;
	new Result[20];
	while ((Index < Length) && (String[Index] > ' ') && ((Index - Offset) < (sizeof(Result) - 1)))
	{
		Result[Index - Offset] = String[Index];
		Index++;
	}
	Result[Index - Offset] = EOS;
	return Result;
}

ConvertSeconds(Seconds)
{
	return (Seconds * 1000);
}

GetLanguageString(Label[])
{
	return GetDataBaseValue(PATH_LANGUAGE, Label);
}

//-- System Including --
#include "Systems\Dynamic\AccountFunctions"
#include "Systems\AreaFunctions"
#include "Systems\ChatCommandFunctions"
#include "Systems\CheckpointFunctions"
#include "Systems\DeathMatchFunctions"
#include "Systems\EmoticonFunctions"
#include "Systems\Dynamic\GangFunctions"
#include "Systems\GangHallFunctions"
#include "Systems\HouseFunctions"
#include "Systems\InterfaceFunctions"
#include "Systems\MainMenuFunctions"
#include "Systems\MissionFunctions"
#include "Systems\Dynamic\PlayerFunctions"
#include "Systems\ProfessionFunctions"
#include "Systems\ShopTypeFunctions"
#include "Systems\ShopFunctions"
#include "Systems\SkinFunctions"
#include "Systems\TownFunctions"
#include "Systems\VehicleTypeFunctions"
#include "Systems\VehicleFunctions"
#include "Systems\WeaponTypeFunctions"
#include "Systems\WeaponFunctions"

//-- Game Including --
#include "Game\Objects"

//-- Plugin Including --
/*
#if defined a_irc_used
	#include "Plugins\IRCPlugin"
#endif
*/
