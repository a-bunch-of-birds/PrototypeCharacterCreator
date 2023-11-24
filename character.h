#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "abilityscore.h"
#include "species.h"
#include "charclass.h"
#include "proficiency.h"
#include "clssexp.h"


class Character
{
private:
	Abilityscore abscore_obj;
	Species spec_obj;
	Charclass chacl_obj;
	proficiency prof_obj;

	struct ability_summary
	{
		int str = 0;
		int dex = 0;
		int con = 0;
		int intl = 0;
		int wis = 0;
		int cha = 0;
		int strabm = 0;
		int dexabm = 0;
		int conabm = 0;
		int intlabm = 0;
		int wisabm = 0;
		int chaabm = 0;
		int armor_class = 0;
	};
	ability_summary absumm;

	struct species_summary
	{
		int species = 0;
		std::string spec_name = "";
		int age = 0;
		std::string alignment = "";
		std::string size = "";
		int speed = 0;
		bool darkvision = false;
		std::vector<std::string> skill_profs{};
		std::vector<std::string> tool_profs{};
		std::vector<std::string> languages{};
	};
	species_summary specsumm;

	struct class_summary
	{
		int clss = 0;
		int hit_dice = 0;
		int hd_count = 0;
		int hit_points = 0;
		int exp = 0;
		int level = 0;
		int prof_bonus = 0;
		bool lvlup_abscore = false;
		int spell_save_dc = 0;
		int spell_attk_mod = 0;

		std::vector<std::string> skill_profs{};
		std::vector<std::string> wpn_profs{};
		std::vector<std::string> tool_profs{};
		std::vector<std::string> armor_profs{};
		std::vector<std::string> equipment{};
	};
	class_summary csumm;
	
	
	//not sure what to do with these yet
	struct add_ons {
		int buff_score = 0;
		char type = 'z';
	};

	std::vector<add_ons> species_buff{};
	std::vector<add_ons> class_buff{};

	//for point buy system
	const int point_buy_total = 27;

	struct weapon {
		std::string wpn_name = " ";
		std::string wpn_tag = " ";
		int cost = 0;
		std::string cost_denom = " ";
		int die_count = 1;
		int dmg_die = 4;
		std::string dmg_type = " ";
		float weight = 0.0;
		std::vector<std::string> wpn_properties;
	};

	std::vector<weapon> avail_wpns;

	struct gear {
		std::string item_name = " ";
		std::string item_tag = " ";
		int cost = 0;
		std::string cost_denom = " ";
		float weight = 0.0;
	};

	std::vector<gear> avail_gear;

	std::vector<int> prof_selec{
		0, //  0 : athletics
		0, //  1 : acrobatics
		0, //  2 : sleight of hand
		0, //  3 : stealth
		0, //  4 : arcana
		0, //  5 : history
		0, //  6 : investigation
		0, //  7 : nature
		0, //  8 : religion
		0, //  9 : animal handling
		0, // 10 : insight
		0, // 11 : medicine
		0, // 12 : perception
		0, // 13 : survival
		0, // 14 : deception
		0, // 15 : intimidation
		0, // 16 : performance
		0  // 17 : persuasion
	};

	struct skills {
		//strength checks
		bool athletics =		false;
		//dexterity
		bool acrobatics =		false;
		bool sleightofhand =	false;
		bool stealth =			false;
		//intelligence
		bool arcana =			false;
		bool history =			false;
		bool investigation =	false;
		bool nature =			false;
		bool religion =			false;
		//wisdom
		bool animalhandling =	false;
		bool insight =			false;
		bool medicine =			false;
		bool perception =		false;
		bool survival =			false;
		//charisma
		bool deception =		false;
		bool intimidation =		false;
		bool performance =		false;
		bool persuasion =		false;
	};
	skills skill_summ;

	const int acolyte = 1;
	const int charlatan = 2;
	const int criminal = 3;
	const int entertainer = 4;
	const int folk_hero = 5;
	const int guild_artisan = 6;
	const int hermit = 7;
	const int noble = 8;
	const int outlander = 9;
	const int sage = 10;
	const int sailor = 11;
	const int soldier = 12;
	const int urchin = 13;
	//std::string bckg_prof;
	std::vector<std::string> bckg_tool_profs{};
	std::vector<std::string> bckg_skill_profs{};
	int background_idx = 0;

	
	int tools_choices = 0; //internally tracks how many tools proficiencies the user is allowed to select

