#ifndef CHARCLASS_H
#define CHARCLASS_H
//#include "abilityscore.h"
//#include "species.h"

/*
0 == NONE
1 == Barbarian
2 == Bard
3 == Cleric
4 == Druid
5 == Fighter
6 == Monk
7 == Paladin
8 == Ranger
9 == Rogue
10 == Sorcerer
11 == Warlock
12 == Wizard

*/


class Charclass
{
private:
public:
	
	Charclass();
	~Charclass() {};
	void level_hd_hp(int conabm, int hitdie, int level, int& hp);
	int hd_lvl_calc(int hitdie);
	void exp_lvlup(int exp, int level, int& prof_bonus);
	void prof_incr(int level, int& prof_bonus);
	int ab_upscore(int level, int clss);
	void barbarian(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void bard(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void cleric(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void druid(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void fighter(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void monk(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void paladin(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void ranger(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void rogue(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void sorcerer(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void warlock(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);
	void wizard(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss);

	void acolyte();


};

#endif CHARCLASS_H
