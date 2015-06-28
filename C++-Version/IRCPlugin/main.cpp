//----------------------------------------------------------
//
//   SA:MP Multiplayer Modification For GTA:SA
//   Copyright 2004-2007 SA:MP Team
//
//----------------------------------------------------------
// cross-compatible IRC sockets (by Jacob)

#include "../SDK/amx/amx.h"
#include "../SDK/plugincommon.h"
#include "IRC.h"             // cross-compatible IRC class
#include "XPThreads.h"       // cross-compatible thread header
#include <malloc.h>
#include <stdarg.h>
#include "main.h"

#define Listen(i) while(true)							\
				  {										\
				  if (samp_conn[i].message_loop() == -5)\
				  {										\
				   	  break;							\
				  }										\
				  thr_sleep(50); 						}		
				  
// Declarations and prototypes
//----------------------------------------------------------
IRC samp_conn[MAX_CONNECTIONS];
bool bConn[MAX_CONNECTIONS];
AMX *pAMX;
int NUM_CONNECTIONS = 0;
XPThreads* ListenMessages[5];
void **ppPluginData;
extern void *pAMXFunctions;
char GlobalBuffer[3024];
bool bCreatedThread;
int ex_tokens(char *string, char c, char ***tokens);  		
list<string> functions;
bool bParseFunctions = false;
logprintf_t logprintf;

// Support stuff
//----------------------------------------------------------
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

// Called when IRC plugin is loaded
//----------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	savelogprintf(logprintf);
	logprintf( "*** IRC plugin v1.1 [by jacob] loaded!" );
	return true;
}

// Called when IRC plugin is unloaded
//----------------------------------------------------------
PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	logprintf( "*** IRC plugin v1.1 [by jacob] unloaded!" );
	int i;
	for (i=1; i<=MAX_CONNECTIONS; i++)
	{
	 	if (samp_conn[i].connected) samp_conn[i].disconnect();
	 	if (ListenMessages[i]) delete ListenMessages[i];
 	}
}


// These are the threads that listen for data from the IRC server. (max 5 connections)
//----------------------------------------------------------
#if defined WIN32
unsigned long listen1(void* nothing)
#else
void* listen1(void* nothing)
#endif
{
 	  Listen(1);
	  return 0;
}

#if defined WIN32
unsigned long listen2(void* nothing)
#else
void* listen2(void* nothing)
#endif
{
 	  Listen(2);
	  return 0;
}

#if defined WIN32
unsigned long listen3(void* nothing)
#else
void* listen3(void* nothing)
#endif
{
 	  Listen(3);
	  return 0;
}

#if defined WIN32
unsigned long listen4(void* nothing)
#else
void* listen4(void* nothing)
#endif
{
 	  Listen(4);
	  return 0;
}

#if defined WIN32
unsigned long listen5(void* nothing)
#else
void* listen5(void* nothing)
#endif
{
 	  Listen(5);
	  return 0;
}


// PAWN function that allows you to join channels
//----------------------------------------------------------
static cell AMX_NATIVE_CALL n_JoinChan( AMX* amx, cell* params )
{
	if (params[0] != 8)
	{
 	   logprintf("*** ircJoinChan expecting 2 parameters, not %d", params[0]/4);
 	   return 0;
   }
    int conn; char* channel;
    conn = params[1];
    amx_StrParam(amx, params[2], channel);
    //logprintf("Joining %s...", channel);
    samp_conn[conn].join(channel);
    return 0;
}

// PAWN function that allows you to get a user's level
//----------------------------------------------------------
static cell AMX_NATIVE_CALL n_GetUserLevel( AMX* amx, cell* params )
{
	if (params[0] != 16)
	{
 	   logprintf("*** ircGetUserLevel expecting 4 parameters, not %d", params[0]/4);
 	   return 0;
   }
    int conn; char* channel; char* user; cell* dest;
    conn = params[1];
    amx_StrParam(amx, params[2], channel);
    amx_StrParam(amx, params[3], user);
	amx_GetAddr(amx,params[4],&dest);
    int chanindex = samp_conn[conn].GetChanIndex(channel);
    string tmpret(samp_conn[conn].getuserlevel(chanindex, user));
    //printf("GetUserLevel(%i, %s) = %s.\n", chanindex, user, tmpret.c_str());
    if ((bConn[conn]) && (chanindex != -1))
    {
       amx_SetString(dest, tmpret.c_str(), 0, 0, 4);
       return 1;
	}
	return -1;
}
   
