/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       login.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_player_login
	#undef _inc_player_login
#endif

#if defined _player_login_included
	#endinput
#endif
#define _player_login_included

/*
* ==============================================================================
* Dependencies
* ==============================================================================
*/

#include <YSI_Coding\y_hooks>
#include <samp_bcrypt>

/*
* ==============================================================================
* Constants
* ==============================================================================
*/

#define MAX_LOGIN_PASSWORD_ATTEMPTS     (3)
#define MAX_LOGIN_PIN_ATTEMPTS          (3)

/*
* ==============================================================================
* Forwards
* ==============================================================================
*/

forward Login_OnPasswordChecked(playerid, bool:success);
forward Login_OnPinChecked(playerid, bool:success);
forward OnPlayerLogged(playerid);

/*
* ==============================================================================
* Enums
* ==============================================================================
*/

enum E_PLAYER_LOGIN_DATA
{
    pLogin_PasswordAttempts,
    pLogin_PinAttempts
}

/*
* ==============================================================================
* Declarations
* ==============================================================================
*/

static playerLogin_Data[MAX_PLAYERS][E_PLAYER_LOGIN_DATA];

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

hook OnPlayerConnect(playerid) 
{
    // Reset properties
    playerLogin_Data[playerid][pLogin_PasswordAttempts] = 0;
    playerLogin_Data[playerid][pLogin_PinAttempts] = 0;

    return 1;
}

/*
* ==============================================================================
* Internal events
* ==============================================================================
*/

public Login_OnPasswordChecked(playerid, bool:success)
{
    new
        dialogTitle[TITLE_DIALOG_LEN],
        dialogContent[NORMAL_DIALOG_LEN];
    
    if (!IsNull(player_Data[playerid][p_Password]) && success) {
        if(!strcmp(player_Data[playerid][p_LastLoginIP], player_Data[playerid][p_CurrentIP], false)) {
            CallLocalFunction("OnPlayerLogged", "d", playerid);
        }
        else {
            Login_PinShow(playerid);
        }
    }
    else {
        playerLogin_Data[playerid][pLogin_PasswordAttempts]++;

        if(playerLogin_Data[playerid][pLogin_PasswordAttempts] >= MAX_LOGIN_PASSWORD_ATTEMPTS) {
            playerLogin_Data[playerid][pLogin_PasswordAttempts] = 0;

            // Kick
            Kick(playerid);
        }
        else {
            format(dialogTitle, sizeof(dialogTitle), "Authentification - Échec %d/%d", playerLogin_Data[playerid][pLogin_PasswordAttempts], MAX_LOGIN_PASSWORD_ATTEMPTS);
            format(dialogContent, sizeof(dialogContent), "Mot de passe incorrect !\n\nVeuillez saisir votre mot de passe :");

            Dialog_Open(
                playerid,
                "Login_Dialog",
                DIALOG_STYLE_PASSWORD,
                dialogTitle,
                dialogContent,
                "Valider",
                "Quitter"
            );
        }
    }

	return 1;
}

public Login_OnPinChecked(playerid, bool:success)
{
    new dialogTitle[TITLE_DIALOG_LEN];

    if (!IsNull(player_Data[playerid][p_Pin]) && success) {
        CallLocalFunction("OnPlayerLogged", "d", playerid);
    }
    else {
        playerLogin_Data[playerid][pLogin_PinAttempts]++;

        if(playerLogin_Data[playerid][pLogin_PinAttempts] >= MAX_LOGIN_PIN_ATTEMPTS) {
            playerLogin_Data[playerid][pLogin_PinAttempts] = 0;

            // Kick
            Kick(playerid);
        }
        else {
            format(dialogTitle, sizeof(dialogTitle), "Authentification - Code PIN - Echec %d/%d", playerLogin_Data[playerid][pLogin_PinAttempts], MAX_LOGIN_PIN_ATTEMPTS);

            Dialog_Open(
                playerid,
                "LoginPin_Dialog",
                DIALOG_STYLE_PASSWORD,
                dialogTitle,
                "Code PIN incorrect.\n\nVeuillez saisir votre code pin :",
                "Valider",
                "Quitter"
            );
        }
    }

    return 1;
}

/*
* ==============================================================================
* Functions
* ==============================================================================
*/

Login_PasswordShow(playerid)
{
    Dialog_Open(
        playerid,
        "LoginPassword_Dialog",
        DIALOG_STYLE_PASSWORD,
        "Authentification",
        "Veuillez saisir votre mot de passe :",
        "Valider",
        "Quitter"
    );

    return 1;
}

Login_PinShow(playerid) {
    Dialog_Open(
        playerid,
        "LoginPin_Dialog",
        DIALOG_STYLE_PASSWORD,
        "Authentification - Code PIN",
        "Attention, vous vous connectez avec une adresse IP différente de votre dernière session.\n\nVeuillez saisir votre code pin :",
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

/*
* ==============================================================================
* Dialogs
* ==============================================================================
*/

Dialog:LoginPassword_Dialog(playerid, response, item, input[]) 
{
    if(!response) {
        Kick(playerid);

        return 0;
    }

    bcrypt_verify(playerid, "Login_OnPasswordChecked", input, player_Data[playerid][p_Password]);

    return 1;
}

Dialog:LoginPin_Dialog(playerid, response, item, input[]) 
{
    if(!response) {
        Kick(playerid);

        return 0;
    }

    if(strlen(input) != 4) {
        Dialog_Open(
            playerid,
            "LoginPin_Dialog",
            DIALOG_STYLE_PASSWORD,
            "Authentification - Code PIN",
            "Attention, vous vous connectez avec une adresse IP différente de votre dernière session.\n\nVeuillez saisir votre code pin :",
            "Valider",
            "Quitter"
        );

        return 0;    
    }

    if(!isnumeric(input)) {
        Dialog_Open(
            playerid,
            "LoginPin_Dialog",
            DIALOG_STYLE_PASSWORD,
            "Authentification - Code PIN",
            "Attention, vous vous connectez avec une adresse IP différente de votre dernière session.\n\nVeuillez saisir votre code pin :",
            "Valider",
            "Quitter"
        );

        return 0;
    }

    bcrypt_verify(playerid, "Login_OnPinChecked", input, player_Data[playerid][p_Pin]);

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