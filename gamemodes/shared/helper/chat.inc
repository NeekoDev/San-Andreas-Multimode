#if defined _inc_helper_chat
	#undef _inc_helper_chat
#endif

#if defined _helper_chat_included
	#endinput
#endif
#define _helper_chat_included

// Function to clear player chat
Chat_Clear(playerid) 
{
    for(new i = 0; i < 10; i++) {
        SendClientMessage(playerid, -1, "");
    }
    
    return 1;
}

// Function to truncate message
TruncateChatMessage(input[], output[]) {
	if(strlen(input) > 127) {
		new splitpos;

		for(new i = 118; i > 0; i--) {
			if(input[i] == ' ' || input[i] ==  ',' || input[i] ==  '.') {
				splitpos = i;
				break;
			}
		}

		strcat(output, input[splitpos], 118);
		input[splitpos] = 0;

		return 1;
	}

	return 0;
}

SendClientMessageToAllEx(colour, const format[], va_args<>) {
	new
		gs_Buffer[256];
		
	va_format(gs_Buffer, sizeof(gs_Buffer), format, va_start<2>);

	SendClientMessageToAll(colour, gs_Buffer);

	return 1;
}