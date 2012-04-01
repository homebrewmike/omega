#include "glob.h"
#include <unistd.h>
#include <stdlib.h>

//----------------------------------------------------------------------

static int ok_outdated(int ver);
static void restore_country(FILE *fd, int ver);
static void restore_hiscore_npc(pmt npc, int npcid);
static pob restore_item(FILE *fd, int ver);
static pol restore_itemlist(FILE *fd, int ver);
static void restore_level(FILE *fd, int ver);
static void restore_monsters(FILE *fd, plv level, int ver);
static void restore_player(FILE *fd, int ver);
static int save_country(FILE *fd);
static int save_item(FILE *fd, pob o);
static int save_itemlist(FILE *fd, pol ol);
static int save_level(FILE *fd, plv level);
static int save_monsters(FILE *fd, pml ml);
static int save_player(FILE *fd);

//----------------------------------------------------------------------

// Various functions for doing game saves and restores
// The game remembers various player information, the city level,
// the country level, and the last or current dungeon level

//*************** SAVE FUNCTIONS

// Checks to see if save file already exists.
// Checks to see if save file can be opened for write.
// The player, the city level, and the current dungeon level are saved.

int save_game (const char* savestr)
{
    FILE *fd;
    int i, writeok = TRUE;
    plv current, levelToSave;

    if (access (savestr, R_OK) == 0) {
	if (access (savestr, W_OK) == 0) {
	    mprint (" Overwrite old file?");
	    writeok = (ynq() == 'y');
	} else {
	    mprint (" File already exists.");
	    writeok = FALSE;
	}
    }
    if (writeok) {
	fd = fopen (savestr, "wb");
	if (fd == NULL) {
	    writeok = FALSE;
	    mprint (" Error opening file.");
	}
    }
    if (!writeok) {
	morewait();
	print2 ("Save aborted.");
    } else {

	print1 ("Saving Game....");

	// write the version number
	i = OMEGA_VERSION;
	fwrite ((const char*) &i, sizeof (int), 1, fd);
	// write game id to save file

	writeok &= save_player (fd);
	writeok &= save_country (fd);
	writeok &= save_level (fd, City);

	if (Current_Environment == E_CITY || Current_Environment == E_COUNTRYSIDE)
	    levelToSave = Dungeon;
	else if (Current_Environment == Current_Dungeon)
	    levelToSave = Dungeon;
	else
	    levelToSave = Level;
	for (i = 0, current = levelToSave; current; current = current->next, i++);
	if (!fwrite ((const char*) &i, sizeof (int), 1, fd))
	    writeok = FALSE;
	for (current = levelToSave; current; current = current->next)
	    if (current != Level)
		writeok &= save_level (fd, current);
	if (levelToSave)
	    writeok &= save_level (fd, Level);	// put current level last
	fclose (fd);
	if (writeok)
	    print1 ("Game Saved.");
	else
	    print1 ("Something didn't work... save aborted.");
	morewait();
	clearmsg();
    }
    return (writeok);
}

// saves game on SIGHUP
// no longer tries to compress, which hangs
void signalsave (int sig UNUSED)
{
    save_game ("omega.sav");
    print1 ("Signal - Saving file 'omega.sav'.");
    morewait();
    endgraf();
    exit (0);
}

// also saves some globals like Level->depth...

