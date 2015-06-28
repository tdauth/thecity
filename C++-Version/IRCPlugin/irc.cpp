/*
	cpIRC - C++ class based IRC protocol wrapper
	Copyright (C) 2003 Iain Sheppard
	Rewritten by Jacob Dis

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

	Contacting the author:
	~~~~~~~~~~~~~~~~~~~~~~

	email:	iainsheppard@yahoo.co.uk
	IRC:	#magpie @ irc.quakenet.org


// This file has been rewritten by Jacob Dis on the following dates:
// June 28th, 2007 through July 14th, 2007
// Full permission to do so was granted by the author, Iain Sheppard, on June 28th, 2007. */


#ifdef WIN32
bool bWindows = true;
#include <windows.h>
#else
bool bWindows = false; 
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define closesocket(s) close(s)
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#include <fcntl.h>
#include <ctype.h>
#endif
#include "IRC.h"

#ifndef WIN32
char *strlwr(char *str)
{
      char *s;

      if (str)
      {
            for (s = str; *s; ++s)
                  *s = tolower(*s);
      }
      return str;
}
#endif

logprintf_t ircprintf;

void savelogprintf(logprintf_t log)
{
 	 ircprintf = log;
 	 return;
}
 	 
bool equal(char* szString1, char* szString2)
{
 if ((!szString1) || (!szString2)) return false;
    return (!strcmp(szString1, szString2));
}

char* IRC::GetChanName(int chanindex)
{
 	list<string>::iterator ChanIter;
 	int idx=-1;
 	for (ChanIter = ServerData.ChannelList.begin(); ChanIter != ServerData.ChannelList.end(); ChanIter++)
 	{
	 	idx++;
	 	if (idx == chanindex-1) return (char*)((*ChanIter).c_str());
	}
}
	 	
		   		   
int IRC::GetChanIndex(char* channel)
{
 	if (strchr(channel, ' ') || (channel[0] != '#')) return -1; // channels don't have spaces..
 	int n=0;
  	list<string>::iterator ChanIter;
	for (list<string>::iterator it = ServerData.ChannelList.begin(); it != ServerData.ChannelList.end(); it++)
	{
	 	n++;
	 	if (equal(strlwr(channel), (char*)(*it).c_str())) goto retn;
 	} 
 	//ircprintf("[getchanindex] Channel '%s' not found! (possible crash)", channel);
	if ((*ChanIter).empty() || (n == ServerData.ChanCount)) return -1;
retn:	
  	return n;
}   
 

char* IRC::getuserlevel(int chanindex, char* nick)
{
 	list<string> tmpPlayerList = ServerData.PlayerList[chanindex];
 	list<string>::iterator nickIter;
 	bool bHasLevel;
  	for (nickIter=tmpPlayerList.begin(); nickIter!=tmpPlayerList.end(); ++nickIter)
	{
	 	bHasLevel = false;
	 	string szNickLevel = (*nickIter).substr(0,1);
		if ((!strcmp(szNickLevel.c_str(),"@")) || (!strcmp(szNickLevel.c_str(),"~")) || (!strcmp(szNickLevel.c_str(),"+")) || (!strcmp(szNickLevel.c_str(),"%")) || (!strcmp(szNickLevel.c_str(),"&")))
		{
  		   bHasLevel = true;
		  (*nickIter).erase (0,1);	
		}
		if (!strcmp(strlwr((char*)(*nickIter).c_str()), strlwr(nick))) // case insensitive
		{				   				   
		   if (bHasLevel)
		   {
		   	  return (char*)(szNickLevel.c_str());
		   }
		   else
		   {
		   	   return "-"; // - = no level
		   }				   
  		   break;
		}
	} 
	return "-"; // nick not found...
}
 

void IRC::SaveChannel(char* channel)
{
 	 ServerData.ChannelList.push_back(strlwr(channel));
     //strcpy(channels[index].name, strlwr(channel));
}

void IRC::AppendPlayerlist(int chanindex, char* nickname)
{
 	 ServerData.PlayerList[chanindex].push_back(nickname);	// rewrote this function 3 times, ended up using STL.
}

