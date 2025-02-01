CMD:sethealth(playerid, params[])
{
    new string[128], targetid, value;
    if(sscanf(params, "ii", targetid, value)) {
        format(string, sizeof(string), "{%06x}Command Syntax: {FFFFFF}/sethealth [targetid] [value]", COLOR_SERVER & 0xFFFFFF);
        SendClientMessage(playerid, COLOR_SERVER, string);
        return 1;
    }
    if (!IsPlayerConnected(targetid)) {
        SendClientMessage(playerid, COLOR_SERVER, "Invalid target ID. The player is not connected.");
        return 1;
    }
    if (value < 0 || value > 100) {
        format(string, sizeof(string), "{%06x}Syntax Error: Value must be between 0 and 100.", COLOR_SERVER & 0xFFFFFF);
        SendClientMessage(playerid, COLOR_SERVER, string);
        return 1;
    }
    SetPlayerHealth(targetid, value);
    return 1;
}

CMD:setarmour(playerid, params[])
{
    new string[128], targetid, value;
    if(sscanf(params, "ii", targetid, value)) {
        format(string, sizeof(string), "{%06x}Command Syntax: {FFFFFF}/setarmour [targetid] [value]", COLOR_SERVER & 0xFFFFFF);
        SendClientMessage(playerid, COLOR_SERVER, string);
        return 1;
    }
    if (!IsPlayerConnected(targetid)) {
        SendClientMessage(playerid, COLOR_SERVER, "Invalid target ID. The player is not connected.");
        return 1;
    }
    if (value < 0 || value > 100) {
        format(string, sizeof(string), "{%06x}Syntax Error: Value must be between 0 and 100.", COLOR_SERVER & 0xFFFFFF);
        SendClientMessage(playerid, COLOR_SERVER, string);
        return 1;
    }
    SetPlayerArmour(targetid, value);
    return 1;
}

CMD:setskin(playerid, params[])
{
    new targetid, skinid, string[128];
    if(sscanf(params, "ii", targetid, skinid)) {
        format(string, sizeof(string), "{%06x}Command Syntax: {FFFFFF}/setskin [targetid] [skinid]", COLOR_SERVER & 0xFFFFFF);
        SendClientMessage(playerid, COLOR_SERVER, string);
        return 1;
    }
    if (!IsPlayerConnected(targetid)) {
        SendClientMessage(playerid, COLOR_SERVER, "Invalid target ID. The player is not connected.");
        return 1;
    }
    SetPlayerSkin(targetid, skinid);
    return 1;
}

CMD:giveweapon(playerid, params[])
{
    new string[128], targetid, weaponid, weaponammo;
    if(sscanf(params, "iii", targetid, weaponid, weaponammo)) {
        format(string, sizeof(string), "{%06x}Command Syntax: {FFFFFF}/giveweapon [targetid] [weaponid] [ammo]", COLOR_SERVER & 0xFFFFFF);
        SendClientMessage(playerid, COLOR_SERVER, string);
        return 1;
    }
    if (!IsPlayerConnected(targetid)) {
        SendClientMessage(playerid, COLOR_SERVER, "Invalid target ID. The player is not connected.");
        return 1;
    }
    if (weaponid <= 1 || weaponid >= 46) {
        format(string, sizeof(string), "{%06x}Syntax Error: Invalid weapon ID %d.", COLOR_SERVER & 0xFFFFFF, weaponid);
        SendClientMessage(playerid, COLOR_SERVER, string);
        return 1;
    }
    GivePlayerWeapon(targetid, weaponid, weaponammo);
    return 1;
}