static int save_player (FILE* fd)
{
    int i;
    int ok = 1;

    // Save random global state information

    Player.click = (Tick + 1) % 60;
    ok &= (fwrite ((const char*) &Player, sizeof (Player), 1, fd) > 0);
    ok &= (fprintf (fd, "%s\n", Password) >= 0);
    ok &= (fprintf (fd, "%s\n", Player.name) >= 0);
    ok &= (fwrite ((const char*) CitySiteList, sizeof (CitySiteList), 1, fd) > 0);
    ok &= (fwrite ((const char*) &GameStatus, sizeof (long), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Current_Environment, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Last_Environment, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Current_Dungeon, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Villagenum, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Verbosity, sizeof (char), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Time, sizeof (long), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Tick, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Searchnum, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Behavior, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Phase, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Date, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Spellsleft, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &SymbolUseHour, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &ViewHour, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &HelmHour, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Constriction, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Blessing, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &LastDay, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &RitualHour, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Lawstone, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Chaostone, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Mindstone, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Arena_Opponent, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Imprisonment, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Gymcredit, sizeof (long), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Balance, sizeof (long), 1, fd) > 0);
    ok &= (fwrite ((const char*) &StarGemUse, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &HiMagicUse, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &HiMagic, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &FixedPoints, sizeof (long), 1, fd) > 0);
    ok &= (fwrite ((const char*) &LastCountryLocX, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &LastCountryLocY, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &LastTownLocX, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &LastTownLocY, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Pawndate, sizeof (int), 1, fd) > 0);

    ok &= (fwrite ((const char*) Spells, sizeof (Spells), 1, fd) > 0);

    ok &= (fwrite ((const char*) &Command_Duration, sizeof (Command_Duration), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Precipitation, sizeof (Precipitation), 1, fd) > 0);
    ok &= (fwrite ((const char*) &Lunarity, sizeof (Lunarity), 1, fd) > 0);
    ok &= (fwrite ((const char*) &ZapHour, sizeof (ZapHour), 1, fd) > 0);
    ok &= (fwrite ((const char*) &RitualRoom, sizeof (RitualRoom), 1, fd) > 0);

    // stuff which used to be statics
    ok &= (fwrite ((const char*) &twiddle, sizeof (twiddle), 1, fd) > 0);
    ok &= (fwrite ((const char*) &saved, sizeof (saved), 1, fd) > 0);
    ok &= (fwrite ((const char*) &onewithchaos, sizeof (onewithchaos), 1, fd) > 0);
    ok &= (fwrite ((const char*) &club_hinthour, sizeof (club_hinthour), 1, fd) > 0);
    ok &= (fwrite ((const char*) &winnings, sizeof (winnings), 1, fd) > 0);
    ok &= (fwrite ((const char*) &tavern_hinthour, sizeof (tavern_hinthour), 1, fd) > 0);
    ok &= (fwrite ((const char*) deepest, sizeof (int), E_MAX + 1, fd) > 0);
    ok &= (fwrite ((const char*) level_seed, sizeof (int), E_MAX + 1, fd) > 0);

    // Save player possessions

    if (Player.possessions[O_READY_HAND] == Player.possessions[O_WEAPON_HAND])
	Player.possessions[O_READY_HAND] = NULL;
    for (i = 0; i < MAXITEMS; i++)
	ok &= save_item (fd, Player.possessions[i]);
    for (i = 0; i < MAXPACK; i++)
	ok &= save_item (fd, Player.pack[i]);
    for (i = 0; i < PAWNITEMS; i++)
	ok &= save_item (fd, Pawnitems[i]);

    // Save items in condo vault
    ok &= save_itemlist (fd, Condoitems);

    // Save player item knowledge
    ok &= (fwrite ((const char*) &SpellKnown, sizeof(SpellKnown), 1, fd) > 0);
    ok &= (fwrite ((const char*) ObjectAttrs, sizeof(ObjectAttrs), 1, fd) > 0);
    return ok;
}