// PAWN function that allows you to set channel modes
//----------------------------------------------------------
static cell AMX_NATIVE_CALL n_SetMode( AMX* amx, cell* params )
{
	if (params[0] != 16)
	{
 	   logprintf("*** ircSetMode expecting 4 parameters, not %d", params[0]/4);
 	   return 0;
   }
    int conn; char* channel; char* modes; char* nicks;
    conn = params[1];
    amx_StrParam(amx, params[2], channel);
    amx_StrParam(amx, params[3], modes);
    amx_StrParam(amx, params[4], nicks);
	samp_conn[conn].mode(channel,modes,nicks);
    return 01;
}

// PAWN function that allows you to part channels
//----------------------------------------------------------
static cell AMX_NATIVE_CALL n_PartChan( AMX* amx, cell* params )
{
	if (params[0] != 8)
	{
 	   logprintf("*** ircPartChan expecting 2 parameters, not %d", params[0]/4);
 	   return 0;
   }
    int conn; char* channel;
    conn = params[1];
    amx_StrParam(amx, params[2], channel);   
    samp_conn[conn].part(channel);
    return 1;
}


// PAWN callback, called when a connection is established to the IRC server
//----------------------------------------------------------
int OnConnect(int conn)
{
    int idx; cell ret;
//    logprintf("Connection established! (connection %i)", conn);
    bConn[conn] = true;
    if (!amx_FindPublic(pAMX, "ircOnConnect", &idx))
	{
	  amx_Push(pAMX, conn); 								
	  amx_Exec(pAMX, &ret, idx);
	}
	return 0;
}




// IRC callback, called when a nick says something in an active channel (in IRC thread)
//----------------------------------------------------------
void OnPrivMsg(int conn, char* channel, char* nick, char* msg)
{
  char tmpstr[512];
  sprintf(tmpstr, "%i\001%i\001%s\001%s\001%s", conn, F_PRIVMSG, channel, nick, msg);
  functions.push_back(tmpstr);
  bParseFunctions = true;
}


// PAWN callback, this is called by the correct thread and directly calls ircOnUserSay.
//----------------------------------------------------------	
void OnPrivMsgEx(int conn, const char* globalChan, const char* globalNick, const char* globalMsg)
{
	int idx = 0;
	//printf("OnPrivMsgEx(%i, %s, %s, %s);\n", conn, globalMsg, globalNick, globalChan);						  
	if (!amx_FindPublic(pAMX, "ircOnUserSay", &idx))
	{   
		//printf("Found ircOnUserSay!\n");   
		string::size_type loc;
		string tmp(globalMsg);
again:
		loc = tmp.find("%", 0);     
		if( loc != string::npos )
		{
		 	tmp.replace(loc,1,"#"); // replace with #
			goto again;
		}
          
	    cell amx_addr1, *phys_addr, amx_addr2, amx_addr3;  cell ret;
		amx_PushString(pAMX, &amx_addr1, &phys_addr, tmp.c_str(), 0, 0);
		amx_PushString(pAMX, &amx_addr2, &phys_addr, globalNick, 0, 0);
		amx_PushString(pAMX, &amx_addr3, &phys_addr, globalChan, 0, 0);
		amx_Push(pAMX, conn);
		amx_Exec(pAMX, &ret, idx);
		amx_Release(pAMX, amx_addr1);
		amx_Release(pAMX, amx_addr2);
		amx_Release(pAMX, amx_addr3);
	 }
}

// IRC callback, called when a nick parts joins an active channel (in IRC thread)
//----------------------------------------------------------
void OnUserJoin(int conn, char* channel, char* nick)
{
  char tmpstr[256];
  sprintf(tmpstr, "%i\001%i\001%s\001%s", conn, F_USERJOIN, channel, nick);
  functions.push_back(tmpstr);
  bParseFunctions = true;
}

