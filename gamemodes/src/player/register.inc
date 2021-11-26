/*
    ____    _         __  __ __  __ 
   / ___|  / \       |  \/  |  \/  |
   \___ \ / _ \ _____| |\/| | |\/| |
    ___) / ___ \_____| |  | | |  | |
   |____/_/   \_\    |_|  |_|_|  |_|            

    @File       register.inc
    @Author     Neeko

    COPYRIGHT © 2021 - San Andreas Multimode
*/

#if defined _inc_player_register
	#undef _inc_player_register
#endif

#if defined _player_register_included
	#endinput
#endif
#define _player_register_included

/*
* ==============================================================================
* Dependencies
* ==============================================================================
*/

#include <YSI_Coding\y_hooks>
#include <YSI_Extra\y_inline_mysql>
#include <samp_bcrypt>

/*
* ==============================================================================
* Constants
* ==============================================================================
*/

#define MIN_REGISTER_PASSWORD_LENGTH (6)

/*
* ==============================================================================
* Forwards
* ==============================================================================
*/

forward Register_OnPassswordHash(playerid);
forward Register_OnPinHash(playerid);

/*
* ==============================================================================
* Enums
* ==============================================================================
*/

enum E_PLAYER_REGISTER_DATA {
    pRegister_Dialog,
    pRegister_Email[MAX_EMAIL_LEN],
	pRegister_Password[MAX_PASSWORD_LEN],
	pRegister_Pin[MAX_PIN_LEN]
}

enum 
{
    REGISTER_WELCOME,
    REGISTER_EMAIL,
    REGISTER_PASSWORD,
    REGISTER_PIN,
    REGISTER_SUMMARY
}

/*
* ==============================================================================
* Declarations
* ==============================================================================
*/

static playerRegister_Data[MAX_PLAYERS][E_PLAYER_REGISTER_DATA];

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
    playerRegister_Data[playerid][pRegister_Dialog] = REGISTER_WELCOME;
    playerRegister_Data[playerid][pRegister_Email][0] = EOS;
    playerRegister_Data[playerid][pRegister_Password][0] = EOS;
    playerRegister_Data[playerid][pRegister_Pin][0] = EOS;

    return 1;
}

/*
* ==============================================================================
* Internal events
* ==============================================================================
*/

public Register_OnPassswordHash(playerid)
{
	new hash[MAX_PASSWORD_LEN];
	bcrypt_get_hash(hash);

    strmid(playerRegister_Data[playerid][pRegister_Password], hash, 0, strlen(hash), MAX_PASSWORD_LEN);

    return 1;
}

public Register_OnPinHash(playerid)
{
	new hash[MAX_PIN_LEN];
	bcrypt_get_hash(hash);

    strmid(playerRegister_Data[playerid][pRegister_Pin], hash, 0, strlen(hash), MAX_PIN_LEN);

    return 1;
}

/*
* ==============================================================================
* Functions
* ==============================================================================
*/