// Save whatever is pointed to by level
static int save_level (FILE* fd, plv level)
{
    unsigned i, j, run;
    unsigned long int mask;
    int ok = 1;

    ok &= (fwrite ((const char*) &level->depth, sizeof (char), 1, fd) > 0);
    ok &= (fwrite ((const char*) &level->numrooms, sizeof (char), 1, fd) > 0);
    ok &= (fwrite ((const char*) &level->tunnelled, sizeof (char), 1, fd) > 0);
    ok &= (fwrite ((const char*) &level->environment, sizeof (int), 1, fd) > 0);
    for (j = 0; j < MAXLENGTH; j++)
	for (i = 0; i < MAXWIDTH; i++)
	    if (level->site[i][j].lstatus & CHANGED) {	// this loc has been changed
		for (run = i + 1; run < MAXWIDTH &&	// find how many in a row
		     level->site[run][j].lstatus & CHANGED; run++);
		ok &= (fwrite ((const char*) &i, sizeof (int), 1, fd) > 0);
		ok &= (fwrite ((const char*) &j, sizeof (int), 1, fd) > 0);
		ok &= (fwrite ((const char*) &run, sizeof (int), 1, fd) > 0);
		for (; i < run; i++)
		    ok &= (fwrite ((const char*) &level->site[i][j], sizeof (struct location), 1, fd) > 0);
	    }
    ok &= (fwrite ((const char*) &i, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &j, sizeof (int), 1, fd) > 0);	// signify end
    // since we don't mark the 'seen' bits as CHANGED, need to save a bitmask
    run = 8 * sizeof (long int);
    mask = 0;
    for (j = 0; j < MAXLENGTH; j++)
	for (i = 0; i < MAXWIDTH; i++) {
	    if (run == 0) {
		run = 8 * sizeof (long int);
		ok &= (fwrite ((const char*) &mask, sizeof (long int), 1, fd) > 0);
		mask = 0;
	    }
	    mask >>= 1;
	    if (level->site[i][j].lstatus & SEEN)
		mask |= (1UL << (sizeof (long int) * 8 - 1));
	    run--;
	}
    if (run < 8 * sizeof (long int))
	ok &= (fwrite ((const char*) &mask, sizeof (long int), 1, fd) > 0);
    ok &= save_monsters (fd, level->mlist);
    for (i = 0; i < MAXWIDTH; i++)
	for (j = 0; j < MAXLENGTH; j++)
	    if (level->site[i][j].things) {
		ok &= (fwrite ((const char*) &i, sizeof (int), 1, fd) > 0);
		ok &= (fwrite ((const char*) &j, sizeof (int), 1, fd) > 0);
		ok &= save_itemlist (fd, level->site[i][j].things);
	    }
    ok &= (fwrite ((const char*) &i, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &j, sizeof (int), 1, fd) > 0);	// signify end
    return ok;
}

static int save_monsters (FILE* fd, pml ml)
{
    pml tml;
    int nummonsters = 0;
    int ok = 1;
    unsigned char type;

    // First count monsters
    for (tml = ml; tml != NULL; tml = tml->next)
	if (tml->m->hp > 0)
	    nummonsters++;

    ok &= (fwrite ((const char*) &nummonsters, sizeof (int), 1, fd) > 0);

    // Now save monsters
    for (tml = ml; tml != NULL; tml = tml->next) {
	if (tml->m->hp > 0) {
	    ok &= (fwrite ((const char*) tml->m, sizeof (montype), 1, fd) > 0);
	    if (tml->m->id != HISCORE_NPC) {
		type = 0x0;
		if (strcmp (tml->m->monstring, Monsters[tml->m->id].monstring))
		    type |= 0x1;
		if (strcmp (tml->m->corpsestr, Monsters[tml->m->id].corpsestr))
		    type |= 0x2;
		ok &= (fwrite ((const char*) &type, sizeof (unsigned char), 1, fd) > 0);
		if (type & 1)
		    ok &= (fprintf (fd, "%s\n", tml->m->monstring) >= 0);
		if (type & 2)
		    ok &= (fprintf (fd, "%s\n", tml->m->corpsestr) >= 0);
		// WDT: line moved from here...
	    }
	    // else it'll be reloaded from the hiscore file on restore
	    // WDT: to here.  This bug fix is Sheldon Simm's suggestion
	    // to fix the well-known 'Star Gem' bug; it should allow the
	    // possessions of hiscore NPCs to be restored from the savefile.
	    // See also the complementary change in restore_monsters.
	    ok &= save_itemlist (fd, tml->m->possessions);
	}
    }
    return ok;
}

// Save o unless it's null, then save a special flag byte instead
// Use other values of flag byte to indicate what strings are saved
static int save_item (FILE* fd, pob o)
{
    int ok = 1;
    unsigned char type;

    if (o == NULL) {
	type = 0xff;
	ok &= (fwrite ((const char*) &type, sizeof (type), 1, fd) > 0);
    } else {
	type = 0;
	if (strcmp (o->objstr, Objects[o->id].objstr))
	    type |= 1;
	if (strcmp (o->truename, Objects[o->id].truename))
	    type |= 2;
	if (strcmp (o->cursestr, Objects[o->id].cursestr))
	    type |= 4;
	ok &= (fwrite ((const char*) &type, sizeof (type), 1, fd) > 0);
	ok &= (fwrite ((const char*) o, sizeof (objtype), 1, fd) > 0);
	if (type & 1)
	    ok &= (fprintf (fd, "%s\n", o->objstr) >= 0);
	if (type & 2)
	    ok &= (fprintf (fd, "%s\n", o->truename) >= 0);
	if (type & 4)
	    ok &= (fprintf (fd, "%s\n", o->cursestr) >= 0);
    }
    return ok;
}

