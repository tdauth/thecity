//*******************************************************************
//Emoticon
//*******************************************************************
#if defined Emoticon_included
  	#endinput
#endif
#define Emoticon_included
#pragma library Emoticon

//-- Variables --
new EMOTICONS = 0;

//-- Properties --
new EMOTICON_COMMAND[MAX_EMOTICONS][MAX_EMOTICON_COMMAND];
new EMOTICON_LIBARY[MAX_EMOTICONS][MAX_EMOTICON_LIBARY];
new EMOTICON_ANIMATION[MAX_EMOTICONS][MAX_EMOTICON_ANIMATION];
new EMOTICON_TEXT[MAX_EMOTICONS][MAX_EMOTICON_TEXT];
new Float:EMOTICON_TIME[MAX_EMOTICONS];
new EMOTICON_LOOP[MAX_EMOTICONS];

