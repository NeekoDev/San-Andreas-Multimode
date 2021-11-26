/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       bootstrap.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_bootstrap
	#undef _inc_bootstrap
#endif

#if defined _bootstrap_included
	#endinput
#endif
#define _bootstrap_included

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

new g_PlayerName[MAX_PLAYERS][MAX_PLAYER_NAME];

/*
* ==============================================================================
* Internal Packages
* ==============================================================================
*/

#include "constants"

/*
* ==============================================================================
* Lifecycle events
* ==============================================================================
*/

public OnScriptInit() 
{
    // Log
    Log_Info("Initializing ...");

    // Database connection
    Database_Connect("localhost", "root", "", "samm");
    
	return 1;
}

public OnGameModeInit()
{
	// Set server language
	SendRconCommand("language Français");

	return 1;
}

public OnGameModeExit() 
{
    // Database disconnection
    Database_Disconnect();

	return 1;
}

/*
* ==============================================================================
* Functions
* ==============================================================================
*/

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