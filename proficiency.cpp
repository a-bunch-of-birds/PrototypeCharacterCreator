#include "proficiency.h"

proficiency::proficiency() {};
proficiency::~proficiency() {};

std::vector<std::string> proficiency::fetch_toolprof_names() {
	return tool_prof_names;
}

std::vector<std::string> proficiency::fetch_skillprof_names() {
	return skill_prof_names;
}

std::vector<int> proficiency::retr_skillprof_inds(int mode) {
	switch (mode) {
	case 1:
		return species_skillprf_indices;
		break;
	case 2:
		return class_skillprf_indices;
		break;
	case 3:
		return bckg_skillprf_indices;
		break;
	default:
		break;
	}
}

std::vector<int> proficiency::retr_toolprof_inds(int mode) {
	switch (mode) {
	case 1:
		return species_tlprf_indices;
		break;
	case 2:
		return class_tlprf_indices;
		break;
	case 3:
		return bckg_tlprf_indices;
		break;
	default:
		break;
	}
}

int proficiency::retr_skillprof_limits(int mode) {
	switch (mode) {
	case 1:
		return spec_skill_selec_no;
		break;
	case 2:
		return clss_skill_selec_no;
		break;
	case 3:
		return bckg_skill_selec_no;
		break;
	default:
		return 0;
		break;
	}
}

int proficiency::retr_toolprof_limits(int mode) {
	switch (mode) {
	case 1:
		return spec_tool_selec_no;
		break;
	case 2:
		return class_tool_selec_no;
		break;
	case 3:
		return bckg_tool_selec_no;
		break;
	default:
		return 0;
		break;
	}

}

std::vector<std::string> proficiency::sklprf_shunt(int mode) {
	if (mode == spec_prof) {
		return spec_skillprf_names;
	}
	else if (mode == clss_prof) {
		return clss_skillprf_names;
	}
	else if (mode == bckg_prof) {
		return bckg_skillprf_names;
	}
	else {
		std::vector<std::string> x{ "shunted nothing" };
		return x;
	}
}

std::vector<std::string> proficiency::tlprf_shunt(int mode) {
	if (mode == spec_prof) {
		return spec_tlprf_names;
	}
	else if (mode == clss_prof) {
		return clss_tlprf_names;
	}
	else if (mode == bckg_prof) {
		return bckg_tlprf_names;
	}
	else {
		std::vector<std::string> x{ "shunted nothing" };
		return x;
	}
}

void proficiency::simple_wpns() {
	for (int i = 0; i < 14; i++) {
		wpn_prof.at(i) = selected;
	}
}

void proficiency::martial_wpns() {
	for (int i = 14; i < 37; i++) {
		wpn_prof.at(i) = selected;
	}
}

void proficiency::lt_armor() {
	for (int i = 0; i < 3; i++) {
		armor_prof.at(i) = selected;
	}
}

void proficiency::med_armor() {
	for (int i = 3; i < 8; i++) {
		armor_prof.at(i) = selected;
	}
}

void proficiency::heavy_armor() {
	for (int i = 8; i < 12; i++) {
		armor_prof.at(i) = selected;
	}
}

void proficiency::pan_armor() {
	for (auto x : armor_prof) {
		x = selected;
	}
}

void proficiency::artisans_tls_selec(int vector_destination) {
	for (int i = artisans_bgn; i < artisans_end + 1; i++) {

		if (vector_destination == spec_prof) {
			species_tlprf_indices.push_back(i);

		}
		else if (vector_destination == clss_prof) {
			class_tlprf_indices.push_back(i);

		}
		else if (vector_destination == bckg_prof) {
			bckg_tlprf_indices.push_back(i);

		}
		else {}
	}
}

void proficiency::musical_instrs_selec(int vector_destination) {
	for (int i = music_bgn; i < music_end + 1; i++) {

		if (vector_destination == spec_prof) {
			species_tlprf_indices.push_back(i);
		}
		else if (vector_destination == clss_prof) {
			class_tlprf_indices.push_back(i);
		}
		else if (vector_destination == bckg_prof) {
			bckg_tlprf_indices.push_back(i);
		}
		else {}
	}
}

void proficiency::gaming_selec(int vector_destination) {

	for (int i = gaming_bgn; i < gaming_end + 1; i++) {
		if (vector_destination == spec_prof) {
			species_tlprf_indices.push_back(i);
		}
		else if (vector_destination == clss_prof) {
			class_tlprf_indices.push_back(i);
		}
		else if (vector_destination == bckg_prof) {
			bckg_tlprf_indices.push_back(i);
		}
		else {}
	}
}

