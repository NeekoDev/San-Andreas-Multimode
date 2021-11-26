/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       cmd.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_player_cmd
	#undef _inc_player_cmd
#endif

#if defined _player_cmd_included
	#endinput
#endif
#define _player_cmd_included

// Global
CMD:help(playerid, params[]) 
{
    SendClientMessage(playerid, COLOR_WHITE, "______________________________________________________________________________");
    SendClientMessage(playerid, COLOR_WHITE, "GLOBAL: /admins, /stats, /question (/i), /rapport, /voteban, /vote");
    SendClientMessage(playerid, COLOR_WHITE, "CHAT: /mp (/pm)");
    SendClientMessage(playerid, COLOR_WHITE, "______________________________________________________________________________");

    return 1;
}
alias:help("aide")