/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       main.pwn
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#include <a_samp>

/*
* ==============================================================================
* Library Predefinitions
* ==============================================================================
*/

#undef MAX_PLAYERS
#define MAX_PLAYERS (100)

// YSI
#define CGEN_MEMORY 20000
#define YSI_NO_OPTIMISATION_MESSAGE
#define YSI_NO_OBNOXIOUS_HEADER
#define YSI_NO_MODE_CACHE

/*
* ==============================================================================
* Dependencies
* ==============================================================================
*/

//#include <fixes>
#include <crashdetect>
#include <sscanf2>
#include <streamer>
#include <a_mysql>
#include <easyDialog>
#include <Pawn.CMD>

/*
* ==============================================================================
* Shared packages
* ==============================================================================
*/

#include "shared/log"
#include "shared/settings"
#include "shared/database"
#include "shared/helper/helper"

/*
* ==============================================================================
* Bootstrap
* ==============================================================================
*/

#include "src/bootstrap"

/*
* ==============================================================================
* Internal packages
* ==============================================================================
*/

#include "mode/mode"
#include "room/room"
#include "track/track"
#include "race/race"
#include "player/player"
#include "punishment/punishment"
#include "lobby/lobby"
#include "vehicle/vehicle"

#include "admin/admin"

/*
* ==============================================================================
* Lifecycle events
* ==============================================================================
*/

main()
{
	Log_Info("Gamemode initialized.\n");
}

public OnPlayerRequestDownload(playerid, type, crc) 
{
    return 1;
}

public OnPlayerFinishedDownloading(playerid, virtualworld) 
{
    return 1;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{   
    if (flags > ADMIN_LEVEL_PLAYER && GetPlayerAdmin(playerid) < flags) {
        SendClientMessage(playerid, COLOR_ERROR, "Vous ne disposez pas des permissions requises.");

        return 0; 
    }

    return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) 
{
    if (!IsPlayerSpawned(playerid))
        return 0;

    switch(result) {
        case CMD_NOT_EXIST: SendClientMessage(playerid, COLOR_ERROR, "La commande n'a pas été reconnue, consulter la liste via /aide.");
        case CMD_SUCCESS: return 1;
        case CMD_NO_ACCESS: SendClientMessage(playerid, COLOR_ERROR, "Vous ne disposez pas des permissions requises.");
    }

    return 1;
}