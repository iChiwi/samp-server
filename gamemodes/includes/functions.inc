// Global Variables
new gPlayerCitySelection[MAX_PLAYERS];
new gPlayerHasCitySelected[MAX_PLAYERS];
new gPlayerLastCitySelectionTick[MAX_PLAYERS];

new Text:txtClassSelHelper;
new Text:txtLosSantos;
new Text:txtSanFierro;
new Text:txtLasVenturas;

public OnGameModeInit()
{
    SetGameModeText("iChiwi's server");
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
    ShowNameTags(1);
    SetNameTagDrawDistance(40.0);
    EnableStuntBonusForAll(0);
    DisableInteriorEnterExits();
    SetWeather(2);
    SetWorldTime(11);

    ClassSel_InitTextDraws();

    AddPlayerClass(280, 1759.0189, -1898.1260, 13.5622, 266.4503, 0, 0, 0, 0, 0, 0);
    AddPlayerClass(281, 1759.0189, -1898.1260, 13.5622, 266.4503, 0, 0, 0, 0, 0, 0);
    AddPlayerClass(282, 1759.0189, -1898.1260, 13.5622, 266.4503, 0, 0, 0, 0, 0, 0);
    AddPlayerClass(283, 1759.0189, -1898.1260, 13.5622, 266.4503, 0, 0, 0, 0, 0, 0);
    AddPlayerClass(284, 1759.0189, -1898.1260, 13.5622, 266.4503, 0, 0, 0, 0, 0, 0);
    AddPlayerClass(285, 1759.0189, -1898.1260, 13.5622, 266.4503, 0, 0, 0, 0, 0, 0);
    return 1;
}

public OnPlayerConnect(playerid)
{
    new
        string[64],
        playerName[MAX_PLAYER_NAME];

    GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
    format(string, sizeof string, "%s has connected to the server.", playerName);
    SendClientMessageToAll(COLOR_CONNECT, string);

    gPlayerCitySelection[playerid] = -1;
    gPlayerHasCitySelected[playerid] = 0;
    gPlayerLastCitySelectionTick[playerid] = GetTickCount();
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    new
        szString[64],
        playerName[MAX_PLAYER_NAME],
        szDisconnectReason[5][] =
        {
            "Timeout/Crash",
            "Quit",
            "Kick/Ban",
            "Custom",
            "Mode End"
        };

    GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);

    format(szString, sizeof szString, "%s left the server (%s).", playerName, szDisconnectReason[reason]);
    SendClientMessageToAll(COLOR_DISCONNECT, szString);
    return 1;
}

public OnPlayerText(playerid, text[])
{
    new chatArray[128], playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
    format(chatArray, sizeof(chatArray), "{%06x}%s {FFFFFF}(%i): %s", GetPlayerColor(playerid) & 0xFFFFFF, playerName, playerid, text);
    SendClientMessageToAll(COLOR_WHITE, chatArray);
    return false;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    SetPlayerPosFindZ(playerid, fX, fY, fZ);
    return 1;
}

public OnPlayerSpawn(playerid)
{
    if(IsPlayerNPC(playerid)) return 1;
    
    new randSpawn = 0;
    
    SetPlayerInterior(playerid, 0);
    TogglePlayerClock(playerid, 0);
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, 50000);

    if(CITY_LOS_SANTOS == gPlayerCitySelection[playerid])
    {
        randSpawn = random(sizeof(gRandomSpawns_LosSantos));
        SetPlayerPos(playerid,
            gRandomSpawns_LosSantos[randSpawn][0],
            gRandomSpawns_LosSantos[randSpawn][1],
            gRandomSpawns_LosSantos[randSpawn][2]);
        SetPlayerFacingAngle(playerid, gRandomSpawns_LosSantos[randSpawn][3]);
    }
    else if(CITY_SAN_FIERRO == gPlayerCitySelection[playerid])
    {
        randSpawn = random(sizeof(gRandomSpawns_SanFierro));
        SetPlayerPos(playerid,
            gRandomSpawns_SanFierro[randSpawn][0],
            gRandomSpawns_SanFierro[randSpawn][1],
            gRandomSpawns_SanFierro[randSpawn][2]);
        SetPlayerFacingAngle(playerid, gRandomSpawns_SanFierro[randSpawn][3]);
    }
    else if(CITY_LAS_VENTURAS == gPlayerCitySelection[playerid])
    {
        randSpawn = random(sizeof(gRandomSpawns_LasVenturas));
        SetPlayerPos(playerid,
            gRandomSpawns_LasVenturas[randSpawn][0],
            gRandomSpawns_LasVenturas[randSpawn][1],
            gRandomSpawns_LasVenturas[randSpawn][2]);
        SetPlayerFacingAngle(playerid, gRandomSpawns_LasVenturas[randSpawn][3]);
    }

    SetPlayerColor(playerid, COLOR_NORMAL_PLAYER);
    
    SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 999);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 999);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 999);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 999);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 999);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 999);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 999);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 999);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 999);

    GivePlayerWeapon(playerid, 24, 12000);
    SetPlayerArmour(playerid, 100);
    return 1;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
    if (!success)
    {
        SendClientMessage(playerid, COLOR_SERVER, "Unknown command.");
    }
    return 1;
}