void proficiency::dwarf_arttools_selec() {
	for (int i = 0; i < 3; i++) {
		species_tlprf_indices.push_back(dwarf_tool_profs[i]);
	}
}

void proficiency::bard_music_selec() {

	musical_instrs_selec(clss_prof);
}

void proficiency::monk_tls_selec() {

	artisans_tls_selec(clss_prof);
	musical_instrs_selec(clss_prof);

}

bool proficiency::skillprf_selection_ceiling(int mode) {
	// if return true: -> disables all currently unselected indices  
	// if return false: -> allows more selections
	int vec_total = 0;
	if (mode == spec_prof) {
		for (const auto& i : skillprf_map) {
			if (i.second.first == true && i.second.second == spec_prof) {
				vec_total += 1;
			}
			if (vec_total >= spec_skill_selec_no) {
				return true;
			}
		}
		return false;
	}
	else if (mode == clss_prof) {
		for (const auto& i : skillprf_map) {
			if (i.second.first == true && i.second.second == clss_prof) {
				vec_total += 1;
			}
			if (vec_total >= clss_skill_selec_no) {
				return true;
			}
		}
		return false;
	}
	else if (mode == bckg_prof) {
		for (const auto& i : skillprf_map) {
			if (i.second.first == true && i.second.second == bckg_prof) {
				vec_total += 1;
			}
			if (vec_total >= bckg_skill_selec_no) {
				return true;
			}
		}
		return false;
	}
	else {
		std::cout << "incorrect input" << std::endl;
		return false;
	}
}

bool proficiency::tlprf_selection_ceiling(int mode) {
	// if return true: -> disables all currently unselected indices  
	// if return false: -> allows more selections
	int vec_total = 0;
	if (mode == spec_prof) {
		for (const auto& i : tlprf_map) {
			if (i.second.first == true && i.second.second == spec_prof) {
				vec_total += 1;
			}
			if (vec_total >= spec_tool_selec_no) {
				return true;
			}
		}
		return false;
	}
	else if (mode == clss_prof) {
		for (const auto& i : tlprf_map) {
			if (i.second.first == true && i.second.second == clss_prof) {
				vec_total += 1;
			}
			if (vec_total >= class_tool_selec_no) {
				return true;
			}
		}
		return false;
	}
	else if (mode == bckg_prof) {
		for (const auto& i : tlprf_map) {
			if (i.second.first == true && i.second.second == bckg_prof) {
				vec_total += 1;
			}
			if (vec_total >= bckg_tool_selec_no) {
				return true;
			}
		}
		return false;
	}
	else {
		std::cout << "incorrect input" << std::endl;
		return false;
	}
}

bool proficiency::skill_index_collision_ctrl(int index, int mode) {
	int type = skillprf_map.at(index).second;
	if (type > 0 && type != mode) {
		return true;
	}
	else {
		return false;
	}
}

bool proficiency::tool_index_collision_ctrl(int index, int mode) {
	int type = tlprf_map.at(index).second;
	if (type > 0 && type != mode) {
		return true;
	}
	else {
		return false;
	}
}

bool proficiency::enforce_skill_ceiling(int index, int mode) {
	int type = skillprf_map.at(index).second;
	if (type == 0 || type != mode) {
		return true;
	}
	else {
		return false;
	}
}

bool proficiency::enforce_tool_ceiling(int index, int mode) {
	int type = tlprf_map.at(index).second;
	if (type == 0 || type != mode) {
		return true;
	}
	else {
		return false;
	}
}

void proficiency::assign_skillprf_mode(int index, int mode) {
	if (skillprf_map.at(index).first == true && skillprf_map.at(index).second == no_prof) {
		skillprf_map.at(index).second = mode;
	}
	else if (skillprf_map.at(index).first == false && skillprf_map.at(index).second != no_prof) {
		skillprf_map.at(index).second = no_prof;
	}
	else {

	}
}

void proficiency::assign_tlprf_mode(int index, int mode) {
	if (tlprf_map.at(index).first == true && tlprf_map.at(index).second == no_prof) {
		tlprf_map.at(index).second = mode;
	}
	else if (tlprf_map.at(index).first == false && tlprf_map.at(index).second != no_prof) {
		tlprf_map.at(index).second = no_prof;
	}
	else {

	}
}

