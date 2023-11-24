#ifndef SPECIES_H
#define SPECIES_H

#include <iostream>
#include <vector>
#include <string>

class Species
{
private:

	int species = 0;
	// 0: STR  1: DEX  2: CON  3: INTL  4: WIS  5: CHA
	std::vector<int> score_buffs;
	bool darkvision = false;

	int halfelf_choice_one = 0;
	int halfelf_choice_two = 0;
	static constexpr int str_i = 0;
	static constexpr int dex_i = 1;
	static constexpr int con_i = 2;
	static constexpr int intl_i = 3;
	static constexpr int wis_i = 4;
	static constexpr int cha_i = 5;
	
	static constexpr int hill_dwarf_i = 1;
	static constexpr int mtn_dwarf_i = 2;
	static constexpr int hi_elf_i = 3;
	static constexpr int wd_elf_i = 4;
	static constexpr int dr_elf_i = 5;
	static constexpr int ltft_halfling_i = 6;
	static constexpr int st_halfling_i = 7;
	static constexpr int human_i = 8;
	static constexpr int dragonborn_i = 9;
	static constexpr int frst_gnome_i = 10;
	static constexpr int rock_gnome_i = 11;
	static constexpr int halfelf_i = 12;
	static constexpr int halforc_i = 13;
	static constexpr int tiefling_i = 14;

public:

	Species();
	~Species();
	std::vector<int>& scores();
	void default_dwarf();
	void hill_dwarf();
	void mountain_dwarf();
	void default_elf();
	void high_elf();
	void wood_elf();
	void dark_elf();
	void default_halfling();
	void lightfoot_halfling();
	void stout_halfling();
	void human();
	void dragonborn();
	void default_gnome();
	void forest_gnome();
	void rock_gnome();
	void default_halfelf();
	void halfelf_choice_params(int param_one, int param_two);
	void halfelf();
	void halforc();
	void tiefling();
	void set_halfelf_params(int a, int b);
	void species_console(int selec);	
};

#endif SPECIES_H