public OnPlayerRequestDownload(playerid)
{
    SendClientMessage(playerid, COLOR_SERVER, "Verifying files integrity.");
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    new
        weaponName[32],
        string[128],
        playerName[MAX_PLAYER_NAME],
        killerName[MAX_PLAYER_NAME] = "World",
        PlayerDeaths[MAX_PLAYERS],
        PlayerKills[MAX_PLAYERS];

    GetPlayerName(playerid, playerName, sizeof(playerName));

    if(killerid != INVALID_PLAYER_ID)
    {
        GetWeaponName(reason, weaponName, sizeof(weaponName));
        GetPlayerName(killerid, killerName, sizeof(killerName));
        
        format(string, sizeof(string), "You were killed by %s.", killerName);
        SendClientMessage(playerid, 0xFF0000FF, string);
        
        format(string, sizeof(string), "You killed %s.", playerName);
        SendClientMessage(killerid, 0x00FF00FF, string);

        PlayerKills[killerid]++;
    }
    else
    {
        SendClientMessage(playerid, 0xFF0000FF, "You died.");
    }

    format(string, sizeof(string), "%s (%i) has killed %s (%i) using a %s.", killerName, killerid, playerName, playerid, weaponName);
    SendClientMessageToAll(0xFFFFFFAA, string);

    SendDeathMessage(killerid, playerid, reason);

    PlayerDeaths[playerid]++;

    gPlayerHasCitySelected[playerid] = 0;
    return 1;
}

ClassSel_SetupCharSelection(playerid)
{
    if(gPlayerCitySelection[playerid] == CITY_LOS_SANTOS)
    {
        SetPlayerInterior(playerid, 11);
        SetPlayerPos(playerid, 508.7362, -87.4335, 998.9609);
        SetPlayerFacingAngle(playerid, 0.0);
        SetPlayerCameraPos(playerid, 508.7362, -83.4335, 998.9609);
        SetPlayerCameraLookAt(playerid, 508.7362, -87.4335, 998.9609);
    }
    else if(gPlayerCitySelection[playerid] == CITY_SAN_FIERRO)
    {
        SetPlayerInterior(playerid, 3);
        SetPlayerPos(playerid, -2673.8381, 1399.7424, 918.3516);
        SetPlayerFacingAngle(playerid, 181.0);
        SetPlayerCameraPos(playerid, -2673.2776, 1394.3859, 918.3516);
        SetPlayerCameraLookAt(playerid, -2673.8381, 1399.7424, 918.3516);
    }
    else if(gPlayerCitySelection[playerid] == CITY_LAS_VENTURAS)
    {
        SetPlayerInterior(playerid, 3);
        SetPlayerPos(playerid, 349.0453, 193.2271, 1014.1797);
        SetPlayerFacingAngle(playerid, 286.25);
        SetPlayerCameraPos(playerid, 352.9164, 194.5702, 1014.1875);
        SetPlayerCameraLookAt(playerid, 349.0453, 193.2271, 1014.1797);
    }
}

ClassSel_InitCityNameText(Text:txtInit)
{
    TextDrawUseBox(txtInit, 0);
    TextDrawLetterSize(txtInit, 1.25, 3.0);
    TextDrawFont(txtInit, 0);
    TextDrawSetShadow(txtInit, 0);
    TextDrawSetOutline(txtInit, 1);
    TextDrawColor(txtInit, 0xEEEEEEFF);
    TextDrawBackgroundColor(txtClassSelHelper, 0x000000FF);
}

ClassSel_InitTextDraws()
{
    new
        LosSantosText[] = "Los Santos",
        SanFierroText[] = "San Fierro",
        LasVenturasText[] = "Las Venturas",
        SwitchText[] = " Press ~b~~k~~GO_LEFT~ ~w~or ~b~~k~~GO_RIGHT~ ~w~to switch cities.~n~ Press ~r~~k~~PED_FIREWEAPON~ ~w~to select.";
    txtLosSantos = TextDrawCreate(10.0, 380.0, LosSantosText);
    ClassSel_InitCityNameText(txtLosSantos);
    txtSanFierro = TextDrawCreate(10.0, 380.0, SanFierroText);
    ClassSel_InitCityNameText(txtSanFierro);
    txtLasVenturas = TextDrawCreate(10.0, 380.0, LasVenturasText);
    ClassSel_InitCityNameText(txtLasVenturas);

    txtClassSelHelper = TextDrawCreate(10.0, 415.0, SwitchText);
    TextDrawUseBox(txtClassSelHelper, 1);
    TextDrawBoxColor(txtClassSelHelper, 0x222222BB);
    TextDrawLetterSize(txtClassSelHelper, 0.3, 1.0);
    TextDrawTextSize(txtClassSelHelper, 400.0, 40.0);
    TextDrawFont(txtClassSelHelper, 2);
    TextDrawSetShadow(txtClassSelHelper, 0);
    TextDrawSetOutline(txtClassSelHelper, 1);
    TextDrawBackgroundColor(txtClassSelHelper, 0x000000FF);
    TextDrawColor(txtClassSelHelper, 0xFFFFFFFF);
}

