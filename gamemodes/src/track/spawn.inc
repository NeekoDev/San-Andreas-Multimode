/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       spawn.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_track_spawn
	#undef _inc_track_spawn
#endif

#if defined _track_spawn_included
	#endinput
#endif
#define _track_spawn_included

/*
* ==============================================================================
* Dependencies
* ==============================================================================
*/

#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_iterate>

/*
* ==============================================================================
* Constants
* ==============================================================================
*/

#define MAX_TRACK_SPAWN                (256)
#define INVALID_TRACK_SPAWN_ID         (-1)

/*
* ==============================================================================
* Forwards
* ==============================================================================
*/

forward TrackSpawn_OnLoad();

/*
* ==============================================================================
* Enums
* ==============================================================================
*/

enum E_TRACK_SPAWN_DATA 
{
    ts_Id,
    ts_TrackId
}

/*
* ==============================================================================
* Declarations
* ==============================================================================
*/

static trackSpawn_Data[MAX_TRACK_SPAWN][E_TRACK_SPAWN_DATA];
new Iterator:trackSpawn_List<MAX_TRACK_SPAWN>;

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
    Iter_Clear(trackSpawn_List);

    return 1;
}

hook OnDatabaseInitialized()
{
    _TrackSpawn_Load();

    return 1;
}

/*
* ==============================================================================
* Internal events
* ==============================================================================
*/

public TrackSpawn_OnLoad()
{
    if(cache_num_rows() > 0) {
        new trackSpawnId = INVALID_TRACK_SPAWN_ID;

        for(new i = 0, j = cache_num_rows(); i < j; i++) {
            trackSpawnId = Iter_Free(trackSpawn_List);

            if(trackSpawnId == ITER_NONE) {
                Log_Error("MAX_TRACK_SPAWN reached, please increase this constant.");
                return INVALID_TRACK_SPAWN_ID;
            }

            Iter_Add(trackSpawn_List, trackSpawnId);

            if(!Iter_Contains(trackSpawn_List, trackSpawnId)) {
                Log_Error("Error when added id to trackSpawn_List.");
                return INVALID_TRACK_SPAWN_ID;
            }

            cache_get_value_name_int(i, "Id", trackSpawn_Data[trackSpawnId][ts_Id]);
            cache_get_value_name_int(i, "TrackId", trackSpawn_Data[trackSpawnId][ts_TrackId]);
        }
    }

    Log_Info("%d tracks spawns loaded.", cache_num_rows());

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

static _TrackSpawn_Load() 
{
    mysql_tquery(Database_GetHandler(), "SELECT * FROM `"SQL_TABLE_TRACK_SPAWN"`", "TrackSpawn_OnLoad");

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