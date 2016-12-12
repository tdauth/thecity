//*******************************************************************
//Main
//*******************************************************************
//To-Do-Liste
//- Profession-Functions überarbeiten
//- Die Längenüberprüfungen bei der Registrierung eines Accounts in eine Funktion fassen.
//- Eventuell statt MAX_PLAYERS PLAYERS nehmen
//- Hauptmenü fertigstellen
//- Account-Menü zur Verwaltung der Account-Player einbauen
//- Sprachensystem einbauen
//- Enums einbauen, herausfinden, wie man auf die Maximalgröße eines Enums zugreift. Enums sind immer ints
//- Zu den Interface-Klassen nichtdynamische Add-Funktionen erstellen
//- Spielmoduskonfigurationen über server.cfg-Datei möglich machen
//- Gang-Schlachten einbauen
//- GivePlayerMoney irgendwann mit AccountPlayerMoney verbinden, damit das Geld auch geladen werden kann
#include "General"

main()
{
	//Hier werden die Systeme initialisiert
	print("\n---------------------------------------");
	print("'The City' - Developed by Barade");
	print("---------------------------------------\n");
	print("Timer wurden initialisiert...");
	//Clearen der dynamischen Klassen
	ClearAllAccounts();
	ClearAllGangs();
	ClearAllPlayers();
	print("Dynamische Klassen wurden gesaeubert...");
	return true;
}

public OnGameModeInit()
{
    print("Spielmodus wird initialisiert...");
	//Hier werden die Eigenschaften und Objekte des Spielmodi initialisiert
	//Settings
	SetGameModeText("The City");
	ShowNameTags(true);
	ShowPlayerMarkers(true);
	EnableTirePopping(true);
	AllowInteriorWeapons(true);
	AllowAdminTeleport(true);
	SetDeathDropAmount(true);
	EnableZoneNames(true);
	EnableStuntBonusForAll(true);
	UsePlayerPedAnims();
	SetGravity(0.010200); //Nach dem Forum die beste Einstellung
	print("Einstellungen wurden uebernommen...");
	//Initialisierung der Timer (Muss eventuell in die OnGameModeInit-Funktion)
	InitTimeTimer();
	InitPlayerMessages();
	InitCheckpointTimer();
	InitAreaTimer();
	InitVehicleDataTimer();
	InitHouseTimer();
	InitMoneyTimer();
	//Objects
	InitAreas();
	printf("%d Gebiete", AREAS);
	CreateAreaGangZones();
	InitSkins();
	printf("%d Skins", SKINS);
	InitSkinPlayerClasses();
	InitTowns();
	printf("%d Staedte", TOWNS);
	InitVehicleTypes();
	printf("%d Fahrzeugtypen", VEHICLE_TYPES);
	InitVehicles();
	printf("%d Fahrzeuge", VEHICLES);
	InitWeaponTypes();
	printf("%d Waffentypen", WEAPON_TYPES);
	printf("%d Waffentyp-Typen", WEAPON_TYPE_TYPES);
	InitWeapons();
	printf("%d Waffen", WEAPONS);
	InitProfessions();
	printf("%d Berufe", PROFESSIONS);
	InitMissions();
	printf("%d Missionen", MISSIONS);
	InitShopTypes();
	printf("%d Ladentypen", SHOP_TYPES);
	InitShops();
	printf("%d Laeden", SHOPS);
	InitHouses();
	printf("%d Haeuser", HOUSES);
	InitGangHalls();
	printf("%d Gang-Hallen", GANG_HALLS);
	InitDeathMatches();
	printf("%d Death-Matches", DEATH_MATCHES);
	InitEmoticons();
	printf("%d Emoticons", EMOTICONS);
	print("Objekte wurden erzeugt...");
	
	new DB:db;
	db = db_open("thecity.db");
	
	//Load existing database
	if (db != DB:0)
	{
	    new DBResult:db_result;
		db_result = db_query(db, "SELECT * FROM `Accounts`;");
		
		if (db_result)
		{
			new AccountsCounter;
		    AccountsCounter = db_num_rows(db_result);
		    new I0;

		    for (I0 = 0; I0 < AccountsCounter; I0++)
		    {
		        new AccountName[MAX_STRING];
				db_get_field(db_result, 0, AccountName, MAX_STRING);
				new AccountPassword[MAX_STRING];
				db_get_field(db_result, 1, AccountPassword, MAX_STRING);
				
				ACCOUNT_PLAYER_ID[I0] = -1;
				strcat(ACCOUNT_NAME[I0], AccountName, MAX_ACCOUNT_NAME);
				strcat(ACCOUNT_PASSWORD[I0], AccountPassword, MAX_ACCOUNT_PASSWORD);
				ACCOUNT[I0] = I0;
				ACCOUNTS++;
				
				if (!db_next_row(db_result))
				{
				    break;
				}
	    	}
		}
		
		db_free_result(db_result);
		
		db_close(db);
	}

	return true;
}

