#if defined _inc_helper_global
	#undef _inc_helper_global
#endif

#if defined _helper_global_included
	#endinput
#endif
#define _helper_global_included

IsValidEmailAddress(const email[]) {
    new at_pos = strfind(email, "@", true);
    
    if(at_pos >= 1) {
        new offset = (at_pos + 1), dot_pos = strfind(email, ".", true, offset);
        
        if(dot_pos > offset) {
            return 1;
        }
    }

    return 0;
}