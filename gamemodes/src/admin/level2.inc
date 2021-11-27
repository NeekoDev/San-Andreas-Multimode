/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       level2.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_admin_level2
	#undef _inc_admin_level2
#endif

#if defined _admin_level2_included
	#endinput
#endif
#define _admin_level2_included

flags:goto(ADMIN_LEVEL_MODO | ADMIN_LEVEL_ADMIN | ADMIN_LEVEL_MANAGER | ADMIN_LEVEL_DEV)
CMD:goto(playerid, params[]) 
{

    return 1;
}
alias:goto("go")