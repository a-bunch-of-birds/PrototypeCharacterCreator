#include "command.h"
//#include "abilityscore.h"
//#include "character.h"


void RollComm::Execute() const {
	objptr->roll_abilities();
	std::cout << "RollComm -> Execute() -> receiver.sextuple_score()" << std::endl;
};

/*
void RollComm::Undo() const {
	objptr->clear_init();
	std::cout << "RollComm -> Undo() -> receiver.clear_init()" << std::endl;
}
*/
/*
void ResortComm::Execute() const {
	objptr->resort_init();
	std::cout << "ResortComm -> Execute() -> receiver.resort_init_scores()" << std::endl;
}
*/
/*
//this Clr command is deprecated, as the usefulness of filling the init_scores vector with zeroes has been made moot
void ClrComm::Execute() const {
	objptr->clear_init();
	std::cout << "ClrComm -> Execute() -> receiver.clear_init_scores()" << std::endl;
}
*/

void MTwisterComm::Execute() const {
	objptr->roll_abilities_mersenne_twister();
	std::cout << "RollComm -> Execute() -> sextuple_score_mersenne_twister()" << std::endl;
}

void CommitRollComm::Execute() const {
	objptr->commit_abilities();
	std::cout << "CommitRollComm -> Execute() -> receiver.commit_scores()" << std::endl;
}
/*
void CommitPointBuyComm::Set_Params(std::vector<int> vc) {
	pb_stor = vc;
}
*/
void CommitPointBuyComm::Execute() const {
	//objptr->retr_point_buy() = pb_stor;
	objptr->commit_abilities_pointbuy();
	std::cout << "CommitPointBuyComm -> Execute() -> receiver.commit_abilities_pointbuy()" << std::endl;
}

void PointPurchButtonComm::Set_Params(char choice_input, int index_input) {
	choice = choice_input;
	index = index_input;
	std::cout << "CommitPointPurchComm -> Set_Params(" << choice << ", " << index << ")" << std::endl;
}

void PointPurchButtonComm::Execute() const {
	objptr->point_purchase(choice, index);
	
}

/*
void CommitLvlComm::Execute() const {
	objptr->clr_init();
	objptr->pushback_init(str_up);
	objptr->pushback_init(dex_up);
	objptr->pushback_init(con_up);
	objptr->pushback_init(intl_up);
	objptr->pushback_init(wis_up);
	objptr->pushback_init(cha_up);
}
*/
/*
void SpecSelecComm::Set_Params(int index, char a, char b) {
	spec_selec_index = index;
	half_elf_plus_a = a;
	half_elf_plus_b = b;
	std::cout << "SpecSelecComm -> Set_Params(" << spec_selec_index << ", " << half_elf_plus_a << ", " << half_elf_plus_b << ")" << std::endl;
}
*/

bool SpecSelecComm::No_Empties() {
	return true;
}

void SpecSelecComm::Set_Params(int index, int a, int b) {
	spec_selec_index = index;
	half_elf_plus_a = a;
	half_elf_plus_b = b;
	objptr->halfelf_params(half_elf_plus_a, half_elf_plus_b);
	std::cout << "SpecSelecComm -> Set_Params(" << spec_selec_index << ", " << half_elf_plus_a << ", " << half_elf_plus_b << ")" << std::endl;
}

void SpecSelecComm::Execute() const {
	//objptr->species_selec(spec_selec_index, half_elf_plus_a, half_elf_plus_b);
	objptr->species_selec(spec_selec_index);
	std::cout << "SpecSelecComm -> Execute() -> receiver.species_selec(" << spec_selec_index << ")" << std::endl;
}

void SpecProfComm::Set_Params(int index) {
	//ab_idx_one = idx_one;
	//ab_idx_two = idx_two;
	//sk_idx_three = idx_three;
	//sk_idx_four = idx_four;
	selec_index = index;
	//std::cout << "SpecProfComm -> Set_Params(" << index << ", " << idx_one << ", " << idx_two << ")" << std::endl;
	std::cout << "SpecProfComm -> Set_Params(" << index << ")" << std::endl;
}

void SpecProfComm::Execute() const {
	//objptr->prof_dist(selec_index, ab_idx_one, ab_idx_two);
	//std::cout << "SpecProfComm -> Execute() -> receiver.prof_dist(" << selec_index << ", " << ab_idx_one << ", " << ab_idx_two << std::endl;
	objptr->spec_prof_dist(selec_index);
	std::cout << "SpecProfComm -> Execute() -> receiver.spec_prof_dist(" << selec_index << ")" << std::endl;
}

