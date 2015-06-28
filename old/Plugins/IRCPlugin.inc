//*******************************************************************
//IRC Plugin
//*******************************************************************
#if defined IRCPlugin_included
  	#endinput
#endif
#define IRCPlugin_included
#pragma library IRCPlugin

//-- Variables --
new IRC_CONNECTION;
new IRC_TIMER;
new IRC_TIMER_SET = false;
new IRC_CONNECTIONS = 0;

//-- Functions --
//1.  Init IRC Timer
//2.  Timer Function IRC Events

public InitIRCTimer()
{
	if (!IRC_TIMER_SET)
	{
		IRC_TIMER = SetTimer("TimerFunctionIrcEvents", 500, true);
	}
	return true;
}

public TimerFunctionIRCEvents()
{
    IRC_TIMER_SET = true;
    ircPollEvents();
    return true;
}
