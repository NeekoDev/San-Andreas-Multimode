#if defined _inc_database
	#undef _inc_database
#endif

#if defined _database_included
	#endinput
#endif
#define _database_included

/*
* ==============================================================================
* Dependencies
* ==============================================================================
*/

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

forward OnDatabaseInitialized();

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

static stock MySQLOpt:databaseOptions;
static stock MySQL:databaseHandler;

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

/*
* ==============================================================================
* Functions
* ==============================================================================
*/

Database_Connect(const hostname[], const username[], const password[], const database[]) 
{
    // Initialize plugin MySQL (set options)
    _Database_Initialize();

    // Create new mysql instance
    databaseHandler = mysql_connect(hostname, username, password, database, databaseOptions);

    // If the connection failed
    if(databaseHandler == MySQL:0 || mysql_errno(databaseHandler) != 0) {
        Log_Fatal("Failed to connect to the database.");
        SendRconCommand("exit");
        return 0;
    }

    // Log
    Log_Info("Database connection successful.");
    
    // Callback
    CallLocalFunction("OnDatabaseInitialized", "");

    return 1;
}

Database_Disconnect() 
{
    if(databaseHandler) {
        if(!mysql_close(databaseHandler)) {
            print("Can't disconnect to MySQL database. Shutting down...");
            return 0;
        }
    }

    return 1;
}

/*
* ==============================================================================
* Private functions
* ==============================================================================
*/

static _Database_Initialize() 
{
    // Log
    Log_Info("Initialize database ...");

    mysql_log(ALL);

    databaseOptions = mysql_init_options();

    mysql_set_option(databaseOptions, AUTO_RECONNECT, true);
    mysql_set_option(databaseOptions, POOL_SIZE, 2);

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

stock MySQL:Database_GetHandler() 
{
    return databaseHandler;
}