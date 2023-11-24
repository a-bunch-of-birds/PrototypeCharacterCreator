#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iterator>

#include "character.h"

namespace fs = std::filesystem;

class file_dialogue
{
private:
	std::vector<std::string> flib{};
	fs::path curr_dir = fs::current_path();
public:
	file_dialogue();
	~file_dialogue();
	std::vector<std::string> retr_flib();
	void set_to_flib(std::string filename);
	void export_flib();
	void import_flib();
	void new_file(std::string filename);
	void transfer_data(Character* chaptr);
	void parse_file(std::string filename, Character* chaptr);
	void save_file(std::string filename, Character* chaptr);
	void del_file(std::string fname);
	void rename_file();
	void open_file(std::string fname, Character* chaptr);
	void test_fs();


};

