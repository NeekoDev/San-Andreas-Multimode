/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       constants.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_constants
	#undef _inc_constants
#endif

#if defined _constants_included
	#endinput
#endif
#define _constants_included

/*
* ==============================================================================
* Macros
* ==============================================================================
*/

#if !defined IsNull
    #define IsNull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

/*
* ==============================================================================
* Colors
* ==============================================================================
*/

#define COLOR_WHITE                             0xFFFFFFFF
#define COLOR_RED                               0xFF6347AA

#define COLOR_ERROR                             0xFF6347AA
#define COLOR_ADMIN                             0xFFFFFFFF // TODO
#define COLOR_ADMIN_CHAT                        0xFFFFFFFF // TODO
#define COLOR_USAGE                             0xFFFFFFFF // TODO
#define COLOR_OPTION                            0xFFFFFFFF // TODO
#define COLOR_LOBBY                             0xFFFFFFFF // TODO

/*
* ==============================================================================
* Commands
* ==============================================================================
*/

#define CMD_NOT_EXIST                           (-1)
#define CMD_SUCCESS                             (1)
#define CMD_NO_ACCESS                           (2)

/*
* ==============================================================================
* Admin levels
* ==============================================================================
*/

#define ADMIN_LEVEL_PLAYER                      (0)
#define ADMIN_LEVEL_SUPPORT                     (1)
#define ADMIN_LEVEL_MODO                        (2)
#define ADMIN_LEVEL_ADMIN                       (3)
#define ADMIN_LEVEL_MANAGER                     (4)
#define ADMIN_LEVEL_DEV                         (5)

/*
* ==============================================================================
* String length
* ==============================================================================
*/

// Strings
#define LIGHT_STRING_LEN                        (64)
#define CHAT_STRING_LEN                         (128)
#define NORMAL_STRING_LEN                       (256)


// Query
#define LIGHT_MYSQL_QUERY                       (64)
#define NORMAL_MYSQL_QUERY                      (256)
#define HIGHT_MYSQL_QUERY                       (1024)

// Dialog
#define TITLE_DIALOG_LEN                        (64)
#define LIGHT_DIALOG_LEN                        (128)
#define NORMAL_DIALOG_LEN                       (256)
#define HIGHT_DIALOG_LEN                        (1024)
#define BIG_DIALOG_LEN                          (2048)

/*
* ==============================================================================
* Database table names
* ==============================================================================
*/

#define SQL_TABLE_MODE                  "server_modes"
#define SQL_TABLE_PLAYER                "server_players"
#define SQL_TABLE_RACE                  "server_races"
#define SQL_TABLE_ROOM                  "server_rooms"
#define SQL_TABLE_TRACK                 "server_tracks"
#define SQL_TABLE_TRACK_SPAWN           "server_tracks_spawns"
#define SQL_TABLE_TRACK_WAYPOINT        "server_tracks_waypoints"