bool& proficiency::skillprof_map_toggle(int index) {
	return skillprf_map.at(index).first;
}

bool& proficiency::toolprof_map_toggle(int index) {
	return tlprf_map.at(index).first;
}

std::vector<std::string> proficiency::map_to_vec_util(int type, std::vector<std::string>& names_vec, std::unordered_map<int, std::pair<bool, int>>& map_ref) {
	std::vector<std::string> ret{};
	int type_verify = 0;
	int type_verify_incl = 0;
	bool selec_verify = false;
	if (type == spec_prof) {
		type_verify_incl = spec_prof_incl;
	}
	else if (type == clss_prof) {
		type_verify_incl = clss_prof_incl;
	}
	else if (type == bckg_prof) {
		type_verify_incl = bckg_prof_incl;
	}
	for (const auto& i : map_ref) {
		type_verify = i.second.second;
		selec_verify = i.second.first;
		if (selec_verify && type_verify == type) {
			std::string prf_name = names_vec.at(i.first);
			ret.push_back(prf_name);
		}
		else if (selec_verify && type_verify == type_verify_incl) {
			std::string prf_name_incl = names_vec.at(i.first);
			ret.push_back(prf_name_incl);
		}
	}
	return ret;
}

void proficiency::map_to_vec(int map_type, std::vector<std::string>& vec_spec, std::vector<std::string>& vec_clss, std::vector<std::string>& vec_bckg) {
	const int skills = 1;
	const int tools = 2;
	if (map_type == skills) {
		vec_spec = map_to_vec_util(spec_prof, skill_prof_names, skillprf_map);
		vec_clss = map_to_vec_util(clss_prof, skill_prof_names, skillprf_map);
		vec_bckg = map_to_vec_util(bckg_prof, skill_prof_names, skillprf_map);
	}
	else if (map_type == tools) {
		vec_spec = map_to_vec_util(spec_prof, tool_prof_names, tlprf_map);
		vec_clss = map_to_vec_util(clss_prof, tool_prof_names, tlprf_map);
		vec_bckg = map_to_vec_util(bckg_prof, tool_prof_names, tlprf_map);
	}
	else {
		std::cout << "map_to_vec, invalid map_type parameter input" << std::endl;
	}
}

void proficiency::barbarian() {

	class_skillprf_indices = barbarian_sk;
	clss_skill_selec_no = 2;

	simple_wpns();
	martial_wpns();

	//no tool profs

	saving_throws.at(0) = selected;
	saving_throws.at(2) = selected;

	lt_armor();
	med_armor();
	armor_prof.at(12) = selected;

}

void proficiency::bard() {

	musical_instrs_selec(clss_prof);
	class_tool_selec_no = 3;

	for (int i = skill_begin; i <= skill_end; i++) {
		class_skillprf_indices.push_back(i);
	}
	clss_skill_selec_no = 3;

	simple_wpns();
	wpn_prof.at(33) = selected;
	wpn_prof.at(21) = selected;
	wpn_prof.at(25) = selected;
	wpn_prof.at(27) = selected;

	saving_throws.at(1) = selected;
	saving_throws.at(5) = selected;

	lt_armor();

	//musical_instrs_selec();
}

void proficiency::cleric() {

	class_skillprf_indices = cleric_sk;
	clss_skill_selec_no = 2;

	simple_wpns();

	//no tool profs

	saving_throws.at(4) = selected;
	saving_throws.at(5) = selected;

	lt_armor();
	med_armor();
	armor_prof.at(12) = selected;
}

void proficiency::druid() {

	class_skillprf_indices = druid_sk;
	clss_skill_selec_no = 2;

	wpn_prof.at(0) = selected;
	wpn_prof.at(1) = selected;
	wpn_prof.at(11) = selected;
	wpn_prof.at(4) = selected;
	wpn_prof.at(6) = selected;
	wpn_prof.at(7) = selected;
	wpn_prof.at(26) = selected;
	wpn_prof.at(8) = selected;
	wpn_prof.at(13) = selected;
	wpn_prof.at(9) = selected;

	tlprf_map.at(23).first = selected;
	tlprf_map.at(23).second = clss_prof_incl;

	saving_throws.at(3) = selected;
	saving_throws.at(4) = selected;
	//druids will not use armor or shields with metal apparently
	lt_armor();
	med_armor();
	armor_prof.at(12) = selected;
}

