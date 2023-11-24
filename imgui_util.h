#ifndef IMGUI_UTIL_H
#define IMGUI_UTIL_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


/*
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
*/
#include <vector>
#include <algorithm>

//#include "abilityscore.h"
//#include "species.h"
//#include "charclass.h"
#include "command.h"
#include "character.h"
//#include "file_dialogue.h"
#include <iterator>

class ImGuiUtil {
private:
	//reviewed and reorganized
	bool rng_select = false;
	bool disabled_marker = false; //switch to true
	
	bool swap_disabled = false; // disables user ability to reorganize scores once rolls have been committed
	bool press_to_roll = false; //simple bool toggle for when roll button is pressed
	bool three_rolls = false; //disables the roll button after three rolls
	
	int srand_mersenne = 0;
	
	bool is_commit_clicked = false;
	int abscore_total = 0;
	bool lvl_picked = false;
	
	//three_rollctr no longer needed
	//int three_rollctr = 0; //simple roll counter for 
	
	//below is for sequential window triggering
	bool abscore_complete = false;
	bool species_picked = false; //disables Species Selection console once user commits their choice
	bool clss_picked = false;

	bool abroll = false;
	bool pointbuy = false;


	//for the point purchase function
	struct point_purchase {
		int ppscore = 8;
		int ppcost = 0;
	};
	
	const point_purchase purchase_stairs[9] = {
		{8, 0},
		{9, 1},
		{10, 1},
		{11, 1},
		{12, 1},
		{13, 1},
		{14, 2},
		{15, 2},
		{0, 0} //we add one to the array of structs so the cutoff bools can access the next value without going out of bounds
	};
	int strppm = 0;
	int dexppm = 0;
	int conppm = 0; 
	int intlppm = 0; 
	int wisppm = 0;
	int chappm = 0;
	bool strcutoff = false;
	bool dexcutoff = false;
	bool concutoff = false;
	bool intlcutoff = false;
	bool wiscutoff = false;
	bool chacutoff = false;

	const int purchmin = 8;
	const int purchmax = 15;
	//int purchtotal = 0;
	const int purchconstant = 27;
	int purchtotal = 27;
	int purchspent = 0;
	std::vector<int> purch{0, 0, 0, 0, 0, 0};
	std::vector<int> purchdisplay{8, 8, 8, 8, 8, 8};

	
	
public:
	static void HelpMarker(const char* desc);
	void Init(GLFWwindow* window);
	void NewFrame();
	std::vector<int>& Retrieve_Init(Character& obj);
	void Clr_Init(Character& obj);
	void Sort_Init(Character& obj);
	void HistoUndo(bool& swap_disabled, bool& threerolls, int& three_roll_ctr, Character& obj);
	void Histogram(Character& obj);
	void Avail_Rolls(Character& obj);
	void SpeciesList(Character& obj, Invoker* inv);
	//void SpeciesSelection(Character& obj, Invoker* inv);
	void Species_Selection(Character& obj, Invoker* inv);
	void ClassList(Character& obj, Invoker* inv);
	void ClassSelection(Character& obj, Invoker* inv);
	void LevelUp(Character& obj, Invoker* cmt_inv);
	void Background(Character& obj, Invoker* inv);
	void Species_Tool_Proficiencies(Character& obj);
	void Class_Tool_Proficiencies(Character& obj);
	void Bckg_Tool_Proficiencies(Character& obj);
	void Tool_Wpn_Proficiencies(Character& obj, Invoker* inv);
	void Skill_Proficiencies(Character& obj, Invoker* inv);
	void BeyondFirstLevel(Character& obj, Invoker* cmt_inv);
	void SkillsProf(proficiency& prof_obj);
	void Weaponry(Character& obj);
	void ScoreDisplay(Character& obj);
	void Points_or_Roll();
	void AbilityScorePkg(Character& obj, RollComm& roll_bttn, MTwisterComm& roll_bttn_mt, CommitRollComm& cmt, Invoker* inv);
	int& Retr_PurchTotal(Character& obj);
	int& Retr_PurchSpent(Character& obj);
	int Retr_PurchMap_Cost(Character& obj, int key);
	void PurchaseDecr(Character& obj, PointPurchButtonComm& prs, Invoker* inv, int button_id, int index);
	void PurchaseIncr(Character& obj, PointPurchButtonComm& prs, Invoker* inv, int button_id, int index);
	void PointPurchase(Character& obj, PointPurchButtonComm& prs, CommitPointBuyComm& pcmt, Invoker* inv);
	//void PointPurchaseX(Character& obj, PointPurchButtonComm& prs, CommitPointBuyComm& pcmt, Invoker* inv);
	//void PointPurchase(Character& obj, CommitPointBuyComm& cmt, Invoker* inv);
	void SpeciesPkg(Character& obj, Invoker* inv);
	//virtual void Update(int& abscore_total, bool mode, bool& is_commit_clicked, Character& obj, Invoker res_inv, Invoker clr_inv, Invoker roll_inv, Invoker cmt_inv);
	void SideBar(Character& obj);
	void WindowPos(int mode);
	void WindowSize(int mode);
	virtual void Update(bool mode, Character& obj, file_dialogue& handler);
	void Render();
	void Shutdown();
};

#endif IMGUI_UTIL_H