ClassSel_SetupSelectedCity(playerid)
{
    if(gPlayerCitySelection[playerid] == -1)
    {
        gPlayerCitySelection[playerid] = CITY_LOS_SANTOS;
    }
    
    if(gPlayerCitySelection[playerid] == CITY_LOS_SANTOS)
    {
        SetPlayerInterior(playerid, 0);
        SetPlayerCameraPos(playerid, 1630.6136, -2286.0298, 110.0);
        SetPlayerCameraLookAt(playerid, 1887.6034, -1682.1442, 47.6167);
        
        TextDrawShowForPlayer(playerid, txtLosSantos);
        TextDrawHideForPlayer(playerid, txtSanFierro);
        TextDrawHideForPlayer(playerid, txtLasVenturas);
    }
    else if(gPlayerCitySelection[playerid] == CITY_SAN_FIERRO)
    {
        SetPlayerInterior(playerid, 0);
        SetPlayerCameraPos(playerid, -1300.8754, 68.0546, 129.4823);
        SetPlayerCameraLookAt(playerid, -1817.9412, 769.3878, 132.6589);
        
        TextDrawHideForPlayer(playerid, txtLosSantos);
        TextDrawShowForPlayer(playerid, txtSanFierro);
        TextDrawHideForPlayer(playerid, txtLasVenturas);
    }
    else if(gPlayerCitySelection[playerid] == CITY_LAS_VENTURAS)
    {
        SetPlayerInterior(playerid, 0);
        SetPlayerCameraPos(playerid, 1310.6155, 1675.9182, 110.7390);
        SetPlayerCameraLookAt(playerid, 2285.2944, 1919.3756, 68.2275);
        
        TextDrawHideForPlayer(playerid, txtLosSantos);
        TextDrawHideForPlayer(playerid, txtSanFierro);
        TextDrawShowForPlayer(playerid, txtLasVenturas);
    }   
}

ClassSel_SwitchToNextCity(playerid)
{
    gPlayerCitySelection[playerid]++;
    if(gPlayerCitySelection[playerid] > CITY_LAS_VENTURAS)
    {
        gPlayerCitySelection[playerid] = CITY_LOS_SANTOS;
    }
    PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
    gPlayerLastCitySelectionTick[playerid] = GetTickCount();
    ClassSel_SetupSelectedCity(playerid);
}

ClassSel_SwitchToPreviousCity(playerid)
{
    gPlayerCitySelection[playerid]--;
    if(gPlayerCitySelection[playerid] < CITY_LOS_SANTOS)
    {
        gPlayerCitySelection[playerid] = CITY_LAS_VENTURAS;
    }
    PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);
    gPlayerLastCitySelectionTick[playerid] = GetTickCount();
    ClassSel_SetupSelectedCity(playerid);
}

ClassSel_HandleCitySelection(playerid)
{
    new Keys, ud, lr;
    GetPlayerKeys(playerid, Keys, ud, lr);
    
    if(gPlayerCitySelection[playerid] == -1)
    {
        ClassSel_SwitchToNextCity(playerid);
        return;
    }

    if((GetTickCount() - gPlayerLastCitySelectionTick[playerid]) < 500) return;
    
    if(Keys & KEY_FIRE)
    {
        gPlayerHasCitySelected[playerid] = 1;
        TextDrawHideForPlayer(playerid, txtClassSelHelper);
        TextDrawHideForPlayer(playerid, txtLosSantos);
        TextDrawHideForPlayer(playerid, txtSanFierro);
        TextDrawHideForPlayer(playerid, txtLasVenturas);
        TogglePlayerSpectating(playerid, 0);
        return;
    }
    
    if(lr > 0)
    {
        ClassSel_SwitchToNextCity(playerid);
    }
    else if(lr < 0)
    {
        ClassSel_SwitchToPreviousCity(playerid);
    }
}

public OnPlayerRequestClass(playerid, classid)
{
    if(IsPlayerNPC(playerid)) return 1;

    if(gPlayerHasCitySelected[playerid])
    {
        ClassSel_SetupCharSelection(playerid);
        return 1;
    }
    else
    {
        if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
        {
            TogglePlayerSpectating(playerid, 1);
            TextDrawShowForPlayer(playerid, txtClassSelHelper);
            gPlayerCitySelection[playerid] = -1;
        }
    }
    return 0;
}

public OnPlayerUpdate(playerid)
{
    if(!IsPlayerConnected(playerid)) return 0;
    if(IsPlayerNPC(playerid)) return 1;

    if(!gPlayerHasCitySelected[playerid] && GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
    {
        ClassSel_HandleCitySelection(playerid);
        return 1;
    }
    return 1;
}