void proficiency::fighter() {

	class_skillprf_indices = fighter_sk;
	clss_skill_selec_no = 2;

	simple_wpns();
	martial_wpns();

	//no tool profs

	saving_throws.at(0) = selected;
	saving_throws.at(2) = selected;

	pan_armor();
}


void proficiency::monk() {

	class_skillprf_indices = monk_sk;
	clss_skill_selec_no = 2;

	simple_wpns();
	wpn_prof.at(27) = selected;

	artisans_tls_selec(clss_prof);
	musical_instrs_selec(clss_prof);
	class_tool_selec_no = 1;

	saving_throws.at(0) = selected;
	saving_throws.at(1) = selected;

	//no armor profs
}

void proficiency::paladin() {

	class_skillprf_indices = paladin_sk;
	clss_skill_selec_no = 2;

	simple_wpns();
	martial_wpns();

	// no tool profs

	saving_throws.at(4) = selected;
	saving_throws.at(5) = selected;

	pan_armor();
}

void proficiency::ranger() {

	class_skillprf_indices = ranger_sk;
	clss_skill_selec_no = 3;

	simple_wpns();
	martial_wpns();

	//no tool profs

	saving_throws.at(0) = selected;
	saving_throws.at(1) = selected;

	lt_armor();
	med_armor();
	armor_prof.at(12) = selected;
}

void proficiency::rogue() {

	class_skillprf_indices = rogue_sk;
	clss_skill_selec_no = 4;

	simple_wpns();
	wpn_prof.at(33) = selected;
	wpn_prof.at(21) = selected;
	wpn_prof.at(25) = selected;
	wpn_prof.at(27) = selected;

	tlprf_map.at(36).first = selected;
	tlprf_map.at(36).second = clss_prof_incl;

	saving_throws.at(1) = selected;
	saving_throws.at(3) = selected;

	lt_armor();
}

void proficiency::sorcerer() {

	class_skillprf_indices = sorcerer_sk;
	clss_skill_selec_no = 2;

	wpn_prof.at(1) = selected;
	wpn_prof.at(11) = selected;
	wpn_prof.at(13) = selected;
	wpn_prof.at(7) = selected;
	wpn_prof.at(10) = selected;

	// no tool profs

	saving_throws.at(2) = selected;
	saving_throws.at(5) = selected;

	// no armor profs
}

void proficiency::warlock() {

	class_skillprf_indices = warlock_sk;
	clss_skill_selec_no = 2;

	simple_wpns();

	// no tool profs

	saving_throws.at(4) = selected;
	saving_throws.at(5) = selected;

	lt_armor();
}

void proficiency::wizard() {

	class_skillprf_indices = wizard_sk;
	clss_skill_selec_no = 2;

	wpn_prof.at(1) = selected;
	wpn_prof.at(11) = selected;
	wpn_prof.at(13) = selected;
	wpn_prof.at(7) = selected;
	wpn_prof.at(10) = selected;

	// no tool profs

	saving_throws.at(3) = selected;
	saving_throws.at(4) = selected;

	// no armor profs
}

void proficiency::acolyte() {

	skillprf_map.at(10).first = selected;
	skillprf_map.at(8).first = selected;
	skillprf_map.at(10).second = bckg_prof_incl;
	skillprf_map.at(8).second = bckg_prof_incl;
}

void proficiency::charlatan() {

	skillprf_map.at(14).first = selected;
	skillprf_map.at(2).first = selected;
	skillprf_map.at(14).second = bckg_prof_incl;
	skillprf_map.at(2).second = bckg_prof_incl;

	tlprf_map.at(17).first = selected;
	tlprf_map.at(18).first = selected;
	tlprf_map.at(17).second = bckg_prof_incl;
	tlprf_map.at(18).second = bckg_prof_incl;

}

void proficiency::criminal() {

	skillprf_map.at(14).first = selected;
	skillprf_map.at(3).first = selected;
	skillprf_map.at(14).second = bckg_prof_incl;
	skillprf_map.at(3).second = bckg_prof_incl;

	gaming_selec(bckg_prof);

	tlprf_map.at(36).first = selected;
	tlprf_map.at(36).second = bckg_prof_incl;
}

void proficiency::entertainer() {

	skillprf_map.at(1).first = selected;
	skillprf_map.at(16).first = selected;
	skillprf_map.at(1).second = bckg_prof_incl;
	skillprf_map.at(16).second = bckg_prof_incl;

	musical_instrs_selec(bckg_prof);

	tlprf_map.at(17).first = selected;
	tlprf_map.at(17).second = bckg_prof_incl;

}