	int art_tls_choices = 0;
	int music_inst_choices = 0;
	int gaming_set_choices = 0;
	int dwarf_tls_choices = 0;
	int monk_art_or_inst_choice = 0;




	
	
public:
	//constructor & destructuro
	Character() {};
	~Character() {};
	//struct and class getters
	ability_summary& retr_absumm() {
		return absumm;
	}
	species_summary& retr_specsumm() {
		return specsumm;
	}
	class_summary& retr_csumm() {
		return csumm;
	}
	Abilityscore& retr_ab() {
		return abscore_obj;
	}
	std::vector<int>& retr_init_rolls() {
		return abscore_obj.fetch_init_scores();
	}
	std::vector<std::string>& retr_skills() {
		return abscore_obj.skills;
	}
	std::vector<std::vector<int>>& retr_roll_hist() {
		return abscore_obj.retr_roll_hist();
	}
	std::vector<int>& retr_point_buy() {
		//return abscore_obj.fetch_pb_array();
		return abscore_obj.retr_purchdisplay();
	}

	std::vector<int>& retr_purchdisplay() {
		return abscore_obj.retr_purchdisplay();
	}
	
	std::vector<int> retr_toolprof_inds(int mode) {
		return prof_obj.retr_toolprof_inds(mode);
	}

	std::vector<int> retr_skillprof_inds(int mode) {
		return prof_obj.retr_skillprof_inds(mode);
	}

	int retr_toolprof_nos(int mode) {
		return prof_obj.retr_toolprof_limits(mode);
	}

	int retr_skillprof_nos(int mode) {
		return prof_obj.retr_skillprof_limits(mode);
	}

	bool prof_collision_ctrl(int index, int mode) {
		return prof_obj.tool_index_collision_ctrl(index, mode);
	}

	bool skill_prof_collision_ctrl(int index, int mode) {
		return prof_obj.skill_index_collision_ctrl(index, mode);
	}

	bool hit_ceiling(int index, int mode) {
		return prof_obj.enforce_tool_ceiling(index, mode);
	}

	bool skill_hit_ceiling(int index, int mode) {
		return prof_obj.enforce_skill_ceiling(index, mode);
	}

	void prof_assign(int index, int mode) {
		prof_obj.assign_tlprf_mode(index, mode);
	}

	void skill_prof_assign(int index, int mode) {
		prof_obj.assign_skillprf_mode(index, mode);
	}

	bool& prof_toggle(int index) {
		return prof_obj.toolprof_map_toggle(index);
	}

	bool& skill_prof_toggle(int index) {
		return prof_obj.skillprof_map_toggle(index);
	}
	/*
	void assign_tool_profs() {
		const int spec = 1;
		const int clss = 2;
		const int bckg = 3;
		prof_obj.toolmap_to_vec();
		specsumm.tool_profs = prof_obj.tlprf_shunt(spec);
		csumm.tool_profs = prof_obj.tlprf_shunt(clss);
		bckg_tool_profs = prof_obj.tlprf_shunt(bckg);
	}
	*/
	
	void assign_tool_profs() {
		//specsumm.tool_profs = prof_obj.toolmap_to_vec(1);
		//csumm.tool_profs = prof_obj.toolmap_to_vec(2);
		//bckg_tool_profs = prof_obj.toolmap_to_vec(3);
		const int tools_param = 2;
		prof_obj.map_to_vec(tools_param, specsumm.tool_profs, csumm.tool_profs, bckg_tool_profs);

	}
	
	void print_tool_vecs() {
		std::cout << "species tool profs" << std::endl;
		for (const auto& i : specsumm.tool_profs) {
			//std::cout << i << std::endl;
			std::cout << i << " ";
		}
		std::cout << std::endl;
		std::cout << "class tool profs" << std::endl;
		for (const auto& j : csumm.tool_profs) {
			//std::cout << i << std::endl;
			std::cout << j << " ";
		}
		std::cout << std::endl;
		std::cout << "bckg tool profs" << std::endl;
		for (const auto& k : bckg_tool_profs) {
			//std::cout << i << std::endl;
			std::cout << k << " ";
		}
	}

