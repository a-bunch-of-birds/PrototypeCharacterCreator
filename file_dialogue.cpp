#include "file_dialogue.h"

/*
STRUCTURE OF SAVE FILE:

ab (signals to parser that it is reading from the ability summary struct)
13 ints follow

sp (signals to parser that it is reading from the species summary struct)

cl (signals to parser that it is reading from the class summary struct)


*/


file_dialogue::file_dialogue() {};

file_dialogue::~file_dialogue() {};

std::vector<std::string> file_dialogue::retr_flib() {

	return flib;

};

void file_dialogue::set_to_flib(std::string filename) {

	flib.push_back(filename);
};

void file_dialogue::export_flib() {
	std::ofstream file;
	file.open("flib.txt", std::ofstream::trunc);
	if (file.is_open()) {
		for (auto a : flib) {
			file << a << "\n";
		}
		file.close();
	}
	else {
		std::cout << "file not found / corrupted / bad path" << std::endl;
	}
}

void file_dialogue::import_flib() {
	std::ifstream file;
	std::string line;
	file.open("flib.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			set_to_flib(line);
		}
		file.close();
	}
	else {
		std::cout << "unable to import flib.txt" << std::endl;
	}
}

void file_dialogue::new_file(std::string filename) {
	
	std::ofstream file;
	file.open(filename);
	if (file.is_open()) {
		set_to_flib(filename);
		file.close();
	}
	else {
		std::cout << "could not create new file" << std::endl;
	}
};

void file_dialogue::transfer_data(Character* chaptr) {

}

void file_dialogue::parse_file(std::string filename, Character* chaptr) {

	std::ifstream filestream(filename);
	std::string line;
	std::string str, dex, con, intl, wis, cha, strabm, dexabm, conabm, intlabm, wisabm, chaabm, ac;
	/*
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
	int ac = 0;
	*/
	std::cout << filename << std::endl;
	if (filestream.is_open()) {
		std::cout << "file is open" << std::endl;
		while (getline(filestream, line)) {
			if (!line.empty()) {
				//std::string str, dex, con, intl, wis, cha, strabm, dexabm, conabm, intlabm, wisabm, chaabm, ac;
				if (line.substr(0, 1) == "a") {
					//std::stringstream abilities(line.substr(0, 2));
					//std::stringstream abilities(line.substr(2));
					if (line.substr(1, 1) == "s") {
						//std::stringstream ab_str(3);
						std::stringstream abilities(line.substr(2));
						abilities >> str;
						//ab_str >> str;
					}
					else if (line.substr(1, 1) == "d") {
						std::stringstream abilities(line.substr(2));
						abilities >> dex;
					}
					else if (line.substr(1, 1) == "c") {
						std::stringstream abilities(line.substr(2));
						abilities >> con;
					}
					else if (line.substr(1, 1) == "i") {
						std::stringstream abilities(line.substr(2));
						abilities >> intl;
					}
					else if (line.substr(1, 1) == "w") {
						std::stringstream abilities(line.substr(2));
						abilities >> wis;
					}
					else if (line.substr(1, 1) == "r") {
						std::stringstream abilities(line.substr(2));
						abilities >> cha;
					}
					else {
						std::cout << "error reading abilities" << std::endl;
					}
				}
				else if (line.substr(0, 1) == "m") {
					//std::stringstream abmods(line.substr(0, 2));
					
					if (line.substr(1, 1) == "s") {
						std::stringstream abmods(line.substr(2));
						abmods >> strabm;
					}
					else if (line.substr(1, 1) == "d") {
						std::stringstream abmods(line.substr(2));
						abmods >> dexabm;
					}
					else if (line.substr(1, 1) == "c") {
						std::stringstream abmods(line.substr(2));
						abmods >> conabm;
					}
					else if (line.substr(1, 1) == "i") {
						std::stringstream abmods(line.substr(2));
						abmods >> intlabm;
					}
					else if (line.substr(1, 1) == "w") {
						std::stringstream abmods(line.substr(2));
						abmods >> wisabm;
					}
					else if (line.substr(1, 1) == "r") {
						std::stringstream abmods(line.substr(2));
						abmods >> chaabm;
					}
					else {
						std::cout << "error reading ability mods" << std::endl;
					}
				}
				else if (line.substr(0, 1) == "r") {
					//std::stringstream aclass(line.substr(0, 2));
					if (line.substr(1, 1) == "r") {
						std::stringstream aclass(line.substr(2));
						aclass >> ac;
					}
					else {
						std::cout << "error reading AC" << std::endl;
					}
				}
				else {}
			}
			else {}
		}
		chaptr->retr_absumm().str = std::stoi(str);
		chaptr->retr_absumm().dex = std::stoi(dex);
		chaptr->retr_absumm().con = std::stoi(con);
		chaptr->retr_absumm().intl = std::stoi(intl);
		chaptr->retr_absumm().wis = std::stoi(wis);
		chaptr->retr_absumm().cha = std::stoi(cha);
		chaptr->retr_absumm().strabm = std::stoi(strabm);
		chaptr->retr_absumm().dexabm = std::stoi(dexabm);
		chaptr->retr_absumm().conabm = std::stoi(conabm);
		chaptr->retr_absumm().intlabm = std::stoi(intlabm);
		chaptr->retr_absumm().wisabm = std::stoi(wisabm);
		chaptr->retr_absumm().chaabm = std::stoi(chaabm);
		chaptr->retr_absumm().armor_class = std::stoi(ac);
		/*
		chaptr->retr_absumm().str = str;
		chaptr->retr_absumm().dex = dex;
		chaptr->retr_absumm().con = con;
		chaptr->retr_absumm().intl = intl;
		chaptr->retr_absumm().wis = wis;
		chaptr->retr_absumm().cha = cha;
		chaptr->retr_absumm().strabm = strabm;
		chaptr->retr_absumm().dexabm = dexabm;
		chaptr->retr_absumm().conabm = conabm;
		chaptr->retr_absumm().intlabm = intlabm;
		chaptr->retr_absumm().wisabm = wisabm;
		chaptr->retr_absumm().chaabm = chaabm;
		chaptr->retr_absumm().armor_class = ac;
		*/
		filestream.close();
	}
	else {
		std::cout << "Unable to parse file" << std::endl;
	}
};

