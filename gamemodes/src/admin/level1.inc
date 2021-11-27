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

flags:admin(ADMIN_LEVEL_SUPPORT)
CMD:admin(playerid, params[]) 
{
    if(IsNull(params)) {
        return SendClientMessage(playerid, COLOR_USAGE, "[Usage] /(a)dmin <texte>");
    }

    SendAdminMessage(COLOR_ADMIN_CHAT, "[AdminChat] %s : %s", g_PlayerName[playerid], params);

    return 1;
}
alias:admin("a")

flags:ahelp(ADMIN_LEVEL_SUPPORT)
CMD:ahelp(playerid, params[]) 
{
    SendClientMessage(playerid, COLOR_ADMIN, "[Commun] /ahelp (/ah) /aaide, /(a)dmin");

    switch (GetPlayerAdmin(playerid)) {
        case ADMIN_LEVEL_SUPPORT: {
            SendClientMessage(playerid, COLOR_ADMIN, "[Support] /(ann)once, /annonceserveur (/as), /tog");
        }
        case ADMIN_LEVEL_MODO: {
            
        }
        case ADMIN_LEVEL_ADMIN: {
            
        }
        case ADMIN_LEVEL_MANAGER: {
            
        }
        case ADMIN_LEVEL_DEV: {
            
        }
    }

    return 1;
}
alias:ahelp("ah", "aaide")

flags:aclear(ADMIN_LEVEL_SUPPORT)
CMD:aclear(playerid, params[]) 
{
    for(new i; i < 100; i++)
        SendClientMessageToAll(-1, " ");

    SendClientMessageToAll(COLOR_RED, "Un nettoyage du chat a été effectué.");

    return 1;
}
alias:aclear("ac")

flags:annonce(ADMIN_LEVEL_SUPPORT)
CMD:annonce(playerid, params[]) 
{
    new text[CHAT_STRING_LEN];

    if(sscanf(params, "s[128]", text)) {
        SendClientMessage(playerid, COLOR_USAGE, "[Usage] /annonce <texte>");

        return 1;
    }

    SendClientMessageToAllEx(COLOR_RED, "[Annonce] %s : %s", g_PlayerName[playerid], text);

    return 1;
}
alias:annonce("ann")

flags:annonceserveur(ADMIN_LEVEL_SUPPORT)
CMD:annonceserveur(playerid, params[]) 
{
    new text[CHAT_STRING_LEN];

    if(sscanf(params, "s[128]", text)) {
        SendClientMessage(playerid, COLOR_USAGE, "[Usage] /annonceserveur (/as) <texte>");

        return 1;
    }

    SendClientMessageToAllEx(COLOR_RED, "[Serveur] %s", text);

    return 1;
}
alias:annonceserveur("as")

flags:tog(ADMIN_LEVEL_SUPPORT)
CMD:tog(playerid, params[]) 
{
    new
        actionCmd[24];

    if(sscanf(params, "s[24]", actionCmd)) {
        SendClientMessage(playerid, COLOR_USAGE, "[Usage] /tog <option>");
        SendClientMessage(playerid, COLOR_OPTION, "[Options] lobby, question");

        return 1;
    }

    if(!strcmp(actionCmd, "lobby", true)) {
        if(g_ChatLobbyEnabled) {
            g_ChatLobbyEnabled = 0;
           
            SendClientMessageToAllEx(COLOR_RED, "[Annonce] %s a fermé le canal lobby.", g_PlayerName[playerid]);
        }
        else {
            g_ChatLobbyEnabled = 1;

            SendClientMessageToAllEx(COLOR_RED, "[Annonce] %s a ouvert le canal lobby.", g_PlayerName[playerid]);
        }

        UpdateSettingInt("configs.ini", "chat_lobby_enabled", g_ChatLobbyEnabled);
    }
    else if(!strcmp(actionCmd, "question", true)) {
        if(g_ChatQuestionEnabled) {
            g_ChatQuestionEnabled = 0;
           
            SendClientMessageToAllEx(COLOR_RED, "[Annonce] %s a fermé le /question (/i).", g_PlayerName[playerid]);
        }
        else {
            g_ChatQuestionEnabled = 1;

            SendClientMessageToAllEx(COLOR_RED, "[Annonce] %s a ouvert le /question (/i).", g_PlayerName[playerid]);
        }

        UpdateSettingInt("configs.ini", "chat_question_enabled", g_ChatQuestionEnabled);
    }
    else {
        SendClientMessage(playerid, COLOR_USAGE, "[Usage] /tog <option>");
        SendClientMessage(playerid, COLOR_OPTION, "[Options] lobby, question");
    }

    return 1;
}