static int save_itemlist (FILE* fd, pol ol)
{
    int numitems = 0;
    pol tol;
    int ok = 1;

    for (tol = ol; tol != NULL; tol = tol->next)
	numitems++;
    ok &= (fwrite ((const char*) &numitems, sizeof (int), 1, fd) > 0);
    for (tol = ol; tol != NULL; tol = tol->next)
	ok &= save_item (fd, tol->thing);
    return ok;
}

static int save_country (FILE* fd)
{
    int i, j;
    int ok = 1;
    int run;
    unsigned long int mask;

    for (i = 0; i < MAXWIDTH; i++)
	for (j = 0; j < MAXLENGTH; j++)
	    if (c_statusp (i, j, CHANGED)) {
		ok &= (fwrite ((const char*) &i, sizeof (int), 1, fd) > 0);
		ok &= (fwrite ((const char*) &j, sizeof (int), 1, fd) > 0);
		ok &= (fwrite ((const char*) &Country[i][j], sizeof (struct terrain), 1, fd) > 0);
	    }
    ok &= (fwrite ((const char*) &i, sizeof (int), 1, fd) > 0);
    ok &= (fwrite ((const char*) &j, sizeof (int), 1, fd) > 0);
    // since we don't mark the 'seen' bits as CHANGED, need to save a bitmask
    run = 8 * sizeof (long int);
    mask = 0;
    for (i = 0; i < MAXWIDTH; i++)
	for (j = 0; j < MAXLENGTH; j++) {
	    if (run == 0) {
		run = 8 * sizeof (long int);
		ok &= (fwrite ((const char*) &mask, sizeof (long int), 1, fd) > 0);
		mask = 0;
	    }
	    mask >>= 1;
	    if (c_statusp (i, j, SEEN))
		mask |= (1UL << (sizeof (long int) * 8 - 1));
	    run--;
	}
    if (run < (int)(8 * sizeof(long int)))
	ok &= (fwrite ((const char*) &mask, sizeof (long int), 1, fd) > 0);
    return ok;
}

// returns TRUE if the given version can be restored by this version
static int ok_outdated (int ver)
{
    switch (ver) {
	case 80:
	    print1 ("Converting version 0.80 savefile to current.");
	    morewait();
	    return TRUE;
	    break;
	case 81:
	    print1 ("Loading version 0.81 savefile.");
	    morewait();
	    return TRUE;
	    break;
	default:
	    return FALSE;
	    break;
    }
}

// read player data, city level, dungeon level,
// check on validity of save file, etc.
// return TRUE if game restored, FALSE otherwise
int restore_game (const char* savestr)
{
    int i, ver;
    if (access (savestr, F_OK | R_OK | W_OK) == -1) {	// access uses real uid
	print1 ("Unable to access save file: ");
	nprint1 (savestr);
	morewait();
	return FALSE;
    }

    FILE* fd = fopen (savestr, "rb");

    if (fd == NULL) {
	print1 ("Error restoring game -- aborted.");
	print2 ("File name was: ");
	nprint2 (savestr);
	morewait();
	return (FALSE);
    } else {
	print1 ("Restoring...");

	fread ((char*) &ver, sizeof (int), 1, fd);

	if (OMEGA_VERSION != ver && !ok_outdated (ver)) {
	    fclose (fd);
	    clearmsg();
	    mprint (" Sorry, I can't restore an outdated save file!");
	    mprint (" savefile is version ");
	    mnumprint (ver / 100);
	    nprint2 (".");
	    mnumprint (ver % 100);
	    morewait();
	    return (FALSE);
	}
	restore_player (fd, ver);
	restore_country (fd, ver);
	restore_level (fd, ver);	// the city level
	fread ((char*) &i, sizeof (int), 1, fd);
	for (; i > 0; i--) {
	    restore_level (fd, ver);
	    if (Level->environment == Current_Dungeon) {
		Level->next = Dungeon;
		Dungeon = Level;
	    }
	    if (Current_Environment == E_CITY)
		Level = City;
	}
	// this disgusting kludge because LENGTH and WIDTH are globals...
	WIDTH = 64;
	switch (Current_Environment) {
	    case E_COURT:
		LENGTH = 24;
		break;
	    case E_ARENA:
	    case E_ABYSS:
	    case E_CIRCLE:
	    case E_MANSION:
	    case E_HOUSE:
	    case E_HOVEL:
	    case E_DLAIR:
	    case E_STARPEAK:
	    case E_MAGIC_ISLE:
	    case E_TEMPLE:
	    case E_VILLAGE:
		LENGTH = 16;
		break;
	    default:
		LENGTH = 64;
		break;
	}
	fclose (fd);
	print3 ("Restoration complete.");
	ScreenOffset = -1000;	// to force a redraw
	setgamestatus (SKIP_MONSTERS);
	return (TRUE);
    }
}