// PAWN callback, this is called by the correct thread and directly calls ircOnUserJoin.
//----------------------------------------------------------	
void OnUserJoinEx(int conn, const char* channel, const char* nick)
{
    int idx; cell ret;
    if (!amx_FindPublic(pAMX, "ircOnUserJoin", &idx))
    {
        cell amx_addr1, *phys_addr, amx_addr2; 
        amx_PushString(pAMX, &amx_addr1, &phys_addr, nick, 0, 0);
        amx_PushString(pAMX, &amx_addr2, &phys_addr, channel, 0, 0);
        amx_Push(pAMX, conn);
        amx_Exec(pAMX, &ret, idx);
        amx_Release(pAMX, amx_addr1);
        amx_Release(pAMX, amx_addr2);
    }
	return;
}

// IRC callback, called when a nick parts parts an active channel (in IRC thread)
//----------------------------------------------------------
void OnUserPart(int conn, char* channel, char* nick)
{
  char tmpstr[256];
  sprintf(tmpstr, "%i\001%i\001%s\001%s", conn, F_USERPART, channel, nick);
  functions.push_back(tmpstr);
  bParseFunctions = true;
}

// PAWN callback, this is called by the correct thread and directly calls ircOnUserPart.
//----------------------------------------------------------
void OnUserPartEx(int conn, const char* channel, const char* nick)
{
    int idx; cell ret;
    if (!amx_FindPublic(pAMX, "ircOnUserPart", &idx))
    {
        cell amx_addr1, *phys_addr, amx_addr2;
        amx_PushString(pAMX, &amx_addr1, &phys_addr, nick, 0, 0);
        amx_PushString(pAMX, &amx_addr2, &phys_addr, channel, 0, 0);
        amx_Push(pAMX, conn);
        amx_Exec(pAMX, &ret, idx);
        amx_Release(pAMX, amx_addr1);
        amx_Release(pAMX, amx_addr2);
    }
	return;
}

// This function MUST be called from a timer in the PAWN script.
// This allows me to append literally hundreds of events and parameters
// into a global buffer, parse them individually, and call each one from
// the same thread.  This prevents major segmentation faults in *nix.
//----------------------------------------------------------
void ParseBuffer()
{
 	 if (!bParseFunctions) return; // If we have no functions to parse, fuck it.
 	 //printf("[buffer] Parsing buffer.\n");
 	 int params=0, event, conn;
 	 string chan;
	 string nick; 
	 string msg; 
 	 //printf("[buffer] declaring string iterator functionIter\n");
 	 list<string>::iterator functionIter;
 	 for (functionIter=functions.begin(); functionIter!=functions.end(); ++functionIter) {
   	 {	
	 	 //printf("[buffer] tokenizing functionIter '%s'\n", (*functionIter).c_str());
	 	 vector<string> tokens = tokenize(*functionIter, "\001");
	 	// printf("[buffer] string has been tokenized! looping through tokens..\n");
	 	 for (vector<string>::iterator it = tokens.begin(); it!=tokens.end(); ++it)
	 	 {
	        params++;
	        switch (params)
	        {
  		 	    case 1: // connection ID
				{
				 	 //printf("[buffer] Setting connection ID (%s)\n", (*it).c_str());
				 	 conn = atoi((*it).c_str());
				 	 break;
				}
				case 2: // event ID
				{
				 	 //printf("[buffer] Setting event ID (%s)\n", (*it).c_str());
					 event = atoi((*it).c_str());
					 break;
				}
				case 3: // chan
				{
				 	 //printf("[buffer] Setting channel str (%s)\n", (*it).c_str());
				 	 chan = *it;
				 	 //strcpy(chan, (*it).c_str());
				 	 break;
				}	
				case 4: // nick
				{ 
				  	 //printf("[buffer] Setting nick str (%s)\n", (*it).c_str());
				  	 nick = *it;
				 	 //strcpy(nick, (*it).c_str());
				 	 break;
				}	
				case 5: // msg
				{
				 	 //printf("[buffer] Setting msg str (%s)\n", (*it).c_str());
				 	 msg = *it;
				 	 //strcpy(msg, (*it).c_str());
				 	 break;
				}				
			}
		 }
		 
		 params = 0;
		 
		 //printf("[buffer] Gathered all the required parameters! switching through event %i\n", event);
		 
		 switch (event)
		 {
 		     case F_PRIVMSG:
	  		 {
			  	  //printf("[buffer] calling OnPrivMsgEx(%i, %i, %s, %s);\n", conn, chan, nick, msg);
			  	  OnPrivMsgEx(conn, chan.c_str(), nick.c_str(), msg.c_str());
			  	  params = 0;
			  	  break;
			 }
 		     case F_USERJOIN:
	  		 {
			  	  //printf("[buffer] calling OnUserJoinEx(%i, %s, %s);\n", conn, chan, nick);
			  	  OnUserJoinEx(conn, chan.c_str(), nick.c_str());
			  	  params = 0;
			  	  break;
			 }
 		     case F_USERPART:
	  		 {
			  	  //printf("[buffer] calling OnUserPartEx(%i, %s, %s);\n", conn, chan, nick);
			  	  OnUserPartEx(conn, chan.c_str(), nick.c_str());
			  	  params = 0;
			  	  break;
			 }
		 }
	 }
  }	
  	functions.clear();
  	bParseFunctions = false;
}

