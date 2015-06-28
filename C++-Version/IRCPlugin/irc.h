/*
	cpIRC - C++ class based IRC protocol wrapper
	Copyright (C) 2003 Iain Sheppard

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


 This file has been rewritten by Simon "Jacob" Dis on the following dates: June 29th, 2007 through July 3rd, 2007
 Full permission to do so was granted by the author, Iain Sheppard, on June 28th, 2007.   
 
*/


#define __CPIRC_VERSION__	0.1

#define MAX_USERS 200
#define MAX_CHANNELS 10
#define MAX_CONNECTIONS 5
#define IRC_USER_VOICE	1
#define IRC_USER_HALFOP	2
#define IRC_USER_OP		4
#define F_PRIVMSG 0
#define F_USERJOIN 1
#define F_USERPART 2
#define MAX_FUNCTIONS 20
#define MAX_PARAMS 5

#include "main.h"
#include <string>
#include <algorithm>
#include <list>
#include <vector>

typedef void (*logprintf_t)(char* format, ...); 

using namespace std;

vector<string> tokenize(const string& str,const string& delimiters);
char* StripFirstLetter(char* word);
bool equal(char* szString1, char* szString2);
int strFind(char* szCharSet, const char cChar);
void savelogprintf(logprintf_t log);

struct _name_data
{
   char name[30];
   char level;
};

struct _server_data
{
   int UserCount[MAX_CHANNELS];
   list<string> PlayerList[MAX_CHANNELS];
   int ChanCount;
   list<string> ChannelList;
};

struct irc_reply_data
{
	char* nick;
	char* ident;
	char* host;
	char* target;
};


class IRC
{
public:
	IRC();
	~IRC();
	int start(char* server, int port, char* nick, char* user, char* name);
	void disconnect();
	int privmsg(char* target, char* message);
	int notice(char* target, char* message);
	int join(char* channel);
	int part(char* channel);
	int kick(char* channel, char* nick);
	int kick(char* channel, char* nick, char* message);
	int mode(char* modes);
	int mode(char* channel, char* modes, char* targets);
	int nick(char* newnick);
	int quit();
	int say(char* channel, char* message);
	int message_loop();
	int is_voice(char* channel, char* nick);
	void syncplayerlist(char* chan);
	int GetChanIndex(char* channel);
	void SaveChannel(char* channel);
	void AppendPlayerlist(int chanindex, char* nickname);
	char* GetChanName(int chanindex);
	bool connected;
	char* getuserlevel(int chanindex, char* user);
	void raw(char* data);
//	void DeletePlayerFromList(int conn, char* nick, int chanindex);
	_server_data ServerData;
	int connid;
private:
	void parse_irc_reply(char* data);
	void split_to_replies(char* data);
	int irc_socket;
	bool sentnick;
	bool sentpass;
	bool sentuser;
	char* cur_nick;
};


