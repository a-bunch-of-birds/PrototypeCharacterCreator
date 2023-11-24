#ifndef COMMAND_H
#define COMMAND_H

//#include "abilityscore.h"
#include "character.h"
#include "file_dialogue.h"

class IComm {
private:

public:
	virtual ~IComm() {}
	virtual void Execute() const = 0;
	//virtual void Undo() const = 0;
};

class RollComm : public IComm {
private:
	Character* objptr;
public:
	RollComm(Character* receiver) : objptr(receiver) {}
	void Execute() const override;
	//void Undo() const override;
};

/*
class ResortComm : public IComm {
private:
	Character* objptr;
public:
	ResortComm(Character* receiver) : objptr(receiver) {}
	void Execute() const override;
};
*/
/*
class ClrComm : public IComm {
private:
	Character* objptr;
public:
	ClrComm(Character* receiver) : objptr(receiver) {}
	void Execute() const override;
};
*/

class MTwisterComm : public IComm {
private:
	Character* objptr;
public:
	MTwisterComm(Character* receiver) : objptr(receiver) {}
	void Execute() const override;
};

class CommitRollComm : public IComm {
private:
	Character* objptr;
public:
	CommitRollComm(Character* receiver) : objptr(receiver) {}
	void Execute() const override;
	//void Undo() const override;
};

class CommitPointBuyComm : public IComm {
private:
	Character* objptr;
	//std::vector<int> pb_stor{0, 0, 0, 0, 0, 0};
public:
	CommitPointBuyComm(Character* receiver) : objptr(receiver) {}
	//void Set_Params(std::vector<int> sc);
	void Execute() const override;
};

class PointPurchButtonComm : public IComm {
private:
	Character* objptr;
	char choice = 0;
	int index = 0;
public:
	PointPurchButtonComm(Character* receiver) : objptr(receiver) {}
	void Set_Params(char choice_input, int index_input);
	void Execute() const override;
};

class SpecSelecComm : public IComm {
private:
	Character* objptr;
	int spec_selec_index = 0;
	//char half_elf_plus_a = 'z';
	//char half_elf_plus_b = 'z';
	int half_elf_plus_a = -1;
	int half_elf_plus_b = -1;
public:
	SpecSelecComm(Character* receiver) : objptr(receiver) {}
	//void Set_Params(int index, char a, char b);
	bool No_Empties(); 
	void Set_Params(int index, int a = -1, int b = -1);
	void Execute() const override;
};

class SpecProfComm : public IComm {
private:
	Character* objptr;
	//INDICES FOR HALF-ELF ABILITY BUFFS
	//int ab_idx_one = 0;
	//int ab_idx_two = 0;
	//int sk_idx_three = 0;
	//int sk_idx_four = 0;
	int selec_index = 0;
	
public:
	SpecProfComm(Character* receiver) : objptr(receiver) {}
	//void Set_Params(int index, int idx_one = 19, int idx_two = 19);
	void Set_Params(int index);
	void Execute() const override;
};

class ClssProfComm : public IComm {
private:
	Character* objptr;
	//INDICES FOR HALF-ELF ABILITY BUFFS
	//int ab_idx_one = 0;
	//int ab_idx_two = 0;
	//int sk_idx_three = 0;
	//int sk_idx_four = 0;
	int selec_index = 0;

public:
	ClssProfComm(Character* receiver) : objptr(receiver) {}
	//void Set_Params(int index, int idx_one = 19, int idx_two = 19);
	void Set_Params(int index);
	void Execute() const override;
};

/*
class ToolProfComm : public IComm {
private: 
	Character* objptr;
public:
	ToolProfComm(Character* receiver) : objptr(receiver) {}
	void Execute() const override;
};
*/
class ClassSelecComm : public IComm {
private:
	Character* objptr;
	int index = 0;
public:
	ClassSelecComm(Character* receiver) : objptr(receiver) {}
	void Set_Params(int ind);
	void Execute() const override;
	//void Undo() const override;

};

class LevelSelectComm : public IComm {
private:
	Character* objptr;
public:
	LevelSelectComm(Character* receiver) : objptr(receiver) {}
	//void Set_Params(int level);
	void Execute() const override;
};

class LevelUpComm : public IComm {
private:
	Character* objptr;
	int str_l = 0;
	int dex_l = 0;
	int con_l = 0;
	int intl_l = 0;
	int wis_l = 0;
	int cha_l = 0;
public:
	LevelUpComm(Character* receiver) : objptr(receiver) {}
	void Set_Params(int str, int dex, int con, int intl, int wis, int cha);
	void Execute() const override;
	//void Undo() const override;
};

class BckgComm : public IComm {
private:
	Character* objptr;
	int index = 0;
public:
	BckgComm(Character* receiver) : objptr(receiver) {}
	void Set_Params(int index);
	void Execute() const override;
};

/*
class CommitLvlComm : public IComm {
private:
	Abilityscore* objptr;
public:
	CommitLvlComm(Abilityscore* receiver) : objptr(receiver) {}
	void Execute() const override;
};
*/

class SaveComm : public IComm {
private:
	file_dialogue* objptr;
	std::string filename_obj;
	Character* character_obj;
public:
	SaveComm(file_dialogue* receiver, Character* cobj) : objptr(receiver), character_obj(cobj) {}
	void SetParams(std::string filename);
	void Execute() const override;
};

class OpenComm : public IComm {
private: 
	file_dialogue* objptr;
	std::string filename_obj;
	Character* character_obj;
public:
	OpenComm(file_dialogue* receiver, Character* cobj) : objptr(receiver), character_obj(cobj) {}
	void SetParams(std::string fname);
	void Execute() const override;
};

class Invoker {
private:
	IComm* cmd;
public:
	Invoker(IComm* icommand) : cmd(icommand) {}
	~Invoker() {}
	void change_rec(IComm* icommand);
	void invoke();
};

#endif COMMAND_H