public OnGameModeExit()
{
    print("On Game Mode Exit");
	KillTimer(TIMER_TIME);
	KillTimer(TIMER_AREA);
	KillTimer(TIMER_CHECKPOINT);
	KillTimer(TIMER_VEHICLE_DATA);
	KillTimer(TIMER_HOUSE);
	
	new DB:db;
	db = db_open("thecity.db");

	//Store all permanent data to database.
	if (db != DB:0)
	{
	    new DBResult:db_result;

		db_result = db_query(db, "DROP TABLE `Accounts`");
		db_free_result(db_result);
	    
		db_result = db_query(db, "CREATE TABLE IF NOT EXISTS `Accounts`(`ID` INTEGER PRIMARY KEY AUTOINCREMENT,`Name` VARCHAR(255) NOT NULL)");
		db_free_result(db_result);

		new I0;
		
		for (I0 = 0; I0 < ACCOUNTS; I0++)
	    {
	        new Query[MAX_STRING];
	        format(Query, MAX_STRING, "INSERT INTO `Accounts` (`Name`, `Password`) VALUES ('%s', '%s')", ACCOUNT_NAME[I0], ACCOUNT_PASSWORD[I0]);
		    db_result = db_query(db, Query);
		    db_free_result(db_result);
    	}
		
	    db_close(db);
	}
	
	return true;
}

public OnRconCommand(cmd[])
{
    print("On Rcon Command");
    return true;
}

public OnObjectMoved(objectid)
{
    print("On Object Moved");
    return true;
}

public OnPlayerObjectMoved(playerid, objectid)
{
    print("On Player Object Moved");
    return true;
}

public OnPlayerConnect(playerid)
{
    print("On Player Connect");
    new PlayerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, PlayerName, sizeof(PlayerName));
    new PlayerId = AddPlayer(-1, -1, PlayerName);
    if (PlayerId != -1)
    {
        //TogglePlayerSpectating(playerid, true);
    	SendMessageToPlayer(playerid, MESSAGE_TYPE_INFO, "Willkommen im Rollenspiel-Spielmodus 'The City'~n~~y~Regeln~n~~w~- Cheats sind nicht erlaubt~n~- Spawn-Kills sind nicht erlaubt~n~- Ungebührliches Verhalten gegenüber anderer Spieler ist nicht erlaubt~n~~y~Ersteller: ~w~Barade");
		//  ConvertSeconds(8), MESSAGE_TYPE_INFO,
    	SendMessageToPlayer(PlayerId, MESSAGE_TYPE_INFO, "~y~Anmeldung~n~~w~- Geben Sie '/register [Benutzername] [Passwort] [Email-Addresse] [Landeskürzel]' im Chat ein, um sich zu registrieren.~n~- Falls Sie bereits ein Benutzerkonto besitzen, geben Sie '/login [Benutzername] [Passwort]' im Chat ein, um sich anzumelden.");
		//PlayerPlaySound(playerid, 1068, -783.8020, 495.5815, 1376.1953);
    	new InfoMessage[MAX_STRING];
		format(InfoMessage, sizeof(InfoMessage), "%s ist dem Server beigetreten. Nummer %d", PLAYER_NAME[playerid], PlayerId);
		SendClientMessageToAllPlayers(MESSAGE_TYPE_SERVER, InfoMessage);
	}
	else
	{
	    Kick(playerid);
	    SendClientMessageToPlayer(playerid, MESSAGE_TYPE_SERVER, "Der Server ist voll.");
	}
	return true;
}