void proficiency::folk_hero() {

	skillprf_map.at(9).first = selected;
	skillprf_map.at(13).first = selected;
	skillprf_map.at(9).second = bckg_prof_incl;
	skillprf_map.at(13).second = bckg_prof_incl;

	artisans_tls_selec(bckg_prof);

}

void proficiency::guild_artisan() {

	skillprf_map.at(10).first = selected;
	skillprf_map.at(17).first = selected;
	skillprf_map.at(10).second = bckg_prof_incl;
	skillprf_map.at(17).second = bckg_prof_incl;

	artisans_tls_selec(bckg_prof);

}

void proficiency::hermit() {

	skillprf_map.at(11).first = selected;
	skillprf_map.at(8).first = selected;
	skillprf_map.at(11).second = bckg_prof_incl;
	skillprf_map.at(8).second = bckg_prof_incl;

	tlprf_map.at(23).first = selected;
	tlprf_map.at(23).second = bckg_prof_incl;
}

void proficiency::noble() {

	skillprf_map.at(5).first = selected;
	skillprf_map.at(17).first = selected;
	skillprf_map.at(5).second = bckg_prof_incl;
	skillprf_map.at(17).second = bckg_prof_incl;

	gaming_selec(bckg_prof);
}

void proficiency::outlander() {

	skillprf_map.at(0).first = selected;
	skillprf_map.at(13).first = selected;
	skillprf_map.at(0).second = bckg_prof_incl;
	skillprf_map.at(13).second = bckg_prof_incl;

	musical_instrs_selec(bckg_prof);
}

void proficiency::sage() {
	skillprf_map.at(4).first = selected;
	skillprf_map.at(5).first = selected;
	skillprf_map.at(4).second = bckg_prof_incl;
	skillprf_map.at(5).second = bckg_prof_incl;
}

void proficiency::sailor() {
	skillprf_map.at(0).first = selected;
	skillprf_map.at(12).first = selected;
	skillprf_map.at(0).second = bckg_prof_incl;
	skillprf_map.at(12).second = bckg_prof_incl;

	tlprf_map.at(34).first = selected;
	tlprf_map.at(34).second = bckg_prof_incl;
}

void proficiency::soldier() {

	skillprf_map.at(0).first = selected;
	skillprf_map.at(15).first = selected;
	skillprf_map.at(0).second = bckg_prof_incl;
	skillprf_map.at(15).second = bckg_prof_incl;

	gaming_selec(bckg_prof);

}

void proficiency::urchin() {

	skillprf_map.at(2).first = selected;
	skillprf_map.at(3).first = selected;
	skillprf_map.at(2).second = bckg_prof_incl;
	skillprf_map.at(3).second = bckg_prof_incl;

	tlprf_map.at(17).first = selected;
	tlprf_map.at(36).first = selected;
	tlprf_map.at(17).second = bckg_prof_incl;
	tlprf_map.at(36).second = bckg_prof_incl;
}

void proficiency::dwarf() {
	wpn_prof.at(14) = selected;
	wpn_prof.at(3) = selected;
	wpn_prof.at(5) = selected;
	wpn_prof.at(30) = selected;

	dwarf_arttools_selec();
	spec_tool_selec_no = 1;

}

void proficiency::mtn_dwarf() {
	dwarf();
	lt_armor();
	med_armor();
}

void proficiency::high_wood_elf() {

	skillprf_map.at(12).first = selected;
	skillprf_map.at(12).second = spec_prof_incl;

	wpn_prof.at(21) = selected;
	wpn_prof.at(27) = selected;
	wpn_prof.at(12) = selected;
	wpn_prof.at(35) = selected;
}

void proficiency::darkelf() {

	skillprf_map.at(12).first = selected;
	skillprf_map.at(12).second = spec_prof_incl;

	wpn_prof.at(25) = selected;
	wpn_prof.at(27) = selected;
	wpn_prof.at(33) = selected;
}

void proficiency::rock_gnome() {

	tlprf_map.at(14).first = selected;
	tlprf_map.at(14).second = spec_prof_incl;
}

void proficiency::half_elf() {
	for (int i = skill_begin; i <= skill_end; i++) {
		species_skillprf_indices.push_back(i);
	}
	spec_skill_selec_no = 2;
}

void proficiency::half_orc() {
	skillprf_map.at(15).first = selected;
	skillprf_map.at(15).second = spec_prof_incl;
}