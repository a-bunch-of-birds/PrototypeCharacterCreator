#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include <unordered_map>

/*
TO DO:
- Add the ability to choose another tool or skill proficiency if you can receive the same proficiency from multiple sources (species, class, or background)
- Create a suitable constructor for the class
- Create a suitable destructor for the class
*/


class proficiency
{
private:

	const bool selected = true;

	const int artisans_bgn = 0;
	const int artisans_end = 16;

	const int gaming_bgn = 19;
	const int gaming_end = 22;

	const int music_bgn = 24;
	const int music_end = 33;

	const int dwarf_brewers = 1;
	const int dwarf_smiths = 13;
	const int dwarf_masons = 10;

	const int dwarf_tool_profs[3] = { dwarf_brewers, dwarf_masons, dwarf_smiths };

	const int skill_begin = 0;
	const int skill_end = 17;

	//general constants for all maps related to demarcating which prof goes with which selection
	const int no_prof = 0;
	const int spec_prof = 1;
	const int clss_prof = 2;
	const int bckg_prof = 3;
	const int spec_prof_incl = 4;
	const int clss_prof_incl = 5;
	const int bckg_prof_incl = 6;

	//number of skills to select
	int spec_skill_selec_no = 0;
	int clss_skill_selec_no = 0;
	int bckg_skill_selec_no = 0;

	//number of tools to select
	int spec_tool_selec_no = 0;
	int class_tool_selec_no = 0;
	const int bckg_tool_selec_no = 1;
	
	std::vector<bool> wpn_prof{
		// simple melee
		false, // 0 : club
		false, // 1 : dagger
		false, // 2 : greatclub
		false, // 3 : handaxe
		false, // 4 : javelin
		false, // 5 : light hammer
		false, // 6 : mace
		false, // 7 : quarterstaff
		false, // 8 : sickle
		false, // 9 : spear
		// simple ranged
		false, // 10: light crossbow
		false, // 11: dart
		false, // 12: shortbow
		false, // 13: sling
		// martial melee
		false, // 14: battleaxe
		false, // 15: flail
		false, // 16: glaive
		false, // 17: greataxe
		false, // 18: greatsword
		false, // 19: halberd
		false, // 20: lance
		false, // 21: longsword
		false, // 22: maul
		false, // 23: morningstar
		false, // 24: pike
		false, // 25: rapier
		false, // 26: scimitar
		false, // 27: shortsword
		false, // 28: trident
		false, // 29: war pick
		false, // 30: warhammer
		false, // 31: whip
		// martial ranged
		false, // 32: blowgun
		false, // 33: hand crossbow
		false, // 34: heavy crossbow
		false, // 35: longbow
		false  // 36: net
	};

	std::vector<bool> armor_prof{
		//light armor
		false, // 0 : padded
		false, // 1 : leather
		false, // 2 : studded leather
		//end of light armor
		//medium armor
		false, // 3 : hide
		false, // 4 : chain shirt
		false, // 5 : scale mail
		false, // 6 : breastplate
		false, // 7 : half plate
		//end of medium armor
		//heavy armor
		false, // 8 : ring mail
		false, // 9 : chain mail
		false, // 10: splint
		false, // 11: plate
		//end of heavy armor
		//shields
		false  // 12 : shield
	};

	std::unordered_map<int, std::pair<bool, int>> skillprf_map{
		 {0, {false, 0}}, //  0 : athletics
		 {1, {false, 0}}, //  1 : acrobatics
		 {2, {false, 0}}, //  2 : sleight of hand
		 {3, {false, 0}}, //  3 : stealth
		 {4, {false, 0}}, //  4 : arcana
		 {5, {false, 0}}, //  5 : history
		 {6, {false, 0}}, //  6 : investigation
		 {7, {false, 0}}, //  7 : nature
		 {8, {false, 0}}, //  8 : religion
		 {9, {false, 0}}, //  9 : animal handling
		{10, {false, 0}}, // 10 : insight
		{11, {false, 0}}, // 11 : medicine
		{12, {false, 0}}, // 12 : perception
		{13, {false, 0}}, // 13 : survival
		{14, {false, 0}}, // 14 : deception
		{15, {false, 0}}, // 15 : intimidation
		{16, {false, 0}}, // 16 : performance
		{17, {false, 0}}  // 17 : persuasion
	};

	const std::vector<int> barbarian_sk = {
		9, 0, 15, 7, 12, 13
	};
	//bard skills not necessary to delineate since you can just choose any three (PHB 52)
	const std::vector<int> cleric_sk = {
		5, 10, 11, 17, 8
	};
	const std::vector<int> druid_sk = {
		4, 9, 10, 11, 7, 12, 8, 13
	};
	const std::vector<int> fighter_sk = {
		1, 9, 0, 5, 10, 15, 12, 13
	};
	const std::vector<int> monk_sk = {
		1, 0, 5, 10, 8, 3
	};
	const std::vector<int> paladin_sk = {
		0, 10, 15, 11, 17, 8
	};
	const std::vector<int> ranger_sk = {
		9, 0, 10, 6, 7, 12, 3, 13
	};
	const std::vector<int> rogue_sk = {
		1, 0, 14, 10, 15, 6, 12, 16, 17, 2, 3
	};
	const std::vector<int> sorcerer_sk = {
		4, 14, 10, 15, 17, 8
	};
	const std::vector<int> warlock_sk = {
		4, 14, 5, 15, 6, 7, 8
	};
	const std::vector<int> wizard_sk = {
		4, 5, 10, 6, 11, 8
	};