void ClssProfComm::Set_Params(int index) {
	//ab_idx_one = idx_one;
	//ab_idx_two = idx_two;
	//sk_idx_three = idx_three;
	//sk_idx_four = idx_four;
	selec_index = index;
	//std::cout << "ProfComm -> Set_Params(" << index << ", " << idx_one << ", " << idx_two << ")" << std::endl;
	std::cout << "ProfComm -> Set_Params(" << index << ")" << std::endl;
}

void ClssProfComm::Execute() const {
	//objptr->prof_dist(selec_index, ab_idx_one, ab_idx_two);
	objptr->clss_prof_dist(selec_index);
	//std::cout << "ProfComm -> Execute() -> receiver.prof_dist(" << selec_index << ", " << ab_idx_one << ", " << ab_idx_two << std::endl;
	std::cout << "ProfComm -> Execute() -> receiver.clss_prof_dist(" << selec_index << ")" << std::endl;
}
/*
void ToolProfComm::Execute() const {
	objptr
}
*/
void ClassSelecComm::Set_Params(int ind) {
	index = ind;
	std::cout << "ClassSelecComm -> Set_Params(" << index << ")" << std::endl;
}

void ClassSelecComm::Execute() const {
	objptr->character_selec(index);
	std::cout << "ClassSelecComm -> Execute() -> receiver.character_selec(" << index << ")" << std::endl;
}

void LevelSelectComm::Execute() const {
	objptr->proficiency_up();
	std::cout << "LevelSelectComm -> Execute() -> receiver.proficiency_up()" << std::endl;
}

void LevelUpComm::Set_Params(int str, int dex, int con, int intl, int wis, int cha) {
	str_l = str;
	dex_l = dex;
	con_l = con;
	intl_l = intl;
	wis_l = wis;
	cha_l = cha;
	std::cout << "LevelUpComm -> Set_Params(" << str_l << ", " << dex_l << ", " << con_l << ", " << intl_l << ", " << wis_l << ", " << cha_l << ")" << std::endl;
}

void LevelUpComm::Execute() const {
	objptr->clear_init();
	objptr->retr_absumm().str = str_l;
	objptr->retr_absumm().dex = dex_l;
	objptr->retr_absumm().con = con_l;
	objptr->retr_absumm().intl = intl_l;
	objptr->retr_absumm().wis = wis_l;
	objptr->retr_absumm().cha = cha_l;
	objptr->ability_mods();
	objptr->armor_class();
	std::cout << "LevelUpComm -> Execute()" << std::endl;
	std::cout << " -> " << "clear_init()" << std::endl;
	std::cout << " -> " << "retr_absumm().any_ability_scores_needed" << std::endl;
	std::cout << " -> " << "ability_mods()" << std::endl;
	std::cout << " -> " << "armor_class()" << std::endl;
}

void BckgComm::Set_Params(int ind) {
	index = ind;
	std::cout << "BckgComm -> Set_Params(" << index << ")" << std::endl;
}

void BckgComm::Execute() const {
	//objptr->prof_dist(index);
	objptr->bckg_prof_dist(index);
	std::cout << "BckgComm -> Execute() -> bckg_prof_dist(" << index << ")" << std::endl;
}

void SaveComm::SetParams(std::string filename) {
	filename_obj = filename;

	std::cout << "SaveComm -> SetParams(" << filename << ")" << std::endl;
}

void SaveComm::Execute() const {

	objptr->save_file(filename_obj, character_obj);


	std::cout << "SaveComm -> Execute()" << std::endl;

}

void OpenComm::SetParams(std::string fname) {
	filename_obj = fname;
	std::cout << "OpenComm -> SetParams(" << filename_obj << ")" << std::endl;
}

void OpenComm::Execute() const {
	objptr->open_file(filename_obj, character_obj);
	std::cout << "OpenComm -> Execute()" << std::endl;
}

void Invoker::change_rec(IComm* icommand) {
	cmd = icommand;
	std::cout << "Invoker -> change_rec(" << icommand << ")" << std::endl;
}

void Invoker::invoke() {
	cmd->Execute();
	std::cout << "Invoker -> cmd -> Execute()" << std::endl;
}
