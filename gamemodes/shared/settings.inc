#if defined _inc_settings
	#undef _inc_settings
#endif

#if defined _settings_included
	#endinput
#endif
#define _settings_included

/*
* ==============================================================================
* Dependencies
* ==============================================================================
*/

#include <ini>

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
* Internal events
* ==============================================================================
*/

/*
* ==============================================================================
* Functions
* ==============================================================================
*/

stock GetSettingInt(const file[], const key[], defaultValue, &output, openfile = true) 
{
	if(openfile) {
		ini_open(file);
	}

	if(!ini_isKey(key)) {
		ini_setInt(key, defaultValue);
		output = defaultValue;
		ini_commit();
	} 
    else {
		ini_getInt(key, output);
	}

	if(openfile) {
		ini_close();
	}
}

stock GetSettingFloat(file[], key[], Float:defaultValue, &Float:output, openfile = true) 
{
	if(openfile) {
		ini_open(file);
	}

	if(!ini_isKey(key)) {
		ini_setFloat(key, defaultValue);
		output = defaultValue;
		ini_commit();
	} 
    else {
		ini_getFloat(key, output);
	}

	if(openfile) {
		ini_close();
	}
}

stock GetSettingString(file[], key[], defaultValue[], output[], maxsize = sizeof(output), openfile = true) 
{
	if(openfile) {
		ini_open(file);
	}

	if(!ini_isKey(key)) {
		ini_setString(key, defaultValue);
		output[0] = EOS;
		strcat(output, defaultValue, maxsize);
		ini_commit();
	} 
    else {
		ini_getString(key, output, maxsize);
	}

	if(openfile) {
		ini_close();
	}
}

stock GetSettingIntArray(file[], key[], defaultValue, output[], &outputTotal, len = sizeof(output)) 
{
	ini_open(file);

	new tmpkey[MAX_KEY_LENGTH];

	while(outputTotal < len) {
		format(tmpkey, sizeof(tmpkey), "%s/%d", key, outputTotal);

		if(!ini_isKey(tmpkey)) {
			if(outputTotal == 0) {
				ini_setInt(tmpkey, defaultValue);
				ini_commit();
				output[0] = defaultValue;
			}

			break;
		}

		GetSettingInt(file, tmpkey, defaultValue, output[outputTotal], logged, false);

		outputTotal++;
	}

	ini_close();
}

stock GetSettingFloatArray(file[], key[], Float:defaultValue, Float:output[], &outputTotal, len = sizeof(output)) 
{
	ini_open(file);

	new tmpkey[MAX_KEY_LENGTH];

	while(outputTotal < len) {
		format(tmpkey, sizeof(tmpkey), "%s/%d", key, outputTotal);

		if(!ini_isKey(tmpkey)) {
			if(outputTotal == 0) {
				ini_setFloat(tmpkey, defaultValue);
				ini_commit();
				output[0] = defaultValue;
			}

			break;
		}

		GetSettingFloat(file, tmpkey, defaultValue, output[outputTotal], logged, false);

		outputTotal++;
	}

	ini_close();
}

stock GetSettingStringArray(file[], key[], defaultValue[], output[][], &outputTotal, lenDefault = sizeof(defaultValue), len = sizeof(output), lenInner = sizeof(output[])) {
	ini_open(file);

	new tmpkey[MAX_KEY_LENGTH];

	while(outputTotal < len) {
		format(tmpkey, sizeof(tmpkey), "%s/%d", key, outputTotal);

		if(!ini_isKey(tmpkey)) {
			if(outputTotal == 0) {
				ini_setString(tmpkey, defaultValue);
				ini_commit();
				output[0][0] = EOS;
				strcat(output[0], defaultValue, lenDefault);
			}

			break;
		}

		GetSettingString(file, tmpkey, defaultValue, output[outputTotal], lenInner, logged, false);

		outputTotal++;
	}

	ini_close();
}

stock UpdateSettingInt(const file[], const key[], value) 
{
	ini_open(file);
	ini_setInt(key, value);
	ini_commit();
	ini_close();
}

stock UpdateSettingFloat(const file[], const key[], Float:value) 
{
	ini_open(file);
	ini_setFloat(key, value);
	ini_commit();
	ini_close();
}

stock UpdateSettingString(const file[], const key[], const value[]) 
{
	ini_open(file);
	ini_setString(key, value);
	ini_commit();
	ini_close();
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