IRC::IRC()
{
	connected=false;
	sentnick=false;
	sentpass=false;
	sentuser=false;
	cur_nick=0;
}

IRC::~IRC()
{
    if (cur_nick) delete cur_nick;
    ServerData.ChannelList.clear();
    for (int i=1; i<=ServerData.ChanCount; i++)
    {
	 	if (!ServerData.PlayerList[i].empty()) ServerData.PlayerList[i].clear();
	}
}

 	

int IRC::start(char* server, int port, char* nick, char* user, char* name)
{
 	//ircprintf("declaring resolv struct");
 	#if defined WIN32
	HOSTENT* resolv;
  	#else
  	struct hostent *resolv;
   	#endif
	sockaddr_in rem;
	char buffer[514];
	if (connected)
		return 1;
	irc_socket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (irc_socket==INVALID_SOCKET)
	{
		return 1;
	}
	//ircprintf("calling gethostbyname");
	resolv=gethostbyname(server);
	if (!resolv)
	{
		closesocket(irc_socket);
		return 1;
	}
	//ircprintf("getting rem.sin_addr");
	memcpy(&rem.sin_addr, resolv->h_addr, 4);
	rem.sin_family=AF_INET;
	rem.sin_port=htons(port);
	//ircprintf("calling connect");
	if (connect(irc_socket, (const sockaddr*)&rem, sizeof(rem))==SOCKET_ERROR)
	{
		closesocket(irc_socket);
		return 1;
	}
    connected=true;
	cur_nick = new char[strlen(nick)+1]; 
	strcpy(cur_nick, nick);
    ServerData.ChanCount = 0;    
//	sprintf(buffer, "PASS %s\r\n", pass);
//	send(irc_socket, buffer, strlen(buffer), 0);
//	//ircprintf("skipped sending 'PASS %s'!", pass);
//ircprintf("sending NICK/USER to server");
	sprintf(buffer, "NICK %s\r\n", nick);
	send(irc_socket, buffer, strlen(buffer), 0);
	sprintf(buffer, "USER %s * 0 :IRCPlugin\r\n", nick);
	send(irc_socket, buffer, strlen(buffer), 0);
	sprintf(buffer, "MODE %s :+B\r\n", nick); // gtanet policy to set +B (Bot)
	send(irc_socket, buffer, strlen(buffer), 0);
	//ircprintf("done with irc::start");
	return 2;
}


void IRC::disconnect()
{
	if (connected)
	{
		quit();
		#ifdef WIN32
		shutdown(irc_socket, 2);
		#endif
		closesocket(irc_socket);
		connected=false;
	}
}

int IRC::quit()
{
	char buffer[1024];

	if (connected)
	{
		sprintf(buffer, "QUIT\r\n");
		if (send(irc_socket, buffer, strlen(buffer), 0)==SOCKET_ERROR)
			return 1;
	}
	return 0;
}

int IRC::message_loop()
{
	char buffer[6024]; // no more chopping, motherfucker!
	unsigned int ret_len;
	if (!connected) return -5;
	ret_len = recv(irc_socket, buffer, 6024, 0);
	//printf("Received %i bytes: %s\n", ret_len, buffer);
	if (ret_len==SOCKET_ERROR || ret_len==-1 || !ret_len) goto fuck;
	buffer[ret_len]='\0';
	split_to_replies(buffer);
fuck:
	return 0;
}

void IRC::split_to_replies(char* data)
{
	char* p;

	while (p=strstr(data, "\r\n"))
	{
		*p='\0';
		parse_irc_reply(data);
		data=p+2;
	}
}