	std::vector<int> species_skillprf_indices{};
	std::vector<int> class_skillprf_indices{};
	std::vector<int> bckg_skillprf_indices{};

	std::vector<std::string> spec_skillprf_names{};
	std::vector<std::string> clss_skillprf_names{};
	std::vector<std::string> bckg_skillprf_names{};

	std::vector<std::string> skill_prof_names{
		"athletics", "acrobatics", "sleight of hand", "stealth", "arcana", "history",
		"investigation", "nature", "religion", "animal handling", "insight", "medicine",
		"perception", "survival", "deception", "intimidation", "performance", "persuasion"
	};

	std::vector<std::string> tool_prof_names{
		"alchemist's supplies", "brewer's supplies", "calligrapher's supplies", "carpenter's tools",
		"cartographer's tools", "cobbler's tools", "cook's utensils", "glassblower's tools",
		"jeweler's tools", "leatherworker's tools", "mason's tools", "painter's supplies",
		"potter's tools", "smith's tools", "tinker's tools", "weaver's tools", 
		"woodcarver's tools", "disguise kit", "forgery kit", "dice set",
		"dragonchess set", "playing card set", "three-dragon ante set", "herbalism kit",
		"bagpipes", "drum", "dulcimer", "flute",
		"lute", "lyre", "horn", "pan flute",
		"shawm", "viol", "navigator's tools", "poisoner's kit",
		"thieves' tools"
	};

	std::unordered_map<int, std::pair<bool, int>> tlprf_map{
		 {0, {false, 0}},
		 {1, {false, 0}},
		 {2, {false, 0}},
		 {3, {false, 0}},
		 {4, {false, 0}},
		 {5, {false, 0}},
		 {6, {false, 0}},
		 {7, {false, 0}},
		 {8, {false, 0}},
		 {9, {false, 0}},
		{10, {false, 0}},
		{11, {false, 0}},
		{12, {false, 0}},
		{13, {false, 0}},
		{14, {false, 0}},
		{15, {false, 0}},
		{16, {false, 0}},
		{17, {false, 0}},
		{18, {false, 0}},
		{19, {false, 0}},
		{20, {false, 0}},
		{21, {false, 0}},
		{22, {false, 0}},
		{23, {false, 0}},
		{24, {false, 0}},
		{25, {false, 0}},
		{26, {false, 0}},
		{27, {false, 0}},
		{28, {false, 0}},
		{29, {false, 0}},
		{30, {false, 0}},
		{31, {false, 0}},
		{32, {false, 0}},
		{33, {false, 0}},
		{34, {false, 0}},
		{35, {false, 0}},
		{36, {false, 0}}
	};

	std::vector<int> species_tlprf_indices{};
	std::vector<int> class_tlprf_indices{};
	std::vector<int> bckg_tlprf_indices{};

	std::vector<std::string> spec_tlprf_names{};
	std::vector<std::string> clss_tlprf_names{};
	std::vector<std::string> bckg_tlprf_names{};

	std::vector<bool> saving_throws{
		false, // 0: strength
		false, // 1: dexterity
		false, // 2: constitution
		false, // 3: intelligence
		false, // 4: wisdom
		false, // 5: charisma
	};

public:
	proficiency();
	~proficiency();
	std::vector<std::string> fetch_toolprof_names();
	std::vector<std::string> fetch_skillprof_names();
	std::vector<int> retr_skillprof_inds(int mode);
	std::vector<int> retr_toolprof_inds(int mode);
	int retr_skillprof_limits(int mode);
	int retr_toolprof_limits(int mode);
	std::vector<std::string> sklprf_shunt(int mode);
	std::vector<std::string> tlprf_shunt(int mode);
	void simple_wpns();
	void martial_wpns();
	void lt_armor();
	void med_armor();
	void heavy_armor();
	void pan_armor();
	void artisans_tls_selec(int vector_destination);
	void musical_instrs_selec(int vector_destination);
	void gaming_selec(int vector_destination);
	void dwarf_arttools_selec();
	void bard_music_selec();
	void monk_tls_selec();
	bool skillprf_selection_ceiling(int mode);
	bool tlprf_selection_ceiling(int mode);
	bool skill_index_collision_ctrl(int index, int mode);
	bool tool_index_collision_ctrl(int index, int mode);
	bool enforce_skill_ceiling(int index, int mode);
	bool enforce_tool_ceiling(int index, int mode);
	void assign_skillprf_mode(int index, int mode);
	void assign_tlprf_mode(int index, int mode);
	bool& skillprof_map_toggle(int index);
	bool& toolprof_map_toggle(int index);
	std::vector<std::string> map_to_vec_util(int type, std::vector<std::string>& names_vec, std::unordered_map<int, std::pair<bool, int>>& map_ref);
	void map_to_vec(int map_type, std::vector<std::string>& vec_spec, std::vector<std::string>& vec_clss, std::vector<std::string>& vec_bckg);
	void barbarian();
	void bard();
	void cleric();
	void druid();
	void fighter();
	void monk();
	void paladin();
	void ranger();
	void rogue();
	void sorcerer();
	void warlock();
	void wizard();
	void acolyte();
	void charlatan();
	void criminal();
	void entertainer();
	void folk_hero();
	void guild_artisan();
	void hermit();
	void noble();
	void outlander();
	void sage();
	void sailor();
	void soldier();
	void urchin();
	void dwarf();
	void mtn_dwarf();
	void high_wood_elf();
	void darkelf();
	void rock_gnome();
	void half_elf();
	void half_orc();
};

