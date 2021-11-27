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

#if defined _inc_mode_core
	#undef _inc_mode_core
#endif

#if defined _mode_core_included
	#endinput
#endif
#define _mode_core_included

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

#define MAX_MODE                    (10)
#define MAX_MODE_NAME               (128)
#define INVALID_MODE_ID             (-1)

/*
* ==============================================================================
* Forwards
* ==============================================================================
*/

forward Mode_OnLoad();

/*
* ==============================================================================
* Enums
* ==============================================================================
*/

enum E_MODE_TYPE {
    Race,
    Derby
}

enum E_MODE_DATA 
{
    m_Id,
    m_Name[MAX_MODE_NAME],
    E_MODE_TYPE:m_Type,
    bool:m_Enabled
}

/*
* ==============================================================================
* Declarations
* ==============================================================================
*/

static 
    mode_Data[MAX_MODE][E_MODE_DATA],
    mode_ListIndex[MAX_PLAYERS][MAX_MODE],
    mode_ListSelected[MAX_PLAYERS];

new 
    Iterator:mode_List<MAX_MODE>;

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
    Iter_Clear(mode_List);

    return 1;
}

hook OnDatabaseInitialized()
{
    _Mode_Load();

    return 1;
}

hook OnPlayerConnect(playerid)
{
    for(new i = 0; i < MAX_MODE; i++) {
        mode_ListIndex[playerid][i] = INVALID_MODE_ID;
    }

    mode_ListSelected[playerid] = INVALID_MODE_ID;

    return 1;
}

/*
* ==============================================================================
* Internal events
* ==============================================================================
*/

public Mode_OnLoad()
{
    if(cache_num_rows() > 0) {
        new modeid = INVALID_MODE_ID;

        for(new i = 0, j = cache_num_rows(); i < j; i++) {
            modeid = Iter_Free(mode_List);

            if(modeid == ITER_NONE) {
                Log_Error("MAX_MODE reached, please increase this constant.");
                return INVALID_MODE_ID;
            }

            Iter_Add(mode_List, modeid);

            if(!Iter_Contains(mode_List, modeid)) {
                Log_Error("Error when added id to mode_List.");
                return INVALID_MODE_ID;
            }

            cache_get_value_name_int(i, "Id", mode_Data[modeid][m_Id]);
            cache_get_value_name(i, "Name", mode_Data[modeid][m_Name], MAX_MODE_NAME);
            cache_get_value_name_int(i, "Type", _:mode_Data[modeid][m_Type]);
            cache_get_value_name_bool(i, "Enabled", mode_Data[modeid][m_Enabled]);
        }
    }

    Log_Info("%d modes loaded.", cache_num_rows());

    return 1;
}

/*
* ==============================================================================
* Functions
* ==============================================================================
*/

Mode_ShowList(playerid) 
{
    new 
        count = 0,
        dialogContent[NORMAL_DIALOG_LEN];

    foreach(new modeid : mode_List) {
        if(mode_Data[modeid][m_Enabled]) {
            format(dialogContent, sizeof(dialogContent), "%s%s\n", dialogContent, mode_Data[modeid][m_Name]);

            mode_ListIndex[playerid][count] = modeid;

            count++;
        }
    }

    Dialog_Open(
        playerid,
        "Mode_Dialog",
        DIALOG_STYLE_LIST,
        "Liste des modes",
        dialogContent,
        "Valider",
        "Quitter"
    );

    return 1;
}

/*
* ==============================================================================
* Private functions
* ==============================================================================
*/

static _Mode_Load() 
{
    mysql_tquery(Database_GetHandler(), "SELECT * FROM `"SQL_TABLE_MODE"`", "Mode_OnLoad");

    return 1;
}

/*
* ==============================================================================
* Dialogs
* ==============================================================================
*/

Dialog:Mode_Dialog(playerid, response, item, input[]) 
{
    if(!response)
        return 0;

    mode_ListSelected[playerid] = mode_ListIndex[playerid][item];

    Room_ShowList(playerid, mode_ListSelected[playerid]);

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

// m_Id
stock GetModeId(modeid) 
{
    if(!Iter_Contains(mode_List, modeid)) {
        return INVALID_MODE_ID;
    }

    return mode_Data[modeid][m_Id];
}

// m_Name
stock GetModeName(modeid, name[MAX_MODE_NAME]) 
{
    if(!Iter_Contains(mode_List, modeid)) {
        return INVALID_MODE_ID;
    }

    name[0] = EOS;
    strcat(name, mode_Data[modeid][m_Name], MAX_MODE_NAME);

    return 1;
}