/*   	 
void IRC::DeletePlayerFromList(int conn, char* nick, int chanindex)
{
  	int newusercount = ServerData.UserCount[chanindex] - 1;
  	ServerData.UserCount[chanindex] = newusercount;
  	list<string>::iterator remIter;
  	bool bChopped;
  	for (remIter=ServerData.PlayerList[chanindex].begin(); remIter!=ServerData.PlayerList[chanindex].end(); ++remIter)
	{
	 	if ((*remIter).empty()) break;
	 	string szNickLevel = (*remIter).substr(0,1);
	 	bChopped = false;
		if ((!strcmp(szNickLevel.c_str(),"@")) || (!strcmp(szNickLevel.c_str(),"~")) || (!strcmp(szNickLevel.c_str(),"+")) || (!strcmp(szNickLevel.c_str(),"%")) || (!strcmp(szNickLevel.c_str(),"&")))
		{		
			(*remIter).erase (0,1);	
			bChopped = true;
		}
		if (!strcmp((*remIter).c_str(), nick))
		{				   
  		   ServerData.PlayerList[chanindex].erase(remIter);
  		   OnUserPart(conn, GetChanName(chanindex), nick);
  		   break;
		}
		else // fix the bug where playerlist forgot the user levels..
		{
   		 	 if (bChopped) (*remIter).insert(0,szNickLevel);
   		 	 bChopped=false;
		}
	}
}*/


// Replacement for all playerlist parsing. Lazy? Yes.  Will the user tell the difference? No.
void IRC::syncplayerlist(char* chan)
{
 	 char tmpbuf[64];
 	 int chanindex = GetChanIndex(chan);
 	 if (chanindex == -1) return;
	 sprintf(tmpbuf, "NAMES %s\r\n", chan);
	 ServerData.PlayerList[chanindex].clear(); // clear existing playerlist
	 send(irc_socket, tmpbuf, strlen(tmpbuf), 0); // tell the server to send us updated playerlist	
}