static void restore_player (FILE* fd, int ver)
{
    int i;
    fread ((char*) &Player, sizeof (Player), 1, fd);
    filescanstring (fd, Password);
    filescanstring (fd, Player.name);
    fread ((char*) CitySiteList, sizeof (CitySiteList), 1, fd);
    fread ((char*) &GameStatus, sizeof (long), 1, fd);
    fread ((char*) &Current_Environment, sizeof (int), 1, fd);
    fread ((char*) &Last_Environment, sizeof (int), 1, fd);
    fread ((char*) &Current_Dungeon, sizeof (int), 1, fd);
    fread ((char*) &Villagenum, sizeof (int), 1, fd);
    switch (Current_Dungeon) {
	case E_ASTRAL:
	    MaxDungeonLevels = ASTRALLEVELS;
	    break;
	case E_SEWERS:
	    MaxDungeonLevels = SEWERLEVELS;
	    break;
	case E_CASTLE:
	    MaxDungeonLevels = CASTLELEVELS;
	    break;
	case E_CAVES:
	    MaxDungeonLevels = CAVELEVELS;
	    break;
	case E_VOLCANO:
	    MaxDungeonLevels = VOLCANOLEVELS;
	    break;
    }
    fread ((char*) &Verbosity, sizeof (char), 1, fd);
    fread ((char*) &Time, sizeof (long), 1, fd);
    fread ((char*) &Tick, sizeof (int), 1, fd);
    fread ((char*) &Searchnum, sizeof (int), 1, fd);
    fread ((char*) &Behavior, sizeof (int), 1, fd);
    fread ((char*) &Phase, sizeof (int), 1, fd);
    fread ((char*) &Date, sizeof (int), 1, fd);
    fread ((char*) &Spellsleft, sizeof (int), 1, fd);
    fread ((char*) &SymbolUseHour, sizeof (int), 1, fd);
    fread ((char*) &ViewHour, sizeof (int), 1, fd);
    fread ((char*) &HelmHour, sizeof (int), 1, fd);
    fread ((char*) &Constriction, sizeof (int), 1, fd);
    fread ((char*) &Blessing, sizeof (int), 1, fd);
    fread ((char*) &LastDay, sizeof (int), 1, fd);
    fread ((char*) &RitualHour, sizeof (int), 1, fd);
    fread ((char*) &Lawstone, sizeof (int), 1, fd);
    fread ((char*) &Chaostone, sizeof (int), 1, fd);
    fread ((char*) &Mindstone, sizeof (int), 1, fd);
    fread ((char*) &Arena_Opponent, sizeof (int), 1, fd);
    fread ((char*) &Imprisonment, sizeof (int), 1, fd);
    fread ((char*) &Gymcredit, sizeof (long), 1, fd);
    fread ((char*) &Balance, sizeof (long), 1, fd);
    fread ((char*) &StarGemUse, sizeof (int), 1, fd);
    fread ((char*) &HiMagicUse, sizeof (int), 1, fd);
    fread ((char*) &HiMagic, sizeof (int), 1, fd);
    fread ((char*) &FixedPoints, sizeof (long), 1, fd);
    fread ((char*) &LastCountryLocX, sizeof (int), 1, fd);
    fread ((char*) &LastCountryLocY, sizeof (int), 1, fd);
    fread ((char*) &LastTownLocX, sizeof (int), 1, fd);
    fread ((char*) &LastTownLocY, sizeof (int), 1, fd);
    fread ((char*) &Pawndate, sizeof (int), 1, fd);

    fread ((char*) Spells, sizeof (Spells), 1, fd);

    fread ((char*) &Command_Duration, sizeof (Command_Duration), 1, fd);
    fread ((char*) &Precipitation, sizeof (Precipitation), 1, fd);
    fread ((char*) &Lunarity, sizeof (Lunarity), 1, fd);
    fread ((char*) &ZapHour, sizeof (ZapHour), 1, fd);
    fread ((char*) &RitualRoom, sizeof (RitualRoom), 1, fd);

    // stuff which used to be statics
    fread ((char*) &twiddle, sizeof (twiddle), 1, fd);
    fread ((char*) &saved, sizeof (saved), 1, fd);
    fread ((char*) &onewithchaos, sizeof (onewithchaos), 1, fd);
    fread ((char*) &club_hinthour, sizeof (club_hinthour), 1, fd);
    fread ((char*) &winnings, sizeof (winnings), 1, fd);
    fread ((char*) &tavern_hinthour, sizeof (tavern_hinthour), 1, fd);
    fread ((char*) deepest, sizeof (int), E_MAX + 1, fd);
    fread ((char*) level_seed, sizeof (int), E_MAX + 1, fd);

    for (i = 0; i < MAXITEMS; i++)
	Player.possessions[i] = restore_item (fd, ver);

    if (!Player.possessions[O_READY_HAND] && Player.possessions[O_WEAPON_HAND] && twohandedp (Player.possessions[O_WEAPON_HAND]->id))
	Player.possessions[O_READY_HAND] = Player.possessions[O_WEAPON_HAND];

    for (i = 0; i < MAXPACK; i++)
	Player.pack[i] = restore_item (fd, ver);
    for (i = 0; i < PAWNITEMS; i++)
	Pawnitems[i] = restore_item (fd, ver);
    Condoitems = restore_itemlist (fd, ver);

    fread ((char*) &SpellKnown, sizeof(SpellKnown), 1, fd);
    fwrite ((char*) ObjectAttrs, sizeof(ObjectAttrs), 1, fd);
}

