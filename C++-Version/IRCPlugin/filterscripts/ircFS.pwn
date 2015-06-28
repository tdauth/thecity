// ***************************************************
//        IRC Plugin 1.1 ECHO FILTERSCRIPT          //
//   coded by Jacob. (irc.gtanet.com:6667 #jacob) 	//
// ***************************************************


// INCLUDES
// ----------------------------------------------
#include <a_samp>
#include <a_irc>

// DECLARATIONS
// ----------------------------------------------
new EchoConnection; 			// This will hold the connection ID for messages.
new EchoChan[10] = "#jacob";	// This is the channel you want your echo to be in, as well as the !say command.
new bool:TimerSet = false;  	// Prevents the timer from being set multiple times.
forward EventTimer();       	// Forward declaration for Event Timer (explained later)
new Connections = 0;

// Weapon name credits to Simon's Debug FS
new aWeaponNames[][32] = {
	{"Unarmed (Fist)"}, // 0
	{"Brass Knuckles"}, // 1
	{"Golf Club"}, // 2
	{"Night Stick"}, // 3
	{"Knife"}, // 4
	{"Baseball Bat"}, // 5
	{"Shovel"}, // 6
	{"Pool Cue"}, // 7
	{"Katana"}, // 8
	{"Chainsaw"}, // 9
	{"Purple Dildo"}, // 10
	{"Big White Vibrator"}, // 11
	{"Medium White Vibrator"}, // 12
	{"Small White Vibrator"}, // 13
	{"Flowers"}, // 14
	{"Cane"}, // 15
	{"Grenade"}, // 16
	{"Teargas"}, // 17
	{"Molotov"}, // 18
	{" "}, // 19
	{" "}, // 20
	{" "}, // 21
	{"Colt 45"}, // 22
	{"Colt 45 (Silenced)"}, // 23
	{"Desert Eagle"}, // 24
	{"Normal Shotgun"}, // 25
	{"Sawnoff Shotgun"}, // 26
	{"Combat Shotgun"}, // 27
	{"Micro Uzi (Mac 10)"}, // 28
	{"MP5"}, // 29
	{"AK47"}, // 30
	{"M4"}, // 31
	{"Tec9"}, // 32
	{"Country Rifle"}, // 33
	{"Sniper Rifle"}, // 34
	{"Rocket Launcher"}, // 35
	{"Heat-Seeking Rocket Launcher"}, // 36
	{"Flamethrower"}, // 37
	{"Minigun"}, // 38
	{"Satchel Charge"}, // 39
	{"Detonator"}, // 40
	{"Spray Can"}, // 41
	{"Fire Extinguisher"}, // 42
	{"Camera"}, // 43
	{"Night Vision Goggles"}, // 44
	{"Infrared Vision Goggles"}, // 45
	{"Parachute"}, // 46
	{"Fake Pistol"} // 47
};

new aDisconnectNames[][16] = {
	{"Timeout"}, // 0
	{"Left"}, // 1
	{"Kicked"} // 2
};

// onFilterScriptInit function
// ----------------------------------------------
// This is where you will typically call all of the required ircConnects.
// ircConnect will return the connection ID.  You will use this ID with all of your natives and callbacks.
public OnFilterScriptInit()
{
    EchoConnection = ircConnect("irc.gtanet.com", 6667, "jacobot");
	return 1;
}

public OnFilterScriptExit()
{
	ircDisconnect(EchoConnection);
	return 1;
}

// Event timer
// ----------------------------------------------
// The event timer is something new in 1.1. It tells the plugin to cycle through the event que and call each callback.
// It is REQUIRED if you want these functions to be called:
// ircOnUserSay, ircOnUserPart, and ircOnUserJoin.
public EventTimer()
{
	TimerSet = true;
	ircPollEvents();
}

public ircOnConnect(conn)
{
	ircJoinChan(conn, EchoChan);                    // join the echo channel
	if (!TimerSet) SetTimer("EventTimer", 500, 1);  // listen for callbacks from this channel
	Connections++;                                  // save number of connections
	ircSendRawData(conn, "PRIVMSG NickServ :IDENTIFY asd");
}

// ircIsOp stock
// This stock gets the user level in the requested channel, and compares with: ~, &, or @.
// If any of the levels match, stock returns true.  (else, stock return false)
// ----------------------------------------------
stock ircIsOp(conn,channel[],user[])
{
	new ircLevel[4];
	ircGetUserLevel(conn, channel, user, ircLevel);
	if(!strcmp(ircLevel, "~", true,1) || !strcmp(ircLevel, "&", true,1) || !strcmp(ircLevel, "@", true,1)) return 1;
	return 0;
}

// ircOnUserSay callback
// This is called when the plugin receives PRIVMSG: either you received a PM or a message in a joined channel.
// Commands are parsed using a modified DCMD (DracoBlue's Fast Command Processor)
// ----------------------------------------------
public ircOnUserSay(conn, channel[], user[], message[])
{

	if (message[0] != '!') return 1; 			// we only want messages starting with ~
 	new space = (strfind(message, " "));    	// find the location of the space
 	new cmdlen;                             	// holds the length of the command

 	if (space>=1)                           	// do we have a space?
 	{
		new lenmsg = strlen(message);           // get the length of the entire message
		cmdlen = ((lenmsg-(lenmsg-space))-1);   // generate length of command
  	}
  	else
  	{
		cmdlen = (strlen(message)-1);			// generate the length of command
	}
	if (cmdlen == 3)                            // is our command 3 characters long?
	{
		irccmd(say,3,conn,channel,user,message);
		irccmd(ban,3,conn,channel,user,message);
	}
	else if (cmdlen == 4)                       //is our command 4 characters long?
	{
		irccmd(join,4,conn,channel,user,message);
		irccmd(kick,4,conn,channel,user,message);
	}
	return 1;
}