	void assign_skill_profs() {
		const int skills_param = 1;
		prof_obj.map_to_vec(skills_param, specsumm.skill_profs, csumm.skill_profs, bckg_skill_profs);
	}

	void print_skill_vecs() {
		std::cout << "species skill profs" << std::endl;
		for (const auto& i : specsumm.skill_profs) {
			//std::cout << i << std::endl;
			std::cout << i << " ";
		}
		std::cout << std::endl;
		std::cout << "class skill profs" << std::endl;
		for (const auto& j : csumm.skill_profs) {
			//std::cout << i << std::endl;
			std::cout << j << " ";
		}
		std::cout << std::endl;
		std::cout << "bckg skill profs" << std::endl;
		for (const auto& k : bckg_skill_profs) {
			//std::cout << i << std::endl;
			std::cout << k << " ";
		}
	}

	//ability score functions
	void roll_abilities() {
		abscore_obj.sextuple_score();
	}
	
	void roll_abilities_mersenne_twister() {
		abscore_obj.sextuple_score_mersenne_twister();
	}

	void clear_init() {
		abscore_obj.clear_init_scores();
	}

	void resort_init() {
		abscore_obj.resort_init_scores();
	}

	void ability_mods() {
		absumm.strabm = abscore_obj.ability_modifier(absumm.str);
		absumm.dexabm = abscore_obj.ability_modifier(absumm.dex);
		absumm.conabm = abscore_obj.ability_modifier(absumm.con);
		absumm.intlabm = abscore_obj.ability_modifier(absumm.intl);
		absumm.wisabm = abscore_obj.ability_modifier(absumm.wis);
		absumm.chaabm = abscore_obj.ability_modifier(absumm.cha);
	}

	int imgui_abmod(int x) {
		return abscore_obj.ability_modifier(x);
	}

	void armor_class() {
		absumm.armor_class = abscore_obj.ac_assign(absumm.dexabm);
	}
	
	void commit_abilities() {
		//this function is incredibly vulnerable and a different paradigm needs to be implemented
		if (!abscore_obj.fetch_init_scores().empty())
		{
			//note that the scores are now being incrementally added instead of assigned
			//we have changed the order in which the character is made, from ability score first to abscore LAST
			//ERGO - we now have to add the rolls to existing buffs
			absumm.str += retr_init_rolls().at(0);
			absumm.dex += retr_init_rolls().at(1);
			absumm.con += retr_init_rolls().at(2);
			absumm.intl += retr_init_rolls().at(3);
			absumm.wis += retr_init_rolls().at(4);
			absumm.cha += retr_init_rolls().at(5);
			
			ability_mods();
			armor_class();

			
		}
		else {}
	}