// Restore an item, the first byte tells us if it's NULL, and what strings
// have been saved as different from the typical
static pob restore_item (FILE* fd, int ver UNUSED)
{
    char tempstr[80];
    unsigned char type;
    pob obj = NULL;

    fread ((char*) &type, sizeof (type), 1, fd);
    if (type != 0xff) {
	obj = ((pob) checkmalloc (sizeof (objtype)));
	fread ((char*) obj, sizeof (objtype), 1, fd);
	if (type & 1) {
	    filescanstring (fd, tempstr);
	    obj->objstr = salloc (tempstr);
	} else
	    obj->objstr = Objects[obj->id].objstr;
	if (type & 2) {
	    filescanstring (fd, tempstr);
	    obj->truename = salloc (tempstr);
	} else
	    obj->truename = Objects[obj->id].truename;
	if (type & 4) {
	    filescanstring (fd, tempstr);
	    obj->cursestr = salloc (tempstr);
	} else
	    obj->cursestr = Objects[obj->id].cursestr;
    }
    return obj;
}

static pol restore_itemlist (FILE* fd, int ver)
{
    pol ol = NULL, cur = NULL, o = NULL;
    int i, numitems, firsttime = TRUE;
    fread ((char*) &numitems, sizeof (int), 1, fd);
    for (i = 0; i < numitems; i++) {
	o = ((pol) checkmalloc (sizeof (oltype)));
	o->thing = restore_item (fd, ver);
	o->next = NULL;
	if (firsttime == TRUE) {
	    ol = cur = o;
	    firsttime = FALSE;
	} else {
	    cur->next = o;
	    cur = o;
	}
    }
    return (ol);
}

