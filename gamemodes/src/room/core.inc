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

#if defined _inc_room_core
	#undef _inc_room_core
#endif

#if defined _room_core_included
	#endinput
#endif
#define _room_core_included

/*
* ==============================================================================
* Dependencies
* ==============================================================================
*/

#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_hooks>

/*
* ==============================================================================
* Constants
* ==============================================================================
*/

#define MAX_ROOM                    (MAX_MODE + 5)
#define MAX_ROOM_NAME               (128)
#define MAX_ROOM_PLAYERS            (20)

#define INVALID_ROOM_ID             (-1)

/*
* ==============================================================================
* Forwards
* ==============================================================================
*/

forward Room_OnLoad();

/*
* ==============================================================================
* Enums
* ==============================================================================
*/

enum E_ROOM_DATA 
{
    r_Id,
    r_Name[MAX_ROOM_NAME],
    r_ModeId,

    // Internal properties (not saved in database)
}

/*
* ==============================================================================
* Declarations
* ==============================================================================
*/

static 
    room_Data[MAX_ROOM][E_ROOM_DATA],
    room_ListIndex[MAX_PLAYERS][MAX_ROOM],
    room_ListSelected[MAX_PLAYERS];

new 
    Iterator:room_List<MAX_ROOM>,
    Iterator:room_Players[MAX_ROOM]<MAX_ROOM_PLAYERS>;

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

hook OnGameModeInit()
{
    Iter_Clear(room_List);

    for(new i = 0; i < MAX_ROOM; i++) {
        Iter_Clear(room_Players[i]);
    }

    return 1;
}

hook OnDatabaseInitialized()
{
    _Room_Load();

    return 1;
}

hook OnPlayerConnect(playerid)
{
    for(new i = 0; i < MAX_ROOM; i++) {
        room_ListIndex[playerid][i] = INVALID_ROOM_ID;
    }

    room_ListSelected[playerid] = INVALID_ROOM_ID;

    return 1;
}

/*
* ==============================================================================
* Internal events
* ==============================================================================
*/

public Room_OnLoad()
{
    if(cache_num_rows() > 0) {
        new roomid = INVALID_ROOM_ID;

        for(new i = 0, j = cache_num_rows(); i < j; i++) {
            roomid = Iter_Free(room_List);

            if(roomid == ITER_NONE) {
                Log_Error("MAX_ROOM reached, please increase this constant.");
                return INVALID_ROOM_ID;
            }

            Iter_Add(room_List, roomid);

            if(!Iter_Contains(room_List, roomid)) {
                Log_Error("Error when added id to room_List.");
                return INVALID_ROOM_ID;
            }

            cache_get_value_name_int(i, "Id", room_Data[roomid][r_Id]);
            cache_get_value_name(i, "Name", room_Data[roomid][r_Name], MAX_ROOM_NAME);
            cache_get_value_name_int(i, "ModeId", room_Data[roomid][r_ModeId]);
        }
    }

    Log_Info("%d rooms loaded.", cache_num_rows());

    return 1;
}

/*
* ==============================================================================
* Functions
* ==============================================================================
*/

Room_ShowList(playerid, modeid)
{
    new 
        count = 0,
        modeName[MAX_MODE_NAME],
        dialogTitle[TITLE_DIALOG_LEN],
        dialogContent[NORMAL_DIALOG_LEN];

    GetModeName(modeid, modeName);

    format(dialogTitle, sizeof(dialogTitle), "%s - Liste des salons", modeName);
    format(dialogContent, sizeof(dialogContent), "Nom\tJoueurs\n");

    foreach(new roomid : room_List) {
        if(room_Data[roomid][r_ModeId] == GetModeId(modeid)) {
            format(dialogContent, sizeof(dialogContent), "%s%s\t%d/%d\n", dialogContent, room_Data[roomid][r_Name], Iter_Count(room_Players[roomid]), MAX_ROOM_PLAYERS);

            room_ListIndex[playerid][count] = roomid;

            count++;
        }
    }

    Dialog_Open(
        playerid,
        "Room_Dialog",
        DIALOG_STYLE_TABLIST_HEADERS,
        dialogTitle,
        dialogContent,
        "Valider",
        "Quitter"
    );

    return 1;
}

Room_Join(playerid, roomid)
{
    // Add player to room players list
    _Room_AddPlayer(playerid, roomid);

    // Set player room
    SetPlayerRoom(playerid, roomid);

    // TODO

    return 1;
}

/*
* ==============================================================================
* Private functions
* ==============================================================================
*/

static _Room_Load() 
{
    mysql_tquery(Database_GetHandler(), "SELECT * FROM `"SQL_TABLE_ROOM"`", "Room_OnLoad");

    return 1;
}

static _Room_AddPlayer(playerid, roomid)
{
    // TODO: Prevent player
    
    if(Iter_Contains(room_Players[roomid], playerid)) {
        Log_Error("Error when added player to room. Already in room ...");
        return INVALID_PLAYER_ID;
    }

    Iter_Add(room_Players[roomid], playerid);

    return 1;
}

/*
* ==============================================================================
* Dialogs
* ==============================================================================
*/

Dialog:Room_Dialog(playerid, response, item, input[]) 
{
    if(!response)
        return 0;

    room_ListSelected[playerid] = room_ListIndex[playerid][item];

    // TODO: Check if room is full
    
    Room_Join(playerid, room_ListSelected[playerid]);

    return 1;
}

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

//
stock bool:IsValidRoom(roomid) 
{
    if(!Iter_Contains(room_List, roomid)) {
        return false;
    }

    return true;
}