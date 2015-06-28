#ifndef _MAIN_INClUDED
#define _MAIN_INCLUDED



// nothing special here, this is just so the irc class can call these when certain things happen.

void OnPrivMsg(int conn, char* channel, char* nick, char* msg);
void OnUserJoin(int conn, char* channel, char* nick);
void OnUserPart(int conn, char* channel, char* nick);
void OnPrivMsgEx(int conn, const char* globalMsg, const char* globalNick, const char* globalChan);
void OnUserJoinEx(int conn, const char* channel, const char* nick);
void OnUserPartEx(int conn, const char* channel, const char* nick);
int GetConnSlot();


#endif