public OnPlayerDisconnect(playerid)
{
    print("On Player Disconnect");
    RemovePlayer(playerid);
    new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "%s hat den Server verlassen.", PLAYER_NAME[playerid]);
	SendClientMessageToAllPlayers(MESSAGE_TYPE_SERVER, InfoMessage);
	return true;
}

public OnPlayerSpawn(playerid)
{
    print("On Player Spawn");
	if (PLAYER_ACCOUNT[playerid] == -1)
	{
	    TogglePlayerControllable(playerid, false);
 	   	SendClientMessageToPlayer(playerid, MESSAGE_TYPE_INFO, "Sie wurden vom Server gekickt, da Sie sich nicht angemeldet haben.");
 	   	Kick(playerid);
	}
	else
	{
	    TogglePlayerClock(playerid, true);
	    InitPlayerMiniMap(playerid);
 		PreloadEmoticonLibraries(playerid);
	}
	return true;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    print("On Player Death");
    PlayerDies(playerid, killerid, reason);
	return true;
}

public OnPlayerText(playerid, text[])
{
    print("On Player Text");
	SavePlayerChatLogData(playerid, text);
	return true;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    print("On Player Command Text");
    new Command[MAX_STRING];
	new Index;
	new ValueString[MAX_STRING];
	SavePlayerChatLogData(playerid, cmdtext);
	Command = Strtok(cmdtext, Index);
	if (strcmp(Command, "/register", true) == 0)
	{
	    new RegisterName[MAX_STRING];
		new RegisterPassword[MAX_STRING];
	    new RegisterEmail[MAX_STRING];
	    new RegisterCountry[MAX_STRING];
	    ValueString = Strtok(cmdtext, Index);
        RegisterName = ValueString;
		ValueString = Strtok(cmdtext, Index);
		RegisterPassword = ValueString;
	    ValueString = Strtok(cmdtext, Index);
	    RegisterEmail = ValueString;
	    ValueString = Strtok(cmdtext, Index);
	    RegisterCountry = ValueString;
	    AccountRegister(playerid, RegisterName, RegisterPassword, RegisterEmail, RegisterCountry);
		return true;
	}
	else if (strcmp(Command, "/login", true) == 0)
	{
		new LoginName[MAX_STRING];
	    new LoginPassword[MAX_STRING];
	    new LoginPlayerName[MAX_STRING];
	    ValueString = Strtok(cmdtext, Index);
        LoginName = ValueString;
        ValueString = Strtok(cmdtext, Index);
        LoginPassword = ValueString;
        ValueString = Strtok(cmdtext, Index);
        LoginPlayerName = ValueString;
        AccountLogin(playerid, LoginName, LoginPassword, LoginPlayerName);
		return true;
	}
	//Hunt
	else if (strcmp(Command, "/hunt", true) == 0)
	{
	    new Otherplayerid[MAX_STRING];
	    new Money[MAX_STRING];
	    ValueString = Strtok(cmdtext, Index);
        Otherplayerid = ValueString;
        ValueString = Strtok(cmdtext, Index);
        Money = ValueString;
        ChatCommandAddPlayerHeadMoney(playerid, strval(Otherplayerid), strval(Money));
		return true;
	}
	//Give
	else if (strcmp(Command, "/give", true) == 0)
	{
	    new Otherplayerid[MAX_STRING];
	    new Money[MAX_STRING];
	    ValueString = Strtok(cmdtext, Index);
        Otherplayerid = ValueString;
        ValueString = Strtok(cmdtext, Index);
        Money = ValueString;
        ChatCommandPlayerGivesPM(playerid, strval(Otherplayerid), strval(Money));
		return true;
	}
	//Gang Name
	else if (strcmp(Command, "/gangname", true) == 0)
	{
	    new GangName[MAX_GANG_NAME];
	    ValueString = Strtok(cmdtext, Index);
		format(GangName, sizeof(GangName), "%s", ValueString); //Wegen der String-Länge
       	ChatCommandPlayerSetsGangName(playerid, GangName);
		return true;
	}
	//Gang Invite
	else if (strcmp(Command, "/ganginvite", true) == 0)
	{
	    new Otherplayerid[MAX_STRING];
	    ValueString = Strtok(cmdtext, Index);
        Otherplayerid = ValueString;
       	ChatCommandInvitePlayerInGang(playerid, strval(Otherplayerid));
		return true;
	}
	//Exit
	else if (strcmp(Command, "/exit", true) == 0)
	{
	    CommandExit(playerid);
		return true;
	}
	//Admin
	else if (strcmp(Command, "/admin", true) == 0)
	{
	    CommandTurnPlayerToAdmin(playerid);
		return true;
	}
	//Heli
	else if (strcmp(Command, "/heli", true) == 0)
	{
	    if (IsPlayerAdmin(playerid))
	    {
		    new Float:x, Float:y, Float:z;
		    // Use GetPlayerPos, passing the 3 float variables we just created
		    GetPlayerPos(playerid, x, y, z);
     		RefreshVehicle(AddVehicle(VEHICLE_TYPE_MAVERICK, x, y, z, 0.0000, -1, -1)); //Maverick
     		print("Spawned heli!");
		}
		
		return true;
	}
	//Emoticons
	else
	{
	    CommandPlayPlayerEmoticon(playerid, Command);
	    return true;
	}
}

