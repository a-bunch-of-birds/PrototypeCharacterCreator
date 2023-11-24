#include "abilityscore.h"
#include "charclass.h"

Charclass::Charclass()
{

}

int Charclass::hd_lvl_calc(int hitdie)
{
	const int min = 1;
	const int max = hitdie;
	int result = 0;
	result = rand() % max + min;
	return result;
}

void Charclass::level_hd_hp(int conabm, int hitdie, int level, int& hp)
{
	int hp_passoff = 0;
	//int con_mod = object.ability_summary.conabm;
	int con_mod = conabm;

	for (int i = 2; i <= level; i++)
	{
		hp_passoff = hd_lvl_calc(hitdie);
		hp += hp_passoff;
		hp += con_mod;
	}
}

void Charclass::exp_lvlup(int exp, int level, int& prof_bonus)
{
	if (exp == 0 || level == 1)
	{
		prof_bonus = 2;
	}
	else if (exp == 300 || level == 2)
	{

	}
	else if (exp == 900 || level == 3)
	{

	}
	else if (exp == 2700 || level == 4)
	{
		
	}
	else if (exp == 6500 || level == 5)
	{
		prof_bonus = 3;
	}
	else if (exp == 14000 || level == 6)
	{
		
	}
	else {}
}

void Charclass::prof_incr(int level, int& prof_bonus)
{
	int lvl_stor = level;
	if (lvl_stor < 5)
	{
		prof_bonus = 2;
	}
	else if (lvl_stor > 4 && lvl_stor < 9)
	{
		prof_bonus = 3;
	}
	else if (lvl_stor > 8 && lvl_stor < 13)
	{
		prof_bonus = 4;
	}
	else if (lvl_stor > 12 && lvl_stor < 17)
	{
		prof_bonus = 5;
	}
	else if (lvl_stor > 16)
	{
		prof_bonus = 6;
	}
}

int Charclass::ab_upscore(int level, int clss)
{
	int score_incr = 0; //score increment will collect how many ability points you can choose from to increase.  imgui will take care of denominations
	int lvl_stor = level;
	int clss_type = clss;
	//<><><><><><><>

	if (clss_type == 0)
	{
		std::cout << "WARNING: CLASS NOT CHOSEN" << std::endl;	
	}
	//fighter ability score increment
	else if (clss_type == 5)
	{
		for (int i = 1; i <= lvl_stor; i++)
		{
			if (i == 4 || i == 6 || i == 8 || i == 12 || i == 14 || i == 16 || i == 19)
			{
				score_incr += 2;
			}
			else {}
		}
	}
	//rogue ability score increment
	else if (clss_type == 9)
	{
		for (int i = 1; i <= lvl_stor; i++)
		{
			if (i == 4 || i == 8 || i == 10 || i == 12 || i == 16 || i == 19)
			{
				score_incr += 2;
			}
			else {}
		}
	}
	//if (clss_type == 1 || clss_type == 2 || clss_type == 3 || clss_type == 4 || clss_type == 6 || clss_type == 7 || clss_type == 8 || clss_type == 10 || clss_type == 11 || clss_type == 12)
	else 
	{
		for (int i = 1; i <= lvl_stor; i++)
		{
			if (i == 4 || i == 8 || i == 12 || i == 16 || i == 19)
			{
				score_incr += 2;
			}
			else {}
		}
	}

	return score_incr;

}

void Charclass::barbarian(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 12;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 1; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::bard(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 8;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 2; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::cleric(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 8;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 3; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::druid(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 8;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 4; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::fighter(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 10;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 5; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::monk(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 8;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 6; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::paladin(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 10;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 7; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::ranger(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 10;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 8; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::rogue(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 8;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 9; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::sorcerer(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 6;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 10; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::warlock(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 8;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 11; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::wizard(int& hit_dice, int& hd_count, int& conabm, int& hit_points, int& prof_bonus, int& level, int& exp, int& clss)
{
	hit_dice = 6;
	hd_count = 1;
	int con_mod = conabm;
	int hp_calc = hit_dice;
	hit_points = con_mod + hp_calc;
	prof_bonus = 2;
	level = 1;
	exp = 0;
	clss = 12; //integer denotation of class in the csumm struct.  see charclass.h note at the top
}

void Charclass::acolyte() {

}
