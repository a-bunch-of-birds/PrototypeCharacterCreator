#include "species.h"

Species::Species() {
	species = 0;
	darkvision = false;
	score_buffs = std::vector<int>(6, 0);
}

Species::~Species() {

}

std::vector<int>& Species::scores() {
	return score_buffs;
}

void Species::default_dwarf() {
	const int defdw_con = 2;
	scores().at(con_i) += defdw_con;
}

void Species::hill_dwarf() {
	const int hildw_wis = 1;
	default_dwarf();
	scores().at(wis_i) += hildw_wis;
}

void Species::mountain_dwarf() {
	const int mtndw_str = 2;
	default_dwarf();
	scores().at(str_i) += mtndw_str;
}

void Species::default_elf() {
	const int defelf_dex = 2;
	scores().at(dex_i) += defelf_dex;
}

void Species::high_elf() {
	const int hielf_intl = 1;
	default_elf();
	scores().at(intl_i) += hielf_intl;
}

void Species::wood_elf() {
	const int wdelf_wis = 1;
	default_elf();
	scores().at(wis_i) += wdelf_wis;

}

void Species::dark_elf() {
	const int drkelf_cha = 1;
	default_elf();
	scores().at(cha_i) += drkelf_cha;
}

void Species::default_halfling() {
	const int defhlf_dex = 2;
	scores().at(dex_i) += defhlf_dex;
}

void Species::lightfoot_halfling() {
	const int lthlf_cha = 1;
	default_halfling();
	scores().at(cha_i) += lthlf_cha;
}

void Species::stout_halfling() {
	const int sthlf_con = 1;
	default_halfling();
	scores().at(con_i) += sthlf_con;
}

void Species::human() {
	const int human_pan = 1;
	for (auto& i : scores()) {
		i += human_pan;
	}
}

void Species::dragonborn() {
	const int drgn_str = 2;
	const int drgn_cha = 1;
	scores().at(str_i) += drgn_str;
	scores().at(cha_i) += drgn_cha;
}

void Species::default_gnome() {
	const int gno_intl = 2;
	scores().at(intl_i) += gno_intl;
}

void Species::forest_gnome() {
	const int fstgno_dex = 1;
	default_gnome();
	scores().at(dex_i) += fstgno_dex;
}

void Species::rock_gnome() {
	const int rckgno_con = 1;
	default_gnome();
	scores().at(con_i) += rckgno_con;
}

void Species::default_halfelf() {
	const int hlfelf_cha = 2;
	scores().at(cha_i) += hlfelf_cha;
}
void Species::halfelf_choice_params(int param_one, int param_two) {
	
	halfelf_choice_one = param_one;
	halfelf_choice_two = param_two;
	
}

void Species::halfelf() {
	const int hlfelf_buff = 1;
	default_halfelf();
	//potentially nasty bug where the default index of 0 will be buffed twice (so STR will get +2)
	scores().at(halfelf_choice_one) += hlfelf_buff;
	scores().at(halfelf_choice_two) += hlfelf_buff;
}

void Species::halforc() {
	const int hlforc_str = 2;
	const int hlforc_con = 2;
	scores().at(str_i) += hlforc_str;
	scores().at(con_i) += hlforc_con;
}

void Species::tiefling() {
	const int tief_intl = 1;
	const int tief_cha = 2;
	scores().at(intl_i) += tief_intl;
	scores().at(cha_i) += tief_cha;
}

void Species::set_halfelf_params(int param_one, int param_two) {
	bool no_double_selection = (param_one != param_two) ? true : false;
	bool no_dead_params = (param_one > -1 && param_two > -1) ? true : false;
	if (no_double_selection && no_dead_params) {
		halfelf_choice_one = param_one;
		halfelf_choice_two = param_two;
	}
}

void Species::species_console(int selec) {
	switch (selec) {
	case hill_dwarf_i:
		hill_dwarf();
		break;
	case mtn_dwarf_i:
		mountain_dwarf();
		break;
	case hi_elf_i:
		high_elf();
		break;
	case wd_elf_i:
		wood_elf();
		break;
	case dr_elf_i:
		dark_elf();
		break;
	case ltft_halfling_i:
		lightfoot_halfling();
		break;
	case st_halfling_i:
		stout_halfling();
		break;
	case human_i:
		human();
		break;
	case dragonborn_i:
		dragonborn();
		break;
	case frst_gnome_i:
		forest_gnome();
		break;
	case rock_gnome_i:
		rock_gnome();
		break;
	case halfelf_i:
		halfelf();
		break;
	case halforc_i:
		halforc();
		break;
	case tiefling_i:
		tiefling();
		break;
	default:
		break;
	}
}