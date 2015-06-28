//*******************************************************************
//Emoticon Functions
//*******************************************************************
#if defined EmoticonFunctions_included
  	#endinput
#endif
#define EmoticonFunctions_included
#pragma library EmoticonFunctions

//-- Functions --
public PreloadEmoticonLibraries(PlayerId)
{
	for (new I0 = 0; I0 < EMOTICONS; I0++)
	{
	    PreloadAnimationLibrary(PlayerId, EMOTICON_LIBARY[I0]);
	}
	return true;
}

public PlayerMakesEmoticon(PlayerId, EmoticonId)
{
    PLAYER_PLAYS_EMOTICON[PlayerId] = true;
	ApplyAnimation(PlayerId, EMOTICON_LIBARY[EmoticonId], EMOTICON_ANIMATION[EmoticonId], EMOTICON_TIME[EmoticonId], EMOTICON_LOOP[EmoticonId], 0, 0, 0, -1);
	if (!EMOTICON_LOOP[EmoticonId])
	{
		PLAYER_EMOTICON_TIMER[PlayerId] = SetTimerEx("ResetPlayerEmoticon", floatround(EMOTICON_TIME[EmoticonId] * 1000.0000), false, "i", PlayerId);
	}
	new InfoMessage[MAX_STRING];
	format(InfoMessage, sizeof(InfoMessage), "%s %s.", PLAYER_NAME[PlayerId], EMOTICON_TEXT[EmoticonId]);
	SendClientMessageToAllPlayers(MESSAGE_TYPE_INFO, InfoMessage);
	return true;
}

public ResetPlayerEmoticon(PlayerId)
{
    PLAYER_PLAYS_EMOTICON[PlayerId] = false;
    ClearAnimations(PlayerId);
    return true;
}

public AddEmoticon(Command[MAX_EMOTICON_COMMAND], Libary[MAX_EMOTICON_LIBARY], Animation[MAX_EMOTICON_ANIMATION], Text[MAX_EMOTICON_TEXT], Float:Time, Loop)
{
	new EmoticonId = EMOTICONS;
	if (EmoticonId < MAX_EMOTICONS)
	{
		EMOTICON_COMMAND[EmoticonId] = Command;
		EMOTICON_LIBARY[EmoticonId] = Libary;
		EMOTICON_ANIMATION[EmoticonId] = Animation;
		EMOTICON_TEXT[EmoticonId] = Text;
		EMOTICON_TIME[EmoticonId] = Time;
		EMOTICON_LOOP[EmoticonId] = Loop;
		EMOTICONS++;
		return EmoticonId;
	}
	return -1;
}

