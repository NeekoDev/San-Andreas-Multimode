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

#if defined _inc_player_core
	#undef _inc_player_core
#endif

#if defined _player_core_included
	#endinput
#endif
#define _player_core_included

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

#define MAX_IP_LEN                      (16 + 1)
#define MAX_EMAIL_LEN 					(255)
#define MAX_PASSWORD_LEN                (255)
#define MAX_PIN_LEN                     (128)

// TODO: Lobby default pos (will allow the mapping to be preloaded)

#define INIT_POS_X (0)
#define INIT_POS_Y (0)
#define INIT_POS_Z (2)
#define INIT_POS_A (0)

/*
* ==============================================================================
* Forwards
* ==============================================================================
*/

forward Player_OnLoad(playerid);
forward Player_OnRegister(playerid);
forward OnPlayerRegistered(playerid);

/*
* ==============================================================================
* Enums
* ==============================================================================
*/

enum E_PLAYER_DATA
{
    p_Id,
	p_Name[MAX_PLAYER_NAME],
	p_Email[MAX_EMAIL_LEN],
	p_Password[MAX_PASSWORD_LEN],
	p_Pin[MAX_PIN_LEN],
	p_LastLoginIP[MAX_IP_LEN],
	p_LastLoginAt,
	p_Admin,
	p_Skin,
	p_TotalTimePlayed,
	p_Score,
	p_Money,

    // Internal properties (not saved in database)
	p_CurrentIP[MAX_IP_LEN],
    bool:p_Connecting,
	bool:p_Spawned,
	bool:p_InLobby
}

/*
* ==============================================================================
* Declarations
* ==============================================================================
*/

new player_Data[MAX_PLAYERS][E_PLAYER_DATA];

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

hook OnPlayerConnect(playerid) 
{
	// Reset properties
	_Player_Reset(playerid);

	// Set global player name
    GetPlayerName(playerid, g_PlayerName[playerid], MAX_PLAYER_NAME);

	// Set current ip
	GetPlayerIp(playerid, player_Data[playerid][p_CurrentIP], MAX_IP_LEN);

	// Player is connecting
	player_Data[playerid][p_Connecting] = true;

    return 1;
}

hook OnPlayerDisconnect(playerid, reason) 
{
	// Update player
	Player_Update(playerid);

	return 1;
}

hook OnPlayerRequestClass(playerid, classid) 
{
	// Clear player chat
	Chat_Clear(playerid);

	// Spawn info
	SetSpawnInfo(playerid, NO_TEAM, 0, INIT_POS_X, INIT_POS_Y, INIT_POS_Z, INIT_POS_A, 0, 0, 0, 0, 0, 0);

	// To hide « Spawn » button
	// The order of these functions is important
	TogglePlayerSpectating(playerid, true);
	SpawnPlayer(playerid);

	// TODO: Show loading screen ?

	return 1;
}

hook OnPlayerSpawn(playerid) 
{
	// Preload animations
    PreloadPlayerAnims(playerid);

	// If player is connecting
	if(player_Data[playerid][p_Connecting]) 
	{
        // Set camera
        SetPlayerCameraPos(playerid, -2767.2, 1672.8, 117.4);
		SetPlayerCameraLookAt(playerid, -2746.8, 1583.8, 105.1);

		// Load player
		_Player_Load(playerid);

		// Player isn't connecting anymore
        player_Data[playerid][p_Connecting] = false;
	}

	return 1;
}

/*
* ==============================================================================
* Internal events
* ==============================================================================
*/