public OnPlayerRequestClass(playerid, classid)
{
    print("On Player Request Class");
    if (PLAYER_ACCOUNT[playerid] != -1)
    {
		ShowSkinInfoForPlayer(playerid, classid);
		return true;
	}
	
	return false;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    print("On Player State Change");
	return true;
}

public OnPlayerPrivmsg(playerid, recieverid, text[])
{
    print("On Player Privmsg");
	new SaveText[MAX_STRING];
	format(SaveText, sizeof(SaveText), " zu %s: %s", PLAYER_NAME[recieverid], text);
    SavePlayerChatLogData(playerid, SaveText);
	return true;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
    print("On Player Pick Up Pickup");
    if (WEAPON_TYPE[pickupid] != -1)
    {
   		CreateWeaponTypeForPlayer(playerid, WEAPON_TYPE[pickupid], WEAPON_AMMO[pickupid]);
	}
	return true;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
    print("On Player Selected Menu Row");
	new MenuType = PLAYER_MENU_TYPE[playerid]; //Wird in lokale Variable gespeichert, da es danach gecleared wird.
	DestroyAllCustomMenuesForPlayer(playerid);
	SetCameraBehindPlayer(playerid);
	TogglePlayerControllable(playerid, true);
	switch (MenuType)
	{
		//Main Menu
		case MENU_TYPE_MAIN_MENU:
		{
     		PlayerSelectsMainMenuItem(playerid, row);
	   		return true;
		}
		//Account Menu
		case MENU_TYPE_ACCOUNT_MENU:
		{
     		PlayerSelectsAccountMenuItem(playerid, row);
	   		return true;
		}
		//Account Player Menu
		case MENU_TYPE_ACCOUNT_PLAYER_MENU:
		{
     		PlayerSelectsAPMenuItem(playerid);
	   		return true;
		}
		//Help Menu
		case MENU_TYPE_HELP_MENU:
		{
     		PlayerSelectsHelpMenuItem(playerid, row);
	   		return true;
		}
		//Town Selection Menu
		case MENU_TYPE_TOWN_SELECTION:
		{
	    	PlayerChoosesTown(playerid, row);
	    	return true;
		}
		//Houses Menu
		case MENU_TYPE_HOUSES:
  		{
		  	CreateHouseSettingsMenu(playerid, row); //Hausnummer wird übergeben
			return true;
  		}
		//House Settings Menu
		case MENU_TYPE_HOUSE_SETTINGS:
  		{
  		    if (row == 0)
  		    {
  		        CreateHouseSellingMenu(playerid);
  		    }
  		    else
  		    {
  				ShowHouseCameraForPlayer(playerid, PLAYER_MENU[playerid], (row - 1));
			}
	  		return true;
  		}
  		case MENU_TYPE_HOUSE_SELLING:
  		{
			if (row == 0)
  		    {
	  		    PlayerSellsHouse(playerid, PLAYER_MENU[playerid]);
			}
			
			CreateMainMenuForPlayer(playerid);
			 
			 return true;
  		}
  		//Gang Creation Menu
		case MENU_TYPE_GANG_CREATION:
  		{
  		    PlayerCreatesGang(playerid, row);
            return true;
  		}
  		//Gang Menu
		case MENU_TYPE_GANG:
  		{
  		    new AccountId = PLAYER_ACCOUNT[playerid];
  		    new Accountplayerid = PLAYER_ACCOUNT_PLAYER[playerid];
  		    new GangId = ACCOUNT_P_GANG[AccountId][Accountplayerid];
  		    if (ACCOUNT_P_GANG_RANK[AccountId][Accountplayerid] != GANG_RANK_BOSS && row == 0)
 			{
				PlayerLeavesGang(playerid, GangId);
				CreateMainMenuForPlayer(playerid);
			}
			else if (GANG_GANG_HALL[GangId] == -1 && row == 0)
			{
	    		CreateBuyGangHallMenu(playerid);
			}
			else if (GANG_GANG_HALL[GangId] != -1 && !PLAYER_IS_IN_GANG_HALL[playerid])
			{
	    		PlayerEntersGangHall(playerid);
	    		CreateMainMenuForPlayer(playerid);
			}
			else if (GANG_GANG_HALL[GangId] != -1)
			{
	    		PlayerLeavesGangHall(playerid);
	    		CreateMainMenuForPlayer(playerid);
			}
            return true;
  		}
  		//Gang Hall Selection Menu
		case MENU_TYPE_GANG_HALL_SELECTION:
  		{
  		    GangBuysGangHall(playerid, row);
  		    CreateMainMenuForPlayer(playerid);
            return true;
  		}
		//Profession Selection Menu
		case MENU_TYPE_PROFESSION_SELECTION:
		{
	    	PlayerSelectsProfession(playerid, row);
	    	return true;
		}
		//Profession Start Menu
		case MENU_TYPE_PROFESSION_START:
		{
	    	PlayerStartsProfession(playerid, row);
	    	return true;
		}
		//Shop Menu
		case MENU_TYPE_SHOP:
  		{
	    	PlayerBuysShopTypeObject(playerid, row);
	    	return true;
  		}
		//House Menu
		case MENU_TYPE_HOUSE:
  		{
	   		PlayerBuysHouse(playerid, PLAYER_MENU[playerid]);
			return true;
		}
		//Death Match Menu
		case MENU_TYPE_DEATH_MATCH:
		{
		    //Enter Death Match
		    if (PLAYER_DEATH_MATCH[playerid] == -1)
    		{
    		    SetupDeathMatchSkinSelection(playerid, PLAYER_MENU[playerid]);
    		}
			//Repick Skin
			else if (row == 0)
			{
				SetupDeathMatchSkinSelection(playerid, PLAYER_DEATH_MATCH[playerid]);
			}
			//Leave Death Match
			else if (row == 1)
    		{
    		    PlayerLeavesDeathMatch(playerid);
    		}
		    return true;
		}
		//Gang Invitation
		case MENU_TYPE_GANG_INVITATION:
  		{
    		PlayerJoinsGang(playerid, PLAYER_MENU[playerid]);
    		return true;
  		}
	}
	return false;
}

