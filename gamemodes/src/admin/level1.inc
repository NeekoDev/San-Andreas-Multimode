/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       level1.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_admin_level1
	#undef _inc_admin_level1
#endif

#if defined _admin_level1_included
	#endinput
#endif
#define _admin_level1_included

flags:admin(ADMIN_LEVEL_SUPPORT | ADMIN_LEVEL_MODO | ADMIN_LEVEL_ADMIN | ADMIN_LEVEL_MANAGER | ADMIN_LEVEL_DEV)
CMD:admin(playerid, params[]) {
    if(IsNull(params)) {
        return SendClientMessage(playerid, COLOR_USAGE, "[Usage] /(a)dmin <texte>");
    }

    SendAdminMessage(COLOR_ADMIN_CHAT, "[AdminChat] %s : %s", g_PlayerName[playerid], params);

    return 1;
}
alias:admin("a")