	void commit_abilities_pointbuy() {
		//if (!abscore_obj.fetch_pb_array().empty()) {
		if (!retr_point_buy().empty()) {
			absumm.str += retr_point_buy().at(0);
			absumm.dex += retr_point_buy().at(1);
			absumm.con += retr_point_buy().at(2);
			absumm.intl += retr_point_buy().at(3);
			absumm.wis += retr_point_buy().at(4);
			absumm.cha += retr_point_buy().at(5);

			ability_mods();
			armor_class();
		}
	}
	/*
	//I don't think we can avoid these char parameters, so the imgui util will just input these as 'z', and they will never be used
	void species_selec(int spec, char a, char b) {

		switch(spec) {
		case 1:
			spec_obj.hill_dwarf(specsumm.species, absumm.con, absumm.wis, specsumm.spec_name, specsumm.darkvision);
			break;
		case 2:
			spec_obj.mountain_dwarf(specsumm.species, absumm.con, absumm.str);
			break;
		case 3:
			spec_obj.high_elf(specsumm.species, absumm.dex, absumm.intl);
			break;
		case 4:
			spec_obj.wood_elf(specsumm.species, absumm.dex, absumm.wis);
			break;
		case 5:
			spec_obj.dark_elf(specsumm.species, absumm.dex, absumm.cha);
			break;
		case 6:
			spec_obj.lightfoot_halfling(specsumm.species, absumm.dex, absumm.cha);
			break;
		case 7:
			spec_obj.stout_halfling(specsumm.species, absumm.dex, absumm.con);
			break;
		case 8:
			spec_obj.human(specsumm.species, absumm.str);
			spec_obj.human(specsumm.species, absumm.dex);
			spec_obj.human(specsumm.species, absumm.con);
			spec_obj.human(specsumm.species, absumm.intl);
			spec_obj.human(specsumm.species, absumm.wis);
			spec_obj.human(specsumm.species, absumm.cha);
			break;
		case 9:
			spec_obj.dragonborn(specsumm.species, absumm.str, absumm.cha);
			break;
		case 10:
			spec_obj.forest_gnome(specsumm.species, absumm.intl, absumm.dex);
			break;
		case 11:
			spec_obj.rock_gnome(specsumm.species, absumm.intl, absumm.con);
			break;
		case 12:
			spec_obj.default_halfelf(absumm.cha);
			//take care of char a input
			if (a == 's') {
				spec_obj.halfelf_choice(specsumm.species, absumm.str);
			}
			else if (a == 'd') {
				spec_obj.halfelf_choice(specsumm.species, absumm.dex);
			}
			else if (a == 'c') {
				spec_obj.halfelf_choice(specsumm.species, absumm.con);
			}
			else if (a == 'i') {
				spec_obj.halfelf_choice(specsumm.species, absumm.intl);
			}
			else if (a == 'w') {
				spec_obj.halfelf_choice(specsumm.species, absumm.wis);
			}
			else if (a == 'a') {
				spec_obj.halfelf_choice(specsumm.species, absumm.cha);
			}
			else {
				std::cout << "Input for CHAR A parameter invalid" << std::endl;
			}
			// take care of the char b input
			if (b == 's') {
				spec_obj.halfelf_choice(specsumm.species, absumm.str);
			}
			else if (b == 'd') {
				spec_obj.halfelf_choice(specsumm.species, absumm.dex);
			}
			else if (b == 'c') {
				spec_obj.halfelf_choice(specsumm.species, absumm.con);
			}
			else if (b == 'i') {
				spec_obj.halfelf_choice(specsumm.species, absumm.intl);
			}
			else if (b == 'w') {
				spec_obj.halfelf_choice(specsumm.species, absumm.wis);
			}
			else if (b == 'a') {
				spec_obj.halfelf_choice(specsumm.species, absumm.cha);
			}
			else {
				std::cout << "Input for CHAR B parameter invalid" << std::endl;
			}
			break;
		case 13:
			spec_obj.halforc(specsumm.species, absumm.str, absumm.con);
			break;
		case 14:
			spec_obj.tiefling(specsumm.species, absumm.intl, absumm.cha);
			break;
		default:
			std::cout << "species_selec DEFAULT HIT" << std::endl;
			break;
		}
		
		ability_mods();
		armor_class();
	}
	*/
	
	void add_species_score_buffs() {
		absumm.str += spec_obj.scores().at(0);
		absumm.dex += spec_obj.scores().at(1);
		absumm.con += spec_obj.scores().at(2);
		absumm.intl += spec_obj.scores().at(3);
		absumm.wis += spec_obj.scores().at(4);
		absumm.cha += spec_obj.scores().at(5);
	}

	void halfelf_params(int a, int b) {
		spec_obj.set_halfelf_params(a, b);
	}

	void species_selec(int selec) {
		spec_obj.species_console(selec);
		add_species_score_buffs();
		ability_mods();
		armor_class();
	}