// Command handling (using Fast Command Processor)
// ----------------------------------------------
// !say X       Sends X from the IRC channel to the game.
// !join X      Forces bot to join channel X.
// !kick X      Kicks player X (supports partial name).
// !ban X       Bans player X (supports partial name).

irccmd_say(conn, channel[], user[], params[])
{
	printinfo
	new msg[112];
	format(msg,sizeof(msg), "%s on IRC: %s", user, params);
	SendClientMessageToAll(0xFFFFFFFF, msg);
	format(msg, sizeof(msg), "2*** \2%s\2; on IRC: 2%s", user, params);
	ircSay(conn, channel, msg);
	return true;
}

irccmd_join(conn,  channel[], user[],  params[])
{
    if (!ircIsOp(conn,channel,user)) return false;
	printinfo
	new strmessage[64];
	format(strmessage, sizeof(strmessage), "2*** Joining channel \2;%s's\2;...", params);
	ircSay(conn, channel, strmessage);
	ircJoinChan(conn, params);
	return true;
}

irccmd_kick(conn,  channel[], user[],  params[]) // supports kicking by partial nickname
{
	if (!ircIsOp(conn,channel,user)) return false;
	printinfo
	new strname[16];
	new strmessage[64];
	for (new a=0; a<=MAX_PLAYERS; a++)
	{
	    if (IsPlayerConnected(a))
	    {
			GetPlayerName(a,strname,16);
			new space = (strfind(strname, params));
			if (space != -1)
			{
				Kick(a);
				format(strmessage, sizeof(strmessage), "2*** \2;%s\2; has been kicked by 2%s from IRC.", strname, user);
				SendClientMessageToAll(0xFFFFFFFF, strmessage);
				ircSay(conn,channel,strmessage);
				return true;
			}
		}
 	}
 	format(strmessage, sizeof(strmessage), "2*** \2;%s\2; is not found on the server.", params);
 	ircSay(conn,channel,strmessage);
	return true;
}

irccmd_ban(conn,  channel[], user[],  params[]) // supports banning by partial nickname
{
	if (!ircIsOp(conn,channel,user)) return false;
	printinfo
	new strname[16];
	new strmessage[64];
	for (new a=0; a<=MAX_PLAYERS; a++)
	{
	    if (IsPlayerConnected(a))
	    {
			GetPlayerName(a,strname,16);
			new space = (strfind(params, strname));
			if (space != -1)
			{
				Ban(a);
				format(strmessage, sizeof(strmessage), "2*** \2;%s\2; has been banned by 2%s from IRC.", strname, user);
				SendClientMessageToAll(0xFFFFFFFF, strmessage);
				ircSay(conn,channel,strmessage);
				return true;
			}
		}
 	}
 	format(strmessage, sizeof(strmessage), "2*** \2;%s\2; is not found on the server.", params);
 	ircSay(conn,channel,strmessage);
	return true;
}

// User join/part callbacks, called when a user joins the CHANNEL.  Not the game.
// I didn't do anything when this happened in the filterscript, but you can easily with the callbacks below.
// ----------------------------------------------
public ircOnUserPart(conn, channel[], user[])
{
	return 1;
}

public ircOnUserJoin(conn, channel[], user[])
{
	return 1;
}

// Some default SA:MP callbacks, we're just going to echo a few of them.
// ----------------------------------------------
public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

public OnPlayerConnect(playerid)
{
	new msg[128];
	new name[32];
	GetPlayerName(playerid, name, sizeof(name));
	format(msg, sizeof(msg), "2*** \2;%s\2; has joined the server.", name);
	ircSay(EchoConnection, EchoChan, msg);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	new msg[128];
	new name[32];
	GetPlayerName(playerid, name, sizeof(name));
	format(msg, sizeof(msg), "2*** \2;%s\2; has left the server. (2%s)", name, aDisconnectNames[reason]);
	ircSay(EchoConnection, EchoChan, msg);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	new msg[128];
	new name[32];
	GetPlayerName(playerid, name, sizeof(name));
	format(msg, sizeof(msg), "2[%i] <\2;%s\2;> %s", playerid, name, text); // [0] <jacob> hi
	ircSay(EchoConnection, EchoChan, msg);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	new msg[128];
	new playername[32];
	new killername[32];
	GetPlayerName(playerid,playername,32);
	if ((reason == 255) || (killerid == 255))
	{
	    format(msg, sizeof(msg), "*** \2;%s\2; killed himself.", playername);
	    goto snd;
	}
	else
	{
	    GetPlayerName(killerid,killername,32);
	    format(msg, sizeof(msg), "*** \2;%s\2; was killed by \2;%s\2;. (2%s)", playername, killername, aWeaponNames[reason]);
    }
snd:
	printf("msg: %s\n", msg);
	ircSay(EchoConnection, EchoChan, msg);
	return 1;
}

