#pragma once

// aux.c
void tunnelcheck(void);
void showroom(int i);
int player_on_sanctuary(void);
int p_moveable(int x, int y);
int p_country_moveable(int x, int y);
void searchat(int x, int y);
void calc_melee(void);
int damage_item(pob o);
void p_damage(int dmg, int dtype, const char* fromstring);
void p_death(const char* fromstring);
void setspot(int* x, int* y);
int getdir(void);
const char* mstatus_string(struct monster *m);
void describe_player(void);
void gain_experience(int amount);
int goberserk(void);
const char* trapid(int trapno);
void foodcheck(void);
void roomcheck(void);
void surrender(struct monster *m);
void threaten(struct monster *m);
const char* levelname(int level);
int statmod(int stat);
void p_hit(struct monster *m, int dmg, int dtype);
void p_win(void);
int p_immune(int dtype);
void minute_status_check(void);
void moon_check(void);
void torch_check(void);
void tenminute_status_check(void);
long item_value(const object* item);
inline long item_value (const object& o) { return (item_value(&o)); }
long true_item_value(const object* item);
inline long true_item_value (const object& o) { return (true_item_value(&o)); }
void p_drown(void);
void weapon_use(int dmgmod, pob weapon, struct monster *m);
const char* actionlocstr(int dir);
void toggle_item_use(int on);
void enter_site(int site);
void change_environment(int new_environment);
void tenminute_check(void);
void hourly_check(void);
char getlocation(void);
int magic_resist(int hostile_magic);
void terrain_check(int takestime);
void countrysearch(void);
const char* countryid(int terrain);
int parsecitysite(void);
int hostilemonstersnear(void);
int stonecheck(int alignment);
void alert_guards(void);
int maneuvers(void);
// char.c
void initplayer(void);
long calcmana(void);
int fixnpc(int status);
// command.c
void p_process(void);
void p_country_process(void);
void pickup(void);
void drop(void);
void setoptions(void);
void bash_item(void);
void save(int compress, int force);
void quit(void);
void rename_player(void);
void dismount_steed(void);
// effect.c
void accuracy(int blessing);
void acid_cloud(void);
void acquire(int blessing);
void aggravate(void);
void alert(int blessing);
void amnesia(void);
void annihilate(int blessing);
void apport(int blessing);
void augment(int blessing);
void bless(int blessing);
void breathe(int blessing);
void clairvoyance(int vision);
void cleanse(int blessing);
void cure(int blessing);
void deflection(int blessing);
void disease(int amount);
void disintegrate(int x, int y);
void dispel(int blessing);
void displace(int blessing);
void disrupt(int x, int y, int amount);
void drain(int blessing);
void drain_life(int amount);
void enchant(int delta);
void fball(int fx, int fy, int tx, int ty, int dmg);
void fbolt(int fx, int fy, int tx, int ty, int hit, int dmg);
void flux(int blessing);
void haste(int blessing);
void heal(int amount);
void hellfire(int x, int y, int blessing);
void hero(int blessing);
void hide(int x, int y);
void i_chaos(pob o);
void i_law(pob o);
void icebolt(int fx, int fy, int tx, int ty, int hit, int dmg);
void identify(int blessing);
void illuminate(int blessing);
void inflict_fear(int x, int y);
void invisible(int blessing);
void knowledge(int blessing);
void lball(int fx, int fy, int tx, int ty, int dmg);
void lbolt(int fx, int fy, int tx, int ty, int hit, int dmg);
void learnspell(int blessing);
void level_drain(int levels, const char* source);
void level_return(void);
void levitate(int blessing);
void manastorm(int x, int y, int dmg);
void mondet(int blessing);
void nbolt(int fx, int fy, int tx, int ty, int hit, int dmg);
void objdet(int blessing);
void p_poison(int toxicity);
void p_teleport(int type);
void polymorph(int blessing);
int random_item (void);
void recover_stat(int blessing);
void regenerate(int blessing);
void sanctify(int blessing);
void sanctuary(void);
void shadowform(void);
void sleep_monster(int blessing);
void sleep_player(int amount);
void snowball(int fx, int fy, int tx, int ty, int dmg);
void strategic_teleport(int blessing);
void summon(int blessing, int id);
void truesight(int blessing);
void warp(int blessing);
void wish(int blessing);
// env.c
int difficulty(void);
void l_adept(void);
void l_alchemist(void);
void l_arena(void);
void l_armorer(void);
void l_bank(void);
void l_brothel(void);
void l_cartographer(void);
void l_casino(void);
void l_castle(void);
void l_charity(void);
void l_club(void);
void l_college(void);
void l_commandant(void);
void l_condo(void);
void l_countryside(void);
void l_crap(void);
void l_diner(void);
void l_dpw(void);
void l_gym(void);
void l_healer(void);
void l_house(void);
void l_hovel(void);
void l_library(void);
void l_mansion(void);
void l_merc_guild(void);
void l_oracle(void);
void l_order(void);
void l_pawn_shop(void);
void l_safe(void);
void l_sorcerors(void);
void l_statue_wake(void);
void l_tavern(void);
void l_thieves_guild(void);
void l_trifid(void);
void l_vault(void);
void load_abyss(void);
void load_arena(void);
void load_circle(int populate);
void load_city(int populate);
void load_country(void);
void load_court(int populate);
void load_dlair(int empty, int populate);
void load_house(int kind, int populate);
void load_misle(int empty, int populate);
void load_speak(int empty, int populate);
void load_temple(int deity, int populate);
void load_village(int villagenum, int populate);
void make_country_monsters(int terrain);
monster& make_site_monster (int i, int j, int mid, int wandering = WANDERING, int dlevel = 0);
void make_hiscore_npc (monster& npc, int npcid);
void pacify_guards(void);
void populate_level(int monstertype);
void resurrect_guards(void);
void send_to_jail(void);
void sign_print(int x, int y, int signp);
void statue_random(int x, int y);
void stock_level(void);
void wandercheck(void);
// file.c
FILE *checkfopen(const char* filestring, const char* optionstring);
int filecheck(void);
void abyss_file(void);
void adeptfile(void);
void cityguidefile(void);
void combat_help(void);
void displayfile(const char* filestr);
void inv_help(void);
void showmotd(void);
void theologyfile(void);
void user_intro(void);
void wishfile(void);
// gen.c
void cavern_level(void);
void change_level(int fromlevel, int tolevel, int rewrite_level);
void clear_level(struct level *dungeon_level);
void free_dungeon(void);
void install_specials(void);
void install_traps(void);
void make_country_screen(int terrain);
void make_stairs(int fromlevel);
void maze_level(void);
void room_level(void);
const char* roomname(int ri);
void sewer_level(void);
// inv.c
int cursed (const object& o);
void do_inventory_control(void);
void drop_at (int x, int y, const object& o);
void p_drop_at (int x, int y, const object& o, unsigned n);
int find_and_remove_item(int id, int chargeval);
object* find_item (int id);
void gain_item (const object& o);
long get_money(long limit);
int getitem(chtype itype);
void givemonster (monster& m, const object& o);
char index_to_key (unsigned i);
const char* itemid(pob obj);
inline const char* itemid(object& obj) { return (itemid(&obj)); }
void lose_all_items(void);
void pickup_at(int x, int y);
object split_item (const object& item, unsigned n);
// item.c
void item_use (struct object *o);
inline void item_use (object& o) { item_use(&o); }
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
bool twohandedp(int id);
void weapon_acidwhip(int dmgmod, pob o, struct monster *m);
void weapon_arrow(int dmgmod, pob o, struct monster *m);
void weapon_bare_hands(int dmgmod, struct monster *m);
void weapon_bolt(int dmgmod, pob o, struct monster *m);
void weapon_defend(int dmgmod, pob o, struct monster *m);
void weapon_demonblade(int dmgmod, pob o, struct monster *m);
void weapon_desecrate(int dmgmod, pob o, struct monster *m);
void weapon_firestar(int dmgmod, pob o, struct monster *m);
void weapon_lightsabre(int dmgmod, pob o, struct monster *m);
void weapon_mace_disrupt(int dmgmod, pob o, struct monster *m);
void weapon_normal_hit(int dmgmod, pob o, struct monster *m);
void weapon_scythe(int dmgmod, pob o, struct monster *m);
void weapon_tangle(int dmgmod, pob o, struct monster *m);
void weapon_victrix(int dmgmod, pob o, struct monster *m);
void weapon_vorpal(int dmgmod, pob o, struct monster *m);
// mon.c
void m_abyss(struct monster *m);
void m_altar(struct monster *m);
void m_damage(struct monster *m, int dmg, int dtype);
void m_death(struct monster *m);
void m_dropstuff(struct monster *m);
void m_fire(struct monster *m);
void m_lava(struct monster *m);
void m_no_op(struct monster *m);
void m_pulse(struct monster *m);
void m_teleport(struct monster *m);
void m_trap_abyss(struct monster *m);
void m_trap_acid(struct monster *m);
void m_trap_blade(struct monster *m);
void m_trap_dart(struct monster *m);
void m_trap_disintegrate(struct monster *m);
void m_trap_door(struct monster *m);
void m_trap_fire(struct monster *m);
void m_trap_manadrain(struct monster *m);
void m_trap_pit(struct monster *m);
void m_trap_sleepgas(struct monster *m);
void m_trap_snare(struct monster *m);
void m_trap_teleport(struct monster *m);
void m_vanish(struct monster *m);
void m_water(struct monster *m);
const char* mantype(void);
void monster_talk(struct monster *m);
char random_loc(void);
void transcribe_monster_actions(struct monster *m);
const char* m_melee_str (unsigned level);
// move.c
void l_abyss(void);
void l_chaos(void);
void l_portcullis_trap(void);
void l_raise_portcullis(void);
void m_movefunction(struct monster *m, int movef);
void p_movefunction(int movef);
// omega.c
void inititem(int reset);
void initrand(int environment, int level);
void time_clock(int reset);
// priest.c
void l_altar(void);
// save.c
int restore_game(const char* savestr);
int save_game(const char* savestr);
void signalsave(int sig);
// scr.c
void bufferprint(void);
void checkclear(void);
void clear_if_necessary(void);
void clear_screen(void);
void clearmsg(void);
void clearmsg1(void);
void clearmsg3(void);
void commanderror(void);
void comwinprint(void);
void dataprint(void);
void deathprint(void);
void display_bigwin(void);
void display_death(const char* source);
void display_options (unsigned selection);
void display_pack(void);
void display_possessions (unsigned selection = -1);
void display_quit(void);
void display_win(void);
void dodrawspot(int x, int y);
void draw_explosion(chtype pyx, int x, int y);
void drawmonsters(int display);
void drawomega(void);
void drawscreen(void);
void drawspot(int x, int y);
void drawvision(int x, int y);
void endgraf(void);
void erase_level(void);
void erase_monster(struct monster *m);
int getnumber(int range);
chtype getspot(int x, int y, int showmonster);
void initgraf(void);
void levelrefresh(void);
char lgetc(void);
void locprint(const char* s);
int mcigetc(void);
void menuaddch(int c);
void menuclear(void);
char menugetc(void);
void menulongprint(long n);
void menunumprint(int n);
void menuprint(const char* s);
char mgetc(void);
void mlongprint(long n);
void mnumprint(int n);
void morewait(void);
void mprint(const char* s);
void mprintf (const char* fmt, ...) PRINTFARGS(1,2);
const char* msgscanstring(void);
void nprint1(const char* s);
void nprint2(const char* s);
void nprint3(const char* s);
void omega_title(void);
void omshowcursor(int x, int y);
long parsenum(void);
void phaseprint(void);
void plotchar(chtype pyx, int x, int y);
void plotmon(struct monster *m);
void plotspot(int x, int y, int showmonster);
void print1(const char* s);
void print2(const char* s);
void print3(const char* s);
void putspot(int x, int y, chtype c);
void screencheck(int y);
void setlastxy(int new_x, int new_y);
void show_screen(void);
void showflags(void);
void showmenu(void);
void spreadroomdark(int x, int y, int roomno);
void spreadroomlight(int x, int y, int roomno);
int stillonblock(void);
void timeprint(void);
void xredraw(void);
int ynq(void);
int ynq1(void);
int ynq2(void);
// spell.c
void cast_spell(int spell);
int getspell(void);
const char* spellid(int id);
// trap.c
void l_trap_abyss(void);
void l_trap_acid(void);
void l_trap_blade(void);
void l_trap_dart(void);
void l_trap_disintegrate(void);
void l_trap_door(void);
void l_trap_fire(void);
void l_trap_manadrain(void);
void l_trap_pit(void);
void l_trap_siren(void);
void l_trap_sleepgas(void);
void l_trap_snare(void);
void l_trap_teleport(void);
// util.c
long calc_points(void);
void calc_weight(void);
int confirmation(void);
int day(void);
int distance(int x1, int y1, int x2, int y2);
void do_los(int pyx, int* x1, int* y1, int x2, int y2);
void do_object_los(int pyx, int* x1, int* y1, int x2, int y2);
void findspace(int* x, int* y, int baux);
void free_level(plv level);
const char* getarticle(const char* str);
void hint(void);
int hitp(int hit, int ac);
int hour(void);
int inbounds(int x, int y);
void learnclericalspells(int deity, int level);
int los_p(int x1, int y1, int x2, int y2);
int m_unblocked(struct monster *m, int x, int y);
const char* month(void);
const char* nameprint(void);
int nighttime(void);
int offscreen(int y);
int ok_to_free(plv level);
const char* ordinal(int number);
int random_range(int k);
int screenmod(int y);
int showhour(void);
int showminute(void);
const char* slotstr(int num);
int strmem(int c, const char* s);
int unblocked(int x, int y);
int view_los_p(int x1, int y1, int x2, int y2);
int view_unblocked(int x, int y);
const char* wordnum(int num);