static void restore_level (FILE* fd, int ver)
{
    int i, j, run;
    unsigned long int mask;
    int temp_env;

    Level = (plv) checkmalloc (sizeof (levtype));
    clear_level (Level);
    fread ((char*) &Level->depth, sizeof (char), 1, fd);
    fread ((char*) &Level->numrooms, sizeof (char), 1, fd);
    fread ((char*) &Level->tunnelled, sizeof (char), 1, fd);
    fread ((char*) &Level->environment, sizeof (int), 1, fd);
    Level->generated = TRUE;
    temp_env = Current_Environment;
    Current_Environment = Level->environment;
    switch (Level->environment) {
	case E_COUNTRYSIDE:
	    load_country();
	    break;
	case E_CITY:
	    load_city (FALSE);
	    break;
	case E_VILLAGE:
	    load_village (Country[LastCountryLocX][LastCountryLocY].aux, FALSE);
	    break;
	case E_CAVES:
	    initrand (Current_Environment, Level->depth);
	    if ((random_range (4) == 0) && (Level->depth < MaxDungeonLevels))
		room_level();
	    else
		cavern_level();
	    break;
	case E_SEWERS:
	    initrand (Current_Environment, Level->depth);
	    if ((random_range (4) == 0) && (Level->depth < MaxDungeonLevels))
		room_level();
	    else
		sewer_level();
	    break;
	case E_CASTLE:
	    initrand (Current_Environment, Level->depth);
	    room_level();
	    break;
	case E_ASTRAL:
	    initrand (Current_Environment, Level->depth);
	    maze_level();
	    break;
	case E_VOLCANO:
	    initrand (Current_Environment, Level->depth);
	    switch (random_range (3)) {
		case 0:
		    cavern_level();
		    break;
		case 1:
		    room_level();
		    break;
		case 2:
		    maze_level();
		    break;
	    }
	    break;
	case E_HOVEL:
	case E_MANSION:
	case E_HOUSE:
	    load_house (Level->environment, FALSE);
	    break;
	case E_DLAIR:
	    load_dlair (gamestatusp (KILLED_DRAGONLORD), FALSE);
	    break;
	case E_STARPEAK:
	    load_speak (gamestatusp (KILLED_LAWBRINGER), FALSE);
	    break;
	case E_MAGIC_ISLE:
	    load_misle (gamestatusp (KILLED_EATER), FALSE);
	    break;
	case E_TEMPLE:
	    load_temple (Country[LastCountryLocX][LastCountryLocY].aux, FALSE);
	    break;
	case E_CIRCLE:
	    load_circle (FALSE);
	    break;
	case E_COURT:
	    load_court (FALSE);
	    break;
	default:
	    print3 ("This dungeon not implemented!");
	    break;
    }
    if (Level->depth > 0) {	// dungeon...
	install_traps();
	install_specials();
	make_stairs (-1);
	make_stairs (-1);
	initrand (E_RESTORE, 0);
    }
    Current_Environment = temp_env;
    fread ((char*) &i, sizeof (int), 1, fd);
    fread ((char*) &j, sizeof (int), 1, fd);
    while (j < MAXLENGTH && i < MAXWIDTH) {
	fread ((char*) &run, sizeof (int), 1, fd);
	for (; i < run; i++) {
	    fread ((char*) &Level->site[i][j], sizeof (struct location), 1, fd);
	    Level->site[i][j].creature = NULL;
	    Level->site[i][j].things = NULL;
	}
	fread ((char*) &i, sizeof (int), 1, fd);
	fread ((char*) &j, sizeof (int), 1, fd);
    }
    run = 0;
    for (j = 0; j < MAXLENGTH; j++)
	for (i = 0; i < MAXWIDTH; i++) {
	    if (run == 0) {
		run = 8 * sizeof (long int);
		fread ((char*) &mask, sizeof (long int), 1, fd);
	    }
	    if (mask & 1)
		lset (i, j, SEEN);
	    mask >>= 1;
	    run--;
	}
    restore_monsters (fd, Level, ver);
    fread ((char*) &i, sizeof (int), 1, fd);
    fread ((char*) &j, sizeof (int), 1, fd);
    while (j < MAXLENGTH && i < MAXWIDTH) {
	Level->site[i][j].things = restore_itemlist (fd, ver);
	fread ((char*) &i, sizeof (int), 1, fd);
	fread ((char*) &j, sizeof (int), 1, fd);
    }
}