Register_Show(playerid)
{
    Dialog_Open(
        playerid,
        "Register_Dialog",
        DIALOG_STYLE_MSGBOX,
        "Inscription",
        "Bienvenue ... Blablablabla",
        "Continuer",
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

Dialog:Register_Dialog(playerid, response, item, input[]) 
{
    new dialogContent[NORMAL_DIALOG_LEN];

    switch(playerRegister_Data[playerid][pRegister_Dialog]) {
		case REGISTER_WELCOME: {
			if(!response) {
				Kick(playerid);

				return 0;
			}

            playerRegister_Data[playerid][pRegister_Dialog] = REGISTER_EMAIL;

			Dialog_Open(
				playerid,
				"Register_Dialog",
				DIALOG_STYLE_INPUT,
                "Inscription - E-mail",
                "Veuillez choisir votre adresse E-mail :",
                "Continuer",
                "Quitter"
			);
        }
        case REGISTER_EMAIL: {
            if(!response) {
				Kick(playerid);

				return 0;
			}

            if(strlen(input) < 1 || strlen(input) > MAX_EMAIL_LEN) {
                format(dialogContent, sizeof(dialogContent), "Votre adresse e-mail doit comporter maximum %d caractères.\r\n\r\nVeuillez saisir votre adresse e-mail :", MAX_EMAIL_LEN);

                Dialog_Open(
                    playerid,
                    "Register_Dialog",
					DIALOG_STYLE_INPUT,
                    "Inscription - E-mail",
                    dialogContent,
                    "Continuer",
                    "Quitter"
                );

                return 0;
            }

            if(!IsValidEmailAddress(input)) {
                Dialog_Open(
                    playerid,
                    "Register_Dialog",
                    DIALOG_STYLE_INPUT,
                    "Inscription - E-mail",
                    "Votre adresse e-mail est incorrect.\r\n\r\nVeuillez saisir une adresse e-mail valide :",
                    "Continuer",
                    "Quitter"
                );

                return 0;            
            }

            inline InlineCallback() 
            {
                if (cache_num_rows()) {
                    Dialog_Open(
                        playerid,
                        "Register_Dialog",
                        DIALOG_STYLE_INPUT,
                        "Inscription - E-mail",
                        "Un compte est déjà enregistré avec cette adresse e-mail.\r\n\r\nVeuillez saisir une adresse email valide :",
                        "Continuer",
                        "Quitter"
                    );

                    return 0;
                }
            }

            MySQL_PQueryInline(Database_GetHandler(), using inline InlineCallback, "SELECT id FROM `"SQL_TABLE_PLAYER"` WHERE `Email` = '%e'", input);

			strmid(playerRegister_Data[playerid][pRegister_Email], input, 0, MAX_EMAIL_LEN, MAX_EMAIL_LEN);

			playerRegister_Data[playerid][pRegister_Dialog] = REGISTER_PASSWORD;

			Dialog_Open(
                playerid,
                "Register_Dialog",
                DIALOG_STYLE_PASSWORD,
                "Inscription - Mot de passe",
                "Veuillez choisir votre mot de passe :",
                "Continuer",
                "Retour"
            );
        }
        case REGISTER_PASSWORD: {
            if(!response) {
                playerRegister_Data[playerid][pRegister_Dialog] = REGISTER_EMAIL;

                Dialog_Open(
                    playerid,
                    "Register_Dialog",
                    DIALOG_STYLE_INPUT,
                    "Inscription - E-mail",
                    "Veuillez choisir votre adresse E-mail :",
                    "Continuer",
                    "Quitter"
                );

				return 0;
			}

            if(strlen(input) < MIN_REGISTER_PASSWORD_LENGTH) {
				playerRegister_Data[playerid][pRegister_Dialog] = REGISTER_PASSWORD;

                format(dialogContent, sizeof(dialogContent), "Votre mot de passe doit contenir minimum %d caractères.\r\n\r\nVeuillez choisir votre mot de passe :", MIN_REGISTER_PASSWORD_LENGTH);

                Dialog_Open(
                    playerid,
                    "Register_Dialog",
                    DIALOG_STYLE_PASSWORD,
                    "Inscription - Mot de passe",
                    dialogContent,
                    "Continuer",
                    "Retour"
                );

                return 0;
            }

            bcrypt_hash(playerid, "Register_OnPassswordHash", input, BCRYPT_COST);

            playerRegister_Data[playerid][pRegister_Dialog] = REGISTER_PIN;

            Dialog_Open(
                playerid,
                "Register_Dialog",
                DIALOG_STYLE_PASSWORD,
                "Inscription - Code PIN",
                "Afin de protéger votre compte, veuillez saisir un code PIN de sécurité à 4 chiffres :",
                "Continuer",
                "Retour"
            );
        }
        case REGISTER_PIN: {
            if(!response) {
                playerRegister_Data[playerid][pRegister_Dialog] = REGISTER_PASSWORD;

                Dialog_Open(
                    playerid,
                    "Register_Dialog",
                    DIALOG_STYLE_PASSWORD,
                    "Inscription - Mot de passe",
                    "Veuillez choisir votre mot de passe :",
                    "Continuer",
                    "Retour"
                );

				return 0;
			}

            if(strlen(input) != 4) {
				playerRegister_Data[playerid][pRegister_Dialog] = REGISTER_PIN;

                Dialog_Open(
                    playerid,
                    "Register_Dialog",
                    DIALOG_STYLE_PASSWORD,
                    "Inscription - Code PIN",
                    "Votre code PIN de sécurité doit comporter 4 chiffres.\r\n\r\nAfin de protéger votre compte, veuillez saisir un code PIN de sécurité à 4 chiffres :",
                    "Continuer",
                    "Retour"
                ); 

                return 0;
            }

            if(!isnumeric(input)) {
				playerRegister_Data[playerid][pRegister_Dialog] = REGISTER_PIN;

                Dialog_Open(
                    playerid,
                    "Register_Dialog",
                    DIALOG_STYLE_PASSWORD,
                    "Inscription - Code PIN",
                    "Votre code PIN de sécurité doit être composé uniquement de 4 chiffres.\r\n\r\nAfin de protéger votre compte, veuillez saisir un code PIN de sécurité à 4 chiffres :",
                    "Continuer",
                    "Retour"
                ); 

                return 0;
            }

            bcrypt_hash(playerid, "Register_OnPinHash", input, BCRYPT_COST);

            format(dialogContent, sizeof(dialogContent), "Récapitulatif de votre compte :\r\n\r\nNom d\'utilisateur : %s\r\nAdresse E-mail : %s\r\n\r\nCliquez sur \'Créer\' pour valider la création de votre compte.", 
				g_PlayerName[playerid], 
				playerRegister_Data[playerid][pRegister_Email]);

            playerRegister_Data[playerid][pRegister_Dialog] = REGISTER_SUMMARY;

            Dialog_Open(
                playerid,
                "Register_Dialog",
                DIALOG_STYLE_MSGBOX,
                "Inscription - Récapitulatif",
                dialogContent,
                "Créer",
                "Éditer"
            ); 
        }
        case REGISTER_SUMMARY: {
            if (!response) {
                Register_Show(playerid);

                return 0;
            }

            Player_Register(playerid, playerRegister_Data[playerid][pRegister_Email], playerRegister_Data[playerid][pRegister_Password], playerRegister_Data[playerid][pRegister_Pin]);
        }
    }

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