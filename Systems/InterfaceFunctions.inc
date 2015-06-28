//*******************************************************************
//Interface Functions
//*******************************************************************
#if defined InterfaceFunctions_included
  	#endinput
#endif
#define InterfaceFunctions_included
#pragma library InterfaceFunctions

//-- Functions --
public InitTimeTimer()
{
	TIMER_TIME = SetTimer("TimerFunctionSetTime", ConvertSeconds(1), true);
	return true;
}

public TimerFunctionSetTime()
{
	new Hour, Minute, NewHour, NewMinute;
	for (new I0 = 0; I0 < MAX_PLAYERS; I0++)
	{
	    if (IsPlayerConnected(I0))
	    {
	        GetPlayerTime(I0, Hour, Minute);
	        if (Minute != 59)
	        {
	            NewMinute = Minute++;
			}
			else
			{
			    NewMinute = 0;
				if (Hour != 23)
				{
			    	NewHour = Hour++;
				}
				else
				{
				    NewHour = 0;
				}
			}
			SetPlayerTime(I0, NewHour, NewMinute);
		}
	}
	return true;
}

public SendMessageToPlayer(PlayerId, Type, Message[])
{
	new NewMessage[MAX_STRING];
	strcat(NewMessage, Message, sizeof(NewMessage));
    NewMessage = FixString(NewMessage);
	//Text Message
 	TextDrawDestroy(MESSAGE[PlayerId][Type]);
    MESSAGE[PlayerId][Type] = TextDrawCreate(MESSAGE_TYPE_POSITION[Type][X], MESSAGE_TYPE_POSITION[Type][Y], NewMessage);
    TextDrawLetterSize(MESSAGE[PlayerId][Type], MESSAGE_TYPE_SIZE[Type][X], MESSAGE_TYPE_SIZE[Type][Y]);
	TextDrawColor(MESSAGE[PlayerId][Type], MESSAGE_TYPE_COLOUR[Type]);
	TextDrawSetShadow(MESSAGE[PlayerId][Type], MESSAGE_TYPE_SHADOW[Type]);
	TextDrawSetOutline(MESSAGE[PlayerId][Type], MESSAGE_TYPE_OUTLINE[Type]);
	TextDrawBackgroundColor(MESSAGE[PlayerId][Type], MESSAGE_TYPE_BACKGROUND_COLOUR[Type]);
	TextDrawFont(MESSAGE[PlayerId][Type], MESSAGE_TYPE_FONT[Type]);
	//Text Box
	TextDrawUseBox(MESSAGE[PlayerId][Type], MESSAGE_TYPE_USE_BOX[Type]);
	TextDrawTextSize(MESSAGE[PlayerId][Type], MESSAGE_TYPE_BOX_SIZE[Type][X], MESSAGE_TYPE_BOX_SIZE[Type][Y]);
	TextDrawBoxColor(MESSAGE[PlayerId][Type], MESSAGE_TYPE_BOX_COLOUR[Type]);
	TextDrawShowForPlayer(PlayerId, MESSAGE[PlayerId][Type]);
	return true;
}

public SendTimedMessageToPlayer(PlayerId, Time, Type, Message[])
{
	SetTimerEx("SendMessageToPlayer", Time, false, "iis", PlayerId, Type, Message);
	return true;
}

public DestroySendedMessageForPlayer(PlayerId, Type)
{
    TextDrawDestroy(MESSAGE[PlayerId][Type]);
    return true;
}

public SendClientMessageToPlayer(PlayerId, Type, Message[])
{
	SendClientMessage(PlayerId, MESSAGE_TYPE_COLOUR[Type], Message);
	return true;
}

public SendClientMessageToAllPlayers(Type, Message[])
{
	new InfoMessage[MAX_STRING];
	SendClientMessageToAll(MESSAGE_TYPE_COLOUR[Type], Message);
	//IRC Plugin
	format(InfoMessage, sizeof(InfoMessage), "Client-Nachricht: %s", Message);
	//ircSay(IRC_CONNECTION, "#GTA_SA_MP_TC", InfoMessage);
	return true;
}

public CreateCustomMenuForPlayer(PlayerId, Type, Menu, Title[])
{
    DestroyMenu(MENU[PlayerId][Type]);
    PLAYER_MENU_TYPE[PlayerId] = Type;
    PLAYER_MENU[PlayerId] = Menu;
    MENU[PlayerId][Type] = CreateMenu(Title, 1, MENU_TYPE_POSITION[Type][X], MENU_TYPE_POSITION[Type][Y], MENU_TYPE_SIZE[Type]);
    TogglePlayerControllable(PlayerId, false);
    return true;
}

public DestroyAllCustomMenuesForPlayer(PlayerId)
{
    PLAYER_MENU_TYPE[PlayerId] = -1;
    for (new I0 = 0; I0 < MAX_MENU_TYPES; I0++)
	{
	    if (IsValidMenu(MENU[PlayerId][I0]))
	    {
			DestroyMenu(MENU[PlayerId][I0]);
		}
	}
	return true;
}

public SetCustomMenuHeader(PlayerId, Type, Header[])
{
	SetMenuColumnHeader(MENU[PlayerId][Type], 0, Header);
	return true;
}

public ShowCustomMenuForPlayer(PlayerId, Type)
{
    ShowMenuForPlayer(MENU[PlayerId][Type], PlayerId);
    return true;
}

public AddCustomMenuItemForPlayer(PlayerId, Type, Text[])
{
	AddMenuItem(MENU[PlayerId][Type], 0, Text);
	return true;
}