	void character_selec(int selec) {
		switch (selec) {
		case 1: 
			chacl_obj.barbarian(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 2:
			chacl_obj.bard(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 3:
			chacl_obj.cleric(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 4:
			chacl_obj.druid(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 5:
			chacl_obj.fighter(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 6: 
			chacl_obj.monk(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 7:
			chacl_obj.paladin(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 8:
			chacl_obj.ranger(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 9:
			chacl_obj.rogue(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 10:
			chacl_obj.sorcerer(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 11:
			chacl_obj.warlock(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		case 12:
			chacl_obj.wizard(csumm.hit_dice, csumm.hd_count, absumm.conabm, csumm.hit_points, csumm.prof_bonus, csumm.level, csumm.exp, csumm.clss);
			break;
		default:
			break;
		}
	}

	bool tlprf_ceiling(int mode) {
		return prof_obj.tlprf_selection_ceiling(mode);
	}

	bool skillprf_ceiling(int mode) {
		return prof_obj.skillprf_selection_ceiling(mode);
	}

	void spec_prof_dist(int index) {
		switch (index) {
		case 1:
			prof_obj.dwarf();
			break;
		case 2:
			prof_obj.mtn_dwarf();
			break;
		case 3:
		case 4:
			prof_obj.high_wood_elf();
			break;
		case 5:
			prof_obj.darkelf();
			break;
		case 11:
			prof_obj.rock_gnome();
			break;
		case 12:
			prof_obj.half_elf();
			break;
		case 13:
			prof_obj.half_orc();
			break;
		default:
			std::cout << "ERROR: spec_prof_dist switch stmt invalid input" << std::endl;
		}
	}

	void clss_prof_dist(int mode) {
		switch (mode) {
		case 1:
			prof_obj.barbarian();
			break;
		case 2:
			prof_obj.bard();
			break;
		case 3:
			prof_obj.cleric();
			break;
		case 4:
			prof_obj.druid();
			break;
		case 5:
			prof_obj.fighter();
			break;
		case 6:
			prof_obj.monk();
			break;
		case 7:
			prof_obj.paladin();
			break;
		case 8:
			prof_obj.ranger();
			break;
		case 9:
			prof_obj.rogue();
			break;
		case 10:
			prof_obj.sorcerer();
			break;
		case 11:
			prof_obj.warlock();
			break;
		case 12:
			prof_obj.wizard();
			break;
		default:
			std::cout << "ERROR: clss_prof_dist switch stmt invalid input" << std::endl;
		}
	}

	void bckg_prof_dist(int mode) {
		switch (mode) {
		case 1:
			prof_obj.acolyte();
			background_idx = acolyte;
			break;
		case 2:
			prof_obj.charlatan();
			background_idx = charlatan;
			break;
		case 3:
			prof_obj.criminal();
			background_idx = criminal;
			break;
		case 4:
			prof_obj.entertainer();
			background_idx = entertainer;
			break;
		case 5:
			prof_obj.folk_hero();
			background_idx = folk_hero;
			break;
		case 6:
			prof_obj.guild_artisan();
			background_idx = guild_artisan;
			break;
		case 7:
			prof_obj.hermit();
			background_idx = hermit;
			break;
		case 8:
			prof_obj.noble();
			background_idx = noble;
			break;
		case 9:
			prof_obj.outlander();
			background_idx = outlander;
			break;
		case 10:
			prof_obj.sage();
			background_idx = sage;
			break;
		case 11:
			prof_obj.sailor();
			background_idx = sailor;
			break;
		case 12:
			prof_obj.soldier();
			background_idx = soldier;
			break;
		case 13:
			prof_obj.urchin();
			background_idx = urchin;
			break;
		default:
			std::cout << "ERROR: bckg_prof_dist switch stmt invalid input" << std::endl;
		}
	}
	//prof_dist is deservedly obsolete on refactoring
	void prof_dist(int mode, int idx_one = 19, int idx_two = 19) {
		switch (mode) {
		case 0:
			//prof_obj.hill_dwarf(idx_one);
			prof_obj.dwarf();//we can use the first index for dwarf tool profs -> see proficiency.h void hill_dwarf
			break;
		case 1:
			//prof_obj.mtn_dwarf(idx_one);
			prof_obj.mtn_dwarf();
			break;
		case 2:
			prof_obj.high_wood_elf();
			break;
		case 3:
			prof_obj.darkelf();
			break;
		case 4:
			prof_obj.rock_gnome();
			break;
		case 5:
			prof_obj.half_elf();
			break;
		case 6:
			prof_obj.half_orc();
			break;
		case 7:
			prof_obj.barbarian();
			break;
		case 8:
			prof_obj.bard();
			break;
		case 9:
			prof_obj.cleric();
			break;
		case 10:
			prof_obj.druid();
			break;
		case 11:
			prof_obj.fighter();
			break;
		case 12:
			prof_obj.monk();
			break;
		case 13:
			prof_obj.paladin();
			break;
		case 14:
			prof_obj.ranger();
			break;
		case 15:
			prof_obj.rogue();
			break;
		case 16:
			prof_obj.sorcerer();
			break;
		case 17:
			prof_obj.warlock();
			break;
		case 18:
			prof_obj.wizard();
			break;
		case 19:
			prof_obj.acolyte();
			background_idx = acolyte;
			break;
		case 20:
			prof_obj.charlatan();
			background_idx = charlatan;
			break;
		case 21:
			prof_obj.criminal();
			background_idx = criminal;
			break;
		case 22:
			prof_obj.entertainer();
			background_idx = entertainer;
			break;
		case 23:
			prof_obj.folk_hero();
			background_idx = folk_hero;
			break;
		case 24:
			prof_obj.guild_artisan();
			background_idx = guild_artisan;
			break;
		case 25:
			prof_obj.hermit();
			background_idx = hermit;
			break;
		case 26:
			prof_obj.noble();
			background_idx = noble;
			break;
		case 27:
			prof_obj.outlander();
			background_idx = outlander;
			break;
		case 28:
			prof_obj.sage();
			background_idx = sage;
			break;
		case 29:
			prof_obj.sailor();
			background_idx = sailor;
			break;
		case 30:
			prof_obj.soldier();
			background_idx = soldier;
			break;
		case 31:
			prof_obj.urchin();
			background_idx = urchin;
			break;
		default:
			std::cout << "prof_dist DEFAULT HIT" << std::endl;
			break;
		}
		//bckg_tls_choices();
	}

	bool tool_prof_commit() {
		const int species_mode = 1;
		const int class_mode = 2;
		const int bckg_mode = 3;
		
		int index;
		std::string str_payload;
		
		int specv_size = prof_obj.retr_toolprof_inds(species_mode).size();
		int clssv_size = prof_obj.retr_toolprof_inds(class_mode).size();
		int bckg_size = prof_obj.retr_toolprof_inds(bckg_mode).size();
		/*
		for (auto i : prof_obj.retr_toolprof_inds(species_mode)) {
			if (prof_obj.)
		}

		for (auto i : prof_obj.retr_toolprof_inds(class_mode)) {

		}

		for (auto i : prof_obj.retr_toolprof_inds(bckg_mode)) {

		}
		*/
		
		
	}
	
	void proficiency_up() {
		chacl_obj.prof_incr(retr_csumm().level, retr_csumm().prof_bonus);
	}

	int abscore_up() {
		return chacl_obj.ab_upscore(retr_csumm().level, retr_csumm().clss);
	}

	int& fetch_point_buy_total() {

		return abscore_obj.retr_pointbuy_total();

	}

	int& fetch_point_spent_total() {
		return abscore_obj.retr_pointspend_total();
	}

	int fetch_purchmap_cost(int index) {
		return abscore_obj.retr_purchmap_cost(index);
	}

	void point_purchase(char option, int index) {
		abscore_obj.point_purchase_console(option, index);
	}

	std::vector<std::string> wpn_type{ "Simple Melee", "Simple Ranged", "Martial Melee", "Martial Ranged" }; // indices 0 - 3

	std::vector<std::string> sm_wpn_name{ "Club", "Dagger", "Greatclub", "Handaxe", "Javelin", "Light Hammer", "Mace", "Quarterstaff", "Sickle", "Spear" }; // indices 0 - 9
	std::vector<std::string> sr_wpn_name{ "Light Crossbow", "Dart", "Shortbow", "Sling" };
	std::vector<std::string> mm_wpn_name{ "Battleaxe", "Flail", "Glaive", "Greataxe", "Greatsword", "Halberd", "Lance",
										"Longsword", "Maul", "Morningstar", "Pike", "Rapier", "Scimitar", "Shortsword",
										"Trident", "War Pick", "Warhammer", "Whip" };
	std::vector<std::string> mr_wpn_name{ "Blowgun", "Hand Crossbow", "Heavy Crossbow", "Longbow", "Net" };
	std::vector<int> num_cost{ 1, 2, 5, 10, 15, 20, 25, 30, 50, 75 };
	std::vector<std::string> denom{ "cp", "sp", "gp" };
	std::vector<int> dmg_die_type{ 4, 6, 8, 10, 12 };
	std::vector<std::string> dmg_type_slct{ "bludgeoning", "piercing", "slashing" };

	
	int wpn_weight(int weight_index) {

	}
	std::string dmg_type(int dmg_type_index) {
		std::string x = " ";
		x = dmg_type_slct.at(dmg_type_index);
		return x;
	}
	int dmg_die(int dmg_index) {
		int x = 0;
		x = dmg_die_type.at(dmg_index);
		return x;
	}
	int dmg_die_count(bool one_or_two_die) {
		int x = 0;
		x = (one_or_two_die) ? 1 : 2;
		return x;
	}
	std::string cost_denom(int denom_index) {
		return denom.at(denom_index);
	}
	int numerical_cost(int cost_index) {
		return num_cost.at(cost_index);
	}
	std::string sm_wpn_name_assign(int wpn_name_idx) {
		std::string ret_var = " ";
		ret_var = sm_wpn_name.at(wpn_name_idx);
		return ret_var;
		/*
		switch (wpn_name_idx) {
		case 0:
			ret_var = sm_wpn_name.at(wpn_name_idx);
			break;
		case 1:
			ret_var = sm_wpn_name.at(wpn_name_idx);
			break;
		case 2:
			ret_var = sm_wpn_name.at(wpn_name_idx);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;

		}
		*/
	}
	std::string sr_wpn_name_assign(int wpn_name_idx) {
		std::string ret_var = " ";
		ret_var = sr_wpn_name.at(wpn_name_idx);
		return ret_var;
	}
	std::string mm_wpn_name_assign(int wpn_name_idx) {
		std::string ret_var = " ";
		ret_var = mm_wpn_name.at(wpn_name_idx);
		return ret_var;
	}
	std::string mr_wpn_name_assign(int wpn_name_idx) {
		std::string ret_var = " ";
		ret_var = mr_wpn_name.at(wpn_name_idx);
		return ret_var;
	}
	//0 : simple melee
	//1 : simple ranged
	//2 : martial melee
	//3 : martial ranged
	void arsenal(int wpn_type_idx, int wpn_name_idx, int cost_idx, int denom_idx, bool one_or_two_die, int dmg_idx, int dmg_type_idx) {
		weapon x;
		switch (wpn_type_idx) {
		case 0:
			x.wpn_tag = wpn_type.at(0);
			x.wpn_name = sm_wpn_name_assign(wpn_name_idx);
			x.cost = numerical_cost(cost_idx);
			x.cost_denom = cost_denom(denom_idx);
			x.die_count = dmg_die_count(one_or_two_die);
			x.dmg_die = dmg_die(dmg_idx);
			x.dmg_type = dmg_type(dmg_type_idx);
			break;
		case 1:
			x.wpn_tag = wpn_type.at(1);
			x.wpn_name = sr_wpn_name_assign(wpn_name_idx);
			x.cost = numerical_cost(cost_idx);
			x.cost_denom = cost_denom(denom_idx);
			x.die_count = dmg_die_count(one_or_two_die);
			x.dmg_die = dmg_die(dmg_idx);
			x.dmg_type = dmg_type(dmg_type_idx);
			break;
		case 2:
			x.wpn_tag = wpn_type.at(2);
			x.wpn_name = mm_wpn_name_assign(wpn_name_idx);
			x.cost = numerical_cost(cost_idx);
			x.cost_denom = cost_denom(denom_idx);
			x.die_count = dmg_die_count(one_or_two_die);
			x.dmg_die = dmg_die(dmg_idx);
			x.dmg_type = dmg_type(dmg_type_idx);
			break;
		case 3:
			x.wpn_tag = wpn_type.at(3);
			x.wpn_name = mr_wpn_name_assign(wpn_name_idx);
			x.cost = numerical_cost(cost_idx);
			x.cost_denom = cost_denom(denom_idx);
			x.die_count = dmg_die_count(one_or_two_die);
			x.dmg_die = dmg_die(dmg_idx);
			x.dmg_type = dmg_type(dmg_type_idx);
			break;
		default:
			std::cout << "arsenal: invalid indices" << std::endl;
			break;
		}
		
		avail_wpns.push_back(x);

	}

};

#endif CHARACTER_H