// This is the safest possible way to call AMX functions from a single thread.
//  All the events and their parameters are parsed into a global buffer, which 
//  is split by a delimiter and calls every function respectively.
//---------------------------------------------------------- 
static cell AMX_NATIVE_CALL n_EventPoll( AMX* amx, cell* params )
{
 	 ParseBuffer();
 	 return 0;
}
	   	

// PAWN function that allows users to connect to IRC servers (only one though)
//---------------------------------------------------------- 
static cell AMX_NATIVE_CALL n_Connect( AMX* amx, cell* params )
{
	if (params[0] != 12)
	{
 	   logprintf("*** ircConnect expecting 3 parameters, not %d", params[0]/4);
 	   return 0;
	}
    char* server;
    int port;
    char* nick;
    int conn = GetConnSlot();
    NUM_CONNECTIONS++;
    pAMX = amx;
    amx_StrParam(amx, params[1], server);
    port = params[2];
    amx_StrParam(amx, params[3], nick);
    logprintf("*** Connecting to %s:%i... (connection #%i)", server, port, conn);
    samp_conn[conn].connid = conn;
    int result = samp_conn[conn].start(server, port, nick, nick, nick);
    if (result == 2)
    {	   		   
			switch(conn)
			{
			 	case 1:
					 { ListenMessages[1] = new XPThreads(listen1);
	    			 ListenMessages[1]->Run();
					 break;	}
			 	case 2:
					 { ListenMessages[2] = new XPThreads(listen2);
	    			 ListenMessages[2]->Run();
					 break;	}
			 	case 3:
					 { ListenMessages[3] = new XPThreads(listen3);
	    			 ListenMessages[3]->Run();
					 break;	}
			 	case 4:
					 { ListenMessages[4] = new XPThreads(listen4);
	    			 ListenMessages[4]->Run();
					 break;	}
			 	case 5:
					 { ListenMessages[5] = new XPThreads(listen5);
	    			 ListenMessages[5]->Run();
					 break;	}
			}
	    	logprintf("*** IRC Socket %i established.", conn);
	    	OnConnect(conn);
	    	return conn;
    }
    else
    {
        	logprintf("*** Failed to connect to IRC server %i! (code %i)", conn,result);
        	return 0;
    }
}


bool NoConnections()
{
 	 for (int i=1; i<=MAX_CONNECTIONS; i++)
	 {
	  	if (bConn[i]) return false;
	 }
	 return true;
}

int GetConnSlot()
{
 	for (int i=1; i<=MAX_CONNECTIONS; i++)
	 {
	  	if (!bConn[i]) return i;
	 }
}

