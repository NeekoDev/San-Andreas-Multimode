/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       core.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_lobby_core
	#undef _inc_lobby_core
#endif

#if defined _lobby_core_included
	#endinput
#endif
#define _lobby_core_included

/*
* ==============================================================================
* Dependencies
* ==============================================================================
*/

#include <YSI_Coding\y_hooks>

/*
* ==============================================================================
* Constants
* ==============================================================================
*/

/*
* ==============================================================================
* Forwards
* ==============================================================================
*/

/*
* ==============================================================================
* Enums
* ==============================================================================
*/

/*
* ==============================================================================
* Declarations
* ==============================================================================
*/

/*
* ==============================================================================
* Internal Packages
* ==============================================================================
*/

/*
* ==============================================================================
* Lifecycle events
* ==============================================================================
*/

hook OnPlayerLogged(playerid)
{
    // Log
    Log_Info("%s is logged.", g_PlayerName[playerid]);

    // Spawn in lobby
    Lobby_Spawn(playerid);

    return 1;
}

hook OnPlayerRegistered(playerid)
{
    // Spawn in lobby
    Lobby_Spawn(playerid);

    return 1;
}

/*
* ==============================================================================
* Internal events
* ==============================================================================
*/

/*
* ==============================================================================
* Functions
* ==============================================================================
*/

Lobby_Spawn(playerid)
{
    // Reset camera
    TogglePlayerSpectating(playerid, false);
    SetCameraBehindPlayer(playerid);

    // 
    SetPlayerScore(playerid, player_Data[playerid][p_Score]);
    SetPlayerSkin(playerid, player_Data[playerid][p_Skin]);
    GivePlayerMoney(playerid, player_Data[playerid][p_Money]);

    // TODO: Mapping
    
    SetPlayerPos(playerid, -1444.645507, -664.526000, 1053.572998);
    SetPlayerFacingAngle(playerid, 0);
    SetPlayerInterior(playerid, 4);
    SetPlayerVirtualWorld(playerid, 0); // TODO

    // Set player spawned
    player_Data[playerid][p_Spawned] = true;

    // Set player in lobby
    player_Data[playerid][p_InLobby] = true;

    return 1;
}

SendLobbyMessage(playerid, const text[]) 
{
	new
		line1[256],
		line2[128];

    format(line1, sizeof(line1), "[Lobby] %s (%d) : %s", g_PlayerName[playerid], playerid, text);
    TruncateChatMessage(line1, line2);

    foreach(new i : Player) {
        if (!player_Data[i][p_Spawned])
            continue;

        if (!player_Data[i][p_InLobby])
            continue;

        if(!IsNull(line2)) {
            strins(line1, " ...", strlen(line1));
            strins(line2, "... ", 0);

            SendClientMessage(i, COLOR_LOBBY, line1);
            SendClientMessage(i, COLOR_LOBBY, line2);
        }
        else {
            SendClientMessage(i, COLOR_LOBBY, line1);
        }
    }

    return 1;
}

/*
* ==============================================================================
* Private functions
* ==============================================================================
*/

/*
* ==============================================================================
* Dialogs
* ==============================================================================
*/

/*
* ==============================================================================
* Timers
* ==============================================================================
*/

/*
* ==============================================================================
* Commands
* ==============================================================================
*/

/*
* ==============================================================================
* Get / Set
* ==============================================================================
*/