public OnPlayerExitedMenu(playerid)
{
    print("On Player Exited Menu");
	new MenuType = PLAYER_MENU_TYPE[playerid];
    DestroyAllCustomMenuesForPlayer(playerid);
	SetCameraBehindPlayer(playerid);
	TogglePlayerControllable(playerid, true);
	switch (MenuType)
	{
	    //Main Menu
		case MENU_TYPE_MAIN_MENU:
		{
     		SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Hauptmenü geschlossen.");
     		return true;
		}
		//Account Menu
		case MENU_TYPE_ACCOUNT_MENU:
		{
		    CreateMainMenuForPlayer(playerid);
     		SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Benutzermenü geschlossen.");
     		return true;
		}
		//Account Player Menu
		case MENU_TYPE_ACCOUNT_PLAYER_MENU:
		{
		    CreateAccountMenuForPlayer(playerid);
     		SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Spielermenü geschlossen.");
     		return true;
		}
		//Help Menu
		case MENU_TYPE_HELP_MENU:
		{
		    CreateMainMenuForPlayer(playerid);
     		SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Hilfemenü geschlossen.");
     		return true;
		}
		//Town Selection Menu
		case MENU_TYPE_TOWN_SELECTION:
		{
     		CreateTownMenu(playerid);
	    	return true;
		}
		//Houses Menu
		case MENU_TYPE_HOUSES:
  		{
  	    	CreateMainMenuForPlayer(playerid);
	    	SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Häuser-Liste geschlossen.");
    		return true;
  		}
  		//House Settings Menu
  		case MENU_TYPE_HOUSE_SETTINGS:
  		{
  		    LoadPlayerInterior(playerid);
  	    	SetCameraBehindPlayer(playerid);
  	    	CreateHousesMenu(playerid);
  	    	SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Haus-Einstellungen geschlossen.");
    		return true;
  		}
  		//Gang Creation Menu
		case MENU_TYPE_GANG_CREATION:
  		{
  	    	CreateMainMenuForPlayer(playerid);
  	    	SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Gang-Gründung abgebrochen.");
    		return true;
  		}
		//Gang Menu
		case MENU_TYPE_GANG:
  		{
  	    	CreateMainMenuForPlayer(playerid);
  	    	SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Gang-Verwaltung geschlossen.");
    		return true;
  		}
  		//Gang Hall Selection Menu
		case MENU_TYPE_GANG_HALL_SELECTION:
  		{
  		    CreateGangMenu(playerid);
  		    SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Gang-Hallen-Auswahl geschlossen.");
            return true;
  		}
  		//Profession Selection Menu
		case MENU_TYPE_PROFESSION_SELECTION:
		{
			CreateMainMenuForPlayer(playerid);
	 		SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Berufswahl abgebrochen.");
	    	return true;
		}
		//Profession Start Menu
		case MENU_TYPE_PROFESSION_START:
		{
			CreateMainMenuForPlayer(playerid);
	 		SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Berufsstart abgebrochen.");
	    	return true;
		}
		//Shop Menu
		case MENU_TYPE_SHOP:
  		{
     		SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Einkauf abgebrochen.");
    		return true;
  		}
  		//House Menu
  		case MENU_TYPE_HOUSE:
  		{
	    	SetCameraBehindPlayer(playerid);
	    	SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Haus-Besichtigung abgebrochen.");
    		return true;
  		}
  		//Death Match Menu
		case MENU_TYPE_DEATH_MATCH:
		{
		    SetCameraBehindPlayer(playerid);
	    	SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Death-Match-Menü geschlossen.");
    		return true;
		}
  		//Gang Invitation
		case MENU_TYPE_GANG_INVITATION:
  		{
  		    SetCameraBehindPlayer(playerid);
	    	SendClientMessageToPlayer(playerid, MESSAGE_TYPE_ERROR, "Gang-Einladung abgelehnt.");
	    	return true;
  		}
	}
    return false;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    print("On Player Key State Change");
	//Main Menu
	if (newkeys == KEY_MAIN_MENU && !PLAYER_IS_IN_DM_SELECTION[playerid]) //Tab Key
	{
		if (!IsPlayerInAnyVehicle(playerid))
 		{
 			CommandCreateMainMenuForPlayer(playerid);
		}
	}
	//Mission
	else if (newkeys == KEY_START_MISSION) //2 Key
	{
 		if (PLAYER_MISSION[playerid] == -1)
 		{
     		PlayerStartsMission(playerid);
 		}
		else
		{
  			MissionLosesTime(playerid, PLAYER_MISSION[playerid]);
		}
	}
	//Player Is In Death Match Selection
	else if (PLAYER_IS_IN_DM_SELECTION[playerid])
	{
		//Death Match Selection Next
		if (newkeys == KEY_CHANGE_DM_SKIN_NEXT) //6
		{
		    print("Next Skin Key");
			ChangeDeathMatchSkin(playerid, PLAYER_DEATH_MATCH[playerid], true);
		}
		//Death Match Selection Last
		else if (newkeys == KEY_CHANGE_DM_SKIN_LAST) //4
		{
		    print("Last Skin Key");
			ChangeDeathMatchSkin(playerid, PLAYER_DEATH_MATCH[playerid], false);
		}
		//Death Match Selection Select
		else if (newkeys == KEY_SELECT_DM_SKIN) //Fire
		{
			SelectDeathMatchSkin(playerid, PLAYER_DEATH_MATCH[playerid], PLAYER_DEATH_MATCH_SKIN[playerid]);
		}
	}
	//Player Plays Emoticon
	else if (PLAYER_PLAYS_EMOTICON[playerid])
	{
	    print("Plays Emoticon");
	    if (newkeys == KEY_CANCEL_EMOTICON) //Sprint
	    {
			print("Cancel Key");
	        ResetPlayerEmoticon(playerid);
	        KillTimer(PLAYER_EMOTICON_TIMER[playerid]);
	    }
	}
	return true;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
    print("On Player Interior Change");
    return true;
}

