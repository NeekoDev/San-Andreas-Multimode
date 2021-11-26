/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       waypoint.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_track_waypoint
	#undef _inc_track_waypoint
#endif

#if defined _track_waypoint_included
	#endinput
#endif
#define _track_waypoint_included

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

#define MAX_TRACK_WAYPOINT                (256)
#define INVALID_TRACK_WAYPOINT_ID         (-1)

/*
* ==============================================================================
* Forwards
* ==============================================================================
*/

forward TrackWaypoint_OnLoad();

/*
* ==============================================================================
* Enums
* ==============================================================================
*/

enum E_TRACK_WAYPOINT_DATA 
{
    tw_Id,
    tw_TrackId
}

/*
* ==============================================================================
* Declarations
* ==============================================================================
*/

static trackWaypoint_Data[MAX_TRACK_WAYPOINT][E_TRACK_WAYPOINT_DATA];
new Iterator:trackWaypoint_List<MAX_TRACK_WAYPOINT>;

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
    Iter_Clear(trackWaypoint_List);

    return 1;
}

hook OnDatabaseInitialized()
{
    _TrackWaypoint_Load();

    return 1;
}

/*
* ==============================================================================
* Internal events
* ==============================================================================
*/

public TrackWaypoint_OnLoad()
{
    if(cache_num_rows() > 0) {
        new trackWaypointId = INVALID_TRACK_WAYPOINT_ID;

        for(new i = 0, j = cache_num_rows(); i < j; i++) {
            trackWaypointId = Iter_Free(trackWaypoint_List);

            if(trackWaypointId == ITER_NONE) {
                Log_Error("MAX_TRACK_WAYPOINT reached, please increase this constant.");
                return INVALID_TRACK_WAYPOINT_ID;
            }

            Iter_Add(trackWaypoint_List, trackWaypointId);

            if(!Iter_Contains(trackWaypoint_List, trackWaypointId)) {
                Log_Error("Error when added id to trackWaypoint_List.");
                return INVALID_TRACK_WAYPOINT_ID;
            }

            cache_get_value_name_int(i, "Id", trackWaypoint_Data[trackWaypointId][tw_Id]);
            cache_get_value_name_int(i, "TrackId", trackWaypoint_Data[trackWaypointId][tw_TrackId]);
        }
    }

    Log_Info("%d tracks waypoints loaded.", cache_num_rows());

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

static _TrackWaypoint_Load() 
{
    mysql_tquery(Database_GetHandler(), "SELECT * FROM `"SQL_TABLE_TRACK_WAYPOINT"`", "TrackWaypoint_OnLoad");

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