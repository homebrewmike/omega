// Omega is free software, distributed under the MIT license

#pragma once

// aux.c
void showroom (int i);
bool p_moveable (int x, int y);
void searchat (int x, int y);
int damage_item (pob o);
void calc_melee (void);
void p_damage (int dmg, EDamageType dtype, const char* fromstring);
void p_death (const char* fromstring);
void setspot (int* x, int* y);
int getdir (void);
const char* mstatus_string (struct monster *m);
void describe_player (void);
void gain_experience (int amount);
bool goberserk (void);
void foodcheck (void);
void roomcheck (void);
void surrender (struct monster *m);
void threaten (struct monster *m);
int statmod (int stat);
void p_hit (struct monster *m, int dmg, int dtype);
void p_win (void);
void minute_status_check (void);
void moon_check (void);
void torch_check (void);
void tenminute_status_check (void);
unsigned item_value (const object* item);
inline unsigned item_value (const object& o) { return (item_value (&o)); }
unsigned true_item_value (const object* item);
inline unsigned true_item_value (const object& o) { return (true_item_value (&o)); }
void p_drown (void);
void weapon_use (int dmgmod, pob weapon, struct monster *m);
const char* actionlocstr (char dir);
void toggle_item_use (int on);
void change_environment (EEnvironment new_environment);
void tenminute_check (void);
void hourly_check (void);
char getlocation (void);
bool magic_resist (unsigned hostile_magic);
void terrain_check (bool takestime);
void countrysearch (void);
const char* countryid (int terrain);
int parsecitysite (void);
bool hostilemonstersnear (void);
int stonecheck (int alignment);
void alert_guards (void);
unsigned maneuvers (void);
// char.c
void initplayer (void);
// command.c
void p_process (void);
void p_country_process (void);
void pickup (void);
void drop (void);
void setoptions (void);
void bash_item (void);
void save (void);
void quit (void);
void rename_player (void);
void dismount_steed (void);
// effect.c
void accuracy (int blessing);
void acid_cloud (void);
void acquire (int blessing);
void aggravate (void);
void alert (int blessing);
void amnesia (void);
void annihilate (int blessing);
void apport (int blessing);
void augment (int blessing);
void bless (int blessing);
void breathe (int blessing);
void clairvoyance (int vision);
void cleanse (int blessing);
void cure (int blessing);
void deflection (int blessing);
void disease (int amount);
void disintegrate (int x, int y);
void dispel (int blessing);
void displace (int blessing);
void disrupt (int x, int y, int amount);
void drain (int blessing);
void drain_life (int amount);
void enchant (int delta);
void fball (int fx, int fy, int tx, int ty, int dmg);
void fbolt (int fx, int fy, int tx, int ty, int hit, int dmg);
void flux (int blessing);
void haste (int blessing);
void heal (int amount);
void hellfire (int x, int y, int blessing);
void hero (int blessing);
void hide (int x, int y);
void i_chaos (pob o);
void i_law (pob o);
void icebolt (int fx, int fy, int tx, int ty, int hit, int dmg);
void identify (int blessing);
void illuminate (int blessing);
void inflict_fear (int x, int y);
void invisible (int blessing);
void knowledge (int blessing);
void lball (int fx, int fy, int tx, int ty, int dmg);
void lbolt (int fx, int fy, int tx, int ty, int hit, int dmg);
void learnspell (int blessing);
void level_drain (int levels, const char* source);
void level_return (void);
void levitate (int blessing);
void manastorm (int x, int y, int dmg);
void mondet (int blessing);
void nbolt (int fx, int fy, int tx, int ty, int hit, int dmg);
void objdet (int blessing);
void p_poison (int toxicity);
void p_teleport (int type);
void polymorph (int blessing);
int random_item (void);
void recover_stat (int blessing);
void regenerate (int blessing);
void sanctify (int blessing);
void sanctuary (void);
void shadowform (void);
void sleep_monster (int blessing);
void sleep_player (int amount);
void snowball (int fx, int fy, int tx, int ty, int dmg);
void strategic_teleport (int blessing);
void summon (int blessing, int id);
void truesight (int blessing);
void warp (int blessing);
void wish (int blessing);
// env.c
int difficulty (void);
void l_adept (void);
void l_alchemist (void);
void l_arena (void);
void l_armorer (void);
void l_bank (void);
void l_brothel (void);
void l_cartographer (void);
void l_casino (void);
void l_castle (void);
void l_charity (void);
void l_club (void);
void l_college (void);
void l_commandant (void);
void l_condo (void);
void l_countryside (void);
void l_crap (void);
void l_diner (void);
void l_dpw (void);
void l_gym (void);
void l_healer (void);
void l_house (void);
void l_hovel (void);
void l_library (void);
void l_mansion (void);
void l_merc_guild (void);
void l_oracle (void);
void l_order (void);
void l_pawn_shop (void);
void l_safe (void);
void l_sorcerors (void);
void l_statue_wake (void);
void l_tavern (void);
void l_thieves_guild (void);
void l_trifid (void);
void l_vault (void);
void load_abyss (void);
void load_arena (void);
void load_circle (void);
void load_city (void);
void load_country (void);
void load_court (void);
void load_dlair (int empty);
void load_house (EEnvironment kind);
void load_misle (int empty);
void load_speak (int empty);
void load_temple (int deity);
void load_village (uint8_t villagenum);
monster& make_site_monster (int i, int j, int mid, int wandering = WANDERING, int dlevel = 0);
void make_hiscore_npc (monster& npc, int npcid);
void pacify_guards (void);
void populate_level (void);
void resurrect_guards (void);
void send_to_jail (void);
void sign_print (int x, int y, int signp);
void statue_random (int x, int y);
void stock_level (void);
void wandercheck (void);
// gen.c
void change_level (int fromlevel, int tolevel, int rewrite_level);
void clear_level (struct level *dungeon_level);
void generate_level (int tolevel);
void load_encounter (char countryLocChar);
const char* roomname (int ri);
// inv.c
int cursed (const object& o);
void do_inventory_control (void);
void drop_at (int x, int y, const object& o);
void p_drop_at (int x, int y, const object& o, unsigned n);
int find_and_remove_item (int id, int chargeval);
object* find_item (int id);
void gain_item (const object& o);
long get_money (long limit);
int getitem (chtype itype);
void givemonster (monster& m, const object& o);
char index_to_key (unsigned i);
const char* itemid (pob obj);
inline const char* itemid (object& obj) { return (itemid (&obj)); }
void lose_all_items (void);
void pickup_at (int x, int y);
object split_item (const object& item, unsigned n);
// item.c
void item_use (struct object *o);
inline void item_use (object& o) { item_use (&o); }
object create_object (int itemlevel);
object make_corpse (const monster& m);
object make_cash (int level);
object make_food (int id = RANDOM);
object make_ring (int id = RANDOM);
object make_thing (int id = RANDOM);
object make_scroll (int id = RANDOM);
object make_potion (int id = RANDOM);
object make_weapon (int id = RANDOM);
object make_shield (int id = RANDOM);
object make_armor (int id = RANDOM);
object make_cloak (int id = RANDOM);
object make_boots (int id = RANDOM);
object make_stick (int id = RANDOM);
object make_artifact (int id = RANDOM);
bool twohandedp (int id);
void weapon_acidwhip (int dmgmod, pob o, struct monster *m);
void weapon_arrow (int dmgmod, pob o, struct monster *m);
void weapon_bare_hands (int dmgmod, struct monster *m);
void weapon_bolt (int dmgmod, pob o, struct monster *m);
void weapon_defend (int dmgmod, pob o, struct monster *m);
void weapon_demonblade (int dmgmod, pob o, struct monster *m);
void weapon_desecrate (int dmgmod, pob o, struct monster *m);
void weapon_firestar (int dmgmod, pob o, struct monster *m);
void weapon_lightsabre (int dmgmod, pob o, struct monster *m);
void weapon_mace_disrupt (int dmgmod, pob o, struct monster *m);
void weapon_normal_hit (int dmgmod, pob o, struct monster *m);
void weapon_scythe (int dmgmod, pob o, struct monster *m);
void weapon_tangle (int dmgmod, pob o, struct monster *m);
void weapon_victrix (int dmgmod, pob o, struct monster *m);
void weapon_vorpal (int dmgmod, pob o, struct monster *m);
// mon.c
void m_abyss (struct monster *m);
void m_altar (struct monster *m);
void m_damage (struct monster *m, int dmg, int dtype);
void m_death (struct monster *m);
void m_dropstuff (struct monster *m);
void m_fire (struct monster *m);
void m_lava (struct monster *m);
void m_no_op (struct monster *m);
void m_pulse (struct monster *m);
void m_teleport (struct monster *m);
void m_trap_abyss (struct monster *m);
void m_trap_acid (struct monster *m);
void m_trap_blade (struct monster *m);
void m_trap_dart (struct monster *m);
void m_trap_disintegrate (struct monster *m);
void m_trap_door (struct monster *m);
void m_trap_fire (struct monster *m);
void m_trap_manadrain (struct monster *m);
void m_trap_pit (struct monster *m);
void m_trap_sleepgas (struct monster *m);
void m_trap_snare (struct monster *m);
void m_trap_teleport (struct monster *m);
void m_vanish (struct monster *m);
void m_water (struct monster *m);
const char* mantype (void);
void monster_talk (struct monster *m);
char random_loc (void);
void transcribe_monster_actions (struct monster *m);
const char* m_melee_str (unsigned level);
// move.c
void l_abyss (void);
void l_chaos (void);
void l_portcullis_trap (void);
void l_raise_portcullis (void);
void m_movefunction (struct monster *m, int movef);
void p_movefunction (int movef);
// omega.c
void inititem (int reset);
void initrand (int environment, int level);
void time_clock (int reset);
// priest.c
void l_altar (void);
// save.c
bool restore_game (void);
bool save_game (void);
// scr.c
void bufferprint (void);
void clear_screen (void);
void clearmsg (void);
void comwinprint (void);
void dataprint (void);
void deathprint (void);
void displayfile (const char* filedata);
void display_death (const char* source);
void display_options (unsigned selection);
void display_pack (void);
void display_possessions (unsigned selection = -1);
void display_quit (void);
void display_win (void);
void display_messages (void);
void dodrawspot (int x, int y);
void draw_explosion (chtype pyx, int x, int y);
void drawmonsters (int display);
void drawomega (void);
void drawscreen (void);
void drawspot (int x, int y);
void drawvision (int x, int y);
void endgraf (void);
void erase_level (void);
void erase_monster (struct monster *m);
int getnumber (int range);
chtype getspot (int x, int y, int showmonster);
void initgraf (void);
void levelrefresh (void);
wchar_t lgetc (void);
void locprint (const char* s);
wchar_t mcigetc (void);
void menuaddch (int c);
void menuclear (void);
wchar_t menugetc (void);
void menulongprint (long n);
void menunumprint (int n);
void menuprint (const char* s);
wchar_t mgetc (void);
void morewait (void);
void mprint (const char* s);
void mprintf (const char* fmt, ...) PRINTFARGS (1,2);
const char* msgscanstring (void);
void omega_title (void);
void omshowcursor (int x, int y);
long parsenum (void);
void phaseprint (void);
void plotchar (chtype pyx, int x, int y);
void plotmon (struct monster *m);
void plotspot (int x, int y, int showmonster);
void putspot (int x, int y, chtype c);
void screencheck (int y);
void setlastxy (int new_x, int new_y);
void show_screen (void);
void showflags (void);
void showmenu (void);
void spreadroomdark (int x, int y, int roomno);
void spreadroomlight (int x, int y, int roomno);
int stillonblock (void);
void timeprint (void);
void xredraw (void);
wchar_t ynq (void);
void msglist_down (void);
void msglist_up (void);
// spell.c
void cast_spell (int spell);
int getspell (void);
const char* spellid (int id);
// trap.c
void l_trap_abyss (void);
void l_trap_acid (void);
void l_trap_blade (void);
void l_trap_dart (void);
void l_trap_disintegrate (void);
void l_trap_door (void);
void l_trap_fire (void);
void l_trap_manadrain (void);
void l_trap_pit (void);
void l_trap_siren (void);
void l_trap_sleepgas (void);
void l_trap_snare (void);
void l_trap_teleport (void);
// util.c
long calc_points (void);
void calc_weight (void);
int confirmation (void);
int day (void);
int distance (int x1, int y1, int x2, int y2);
void do_los (int pyx, int* x1, int* y1, int x2, int y2);
void do_object_los (int pyx, int* x1, int* y1, int x2, int y2);
void findspace (int* x, int* y);
const char* getarticle (const char* str);
void hint (void);
int hitp (int hit, int ac);
int hour (void);
int inbounds (int x, int y);
void learnclericalspells (int deity, int level);
int los_p (int x1, int y1, int x2, int y2);
int m_unblocked (struct monster *m, int x, int y);
const char* month (void);
const char* nameprint (void);
int nighttime (void);
int offscreen (int y);
const char* ordinal (int number);
unsigned urandom_range (unsigned k);
static inline int random_range (unsigned k) { return (urandom_range (k)); }
int screenmod (int y);
int showhour (void);
int showminute (void);
const char* slotstr (int num);
bool strmem (int c, const char* s);
int mkpath (const char* path);
int unblocked (int x, int y);
int view_los_p (int x1, int y1, int x2, int y2);
int view_unblocked (int x, int y);
const char* wordnum (int num);