public OnPlayerEnterCheckpoint(playerid)
{
    print("On Player Enter Checkpoint");
	switch(PLAYER_CHECKPOINT_TYPE[playerid])
	{
		case CHECKPOINT_TYPE_SHOP:
		{
			PlayerEntersShopCheckpoint(playerid, PLAYER_CHECKPOINT[playerid]);
		}
		case CHECKPOINT_TYPE_HOUSE:
		{
	    	PlayerEntersHouseCheckpoint(playerid, PLAYER_CHECKPOINT[playerid]);
		}
		case CHECKPOINT_TYPE_DEATH_MATCH:
		{
	    	 PlayerEntersDMCheckpoint(playerid, PLAYER_CHECKPOINT[playerid]);
		}
	}
	return true;
}

public OnPlayerLeaveCheckpoint(playerid)
{
    print("On Player Leave Checkpoint");
	return true;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
    print("On Player Enter Race Checkpoint");
    new MissionId = PLAYER_MISSION[playerid];
	if (PLAYER_MISSION_CHECKPOINT[playerid] < MISSION_CHECKPOINTS[MissionId])
	{
	    PLAYER_MISSION_CHECKPOINT[playerid]++;
	}
	else
	{
	    PlayerCompletesMission(playerid, MissionId);
	}
	return true;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
    print("On Player Leave Race Checkpoint");
	return true;
}

public OnVehicleSpawn(vehicleid)
{
    print("On Vehicle Spawn");
    RefreshVehicle(vehicleid);
	return true;
}

public OnVehicleDeath(vehicleid, killerid)
{
    print("On Vehicle Death");
	return true;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    print("On Player Enter Vehicle");
    if (VEHICLE_USED_PLACES[vehicleid] < VEHICLE_TYPE_MAX_PLACES[VEHICLE_TYPE[vehicleid]])
    {
        VEHICLE_USED_PLACES[vehicleid]++;
        //Mission Vehicle
        if (PlayerIsInMissionVehicle(playerid, vehicleid) != -1)
        {
        	PlayerEntersMissionVehicle(playerid);
        }
    }
    else
    {
        RemovePlayerFromVehicle(vehicleid);
    }
	return true;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
    print("On Player Exit Vehicle");
    VEHICLE_USED_PLACES[vehicleid]--;
	return true;
}

public OnPlayerRequestSpawn(playerid)
{
	if (PLAYER_ACCOUNT[playerid] != -1)
	{
	    SetCameraBehindPlayer(playerid);
		CreateTownMenu(playerid);
		
		return true;
	}
	
	return false;
}