void IRC::parse_irc_reply(char* data)
{
	char* hostd;
	char* cmd;
	char* params;
	char buffer[5000];
	irc_reply_data ircdata;
	char* p;
	char* chan_temp;
    int chanindex = -1;
	ircdata.target=0;

	if (data[0]==':')
	{			 
		hostd=&data[1];
		cmd=strchr(hostd, ' ');
		if (!cmd)
			return;
		*cmd='\0';
		cmd++;
		params=strchr(cmd, ' ');
		if (params)
		{
			*params='\0';
			params++;
		}
		ircdata.nick=hostd;
		ircdata.ident=strchr(hostd, '!');
		if (params[0] == ':')
		{	  
           *params='\0';
	        params++;
		}
		if (ircdata.ident)
		{
			*ircdata.ident='\0';
			ircdata.ident++;
			ircdata.host=strchr(ircdata.ident, '@');
			if (ircdata.host)
			{
				*ircdata.host='\0';
				ircdata.host++;
			}
		}
		
		//ircprintf("PARSING CMD %s\n", cmd);
		
		int icmd = atoi(cmd);
		if ((icmd >=401) && (icmd<=491)) // error message from IRC server
		{
  		   //ircprintf("*** %s", params);
  		   return;
		}

        if ((params[0] == '#') && (!strchr(params, ' ')))
		{
  		   chanindex = GetChanIndex(params);
		   //ircprintf("GetChanIndex(%s) = %i\n", params, chanindex);
	    }

		if (!strcmp(cmd, "JOIN"))
		{	 
            if (equal(ircdata.nick,cur_nick)) return; // don't update JOIN on yourself.. I don't think?
            int newusercount = ServerData.UserCount[chanindex] + 1;
			ServerData.UserCount[chanindex] = newusercount;
			syncplayerlist(params);
            OnUserJoin(connid, params, ircdata.nick);
		}
		else if (!strcmp(cmd, "PART"))
		{
		   syncplayerlist(params);
		   OnUserPart(connid, params, ircdata.nick);
		}
		else if (!strcmp(cmd, "QUIT"))
		{
            for (int i=1; i<=ServerData.ChanCount; i++)
            {	
				string chanName(GetChanName(i));	
			   	syncplayerlist((char*)chanName.c_str());
				OnUserPart(connid, (char*)chanName.c_str(), ircdata.nick);	   		  
//		   	   DeletePlayerFromList(connid, ircdata.nick, i);
			}
		}
		else if (!strcmp(cmd, "NICK"))
		{
            for (int i=1; i<=ServerData.ChanCount; i++)	syncplayerlist(GetChanName(i));		
        }
		else if (!strcmp(cmd, "MODE"))
		{
		 	 if (params[0] == '#') // setting a mode on the channel..
			  {
			   	  string szParams(params);	 
				  vector<string> tokens = tokenize(params, " ");
				  syncplayerlist((char*)tokens[0].c_str());
/*				  int tmpindex = GetChanIndex((char*)(tokens[0].c_str()));
				  if (tmpindex != -1)
				  {
				   	 		   
   	 				 char tmpbuf[64];
					 sprintf(tmpbuf, "NAMES %s\r\n", tokens[0].c_str());
					 ServerData.PlayerList[tmpindex].clear(); // clear existing playerlist
					 send(irc_socket, tmpbuf, strlen(tmpbuf), 0); // tell the server to send us updated playerlist						  
				  }*/
			  }			  
		}
		else if (!strcmp(cmd, "372")) // MOTD
		{
		 	 //ircprintf("*** %s", params);
		 }
		
		else if (!strcmp(cmd, "353"))
		{
		 	//ircprintf("Syncing playerlist...\n");
			chan_temp=strchr(params, '#');
		 	char* solution;
			if (chan_temp)
			{	  
				p=strstr(chan_temp, " :");
				if (p)
				{
					*p='\0';
					p+=2;
				   	int chanindex = GetChanIndex(chan_temp);		  
					solution = strchr(p, ' ');
					char* tmp;
					tmp=strchr(p, ' ');
                   	if (chanindex == -1)
                  	{
                          //ircprintf("FATAL ERROR: Could not retrieve channel index for %s!", chan_temp);
                          return;
                    }	
					if (p[0] == ':')
					{
					   *p='\0';
					   p++;
					 }
					 solution = strtok (p, " ");
					 int newusercount = 0;
					 while (solution != NULL)
					 {
					  	   ServerData.UserCount[chanindex]++;
					  	   newusercount = ServerData.UserCount[chanindex];	    				
					  	   AppendPlayerlist(chanindex, solution);	
	  	   				   solution = strtok(NULL, " ");
				     }				  		 	   			  								  			  						
               }
           }
		}

		else if (!strcmp(cmd, "PRIVMSG"))
		{
			ircdata.target=params;
			params=strchr(ircdata.target, ' ');
			if (params)
			{
			   	*params='\0';
				params++;
			}
			if (equal(ircdata.target, cur_nick)) // its to us! (probably ping or CTCP)
			{
			   string szTmp(ircdata.nick);
			   int iloc = szTmp.find("Serv");
			   if (iloc != -1) return;
			}
			if (strlen(params) >= 255) return; // stupid PAWN limitation
			OnPrivMsg(connid, ircdata.target, ircdata.nick, &params[1]);
		}
	}
	else
	{
		cmd=data;
		data=strchr(cmd, ' ');
		if (!data)
			return;
		*data='\0';
		params=data+1;
		if (!strcmp(cmd, "PING"))
		{
			if (!params)
				return;
			sprintf(buffer, "PONG %s\r\n", &params[1]);
			//ircprintf("*** Ping? Pong!\n");
			send(irc_socket, buffer, strlen(buffer), 0);
		}
		else
		{
			ircdata.host=0;
			ircdata.ident=0;
			ircdata.nick=0;
			ircdata.target=0;
		}
	}
}

int IRC::say(char* channel, char* message)
{
    char buffer[514];
    sprintf(buffer, "MSG %s %s", channel, message);
    send(irc_socket, buffer, strlen(buffer), 0);
}

void IRC::raw(char* rawdata)
{
 	 char buffer[514];
 	 sprintf(buffer, "%s\r\n", rawdata);
 	 //ircprintf("Sending raw data '%s'", buffer);
 	 send(irc_socket, buffer, strlen(buffer), 0);
}
 
int IRC::privmsg(char* target, char* message)
{
	char buffer[514];
	if (!connected)
		return 1;
	sprintf(buffer, "PRIVMSG %s :%s\r\n", target, message);
	send(irc_socket, buffer, strlen(buffer), 0);
	return 0;
}