// PAWN function that allows users to send raw data to IRC servers for any extra features
//---------------------------------------------------------- 
static cell AMX_NATIVE_CALL n_SendRawData( AMX* amx, cell* params )
{
		if (params[0] != 8)
		{
	 	   logprintf("*** ircSendRawData expecting 2 parameters, not %d", params[0]/4);
	 	   return 0;
		}
 	   int conn = params[1];
 	   char* rawdata;
 	   amx_StrParam(amx, params[2], rawdata);
 	   samp_conn[conn].raw(rawdata);
 	   return 1;
}

// PAWN function that allows users to disconnect from current IRC server
//---------------------------------------------------------- 
static cell AMX_NATIVE_CALL n_GetUserList( AMX* amx, cell* params )
{
		if (params[0] != 16)
		{
	 	   logprintf("*** ircGetUserList expecting 4 parameters, not %d", params[0]/4);
	 	   return 0;
		}
       char* channel; 
       char* userlist = new char[2024];
       int chanindex;
	   cell* dest;
	   size_t len;
 	   int conn = params[1];
 	   int count = 0;
 	   amx_StrParam(amx, params[2], channel);
 	   amx_GetAddr(amx,params[3],&dest);
 	   len = (size_t)params[4];
	   chanindex = samp_conn[conn].GetChanIndex(channel);
	   for (list<string>::iterator it=samp_conn[conn].ServerData.PlayerList[chanindex].begin(); it!=samp_conn[conn].ServerData.PlayerList[chanindex].end(); ++it)
	   {
	   	   count++;
	   	   if (count == 1) // first user, strcpy.
	   	   {
 		       strcpy(userlist, (*it).c_str());
		   }
		   else
		   {
		   	   strcat(userlist, " ");
		   	   strcat(userlist, (*it).c_str());
		   }
 	   }
	   if (chanindex != -1)
	   {	 
			amx_SetString(dest, userlist, 0, 0, len);
	   }
	   delete userlist;
       return 1;
}

	
// PAWN function that allows users to disconnect from current IRC server
//---------------------------------------------------------- 
static cell AMX_NATIVE_CALL n_Disconnect( AMX* amx, cell* params )
{

 	   int conn = params[1];
 	   if (!bConn[conn]) return 0;
 	   bConn[conn] = false;
 	   ListenMessages[conn]->Stop();
 	   if (ListenMessages[conn]) delete ListenMessages[conn];  
       samp_conn[conn].disconnect();
       samp_conn[conn].~IRC(); // call destructor
       return 1;
}

// PAWN function that allows users to send IRC messages through the server
//---------------------------------------------------------- 
static cell AMX_NATIVE_CALL n_Say( AMX* amx, cell* params )
{
		if (params[0] != 12)
		{
	 	   logprintf("*** ircSay expecting 3 parameters, not %d", params[0]/4);
	 	   return 0;
		}
       int conn = params[1];
	   char* channel;
	   char* message;
       amx_StrParam(amx, params[2], channel);
       amx_StrParam(amx, params[3], message);
       samp_conn[conn].privmsg(channel, message);
       return 1;
}


// Our PAWN natives..
//---------------------------------------------------------- 
AMX_NATIVE_INFO IRCnatives[ ] =
{
	{ "ircConnect",			n_Connect},
	{ "ircDisconnect",		n_Disconnect},
	{ "ircSay",			    n_Say},
	{ "ircJoinChan",	    n_JoinChan},
	{ "ircPartChan",	    n_PartChan},
	{ "ircPartChan",	    n_PartChan},
	{ "ircGetUserList",   	n_GetUserList},
	{ "ircSetMode",	        n_SetMode},
	{ "ircPollEvents",		n_EventPoll},
	{ "ircGetUserLevel",	n_GetUserLevel},	
	{ "ircSendRawData",		n_SendRawData},
	{ 0,					0 }
};


// Called when an AMX is loaded, used to store the AMX pointer so we can use our custom callbacks
//---------------------------------------------------------- 
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	return amx_Register( amx, IRCnatives, -1 );
}

// Called when an AMX is unloaded, unused
//---------------------------------------------------------- 
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	return AMX_ERR_NONE;
}