static void restore_hiscore_npc (pmt npc, int npcid)
{
    int level = Hilevel, behavior = Hibehavior;
    long status;

    switch (npcid) {
	case 0:
	    strcpy (Str2, Hiscorer);
	    break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	    strcpy (Str2, Priest[npcid]);
	    level = Priestlevel[npcid];
	    behavior = Priestbehavior[npcid];
	    break;
	case 7:
	    strcpy (Str2, Shadowlord);
	    level = Shadowlordlevel;
	    behavior = Shadowlordbehavior;
	    break;
	case 8:
	    strcpy (Str2, Commandant);
	    level = Commandantlevel;
	    behavior = Commandantbehavior;
	    break;
	case 9:
	    strcpy (Str2, Archmage);
	    level = Archmagelevel;
	    behavior = Archmagebehavior;
	    break;
	case 10:
	    strcpy (Str2, Prime);
	    level = Primelevel;
	    behavior = Primebehavior;
	    break;
	case 11:
	    strcpy (Str2, Champion);
	    level = Championlevel;
	    behavior = Championbehavior;
	    break;
	case 12:
	    strcpy (Str2, Duke);
	    level = Dukelevel;
	    behavior = Dukebehavior;
	    break;
	case 13:
	    strcpy (Str2, Chaoslord);
	    level = Chaoslordlevel;
	    behavior = Chaoslordbehavior;
	    break;
	case 14:
	    strcpy (Str2, Lawlord);
	    level = Lawlordlevel;
	    behavior = Lawlordbehavior;
	    break;
	case 15:
	    strcpy (Str2, Justiciar);
	    level = Justiciarlevel;
	    behavior = Justiciarbehavior;
	    break;
    }
    npc->monstring = salloc (Str2);
    strcpy (Str1, "The body of ");
    strcat (Str1, Str2);
    npc->corpsestr = salloc (Str1);
    if (!m_statusp (npc, HOSTILE)) {
	status = npc->status;
	determine_npc_behavior (npc, level, behavior);
	npc->status = status;
    }
}

static void restore_monsters (FILE* fd, plv level, int ver)
{
    pml ml = NULL;
    int i, nummonsters;
    char tempstr[80];
    int temp_x, temp_y;
    unsigned char type;

    level->mlist = NULL;

    fread ((char*) &nummonsters, sizeof (int), 1, fd);

    for (i = 0; i < nummonsters; i++) {
	ml = ((pml) checkmalloc (sizeof (mltype)));
	ml->m = ((pmt) checkmalloc (sizeof (montype)));
	ml->next = NULL;
	fread ((char*) ml->m, sizeof (montype), 1, fd);
	if (ml->m->id == HISCORE_NPC)
	    if (ver == 80) {
		temp_x = ml->m->x;
		temp_y = ml->m->y;
		make_hiscore_npc (ml->m, ml->m->aux2);
		ml->m->x = temp_x;
		ml->m->y = temp_y;
	    } else
		restore_hiscore_npc (ml->m, ml->m->aux2);
	else {
	    fread ((char*) &type, sizeof (unsigned char), 1, fd);
	    if (type & 1) {
		filescanstring (fd, tempstr);
		ml->m->monstring = salloc (tempstr);
	    } else
		ml->m->monstring = Monsters[ml->m->id].monstring;
	    if (type & 2) {
		filescanstring (fd, tempstr);
		ml->m->corpsestr = salloc (tempstr);
	    } else
		ml->m->corpsestr = Monsters[ml->m->id].corpsestr;
	    // WDT: As suggested by Sheldon Simms, I'm moving this line...
	    if (ver <= 80)
		ml->m->possessions = restore_itemlist (fd, ver);
	    ml->m->meleestr = Monsters[ml->m->id].meleestr;
	}
	// WDT: ...to here, so that all creatures will have their stuff
	// restored to them.  Savefile versioning added by David Given.
	if (ver > 80)
	    ml->m->possessions = restore_itemlist (fd, ver);
	level->site[ml->m->x][ml->m->y].creature = ml->m;
	ml->next = level->mlist;
	level->mlist = ml;
    }
}

static void restore_country (FILE* fd, int ver UNUSED)
{
    int i, j;
    int run;
    unsigned long int mask;

    load_country();
    fread ((char*) &i, sizeof (int), 1, fd);
    fread ((char*) &j, sizeof (int), 1, fd);
    while (i < MAXWIDTH && j < MAXLENGTH) {
	fread ((char*) &Country[i][j], sizeof (struct terrain), 1, fd);
	fread ((char*) &i, sizeof (int), 1, fd);
	fread ((char*) &j, sizeof (int), 1, fd);
    }
    run = 0;
    for (i = 0; i < MAXWIDTH; i++) {
	for (j = 0; j < MAXLENGTH; j++) {
	    if (run == 0) {
		run = 8 * sizeof (long int);
		fread ((char*) &mask, sizeof (long int), 1, fd);
	    }
	    if (mask & 1)
		c_set (i, j, SEEN);
	    mask >>= 1;
	    run--;
	}
    }
}