int IRC::join(char* channel)
{
 	//ircprintf("IRC::join %s", channel);
	char buffer[514];
	if (!connected)
		return 1;
	ServerData.ChanCount++;
/*	if (ServerData.ChanCount == 1) // first chan
	{
 	   sprintf(buffer, "MODE %s :+B\r\n", cur_nick);
	   send(irc_socket,buffer,strlen(buffer),0);
    }	*/ 
	SaveChannel(channel);
	sprintf(buffer, "JOIN %s\r\n", channel);
//	//ircprintf("Sending JOIN to socket %i\n", irc_socket);
	send(irc_socket, buffer, strlen(buffer), 0);
	//ServerData.PlayerList[ServerData.ChanCount] = new char[1000]; 
	return 0;
}

int IRC::part(char* channel)
{
	char buffer[514];

	if (!connected)
		return 1;
	sprintf(buffer, "PART %s\r\n", channel);
	send(irc_socket, buffer, strlen(buffer), 0);
	ServerData.ChanCount--;
	//if (GetChanIndex(channel) != -1) SetChanIndex(ServerData.ChanCount, '\0');
	return 0;
}

int IRC::kick(char* channel, char* nick)
{
	char buffer[514];

	if (!connected)
		return 1;
	sprintf(buffer, "KICK %s %s\r\n", channel, nick);
	send(irc_socket, buffer, strlen(buffer), 0);
	return 0;
}

int IRC::kick(char* channel, char* nick, char* message)
{
	char buffer[514];

	if (!connected)
		return 1;
	sprintf(buffer, "KICK %s %s :%s\r\n", channel, nick, message);
	send(irc_socket, buffer, strlen(buffer), 0);
	return 0;
}


int IRC::mode(char* channel, char* modes, char* targets)
{
	char buffer[514];

	if (!connected)
		return 1;
	if (!targets)
		sprintf(buffer, "MODE %s %s\r\n", channel, modes);
	else
		sprintf(buffer, "MODE %s %s %s\r\n", channel, modes, targets);
	send(irc_socket, buffer, strlen(buffer), 0);
	return 0;
}

int IRC::mode(char* modes)
{
	if (!connected)
		return 1;
	mode(cur_nick, modes, 0);
	return 0;
}

int IRC::nick(char* newnick)
{
	char buffer[514];

	if (!connected)
		return 1;
	sprintf(buffer, "NICK %s\r\n", newnick);
	send(irc_socket, buffer, strlen(buffer), 0);
	return 0;
}


// The portion below is an excerpt provided by vptr of thescripts.com as a thread-safe alternative
// to strtok().  I would highly reccomend this over strtok, it's faster and doesn't destroy the 
// source string! In addition, using STL eliminates reinventing the same ideas over and over.
//---------------------------------------------------------- 
vector<string> tokenize(const string& str,const string& delimiters)
{
  vector<string> tokens;
  
  string::size_type lastPos = 0, pos = 0;  
  int count = 0;
  
  if(str.length()<1)  return tokens;
  
  // skip delimiters at beginning.  
  lastPos = str.find_first_not_of(delimiters, 0);
      
  if((str.substr(0, lastPos-pos).length()) > 0)
  {  	
  	count = str.substr(0, lastPos-pos).length();  	

  	for(int i=0; i < count; i++)  	
  	 	tokens.push_back("");
  	
  	if(string::npos == lastPos)
  		tokens.push_back("");
  }

  // find first "non-delimiter".
  pos = str.find_first_of(delimiters, lastPos);
  
  while (string::npos != pos || string::npos != lastPos)
  {  	      	    
     	// found a token, add it to the vector.
     	tokens.push_back( str.substr(lastPos, pos - lastPos));
				
    	// skip delimiters.  Note the "not_of"
     	lastPos = str.find_first_not_of(delimiters, pos);   	   	    
		
		if((string::npos != pos) && (str.substr(pos, lastPos-pos).length() > 1))  		
  		{
  			count = str.substr(pos, lastPos-pos).length();

  			for(int i=0; i < count; i++)
  	 			tokens.push_back("");
		}
		
  		pos = str.find_first_of(delimiters, lastPos);
  }

	return tokens;
}