public Player_OnLoad(playerid) 
{
	// The player is not registered in the database
	if (!cache_num_rows()) {
		// Show register dialog
		Register_Show(playerid);
		return 0;
	}

	//
	cache_get_value_name_int(0, "Id", player_Data[playerid][p_Id]);
	cache_get_value_name(0, "Name", player_Data[playerid][p_Name], MAX_PLAYER_NAME);
	cache_get_value_name(0, "Email", player_Data[playerid][p_Email], MAX_EMAIL_LEN);
	cache_get_value_name(0, "Password", player_Data[playerid][p_Password], MAX_PASSWORD_LEN);
	cache_get_value_name(0, "Pin", player_Data[playerid][p_Pin], MAX_PIN_LEN);
	cache_get_value_name_int(0, "Admin", player_Data[playerid][p_Admin]);
	cache_get_value_name_int(0, "LastLoginAt", player_Data[playerid][p_Id]);
	cache_get_value_name(0, "LastLoginIP", player_Data[playerid][p_LastLoginIP], MAX_IP_LEN);
	cache_get_value_name_int(0, "Skin", player_Data[playerid][p_Skin]);
	cache_get_value_name_int(0, "TotalTimePlayed", player_Data[playerid][p_TotalTimePlayed]);
	cache_get_value_name_int(0, "Score", player_Data[playerid][p_Score]);
	cache_get_value_name_int(0, "Money", player_Data[playerid][p_Money]);

	// Show login password dialog
	Login_PasswordShow(playerid);
	
	return 1;
}

public Player_OnRegister(playerid)
{
	// Set Id
	player_Data[playerid][p_Id] = cache_insert_id();

	// Set default properties
	player_Data[playerid][p_Admin] = 0;
	player_Data[playerid][p_Skin] = 1;
	player_Data[playerid][p_Score] = 0;
	player_Data[playerid][p_Money] = 0;

	//
    CallLocalFunction("OnPlayerRegistered", "d", playerid);

	return 1;
}

/*
* ==============================================================================
* Functions
* ==============================================================================
*/

Player_Register(playerid, const email[], const password[], const pin[])
{
	new queryStr[HIGHT_MYSQL_QUERY], emailStr[MAX_EMAIL_LEN];

    mysql_escape_string(email, emailStr);

    mysql_format(Database_GetHandler(), queryStr, sizeof(queryStr), "INSERT INTO `"SQL_TABLE_PLAYER"` (`Name`, `Email`, `Password`, `RegisterIP`, `Pin`, `CreatedAt`, `UpdatedAt`) VALUES ('%s', '%s', '%s', '%s', '%s', NOW(), NOW())", 
        g_PlayerName[playerid],
        emailStr,
		password, 
        player_Data[playerid][p_CurrentIP],
        pin);

    mysql_pquery(Database_GetHandler(), queryStr, "Player_OnRegister", "d", playerid);

	return 1;
}

Player_Update(playerid)
{
	new queryStr[HIGHT_MYSQL_QUERY];

    mysql_format(Database_GetHandler(), queryStr, sizeof(queryStr), "UPDATE `"SQL_TABLE_PLAYER"` SET `Admin` = %d, `LastLoginAt` = NOW(), `LastLoginIP` = '%s', `Skin` = %d, `TotalTimePlayed` = %d, `Score` = %d, `Money` = %d, `UpdatedAt` = NOW() WHERE `Id` = %d", 
        player_Data[playerid][p_Admin],
		player_Data[playerid][p_CurrentIP],
		player_Data[playerid][p_Skin],
		player_Data[playerid][p_TotalTimePlayed],
		player_Data[playerid][p_Score],
		player_Data[playerid][p_Money],
        player_Data[playerid][p_Id]);

	mysql_pquery(Database_GetHandler(), queryStr);

	return 1;
}

/*
* ==============================================================================
* Private functions
* ==============================================================================
*/

static _Player_Load(playerid)
{
    new queryStr[NORMAL_MYSQL_QUERY];

    mysql_format(Database_GetHandler(), queryStr, sizeof(queryStr), "SELECT * FROM `"SQL_TABLE_PLAYER"` WHERE `name` = '%e' LIMIT 1", g_PlayerName[playerid]);
    mysql_tquery(Database_GetHandler(), queryStr, "Player_OnLoad", "d", playerid);

    return 1; 
}

static _Player_Reset(playerid)
{
    // Reset enums
    static const empty_player[E_PLAYER_DATA];
    player_Data[playerid] = empty_player;

	// Reset properties
	player_Data[playerid][p_CurrentIP][0] = EOS;
	player_Data[playerid][p_Connecting] = false;
	player_Data[playerid][p_Spawned] = false;
	player_Data[playerid][p_InLobby] = false;

	return 1;
}

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