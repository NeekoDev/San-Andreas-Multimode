/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       level5.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_admin_level5
	#undef _inc_admin_level5
#endif

#if defined _admin_level5_included
	#endinput
#endif
#define _admin_level5_included

flags:play(ADMIN_LEVEL_DEV)
CMD:play(playerid, params[]) {
    return 1;
}