//void file_dialogue::set_save_state()

void file_dialogue::save_file(std::string filename, Character* chaptr) {

	new_file(filename);
	std::ofstream(file);
	file.open(filename);
	if (file.is_open()) {
		//write the ability summary to file
		//to-do: have to check if the values are initialized/full or not before writing
		//file << "ab" << "\n";

		file << "as" << chaptr->retr_absumm().str << "\n";
		file << "ad" << chaptr->retr_absumm().dex << "\n";
		file << "ac" << chaptr->retr_absumm().con << "\n";
		file << "ai" << chaptr->retr_absumm().intl << "\n";
		file << "aw" << chaptr->retr_absumm().wis << "\n";
		file << "ar" << chaptr->retr_absumm().cha << "\n";
		file << "ms" << chaptr->retr_absumm().strabm << "\n";
		file << "md" << chaptr->retr_absumm().dexabm << "\n";
		file << "mc" << chaptr->retr_absumm().conabm << "\n";
		file << "mi" << chaptr->retr_absumm().intlabm << "\n";
		file << "mw" << chaptr->retr_absumm().wisabm << "\n";
		file << "mr" << chaptr->retr_absumm().chaabm << "\n";
		file << "rr" << chaptr->retr_absumm().armor_class << "\n";

		/*
		file << "sp" << "\n";
		file << chaptr->retr_specsumm().species << "\n";
		file << chaptr->retr_specsumm().spec_name << "\n";
		file << chaptr->retr_specsumm().age << "\n";
		file << chaptr->retr_specsumm().alignment << "\n";
		file << chaptr->retr_specsumm().size << "\n";
		file << chaptr->retr_specsumm().speed << "\n";
		file << chaptr->retr_specsumm().darkvision << "\n";

		file << "cl" << "\n";
		file << chaptr->retr_csumm().clss << "\n";
		file << chaptr->retr_csumm().hit_dice << "\n";
		file << chaptr->retr_csumm().hd_count << "\n";
		file << chaptr->retr_csumm().hit_points << "\n";
		file << chaptr->retr_csumm().exp << "\n";
		file << chaptr->retr_csumm().level << "\n";
		file << chaptr->retr_csumm().prof_bonus << "\n";
		file << chaptr->retr_csumm().lvlup_abscore << "\n";
		file << chaptr->retr_csumm().spell_save_dc << "\n";
		file << chaptr->retr_csumm().spell_attk_mod << "\n";
		*/
		export_flib();

		file.close();
	}
	else {
		std::cout << "Cannot open file for save" << std::endl;
	}
	
};

void file_dialogue::del_file(std::string fname) {

	//std::uintmax_t console_msg = fs::remove(curr_dir / fname);
	std::uintmax_t console_msg = fs::remove(fname);
	std::cout << console_msg << std::endl;
	//std::vector<std::string>::iterator pos;
	
	//std::vector<std::string>::iterator it;
	//it = std::find(retr_flib().begin(), retr_flib().end(), fname);
	//flib.erase(it);
	flib.erase(std::find(retr_flib().begin(), retr_flib().end(), fname));
};

void file_dialogue::rename_file() {};

void file_dialogue::open_file(std::string fname, Character* chaptr) {
	
	parse_file(fname, chaptr);

};

void file_dialogue::test_fs() {
	
	
	
	
	
	//fs::path p = fs::current_path();
	//std::cout << "current path: " << p << std::endl;

}