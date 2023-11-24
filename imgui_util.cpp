#include "imgui_util.h"

void ImGuiUtil::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void ImGuiUtil::Init(GLFWwindow* window) {
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiUtil::NewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

std::vector<int>& ImGuiUtil::Retrieve_Init(Character& obj) {
	return obj.retr_init_rolls();
}

void ImGuiUtil::Clr_Init(Character& obj) {
	obj.clear_init();
}

void ImGuiUtil::Sort_Init(Character& obj) {
	
	std::sort(obj.retr_init_rolls().rbegin(), obj.retr_init_rolls().rend());

}
/*
void ImGuiUtil::HistoUndo(bool& swap_disabled, bool& threerolls, int& three_roll_ctr, Character& obj) {
	
	//NOTE: THIS IS EXPERIMENTAL AND SHOULD NOT BE EXPANDED INTO ACTUAL FUNCTIONALITY
	//- using three_roll_ctr as your marker and then decrementing it is not the intended final functionality
	//- proof of concept ONLY for undo/redo
	
	
	swap_disabled = false;
	if (three_roll_ctr > 0) {
		if (three_roll_ctr == 3) {
			//block here to keep the value
			threerolls = true;
		}
		else {
			three_roll_ctr--;
		}
	}
	if (three_roll_ctr == 0) {
		threerolls = false;
	}
	//std::sort(obj.retr_init_rolls().rbegin(), obj.retr_init_rolls().rend());
	Sort_Init(obj);
}
*/
void ImGuiUtil::Histogram(Character& obj) {
	
	float histogram_conv[6]; //we need floats for the integer values to show up on an ImGui histogram, so we're gonna static cast as float below and shove into a raw array

	for (int a = 0; a < Retrieve_Init(obj).size(); a++)
	{ 
		//histogram_conv[a] = obj.retr_init_rolls()[a];
		histogram_conv[a] = Retrieve_Init(obj)[a];
	}
	
	ImGui::PlotHistogram("##Rolled results", histogram_conv, IM_ARRAYSIZE(histogram_conv), 0, NULL, 1.0, 20.0, ImVec2(520.0f, 200.0f));
	
	ImGui::BeginDisabled(swap_disabled);
	int ymarker = 0;
	for (auto y : obj.retr_skills())
	{
		//int ymarker = 0;
		ImGui::PushID(ymarker);
		const char* sbuffer;
		sbuffer = y.c_str();
		ImGui::Button(sbuffer, ImVec2(80.0f, 60.0f));
		ImGui::PopID();
		ImGui::SameLine();
		ymarker++;
	}

	ImGui::Spacing();
	const char* swap_array[6]; //creating a swap array for drag and drop of const char*; will be filled with data from the init_scores vector

	//for (int v = 0; v < obj.retr_init_rolls().size(); v++)
	for (int v = 0; v < Retrieve_Init(obj).size(); v++)
	{
		//long laborious process to meet the const char* label reqs for buttons and text --
		//use sprintf_s to gt the ints to chars and shunt each int-to-char to the Button
		char ibuffer[50];
		int cti = 0;
		//cti = obj.retr_init_rolls()[v]; 
		cti = Retrieve_Init(obj)[v]; //we also need an explicit int to sort values
		sprintf_s(ibuffer, "%d", cti);
		const char* si = ibuffer;
		swap_array[v] = si;

		ImGui::PushID(v);

		ImGui::Button(si, ImVec2(80.0f, 60.0f));

		//*****DRAG DROP*****

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("PASS_PAYLOAD", &v, sizeof(int));
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PASS_PAYLOAD"))
			{
				IM_ASSERT(payload->DataSize == sizeof(int));
				int payload_v = *(const int*)payload->Data;
				const char* tmp = swap_array[v];
				swap_array[v] = swap_array[payload_v];
				swap_array[payload_v] = tmp;
				//std::iter_swap(obj.retr_init_rolls().begin() + payload_v, obj.retr_init_rolls().begin() + v); //swap the elements in the ACTUAL vector
				std::iter_swap(Retrieve_Init(obj).begin() + payload_v, Retrieve_Init(obj).begin() + v);

			}
			ImGui::EndDragDropTarget();
		}

		ImGui::PopID();
		ImGui::SameLine();
	}

	ImGui::EndDisabled();

	ImGui::Spacing();

	//an attempt to show ability modifiers along with scores -> looks like we abandoned that idea at some point
	/*
	int abm_array[6]; //set up ability modifier scores into an array so we can convert to const char*
	
	for (int abm_ticker = 0; abm_ticker < 6; abm_ticker++)
	{
		if (!obj.retr_init_rolls().empty())
		{
			abm_array[abm_ticker] = obj.imgui_abmod(obj.retr_init_rolls().at(abm_ticker));
		}
	}
	*/
}

void ImGuiUtil::Avail_Rolls(Character& obj) {
	int counter = 0;
	int push_id = 0;
	for (auto x : obj.retr_roll_hist()) {
		++counter;
		++push_id;
		ImGui::PushID(push_id);
		if (ImGui::Button("Select")) {
			//this should be included in the command pattern, but unsure what to do about passing 'x' std::vector<int>
			Clr_Init(obj);
			Retrieve_Init(obj) = x;
		}
		ImGui::PopID();
		ImGui::SameLine();
		ImGui::Text("<Roll %d> ", counter);
		ImGui::SameLine();
		for (auto y : x) {

			ImGui::Text("%d ", y);
			ImGui::SameLine();
		}
		
		ImGui::Spacing();
	}
	
}
//SpeciesList is now deprecated
/*
void ImGuiUtil::SpeciesList(Character& obj, Invoker* inv) {
	
	SpecSelecComm spec(&obj);
	
	const char* species_selec[] = 
	{ 
		" ", "Hill Dwarf", "Mountain Dwarf", "High Elf", "Wood Elf", "Dark Elf", "Lightfoot Halfling", "Stout Halfling", 
		"Human", "Dragonborn", "Forest Gnome", "Rock Gnome", "Half-Elf", "Half-Orc", "Tiefling" 
	};
	static int species_current_idx = 0;
	static bool species_picked = false;
	const char no_char_parameters = 'z';
	ImGui::BeginDisabled(species_picked);
	
	//ImGui::BeginDisabled(spec_toggle);
	//if (ImGui::BeginListBox("##listbox_species", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
	ImGui::Text("Species Selection: ");
	if (ImGui::BeginListBox("##listbox_species", ImVec2(425, 0)))
	{
		for (int n = 0; n < IM_ARRAYSIZE(species_selec); n++)
		{
			const bool is_selected = (species_current_idx == n);
			if (ImGui::Selectable(species_selec[n], is_selected))
				species_current_idx = n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
			//if (is_selected && ImGui::IsItemClicked(0))
			if (ImGui::IsItemClicked(0) && is_selected)
			{

				if (species_current_idx == 1)
				{
					// 'z' 'z' are the char parameters that are supplied as dead params if not used for the half elf 2-plus
					//hill dwarf
					
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					
					//obj.species_selec(1, no_char_parameters, no_char_parameters);
					species_picked = true;
					
				}
				if (species_current_idx == 2)
				{
					//mountain dwarf
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();

					//obj.species_selec(2, no_char_parameters, no_char_parameters);
					species_picked = true;
					
				}
				if (species_current_idx == 3)
				{
					//high elf
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					//obj.species_selec(3, no_char_parameters, no_char_parameters);
					species_picked = true;
					//ImGui::OpenPopup("Please select a halfling sub-species");
				}
				if (species_current_idx == 4)
				{
					//wood elf
					//obj.species_selec(4, no_char_parameters, no_char_parameters);
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					species_picked = true; 
				}
				if (species_current_idx == 5)
				{
					//dark elf
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					//obj.species_selec(5, no_char_parameters, no_char_parameters);
					species_picked = true;
				}
				if (species_current_idx == 6)
				{
					//lightfoot halfling
					//obj.species_selec(6, no_char_parameters, no_char_parameters);
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					species_picked = true;
					//ImGui::OpenPopup("Please select a gnome sub-species");
				}
				if (species_current_idx == 7)
				{
					//stout halfling
					//obj.species_selec(7, no_char_parameters, no_char_parameters);
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					species_picked = true;
					//ImGui::OpenPopup("Please select (2) ability scores to boost by +1");
				}
				if (species_current_idx == 8)
				{
					//human
					//obj.species_selec(8, no_char_parameters, no_char_parameters);
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					species_picked = true;
				}
				if (species_current_idx == 9)
				{
					//dragonborn
					//obj.species_selec(9, no_char_parameters, no_char_parameters);
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					species_picked = true;
				}
				if (species_current_idx == 10)
				{
					//forest gnome
					//obj.species_selec(10, no_char_parameters, no_char_parameters);
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					species_picked = true;
				}
				if (species_current_idx == 11)
				{
					//rock gnome
					//obj.species_selec(11, no_char_parameters, no_char_parameters);
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					species_picked = true;
				}
				if (species_current_idx == 12)
				{
					//half elf
					ImGui::OpenPopup("Please select (2) ability scores to boost by +1");
					//species_picked = true;
				}
				if (species_current_idx == 13)
				{
					//half orc
					//obj.species_selec(13, no_char_parameters, no_char_parameters);
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					species_picked = true;
				}
				if (species_current_idx == 14)
				{
					//tiefling
					//obj.species_selec(14, no_char_parameters, no_char_parameters);
					spec.Set_Params(species_current_idx, no_char_parameters, no_char_parameters);
					inv->change_rec(&spec);
					inv->invoke();
					species_picked = true;
				}
				
			}
		}
		
		//declaring the CENTER ImVec2 variable for the SetNextWindowPos function
		//this has a scope over all of the sub menus, and so only needs to be declared here for use down the line
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		if (ImGui::BeginPopupModal("Please select (2) ability scores to boost by +1", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{

			//static bool cha_a = false;
			//static bool cha_b = false;

			static bool halfelf_commit = false;

			ImGui::Text("Please select first score to +1:");
			ImGui::SameLine();
			HelpMarker("NOTE: (1) You cannot boost your charisma score further as it is already +2; (2) You cannot boost the same score twice!");

			static bool str_a = false;
			static bool str_b = false;
			static bool dex_a = false;
			static bool dex_b = false;
			static bool con_a = false;
			static bool con_b = false;
			static bool intl_a = false;
			static bool intl_b = false;
			static bool wis_a = false;
			static bool wis_b = false;

			static bool choice_a_disabled = false;
			static bool choice_b_disabled = true;
			ImGui::BeginDisabled(choice_a_disabled);

			ImGui::Checkbox("STR##1", &str_a);
			ImGui::Checkbox("DEX##1", &dex_a);
			ImGui::Checkbox("CON##1", &con_a);
			ImGui::Checkbox("INT##1", &intl_a);
			ImGui::Checkbox("WIS##1", &wis_a);
			//ImGui::Checkbox("CHA", &cha_a);

			if (str_a == true || dex_a == true || con_a == true || intl_a == true || wis_a == true)
			{
				choice_a_disabled = true;
				choice_b_disabled = false;
			}
			ImGui::EndDisabled();

			//removed this because it was redefining defined variables above for the same bools
			//static bool str_b = false;
			//static bool dex_b = false;
			//static bool con_b = false;
			//static bool intl_b = false;
			//static bool wis_b = false;
			//static bool choice_b_disabled = false;

			if (str_b == true || dex_b == true || con_b == true || intl_b == true || wis_b == true)
			{
				choice_b_disabled = true;
			}
			ImGui::BeginDisabled(choice_b_disabled);

			ImGui::Text("Please select second score to +1:");
			ImGui::BeginDisabled(str_a);
			ImGui::Checkbox("STR##2", &str_b);
			ImGui::EndDisabled();
			ImGui::BeginDisabled(dex_a);
			ImGui::Checkbox("DEX##2", &dex_b);
			ImGui::EndDisabled();
			ImGui::BeginDisabled(con_a);
			ImGui::Checkbox("CON##2", &con_b);
			ImGui::EndDisabled();
			ImGui::BeginDisabled(intl_a);
			ImGui::Checkbox("INT##2", &intl_b);
			ImGui::EndDisabled();
			ImGui::BeginDisabled(wis_a);
			ImGui::Checkbox("WIS##2", &wis_b);
			ImGui::EndDisabled();
			//ImGui::Checkbox("CHA", &cha_b);

			
			if (str_b == true || dex_b == true || con_b == true || intl_b == true || wis_b == true)
			{
				choice_b_disabled = true;
			}
			
			ImGui::EndDisabled();

			char a = 'z';
			char b = 'z';

			if (str_a == true)
			{
				a = 's';
			}
			else if (dex_a == true)
			{
				a = 'd';
			}
			else if (con_a == true)
			{
				a = 'c';
			}
			else if (intl_a == true)
			{
				a = 'i';
			}
			else if (wis_a == true)
			{
				a = 'w';
			}

			else
			{
				//std::cout << "char a conditionals have a problem" << std::endl;
			}

			if (str_b == true)
			{
				b = 's';
			}
			else if (dex_b == true)
			{
				b = 'd';
			}
			else if (con_b == true)
			{
				b = 'c';
			}
			else if (intl_b == true)
			{
				b = 'i';
			}
			else if (wis_b == true)
			{
				b = 'w';
			}

			else
			{
				//std::cout << "char b conditionals have a problem" << std::endl;
			}

			if (ImGui::Button("COMMIT"))
			{
				//obj.species_selec(12, a, b);
				spec.Set_Params(species_current_idx, a, b);
				inv->change_rec(&spec);
				inv->invoke();
				ImGui::CloseCurrentPopup();
				species_picked = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("CANCEL"))
			{
				ImGui::CloseCurrentPopup();
				species_picked = false;
			}

			ImGui::EndPopup();
		}
		
		//SPECIES LIST BOX ENDS HERE
		ImGui::EndListBox();
	}
	//ENDDISABLED MARKER FOR SPECIES LIST BOX
	ImGui::EndDisabled();

	
}
*/
/*
void ImGuiUtil::SpeciesSelection(Character& obj, Invoker* inv) {
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//FIXED: SPECIES CURRENT IDX WAS NOT ALIGNED CORRECTLY WITH THE SPECIES CLASS.  ARRAY MOVED BACK -1
// 	   SEE COMPAT_IDX below
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	SpecSelecComm spec(&obj);
	ProfComm prof(&obj);

	const char* species_selec[] =
	{
		"Hill Dwarf", "Mountain Dwarf", "High Elf", "Wood Elf", "Dark Elf", "Lightfoot Halfling", "Stout Halfling",
		"Human", "Dragonborn", "Forest Gnome", "Rock Gnome", "Half-Elf", "Half-Orc", "Tiefling"
	};
	const char* species_skill_profs[] =
	{
		"Athletics",		// 0  
		"Acrobatics",		// 1
		"Sleight of Hand",	// 2
		"Stealth",			// 3
		"Arcana",			// 4
		"History",			// 5
		"Investigation",	// 6
		"Nature",			// 7
		"Religion",			// 8
		"Animal Handling",	// 9
		"Insight",			// 10
		"Medicine",			// 11
		"Perception",		// 12
		"Survival",			// 13
		"Deception",		// 14
		"Intimidation",		// 15
		"Performance",		// 16
		"Persuasion"		// 17
	};
	const char* species_wpn_profs[] =
	{
		// simple melee
		"club",				// 0 : 
		"dagger",			// 1 : 
		"greatclub",		// 2 : 
		"handaxe",			// 3 : 
		"javelin",			// 4 : 
		"light hammer",		// 5 : 
		"mace",				// 6 : 
		"quarterstaff",		// 7 : 
		"sickle",			// 8 : 
		"spear",			// 9 : 
		// simple ranged
		"light crossbow",	// 10: 
		"dart",				// 11: 
		"shortbow",			// 12: 
		"sling",			// 13: 
		// martial melee
		"battleaxe",		// 14: 
		"flail",			// 15: 
		"glaive",			// 16: 
		"greataxe",			// 17: 
		"greatsword",		// 18: 
		"halberd",			// 19: 
		"lance",			// 20: 
		"longsword",		// 21: 
		"maul",				// 22: 
		"morningstar",		// 23: 
		"pike",				// 24: 
		"rapier",			// 25: 
		"scimitar",			// 26: 
		"shortsword",		// 27: 
		"trident",			// 28: 
		"war pick",			// 29: 
		"warhammer",		// 30: 
		"whip",				// 31: 
		// martial ranged
		"blowgun",			// 32: 
		"hand crossbow",	// 33: 
		"heavy crossbow",	// 34: 
		"longbow",			// 35: 
		"net"				// 36: 
	};

	static int species_current_idx = 0;
	//static bool species_picked = false;
	const char no_char_parameters = 'z';
	const int no_params = -1;
	ImVec2 bttn_sz(125.0f, 25.0f);
	static int selected = 0;

	ImGui::Begin("SELECT CHARACTER SPECIES", nullptr, ImGuiWindowFlags_NoCollapse);
	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 200);

	ImGui::BeginDisabled(species_picked == true);

	ImGui::Text("Available Species");
	ImGui::SameLine();
	HelpMarker("Select a species you wish to assign to your character; when you are satisfied with your choice, click COMMIT below");
	ImGui::Spacing();
	for (int i = 0; i < IM_ARRAYSIZE(species_selec); i++) {
		if (ImGui::Selectable(species_selec[i], species_current_idx == i, ImGuiSelectableFlags_None, bttn_sz)) {
			species_current_idx = i;
		}
		ImGui::Spacing();
	}
	ImGui::Spacing();

	int compat_idx = species_current_idx + 1;
	//ABOUT COMPAT_IDX:
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		//we have to increment by +1; the GUI is drawing from an array (0-start array), 
		//while the backend logic is using integer values from 1 on to denote species type.  
		//a simple +1 to the GUI index for the backend index is sufficient
	
	const int hill_dwarf = 1;
	const int mtn_dwarf = 2;
	const int high_wood_elf = 3;
	const int dark_elf = 4;
	const int rock_gnome = 5;
	const int half_orc = 7;

	if (ImGui::Button("COMMIT")) {
		
		
		if (species_current_idx == 0)
			{
				// 'z' 'z' are the char parameters that are supplied as dead params if not used for the half elf 2-plus
				//hill dwarf
				//spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				//prof.Set_Params(hill_dwarf);
				//inv->change_rec(&spec);
				//inv->invoke();
				//inv->change_rec(&prof);
				//inv->invoke();

				//species_picked = true;
				ImGui::OpenPopup("Hill Dwarf Tool Proficiency Selection");

			}
		if (species_current_idx == 1)
			{
				//mountain dwarf
				//spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				//prof.Set_Params(mtn_dwarf);
				//inv->change_rec(&spec);
				//inv->invoke();
				//inv->change_rec(&prof);
				//inv->invoke();

				//species_picked = true;
				ImGui::OpenPopup("Mountain Dwarf Tool Proficiency Selection");

			}
		if (species_current_idx == 2)
			{
				//high elf
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				prof.Set_Params(high_wood_elf);
				inv->change_rec(&spec);
				inv->invoke();
				inv->change_rec(&prof);
				inv->invoke();
				species_picked = true;
			}
		if (species_current_idx == 3)
			{
				//wood elf
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				prof.Set_Params(high_wood_elf);
				inv->change_rec(&spec);
				inv->invoke();
				inv->change_rec(&prof);
				inv->invoke();
				species_picked = true;
			}
		if (species_current_idx == 4)
			{
				//dark elf
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				prof.Set_Params(dark_elf);
				inv->change_rec(&spec);
				inv->invoke();
				inv->change_rec(&prof);
				inv->invoke();
				species_picked = true;
			}
		if (species_current_idx == 5)
			{
				//lightfoot halfling
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				inv->change_rec(&spec);
				inv->invoke();
				species_picked = true;
			}
		if (species_current_idx == 6)
			{
				//stout halfling
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				inv->change_rec(&spec);
				inv->invoke();
				species_picked = true;
			}
		if (species_current_idx == 7)
			{
				//human
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				inv->change_rec(&spec);
				inv->invoke();
				species_picked = true;
			}
		if (species_current_idx == 8)
			{
				//dragonborn
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				inv->change_rec(&spec);
				inv->invoke();
				species_picked = true;
			}
		if (species_current_idx == 9)
			{
				//forest gnome
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				inv->change_rec(&spec);
				inv->invoke();
				species_picked = true;
			}
		if (species_current_idx == 10)
			{
				//rock gnome
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				prof.Set_Params(rock_gnome);
				inv->change_rec(&spec);
				inv->invoke();
				inv->change_rec(&prof);
				inv->invoke();
				species_picked = true;
			}
		if (species_current_idx == 11)
		{
			//half elf
			ImGui::OpenPopup("Half Elf Abilities and Skills Selection");
		}
		if (species_current_idx == 12)
			{
				//half orc
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				prof.Set_Params(half_orc);
				inv->change_rec(&spec);
				inv->invoke();
				inv->change_rec(&prof);
				inv->invoke();
				species_picked = true;
			}
		if (species_current_idx == 13)
			{
				//tiefling
				spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
				inv->change_rec(&spec);
				inv->invoke();
				species_picked = true;
			}
	}
	//NOTE: a user can decide to "Commit" ability and skill upgrades without having selected any of them; this needs to be amended	
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	
	if (ImGui::BeginPopupModal("Hill Dwarf Tool Proficiency Selection", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		ImGui::Text("Please select (1) tool prof from the following: ");
		ImGui::Spacing();

		const char* dw_tl_prof[3]{ "Brewer's Supplies", "Mason's Tools", "Smith's Tools" };
		static int dw_tl_selec = 0;
		ImGui::RadioButton(dw_tl_prof[0], &dw_tl_selec, 1);
		ImGui::RadioButton(dw_tl_prof[1], &dw_tl_selec, 10);
		ImGui::RadioButton(dw_tl_prof[2], &dw_tl_selec, 13);
		
		ImGui::Spacing();

		

		if (ImGui::Button("COMMIT")) {
			prof.Set_Params(hill_dwarf, dw_tl_selec);
			spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
			inv->change_rec(&prof);
			inv->invoke();
			inv->change_rec(&spec);
			inv->invoke();
			species_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			species_picked = false;
			ImGui::CloseCurrentPopup();
		}



		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Mountain Dwarf Tool Proficiency Selection", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		ImGui::Text("Please select (1) tool prof from the following: ");
		ImGui::Spacing();

		const char* dw_tl_prof[3]{ "Brewer's Supplies", "Mason's Tools", "Smith's Tools" };
		static int dw_tl_selec = 0;
		ImGui::RadioButton(dw_tl_prof[0], &dw_tl_selec, 1); //brewer's supplies
		ImGui::RadioButton(dw_tl_prof[1], &dw_tl_selec, 10); //mason's tools
		ImGui::RadioButton(dw_tl_prof[2], &dw_tl_selec, 13); //smith's tools

		ImGui::Spacing();



		if (ImGui::Button("COMMIT")) {
			prof.Set_Params(mtn_dwarf, dw_tl_selec);
			spec.Set_Params(compat_idx, no_char_parameters, no_char_parameters);
			inv->change_rec(&prof);
			inv->invoke();
			inv->change_rec(&spec);
			inv->invoke();
			species_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			species_picked = false;
			ImGui::CloseCurrentPopup();
		}



		ImGui::EndPopup();
	}
	
	
	if (ImGui::BeginPopupModal("Half Elf Abilities and Skills Selection", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		//static bool halfelf_commit = false;

		ImGui::Text("Please select (2) ability scores to boost by +1:");
		ImGui::SameLine();
		HelpMarker("NOTE: You cannot boost your charisma score further as it is already +2");

		const char* ab_sc_selec[5]{ "STR", "DEX", "CON", "INT", "WIS" };
		static bool sc_dis[5]{ false };
		int sc_dis_sum = 0;

		for (int w = 0; w < IM_ARRAYSIZE(sc_dis); w++) {
			sc_dis_sum += sc_dis[w];
		}
		if (sc_dis_sum < 2) {
			
			for (int x = 0; x < IM_ARRAYSIZE(ab_sc_selec); x++) {
				ImGui::Checkbox(ab_sc_selec[x], &sc_dis[x]);
			}
		}
		else {
			for (int q = 0; q < IM_ARRAYSIZE(sc_dis); q++) {
				ImGui::BeginDisabled(sc_dis[q] == false);
				ImGui::Checkbox(ab_sc_selec[q], &sc_dis[q]);
				ImGui::EndDisabled();
			}
		}

		int first = 0;
		int second = 0;
		int found = 0;
		for (int t = 0; t < IM_ARRAYSIZE(sc_dis); t++) {
			if (sc_dis[t] == true) {
				if (found == 1) {
					second = t;
					found++;
				}
				else if (found == 0) {
					first = t;
					found++;
				}
				else {}
			}
		}

		ImGui::Spacing();
		ImGui::Text("Please select (2) skill proficiencies");
		ImGui::Spacing();

		static bool check_display[18]{ false };
		int check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(check_display); y++) {
			check_dis_sum += check_display[y];
		}
		if (check_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(species_skill_profs); z++) {
				ImGui::Checkbox(species_skill_profs[z], &check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(check_display); a++) {
				ImGui::BeginDisabled(check_display[a] == false);
				ImGui::Checkbox(species_skill_profs[a], &check_display[a]);
				ImGui::EndDisabled();
			}
		}
		
		char a = 'z';
		char b = 'z';

		if (first == 0)
		{
			a = 's';
		}
		else if (first == 1)
		{
			a = 'd';
		}
		else if (first == 2)
		{
			a = 'c';
		}
		else if (first == 3)
		{
			a = 'i';
		}
		else if (first == 4)
		{
			a = 'w';
		}

		else
		{
			//std::cout << "char a conditionals have a problem" << std::endl;
		}

		if (second == 0)
		{
			b = 's';
		}
		else if (second == 1)
		{
			b = 'd';
		}
		else if (second == 2)
		{
			b = 'c';
		}
		else if (second == 3)
		{
			b = 'i';
		}
		else if (second == 4)
		{
			b = 'w';
		}

		else
		{
			//std::cout << "char b conditionals have a problem" << std::endl;
		}

		int skill_prof_idx_one = 0;
		int skill_prof_idx_two = 0;
		int skill_found = 0;
		for (int r = 0; r < IM_ARRAYSIZE(check_display); r++) {
			if (check_display[r] == true) {
				if (skill_found == 1) {
					skill_prof_idx_two = r;
					skill_found++;
				}
				else if (skill_found == 0) {
					skill_prof_idx_one = r;
					skill_found++;
				}
				else {}
			}
		}

		const int half_elf_prof_idx = 6;
		if (ImGui::Button("COMMIT"))
		{
			//obj.species_selec(12, a, b);
			//spec.Set_Params(species_current_idx, a, b);
			spec.Set_Params(compat_idx, a, b);
			prof.Set_Params(half_elf_prof_idx, skill_prof_idx_one, skill_prof_idx_two);
			inv->change_rec(&spec);
			inv->invoke();
			inv->change_rec(&prof);
			inv->invoke();
			ImGui::CloseCurrentPopup();
			species_picked = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL"))
		{
			ImGui::CloseCurrentPopup();
			species_picked = false;
		}

		ImGui::EndPopup();
	}
		
	ImGui::NextColumn();
	
	if (species_current_idx == 0) {
		ImGui::Text("Hill Dwarf Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextDisabled("STR  +0");
		ImGui::TextDisabled("DEX  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CON  +2");
		ImGui::TextDisabled("INT  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "WIS  +1");
		ImGui::TextDisabled("CHA  +0");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {

				ImGui::TextDisabled(species_skill_profs[skill_idx]);

			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				if (wpn_idx == 3 || wpn_idx == 5 || wpn_idx == 14 || wpn_idx == 30) {
					ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), species_wpn_profs[wpn_idx]);
				}
				else {
					ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
				}
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 1) {
		ImGui::Text("Mountain Dwarf Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "STR  +2");
		ImGui::TextDisabled("DEX  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CON  +2");
		ImGui::TextDisabled("INT  +0");
		ImGui::TextDisabled("WIS  +1");
		ImGui::TextDisabled("CHA  +0");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {

				ImGui::TextDisabled(species_skill_profs[skill_idx]);

			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				if (wpn_idx == 3 || wpn_idx == 5 || wpn_idx == 14 || wpn_idx == 30) {

					ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), species_wpn_profs[wpn_idx]);
				}
				else {
					ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
				}
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 2) {
		ImGui::Text("High Elf Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextDisabled("STR  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "DEX  +2");
		ImGui::TextDisabled("CON  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "INT  +2");
		ImGui::TextDisabled("WIS  +1");
		ImGui::TextDisabled("CHA  +0");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {

				if (skill_idx == 12) {
					ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), species_skill_profs[skill_idx]);
				}
				else {
					ImGui::TextDisabled(species_skill_profs[skill_idx]);
				}
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				if (wpn_idx == 12 || wpn_idx == 21 || wpn_idx == 27 || wpn_idx == 35) {

					ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), species_wpn_profs[wpn_idx]);
				}
				else {
					ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
				}
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 3) {
			
		ImGui::Text("Wood Elf Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextDisabled("STR  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "DEX  +2");
		ImGui::TextDisabled("CON  +0");
		ImGui::TextDisabled("INT  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "WIS  +1");
		ImGui::TextDisabled("CHA  +0");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {

				if (skill_idx == 12) {
					ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), species_skill_profs[skill_idx]);
				}
				else {
					ImGui::TextDisabled(species_skill_profs[skill_idx]);
				}
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				if (wpn_idx == 12 || wpn_idx == 21 || wpn_idx == 27 || wpn_idx == 35) {

					ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), species_wpn_profs[wpn_idx]);
				}
				else {
					ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
				}
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 4) {
		ImGui::Text("Dark Elf Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextDisabled("STR  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "DEX  +2");
		ImGui::TextDisabled("CON  +0");
		ImGui::TextDisabled("INT  +0");
		ImGui::TextDisabled("WIS  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CHA  +1");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {

				if (skill_idx == 12) {
					ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), species_skill_profs[skill_idx]);
				}
				else {
					ImGui::TextDisabled(species_skill_profs[skill_idx]);
				}
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				if (wpn_idx == 25 || wpn_idx == 27 || wpn_idx == 33) {

					ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), species_wpn_profs[wpn_idx]);
				}
				else {
					ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
				}
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 5) {
		ImGui::Text("Lightfoot Halfling Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextDisabled("STR  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "DEX  +2");
		ImGui::TextDisabled("CON  +0");
		ImGui::TextDisabled("INT  +0");
		ImGui::TextDisabled("WIS  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CHA  +1");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {
				ImGui::TextDisabled(species_skill_profs[skill_idx]);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 6) {
		ImGui::Text("Stout Halfling Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextDisabled("STR  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "DEX  +2");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CON  +1");
		ImGui::TextDisabled("INT  +0");
		ImGui::TextDisabled("WIS  +0");
		ImGui::TextDisabled("CHA  +0");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {
				ImGui::TextDisabled(species_skill_profs[skill_idx]);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 7) {
		ImGui::Text("Human Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "STR  +1");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "DEX  +1");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CON  +1");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "INT  +1");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "WIS  +1");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CHA  +1");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {
				ImGui::TextDisabled(species_skill_profs[skill_idx]);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 8) {
		ImGui::Text("Dragonborn Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "STR  +2");
		ImGui::TextDisabled("DEX  +0");
		ImGui::TextDisabled("CON  +0");
		ImGui::TextDisabled("INT  +0");
		ImGui::TextDisabled("WIS  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CHA  +1");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {
				ImGui::TextDisabled(species_skill_profs[skill_idx]);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 9) {
		ImGui::Text("Forest Gnome Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextDisabled("STR  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "DEX  +1");
		ImGui::TextDisabled("CON  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "INT  +2");
		ImGui::TextDisabled("WIS  +0");
		ImGui::TextDisabled("CHA  +0");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {
				ImGui::TextDisabled(species_skill_profs[skill_idx]);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 10) {
		ImGui::Text("Rock Gnome Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextDisabled("STR  +0");
		ImGui::TextDisabled("DEX  +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CON  +1");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "INT  +2");
		ImGui::TextDisabled("WIS  +0");
		ImGui::TextDisabled("CHA  +0");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {
				ImGui::TextDisabled(species_skill_profs[skill_idx]);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			for (int wpn_idx = 0; wpn_idx < 37; wpn_idx++) {
				ImGui::TextDisabled(species_wpn_profs[wpn_idx]);
			}
			ImGui::TreePop();
		}
	}
	if (species_current_idx == 11) {
		ImGui::Text("Half Elf Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "+1 for 2 Abilities of player's choice");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "2 Skills of player's choice");
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			ImGui::TextDisabled("N/A");
			ImGui::TreePop();
		}
		
	}
	if (species_current_idx == 12) {
		ImGui::Text("Half Orc Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "STR +2");
		ImGui::TextDisabled("DEX +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CON +1");
		ImGui::TextDisabled("INT +0");
		ImGui::TextDisabled("WIS +0");
		ImGui::TextDisabled("CHA +0");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			for (int skill_idx = 0; skill_idx < 18; skill_idx++) {

				if (skill_idx == 15) {
					ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), species_skill_profs[skill_idx]);
				}
				else {
					ImGui::TextDisabled(species_skill_profs[skill_idx]);
				}
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			ImGui::TextDisabled("N/A");
			ImGui::TreePop();
		}

	}
	if (species_current_idx == 13) {
		ImGui::Text("Tiefling Ability Score Upgrades");
		ImGui::Spacing();
		ImGui::TextDisabled("STR +0");
		ImGui::TextDisabled("DEX +0");
		ImGui::TextDisabled("CON +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "INT +1");
		ImGui::TextDisabled("WIS +0");
		ImGui::TextColored(ImVec4(0.00, 1.00, 0.05, 1.0), "CHA +2");
		ImGui::Spacing();
		if (ImGui::TreeNode("Skill Proficiencies")) {
			ImGui::TextDisabled("N/A");
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Weapon Proficiencies")) {
			ImGui::TextDisabled("N/A");
			ImGui::TreePop();
		}
	}

	ImGui::EndDisabled();
		
	ImGui::End();
	
}
*/
void ImGuiUtil::Species_Selection(Character& obj, Invoker* inv) {
	SpecSelecComm spec(&obj);
	SpecProfComm prof(&obj);

	const char* species_selec[] =
	{
		" ", "Hill Dwarf", "Mountain Dwarf", "High Elf", "Wood Elf", "Dark Elf", "Lightfoot Halfling", "Stout Halfling",
		"Human", "Dragonborn", "Forest Gnome", "Rock Gnome", "Half-Elf", "Half-Orc", "Tiefling"
	};
	const char* species_skill_profs[] =
	{
		"Athletics",		// 0  
		"Acrobatics",		// 1
		"Sleight of Hand",	// 2
		"Stealth",			// 3
		"Arcana",			// 4
		"History",			// 5
		"Investigation",	// 6
		"Nature",			// 7
		"Religion",			// 8
		"Animal Handling",	// 9
		"Insight",			// 10
		"Medicine",			// 11
		"Perception",		// 12
		"Survival",			// 13
		"Deception",		// 14
		"Intimidation",		// 15
		"Performance",		// 16
		"Persuasion"		// 17
	};
	const char* species_wpn_profs[] =
	{
		// simple melee
		"club",				// 0 : 
		"dagger",			// 1 : 
		"greatclub",		// 2 : 
		"handaxe",			// 3 : 
		"javelin",			// 4 : 
		"light hammer",		// 5 : 
		"mace",				// 6 : 
		"quarterstaff",		// 7 : 
		"sickle",			// 8 : 
		"spear",			// 9 : 
		// simple ranged
		"light crossbow",	// 10: 
		"dart",				// 11: 
		"shortbow",			// 12: 
		"sling",			// 13: 
		// martial melee
		"battleaxe",		// 14: 
		"flail",			// 15: 
		"glaive",			// 16: 
		"greataxe",			// 17: 
		"greatsword",		// 18: 
		"halberd",			// 19: 
		"lance",			// 20: 
		"longsword",		// 21: 
		"maul",				// 22: 
		"morningstar",		// 23: 
		"pike",				// 24: 
		"rapier",			// 25: 
		"scimitar",			// 26: 
		"shortsword",		// 27: 
		"trident",			// 28: 
		"war pick",			// 29: 
		"warhammer",		// 30: 
		"whip",				// 31: 
		// martial ranged
		"blowgun",			// 32: 
		"hand crossbow",	// 33: 
		"heavy crossbow",	// 34: 
		"longbow",			// 35: 
		"net"				// 36: 
	};

	static int species_current_idx = 0;
	const int no_params = -1;
	const int one_past = 14;
	ImVec2 bttn_sz(125.0f, 25.0f);
	static int selected = 0;

	ImGui::Begin("SELECT CHARACTER SPECIES", nullptr, ImGuiWindowFlags_NoCollapse);
	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 200);

	ImGui::BeginDisabled(species_picked == true);

	ImGui::Text("Available Species");
	ImGui::SameLine();
	HelpMarker("Select a species you wish to assign to your character; when you are satisfied with your choice, click COMMIT below");
	ImGui::Spacing();
	for (int i = 0; i < IM_ARRAYSIZE(species_selec); i++) {
		if (ImGui::Selectable(species_selec[i], species_current_idx == i, ImGuiSelectableFlags_None, bttn_sz)) {
			species_current_idx = i;
		}
		ImGui::Spacing();
	}
	ImGui::Spacing();
	//static bool no_empty_params = (species_current_idx > no_params && species_current_idx < one_past) ? true : false;
	bool zeroth_ind = (species_current_idx == 0) ? true : false;
	bool halfelf = (species_current_idx == 12) ? true : false;
	ImGui::BeginDisabled(zeroth_ind);
	if (ImGui::Button("SELECT")) {
		std::cout << "species index: " << species_current_idx << std::endl;
		if (halfelf)
		{
			//half elf
			ImGui::OpenPopup("Half Elf Abilities Selection");
		}
		else {
			spec.Set_Params(species_current_idx, no_params, no_params);
			prof.Set_Params(species_current_idx);
			inv->change_rec(&spec);
			inv->invoke();
			inv->change_rec(&prof);
			inv->invoke();
			//ImGui::CloseCurrentPopup();
			species_picked = true;
		}
		/*
		if (no_empty_params == false) {
			ImGui::OpenPopup("SPECIES SELECTION ERROR");
		}
		else {
			if (halfelf)
			{
				//half elf
				ImGui::OpenPopup("Half Elf Abilities Selection");
			}
			else {
				spec.Set_Params(species_current_idx, no_params, no_params);
				prof.Set_Params(species_current_idx);
				inv->change_rec(&spec);
				inv->invoke();
				inv->change_rec(&prof);
				inv->invoke();
				//ImGui::CloseCurrentPopup();
				species_picked = true;
			}
		}
		*/
	}
	ImGui::EndDisabled(); //for zeroth_ind bool ln 1505

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (ImGui::BeginPopupModal("SPECIES SELECTION ERROR", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Please select a species type for your character");
		if (ImGui::Button("OK")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Half Elf Abilities Selection", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		//static bool halfelf_commit = false;

		ImGui::Text("Please select (2) ability scores to boost by +1:");
		ImGui::SameLine();
		HelpMarker("NOTE: You cannot boost your Charisma score further as it is already +2");

		const char* ab_sc_selec[5]{ "STR", "DEX", "CON", "INT", "WIS" };
		static bool sc_dis[5]{ false };
		int sc_dis_sum = 0;

		for (int w = 0; w < IM_ARRAYSIZE(sc_dis); w++) {
			sc_dis_sum += sc_dis[w];
		}
		if (sc_dis_sum < 2) {

			for (int x = 0; x < IM_ARRAYSIZE(ab_sc_selec); x++) {
				ImGui::Checkbox(ab_sc_selec[x], &sc_dis[x]);
			}
		}
		else {
			for (int q = 0; q < IM_ARRAYSIZE(sc_dis); q++) {
				ImGui::BeginDisabled(sc_dis[q] == false);
				ImGui::Checkbox(ab_sc_selec[q], &sc_dis[q]);
				ImGui::EndDisabled();
			}
		}

		int first = 0;
		int second = 0;
		int found = 0;
		for (int t = 0; t < IM_ARRAYSIZE(sc_dis); t++) {
			if (sc_dis[t] == true) {
				if (found == 1) {
					second = t;
					found++;
				}
				else if (found == 0) {
					first = t;
					found++;
				}
				else {}
			}
		}
		/*
		ImGui::Spacing();
		ImGui::Text("Please select (2) skill proficiencies");
		ImGui::Spacing();

		static bool check_display[18]{ false };
		int check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(check_display); y++) {
			check_dis_sum += check_display[y];
		}
		if (check_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(species_skill_profs); z++) {
				ImGui::Checkbox(species_skill_profs[z], &check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(check_display); a++) {
				ImGui::BeginDisabled(check_display[a] == false);
				ImGui::Checkbox(species_skill_profs[a], &check_display[a]);
				ImGui::EndDisabled();
			}
		}

		int skill_prof_idx_one = 0;
		int skill_prof_idx_two = 0;
		int skill_found = 0;
		for (int r = 0; r < IM_ARRAYSIZE(check_display); r++) {
			if (check_display[r] == true) {
				if (skill_found == 1) {
					skill_prof_idx_two = r;
					skill_found++;
				}
				else if (skill_found == 0) {
					skill_prof_idx_one = r;
					skill_found++;
				}
				else {}
			}
		}
		*/
		//const int half_elf_prof_idx = 6;
		if (ImGui::Button("COMMIT"))
		{
			//obj.species_selec(12, a, b);
			//spec.Set_Params(species_current_idx, a, b);
			//spec.Set_Params(compat_idx, a, b);
			//prof.Set_Params(half_elf_prof_idx, skill_prof_idx_one, skill_prof_idx_two);
			//inv->change_rec(&spec);
			//inv->invoke();
			//inv->change_rec(&prof);
			//inv->invoke();
			spec.Set_Params(species_current_idx, first, second);
			prof.Set_Params(species_current_idx);
			inv->change_rec(&spec);
			inv->invoke();
			inv->change_rec(&prof);
			inv->invoke();
			ImGui::CloseCurrentPopup();
			species_picked = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL"))
		{
			ImGui::CloseCurrentPopup();
			species_picked = false;
		}

		ImGui::EndPopup();
	}

	ImGui::EndDisabled(); //for species_picked bool ln 1490
	ImGui::End();
}

//ClassList is now deprecated
/*
void ImGuiUtil::ClassList(Character& obj, Invoker* inv) {

	ClassSelecComm clss(&obj);
	
	const char* clss_selec[] =
	{
		" ", "Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue", "Sorcerer", "Warlock", "Wizard"
	};
	static int clss_current_idx = 0;
	static bool clss_picked = false;
	ImGui::BeginDisabled(clss_picked == true);
	ImGui::Text("Class Selection: ");
	if (ImGui::BeginListBox("##listbox_class", ImVec2(425, 0)))
	{
		for (int n = 0; n < IM_ARRAYSIZE(clss_selec); n++)
		{
			const bool is_selected = (clss_current_idx == n);
			if (ImGui::Selectable(clss_selec[n], is_selected))
				clss_current_idx = n;
			if (is_selected)
				ImGui::SetItemDefaultFocus();
			if (ImGui::IsItemClicked(0) && is_selected)
			{
				if (clss_current_idx == 1)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);

					clss_picked = true;
				}
				else if (clss_current_idx == 2)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else if (clss_current_idx == 3)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else if (clss_current_idx == 4)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else if (clss_current_idx == 5)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else if (clss_current_idx == 6)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else if (clss_current_idx == 7)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else if (clss_current_idx == 8)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else if (clss_current_idx == 9)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else if (clss_current_idx == 10)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else if (clss_current_idx == 11)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else if (clss_current_idx == 12)
				{
					clss.Set_Params(clss_current_idx);
					inv->change_rec(&clss);
					inv->invoke();
					//obj.character_selec(clss_current_idx);
					clss_picked = true;
				}
				else {}
			}
		}
		ImGui::EndListBox();
	}
	ImGui::EndDisabled();
}
*/


void ImGuiUtil::ClassSelection(Character& obj, Invoker* inv) {

	ClassSelecComm clss(&obj);
	ClssProfComm prof(&obj);

	const char* clss_selec[] =
	{
		" ", "Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue", "Sorcerer", "Warlock", "Wizard"
	};
	static int clss_current_idx = 0;
	const char* species_skill_profs[] =
	{
		"Athletics", // 0  
		"Acrobatics",// 1
		"Sleight of Hand",// 2
		"Stealth", // 3
		"Arcana", // 4
		"History", // 5
		"Investigation", // 6
		"Nature", // 7
		"Religion", // 8
		"Animal Handling", // 9
		"Insight", // 10
		"Medicine", // 11
		"Perception", // 12
		"Survival", // 13
		"Deception", // 14
		"Intimidation", // 15
		"Performance", // 16
		"Persuasion" // 17
	};
	//static bool clss_picked = false;
	ImVec2 bttn_sz(100.0f, 25.0f);

	ImGui::Begin("SELECT CHARACTER CLASS", nullptr, ImGuiWindowFlags_NoCollapse);


	ImGui::BeginDisabled(species_picked == false || clss_picked == true);
	for (int i = 0; i < IM_ARRAYSIZE(clss_selec); i++) {
		if (ImGui::Selectable(clss_selec[i], clss_current_idx == i, ImGuiSelectableFlags_None, bttn_sz)) {
			clss_current_idx = i;
		}
		ImGui::Spacing();
	}
	bool zeroth_ind = (clss_current_idx == 0) ? true : false;
	ImGui::BeginDisabled(zeroth_ind);
	if (ImGui::Button("SELECT")) {
		clss.Set_Params(clss_current_idx);
		prof.Set_Params(clss_current_idx);
		inv->change_rec(&clss);
		inv->invoke();
		inv->change_rec(&prof);
		inv->invoke();

		clss_picked = true;
	}
	ImGui::EndDisabled();
	/*
	if (ImGui::Button("SELECT")) {
		if (clss_current_idx == 1)
		{
			ImGui::OpenPopup("Barbarian Skill Choice");
		}
		else if (clss_current_idx == 2)
		{
			ImGui::OpenPopup("Bard Skill Choice");
		}
		else if (clss_current_idx == 3)
		{
			ImGui::OpenPopup("Cleric Skill Choice");
		}
		else if (clss_current_idx == 4)
		{
			ImGui::OpenPopup("Druid Skill Choice");
		}
		else if (clss_current_idx == 5)
		{
			ImGui::OpenPopup("Fighter Skill Choice");
		}
		else if (clss_current_idx == 6)
		{
			ImGui::OpenPopup("Monk Skill Choice");
		}
		else if (clss_current_idx == 7)
		{
			ImGui::OpenPopup("Paladin Skill Choice");
		}
		else if (clss_current_idx == 8)
		{
			ImGui::OpenPopup("Ranger Skill Choice");
		}
		else if (clss_current_idx == 9)
		{
			ImGui::OpenPopup("Rogue Skill Choice");
		}
		else if (clss_current_idx == 10)
		{
			ImGui::OpenPopup("Sorcerer Skill Choice");
		}
		else if (clss_current_idx == 11)
		{
			ImGui::OpenPopup("Warlock Skill Choice");
		}
		else if (clss_current_idx == 12)
		{
			ImGui::OpenPopup("Wizard Skill Choice");
		}
		else {}
	}
	const char* class_skill_profs[] =
	{
		"Athletics", // 0  
		"Acrobatics",// 1
		"Sleight of Hand",// 2
		"Stealth", // 3
		"Arcana", // 4
		"History", // 5
		"Investigation", // 6
		"Nature", // 7
		"Religion", // 8
		"Animal Handling", // 9
		"Insight", // 10
		"Medicine", // 11
		"Perception", // 12
		"Survival", // 13
		"Deception", // 14
		"Intimidation", // 15
		"Performance", // 16
		"Persuasion" // 17
	};
	const int barbarian_sk[] = {
		9, 0, 15, 7, 12, 13
	};
	//bard skills not necessary to delineate since you can just choose any three (PHB 52)
	const int cleric_sk[] = {
		5, 10, 11, 17, 8
	};
	const int druid_sk[] = {
		4, 9, 10, 11, 7, 12, 8, 13
	};
	const int fighter_sk[] = {
		1, 9, 0, 5, 10, 15, 12, 13
	};
	const int monk_sk[] = {
		1, 0, 5, 10, 8, 3
	};
	const int paladin_sk[] = {
		0, 10, 15, 11, 17, 8
	};
	const int ranger_sk[] = {
		9, 0, 10, 6, 7, 12, 3, 13
	};
	const int rogue_sk[] = {
		1, 0, 14, 10, 15, 6, 12, 16, 17, 2, 3
	};
	const int sorcerer_sk[] = {
		4, 14, 10, 15, 17, 8
	};
	const int warlock_sk[] = {
		4, 14, 5, 15, 6, 7, 8
	};
	const int wizard_sk[] = {
		4, 5, 10, 6, 11, 8
	};
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	if (ImGui::BeginPopupModal("Barbarian Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		
		static bool bcheck_display[6]{ false };
		int bcheck_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(bcheck_display); y++) {
			bcheck_dis_sum += bcheck_display[y];
		}
		if (bcheck_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(barbarian_sk); z++) {
				ImGui::Checkbox(class_skill_profs[barbarian_sk[z]], &bcheck_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(bcheck_display); a++) {
				ImGui::BeginDisabled(bcheck_display[a] == false);
				ImGui::Checkbox(class_skill_profs[barbarian_sk[a]], &bcheck_display[a]);
				ImGui::EndDisabled();
			}
		}
		
		int barbarian_prof_idx_one = 0;
		int barbarian_prof_idx_two = 0;
		int barbarian_skill_found = 0;
		for (int r = 0; r < IM_ARRAYSIZE(bcheck_display); r++) {
			if (bcheck_display[r] == true) {
				if (barbarian_skill_found == 1) {
					barbarian_prof_idx_two = barbarian_sk[r];
					barbarian_skill_found++;
				}
				else if (barbarian_skill_found == 0) {
					barbarian_prof_idx_one = barbarian_sk[r];
					barbarian_skill_found++;
				}
				else {}
			}
		}

		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			prof.Set_Params(8, barbarian_prof_idx_one, barbarian_prof_idx_two);
			inv->change_rec(&clss);
			inv->invoke();
			inv->change_rec(&prof);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}
		

		ImGui::EndPopup();
	}
	
	if (ImGui::BeginPopupModal("Bard Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool bard_check_display[18]{ false };
		int bard_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(bard_check_display); y++) {
			bard_check_dis_sum += bard_check_display[y];
		}
		if (bard_check_dis_sum < 3) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(class_skill_profs); z++) {
				ImGui::Checkbox(class_skill_profs[z], &bard_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(bard_check_display); a++) {
				ImGui::BeginDisabled(bard_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[a], &bard_check_display[a]);
				ImGui::EndDisabled();
			}
		}

		int bard_prof_idx_one = 0;
		int bard_prof_idx_two = 0;
		int bard_prof_idx_three = 0;
		int bard_skill_found = 0;
		for (int r = 0; r < IM_ARRAYSIZE(bard_check_display); r++) {
			if (bard_check_display[r] == true) {
				if (bard_skill_found == 2) {
					bard_prof_idx_three = r;
					bard_skill_found++;
				}
				else if (bard_skill_found == 1) {
					bard_prof_idx_two = r;
					bard_skill_found++;
				}
				else if (bard_skill_found == 0) {
					bard_prof_idx_one = r;
					bard_skill_found++;
				}
				else {}
			}
		}

		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			prof.Set_Params(9, bard_prof_idx_one, bard_prof_idx_two, bard_prof_idx_three);
			inv->change_rec(&clss);
			inv->invoke();
			inv->change_rec(&prof);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}


		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Cleric Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool cleric_check_display[5]{ false };
		int cleric_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(cleric_check_display); y++) {
			cleric_check_dis_sum += cleric_check_display[y];
		}
		if (cleric_check_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(cleric_sk); z++) {
				ImGui::Checkbox(class_skill_profs[cleric_sk[z]], &cleric_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(cleric_check_display); a++) {
				ImGui::BeginDisabled(cleric_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[cleric_sk[a]], &cleric_check_display[a]);
				ImGui::EndDisabled();
			}
		}

		int cleric_prof_idx_one = 0;
		int cleric_prof_idx_two = 0;
		int cleric_skill_found = 0;
		for (int r = 0; r < IM_ARRAYSIZE(cleric_check_display); r++) {
			if (cleric_check_display[r] == true) {
				if (cleric_skill_found == 1) {
					cleric_prof_idx_two = cleric_sk[r];
					cleric_skill_found++;
				}
				else if (cleric_skill_found == 0) {
					cleric_prof_idx_one = cleric_sk[r];
					cleric_skill_found++;
				}
				else {}
			}
		}

		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			prof.Set_Params(10, cleric_prof_idx_one, cleric_prof_idx_two);
			inv->change_rec(&clss);
			inv->invoke();
			inv->change_rec(&prof);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}


		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Druid Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool druid_check_display[8]{ false };
		int druid_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(druid_check_display); y++) {
			druid_check_dis_sum += druid_check_display[y];
		}
		if (druid_check_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(druid_sk); z++) {
				ImGui::Checkbox(class_skill_profs[druid_sk[z]], &druid_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(druid_check_display); a++) {
				ImGui::BeginDisabled(druid_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[druid_sk[a]], &druid_check_display[a]);
				ImGui::EndDisabled();
			}
		}

		int druid_prof_idx_one = 0;
		int druid_prof_idx_two = 0;
		int druid_skill_found = 0;
		for (int r = 0; r < IM_ARRAYSIZE(druid_check_display); r++) {
			if (druid_check_display[r] == true) {
				if (druid_skill_found == 1) {
					druid_prof_idx_two = druid_sk[r];
					druid_skill_found++;
				}
				else if (druid_skill_found == 0) {
					druid_prof_idx_one = druid_sk[r];
					druid_skill_found++;
				}
				else {}
			}
		}

		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			prof.Set_Params(11, druid_prof_idx_one, druid_prof_idx_two);
			inv->change_rec(&clss);
			inv->invoke();
			inv->change_rec(&prof);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}


		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Fighter Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool fighter_check_display[8]{ false };
		int fighter_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(fighter_check_display); y++) {
			fighter_check_dis_sum += fighter_check_display[y];
		}
		if (fighter_check_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(fighter_sk); z++) {
				ImGui::Checkbox(class_skill_profs[fighter_sk[z]], &fighter_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(fighter_check_display); a++) {
				ImGui::BeginDisabled(fighter_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[fighter_sk[a]], &fighter_check_display[a]);
				ImGui::EndDisabled();
			}
		}

		int fighter_prof_idx_one = 0;
		int fighter_prof_idx_two = 0;
		int fighter_skill_found = 0;
		for (int r = 0; r < IM_ARRAYSIZE(fighter_check_display); r++) {
			if (fighter_check_display[r] == true) {
				if (fighter_skill_found == 1) {
					fighter_prof_idx_two = fighter_sk[r];
					fighter_skill_found++;
				}
				else if (fighter_skill_found == 0) {
					fighter_prof_idx_one = fighter_sk[r];
					fighter_skill_found++;
				}
				else {}
			}
		}

		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			prof.Set_Params(12, fighter_prof_idx_one, fighter_prof_idx_two);
			inv->change_rec(&clss);
			inv->invoke();
			inv->change_rec(&prof);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}

		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Monk Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool monk_check_display[6]{ false };
		int monk_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(monk_check_display); y++) {
			monk_check_dis_sum += monk_check_display[y];
		}
		if (monk_check_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(monk_sk); z++) {
				ImGui::Checkbox(class_skill_profs[monk_sk[z]], &monk_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(monk_check_display); a++) {
				ImGui::BeginDisabled(monk_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[monk_sk[a]], &monk_check_display[a]);
				ImGui::EndDisabled();
			}
		}

		int monk_prof_idx_one = 0;
		int monk_prof_idx_two = 0;
		int monk_skill_found = 0;
		for (int r = 0; r < IM_ARRAYSIZE(monk_check_display); r++) {
			if (monk_check_display[r] == true) {
				if (monk_skill_found == 1) {
					monk_prof_idx_two = monk_sk[r];
					monk_skill_found++;
				}
				else if (monk_skill_found == 0) {
					monk_prof_idx_one = monk_sk[r];
					monk_skill_found++;
				}
				else {}
			}
		}

		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			prof.Set_Params(13, monk_prof_idx_one, monk_prof_idx_two);
			inv->change_rec(&clss);
			inv->invoke();
			inv->change_rec(&prof);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}


		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Paladin Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool paladin_check_display[6]{ false };
		int paladin_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(paladin_check_display); y++) {
			paladin_check_dis_sum += paladin_check_display[y];
		}
		if (paladin_check_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(paladin_sk); z++) {
				ImGui::Checkbox(class_skill_profs[paladin_sk[z]], &paladin_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(paladin_check_display); a++) {
				ImGui::BeginDisabled(paladin_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[paladin_sk[a]], &paladin_check_display[a]);
				ImGui::EndDisabled();
			}
		}

		int paladin_prof_idx_one = 0;
		int paladin_prof_idx_two = 0;
		int paladin_skill_found = 0;
		for (int r = 0; r < IM_ARRAYSIZE(paladin_check_display); r++) {
			if (paladin_check_display[r] == true) {
				if (paladin_skill_found == 1) {
					paladin_prof_idx_two = paladin_sk[r];
					paladin_skill_found++;
				}
				else if (paladin_skill_found == 0) {
					paladin_prof_idx_one = paladin_sk[r];
					paladin_skill_found++;
				}
				else {}
			}
		}

		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			prof.Set_Params(14, paladin_prof_idx_one, paladin_prof_idx_two);
			inv->change_rec(&clss);
			inv->invoke();
			inv->change_rec(&prof);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}


		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Ranger Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool ranger_check_display[8]{ false };
		int ranger_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(ranger_check_display); y++) {
			ranger_check_dis_sum += ranger_check_display[y];
		}
		if (ranger_check_dis_sum < 3) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(ranger_sk); z++) {
				ImGui::Checkbox(class_skill_profs[ranger_sk[z]], &ranger_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(ranger_check_display); a++) {
				ImGui::BeginDisabled(ranger_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[ranger_sk[a]], &ranger_check_display[a]);
				ImGui::EndDisabled();
			}
		}
		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			inv->change_rec(&clss);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}


		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Rogue Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool rogue_check_display[11]{ false };
		int rogue_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(rogue_check_display); y++) {
			rogue_check_dis_sum += rogue_check_display[y];
		}
		if (rogue_check_dis_sum < 4) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(rogue_sk); z++) {
				ImGui::Checkbox(class_skill_profs[rogue_sk[z]], &rogue_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(rogue_check_display); a++) {
				ImGui::BeginDisabled(rogue_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[rogue_sk[a]], &rogue_check_display[a]);
				ImGui::EndDisabled();
			}
		}
		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			inv->change_rec(&clss);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}


		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Sorcerer Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool sorcerer_check_display[6]{ false };
		int sorcerer_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(sorcerer_check_display); y++) {
			sorcerer_check_dis_sum += sorcerer_check_display[y];
		}
		if (sorcerer_check_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(sorcerer_sk); z++) {
				ImGui::Checkbox(class_skill_profs[sorcerer_sk[z]], &sorcerer_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(sorcerer_check_display); a++) {
				ImGui::BeginDisabled(sorcerer_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[sorcerer_sk[a]], &sorcerer_check_display[a]);
				ImGui::EndDisabled();
			}
		}
		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			inv->change_rec(&clss);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}

		ImGui::EndPopup();
	}
	
	if (ImGui::BeginPopupModal("Warlock Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool warlock_check_display[7]{ false };
		int warlock_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(warlock_check_display); y++) {
			warlock_check_dis_sum += warlock_check_display[y];
		}
		if (warlock_check_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(warlock_sk); z++) {
				ImGui::Checkbox(class_skill_profs[warlock_sk[z]], &warlock_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(warlock_check_display); a++) {
				ImGui::BeginDisabled(warlock_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[warlock_sk[a]], &warlock_check_display[a]);
				ImGui::EndDisabled();
			}
		}
		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			inv->change_rec(&clss);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}


		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal("Wizard Skill Choice", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		static bool wizard_check_display[6]{ false };
		int wizard_check_dis_sum = 0;

		for (int y = 0; y < IM_ARRAYSIZE(wizard_check_display); y++) {
			wizard_check_dis_sum += wizard_check_display[y];
		}
		if (wizard_check_dis_sum < 2) {
			//species_skill_profs is the string "array"
			for (int z = 0; z < IM_ARRAYSIZE(wizard_sk); z++) {
				ImGui::Checkbox(class_skill_profs[wizard_sk[z]], &wizard_check_display[z]);
			}
		}
		else {
			for (int a = 0; a < IM_ARRAYSIZE(wizard_check_display); a++) {
				ImGui::BeginDisabled(wizard_check_display[a] == false);
				ImGui::Checkbox(class_skill_profs[wizard_sk[a]], &wizard_check_display[a]);
				ImGui::EndDisabled();
			}
		}
		if (ImGui::Button("COMMIT")) {
			clss.Set_Params(clss_current_idx);
			inv->change_rec(&clss);
			inv->invoke();

			clss_picked = true;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL")) {
			ImGui::CloseCurrentPopup();
			clss_picked = false;
		}


		ImGui::EndPopup();
	}
	*/
	ImGui::EndDisabled();
	ImGui::End();
	
}

void ImGuiUtil::LevelUp(Character& obj, Invoker* inv) {
	
	//fire up our command for the Invoker to adopt
	LevelSelectComm lvlselec(&obj);
	
	LevelUpComm lvlup(&obj);
	
	static int lvl_int = 1;
	
	ImGui::BeginDisabled(lvl_picked == true || is_commit_clicked == false);

	ImGui::Text("Starting Level Selection");

	ImGui::Text("Level: %d", lvl_int);
	ImGui::SameLine();
	if (ImGui::SmallButton("-##lvlminus")) {
		if (lvl_int <= 1) {

		}
		else { lvl_int--; }
		std::cout << "-" << " " << lvl_int << std::endl;
	}
	ImGui::SameLine();
	if (ImGui::SmallButton("+##lvlplus")) {
		if (lvl_int >= 20) {

		}
		else { lvl_int++; }
		std::cout << "+" << " " << lvl_int << std::endl;
	}
	ImGui::Spacing();
	if (ImGui::Button("COMMIT LEVEL"))
	{
		obj.retr_csumm().level = lvl_int; //is this really necessary?								  
		std::cout << "lvl_int = " << lvl_int << std::endl;
		inv->change_rec(&lvlselec);
		inv->invoke();
		
		abscore_total = obj.abscore_up();
		lvl_picked = true;
		std::cout << "abscore_total: " << abscore_total << std::endl;
	};
	ImGui::EndDisabled();
	if (abscore_total > 0)
	{
		ImGui::OpenPopup("ABILITY SCORE UPGRADES");
	}
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	if (ImGui::BeginPopupModal("ABILITY SCORE UPGRADES", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{

		ImGui::Text("Select ability scores to increase");
		ImGui::SameLine();
		HelpMarker("When you reach certain levels, you get to increase your scores in increments of +2 and +1; you cannot increase any ability score beyond level 20 with this feature.");
		bool disable_str_decr = false;
		bool disable_str_incr_ii = false;
		bool disable_str_incr_i = false;

		bool disable_dex_decr = false;
		bool disable_dex_incr_ii = false;
		bool disable_dex_incr_i = false;

		bool disable_con_decr = false;
		bool disable_con_incr_ii = false;
		bool disable_con_incr_i = false;

		bool disable_intl_decr = false;
		bool disable_intl_incr_ii = false;
		bool disable_intl_incr_i = false;

		bool disable_wis_decr = false;
		bool disable_wis_incr_ii = false;
		bool disable_wis_incr_i = false;

		bool disable_cha_decr = false;
		bool disable_cha_incr_ii = false;
		bool disable_cha_incr_i = false;


		static int str_up = obj.retr_absumm().str;
		static int dex_up = obj.retr_absumm().dex;
		static int con_up = obj.retr_absumm().con;
		static int intl_up = obj.retr_absumm().intl;
		static int wis_up = obj.retr_absumm().wis;
		static int cha_up = obj.retr_absumm().cha;

		const int max_score = 20;

		//start strength incr/decr here
		//<><><><><><><><><><><><><><><>
		ImGui::Text("Points available: %d", abscore_total);
		ImGui::Text("STR: %d", str_up);
		ImGui::SameLine();

		if (str_up == obj.retr_absumm().str)
		{
			disable_str_decr = true;
		}
		ImGui::BeginDisabled(disable_str_decr == true);
		if (ImGui::SmallButton("UNDO##strclr"))
		{
			//obtain the difference between incr score and original score
			int undo = str_up - obj.retr_absumm().str;
			abscore_total += undo; //add the difference back to the abscore_total
			str_up -= undo; //return str_up to original value (ability_summary.str)

		}

		ImGui::EndDisabled();
		ImGui::SameLine();

		if (str_up + 2 > max_score || abscore_total - 2 < 0)
		{
			disable_str_incr_ii = true;
		}
		ImGui::BeginDisabled(disable_str_incr_ii == true);
		if (ImGui::SmallButton("+2##stri2"))
		{

			str_up += 2;
			abscore_total -= 2;
		}

		ImGui::EndDisabled();
		ImGui::SameLine();

		if (str_up + 1 > max_score || abscore_total - 1 < 0)
		{
			disable_str_incr_i = true;
		}

		ImGui::BeginDisabled(disable_str_incr_i == true);

		if (ImGui::SmallButton("+1##stri1"))
		{

			str_up++;
			abscore_total--;
		}
		ImGui::EndDisabled();

		//<><><><><><><><><>
		//end str incr/decr here

		//<><><><><><><><><><>
		//begin dex incr/decr here
		ImGui::Text("DEX: %d", dex_up);
		ImGui::SameLine();

		if (dex_up == obj.retr_absumm().dex)
		{
			disable_dex_decr = true;
		}
		ImGui::BeginDisabled(disable_dex_decr == true);
		if (ImGui::SmallButton("UNDO##dexclr"))
		{
			//int undo = dex_up - abilities.ability_summary.dex; //obtain the difference between incr score and original score
			int undo = dex_up - obj.retr_absumm().dex;
			abscore_total += undo; //add the difference back to the abscore_total
			dex_up -= undo; //return str_up to original value (ability_summary.dex)
		}
		ImGui::EndDisabled();
		ImGui::SameLine();
		if (dex_up + 2 > max_score || abscore_total - 2 < 0)
		{
			disable_dex_incr_ii = true;
		}
		ImGui::BeginDisabled(disable_dex_incr_ii == true);
		if (ImGui::SmallButton("+2##dexi2"))
		{
			dex_up += 2;
			abscore_total -= 2;
		}
		ImGui::EndDisabled();
		ImGui::SameLine();
		
		if (dex_up + 1 > max_score || abscore_total - 1 < 0)
		{
			disable_dex_incr_i = true;
		}
		ImGui::BeginDisabled(disable_dex_incr_i == true);
		if (ImGui::SmallButton("+1##dexi1"))
		{
			dex_up++;
			abscore_total--;
		}
		ImGui::EndDisabled();
		//dex incr/decr ends here
		//<><><><><><><><><><><><>

		//<><><><><><><><><><><><>
		//con incr/decr begins here
		ImGui::Text("CON: %d", con_up);
		ImGui::SameLine();
		if (con_up == obj.retr_absumm().con)
		{
			disable_con_decr = true;
		}
		ImGui::BeginDisabled(disable_con_decr == true);
		if (ImGui::SmallButton("UNDO##conclr"))
		{
			int undo = con_up - obj.retr_absumm().con; 
			
			abscore_total += undo; //add the difference back to the abscore_total
			con_up -= undo; //return str_up to original value (ability_summary.con)
		}
		ImGui::EndDisabled();
		ImGui::SameLine();
		if (con_up + 2 > max_score || abscore_total - 2 < 0)
		{
			disable_con_incr_ii = true;
		}
		ImGui::BeginDisabled(disable_con_incr_ii == true);
		if (ImGui::SmallButton("+2##coni2"))
		{
			con_up += 2;
			abscore_total -= 2;
		}
		ImGui::EndDisabled();
		ImGui::SameLine();
		if (con_up + 1 > max_score || abscore_total - 1 < 0)
		{
			disable_con_incr_i = true;
		}
		ImGui::BeginDisabled(disable_con_incr_i == true);
		if (ImGui::SmallButton("+1##coni1"))
		{
			con_up++;
			abscore_total--;
		}
		ImGui::EndDisabled();
		//con incr/decr ends here
		//<><><><><><><><>

		//<><><><><><><><>
		//intl incr/decr begins here
		ImGui::Text("INT: %d", intl_up);
		ImGui::SameLine();
		if (intl_up == obj.retr_absumm().intl)
			//if (intl_up == abilities.ability_summary.intl)
		{
			disable_intl_decr = true;
		}
		ImGui::BeginDisabled(disable_intl_decr == true);
		if (ImGui::SmallButton("UNDO##intlclr"))
		{
			//obtain the difference between incr score and original score
			int undo = intl_up - obj.retr_absumm().intl;
			abscore_total += undo; //add the difference back to the abscore_total
			intl_up -= undo; //return str_up to origina value (ability_summary.dex)
		}
		ImGui::EndDisabled();
		ImGui::SameLine();


		if (intl_up + 2 > max_score || abscore_total - 2 < 0)
		{
			disable_intl_incr_ii = true;
		}
		ImGui::BeginDisabled(disable_intl_incr_ii == true);
		if (ImGui::SmallButton("+2##intli2"))
		{
			intl_up += 2;
			abscore_total -= 2;
		}
		ImGui::EndDisabled();
		ImGui::SameLine();

		if (intl_up + 1 > max_score || abscore_total - 1 < 0)
		{
			disable_intl_incr_i = true;
		}
		ImGui::BeginDisabled(disable_intl_incr_i == true);
		if (ImGui::SmallButton("+1##intli1"))
		{
			intl_up++;
			abscore_total--;
		}
		ImGui::EndDisabled();
		//intl incr/decr ends here
		//<><><><><><><><><><><><>

		//<><><><><><><><><><><><>
		//wis incr/decr begins here

		ImGui::Text("WIS: %d", wis_up);
		ImGui::SameLine();
		if (wis_up == obj.retr_absumm().wis)
		{
			disable_wis_decr = true;
		}
		ImGui::BeginDisabled(disable_wis_decr == true);
		if (ImGui::SmallButton("UNDO##wisclr"))
		{
			int undo = wis_up - obj.retr_absumm().wis;
			//obtain the difference between incr score and original score
			abscore_total += undo; //add the difference back to the abscore_total
			wis_up -= undo; //return str_up to origina value (ability_summary.dex)
		}
		ImGui::EndDisabled();
		ImGui::SameLine();
		if (wis_up + 2 > max_score || abscore_total - 2 < 0)
		{
			disable_wis_incr_ii = true;
		}
		ImGui::BeginDisabled(disable_wis_incr_ii == true);
		if (ImGui::SmallButton("+2##wisi2"))
		{
			wis_up += 2;
			abscore_total -= 2;
		}
		ImGui::EndDisabled();
		ImGui::SameLine();
		if (wis_up + 1 > max_score || abscore_total - 1 < 0)
		{
			disable_wis_incr_i = true;
		}
		ImGui::BeginDisabled(disable_wis_incr_i == true);
		if (ImGui::SmallButton("+1##wisi1"))
		{
			wis_up++;
			abscore_total--;
		}
		ImGui::EndDisabled();
		//wis incr/decr ends here
		//<><><><><><><><><><><><><>

		//<><><><><><><><><><><><><>
		//cha incr/decr begins here
		ImGui::Text("CHA: %d", cha_up);
		ImGui::SameLine();
		if (cha_up == obj.retr_absumm().cha)
		{
			disable_cha_decr = true;
		}
		ImGui::BeginDisabled(disable_cha_decr == true);
		if (ImGui::SmallButton("UNDO##chaclr"))
		{
			int undo = cha_up - obj.retr_absumm().cha;
			abscore_total += undo; //add the difference back to the abscore_total
			cha_up -= undo; //return str_up to origina value (ability_summary.dex)
		}
		ImGui::EndDisabled();
		ImGui::SameLine();
		if (cha_up + 2 > max_score || abscore_total - 2 < 0)
		{
			disable_cha_incr_ii = true;
		}
		ImGui::BeginDisabled(disable_cha_incr_ii == true);
		if (ImGui::SmallButton("+2##chai2"))
		{
			cha_up += 2;
			abscore_total -= 2;
		}
		ImGui::EndDisabled();
		ImGui::SameLine();
		if (cha_up + 1 > max_score || abscore_total - 1 < 0)
		{
			disable_cha_incr_i = true;
		}
		ImGui::BeginDisabled(disable_cha_incr_i == true);
		if (ImGui::SmallButton("+1##chai1"))
		{
			cha_up++;
			abscore_total--;
		}
		ImGui::EndDisabled();
		//cha incr/decr ends here
		//<><><><><><><><><><><><><><><><>
		ImGui::BeginDisabled(abscore_total > 0);
		if (ImGui::Button("COMMIT SCORE INCREASES"))
		{
			lvlup.Set_Params(str_up, dex_up, con_up, intl_up, wis_up, cha_up);
			inv->change_rec(&lvlup);
			inv->invoke();
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndDisabled();
		ImGui::SameLine();
		if (ImGui::Button("CANCEL"))
		{
			abscore_total = 0;
			lvl_picked = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();

	}
}

void ImGuiUtil::Weaponry(Character& obj) {

}

void ImGuiUtil::Background(Character& obj, Invoker* inv) {
	
	BckgComm bckg(&obj);
	
	const char* bckg_selec[] =
	{
		" ", "Acolyte", "Charlatan", "Criminal", "Entertainer", "Folk Hero", "Guild Artisan", "Hermit", "Noble", "Outlander", "Sage", "Sailor", "Soldier", "Urchin"
	};
	/*
	const int acolyte_ind = 20;
	const int charlatan_ind = 21;
	const int criminal_ind = 22;
	const int entertainer_ind = 23;
	const int folkhero_ind = 24;
	const int guildartisan_ind = 25;
	const int hermit_ind = 26;
	const int noble_ind = 27;
	const int outlander_ind = 28;
	const int sage_ind = 29;
	const int sailor_ind = 30;
	const int soldier_ind = 31;
	const int urchin_ind = 32;
	*/
	static int bckg_current_idx = 0;
	static bool bckg_picked = false;

	ImVec2 bttn_sz(100.0f, 25.0f);
	
	ImGui::BeginDisabled(bckg_picked == true || lvl_picked == false);
	
	ImGui::Text("Background Selection: ");
	ImGui::NewLine();

	for (int i = 1; i < IM_ARRAYSIZE(bckg_selec); i++) {
		
		if (ImGui::Selectable(bckg_selec[i], bckg_current_idx == i, ImGuiSelectableFlags_None, bttn_sz)) {
			bckg_current_idx = i;
		}
		if (i % 3 != 0) {
			ImGui::SameLine();
		}
		if (i % 3 == 0) {
			ImGui::Spacing();
		}
		
	}
	ImGui::NewLine();
	if (ImGui::Button("SELECT")) {
		bckg_picked = true;
		bckg.Set_Params(bckg_current_idx);
		inv->change_rec(&bckg);
		inv->invoke();
	}
	/*
	if (ImGui::Button("SELECT")) {
		if (bckg_current_idx == 1)
		{
			bckg.Set_Params(acolyte_ind);
			inv->change_rec(&bckg);
			inv->invoke();

			bckg_picked = true;
		}
		else if (bckg_current_idx == 2)
		{
			bckg.Set_Params(charlatan_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else if (bckg_current_idx == 3)
		{
			bckg.Set_Params(criminal_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else if (bckg_current_idx == 4)
		{
			bckg.Set_Params(entertainer_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else if (bckg_current_idx == 5)
		{
			bckg.Set_Params(folkhero_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else if (bckg_current_idx == 6)
		{
			bckg.Set_Params(guildartisan_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else if (bckg_current_idx == 7)
		{
			bckg.Set_Params(hermit_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else if (bckg_current_idx == 8)
		{
			bckg.Set_Params(noble_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else if (bckg_current_idx == 9)
		{
			bckg.Set_Params(outlander_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else if (bckg_current_idx == 10)
		{
			bckg.Set_Params(sage_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else if (bckg_current_idx == 11)
		{
			bckg.Set_Params(sailor_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else if (bckg_current_idx == 12)
		{
			bckg.Set_Params(soldier_ind);
			inv->change_rec(&bckg);
			inv->invoke();
		
			bckg_picked = true;
		}
		else if (bckg_current_idx == 13)
		{
			bckg.Set_Params(urchin_ind);
			inv->change_rec(&bckg);
			inv->invoke();
			
			bckg_picked = true;
		}
		else {}
	}
	*/
	ImGui::EndDisabled();
}

void ImGuiUtil::Species_Tool_Proficiencies(Character& obj) {

}

void ImGuiUtil::Class_Tool_Proficiencies(Character& obj) {

}

void ImGuiUtil::Bckg_Tool_Proficiencies(Character& obj) {

}

void ImGuiUtil::Tool_Wpn_Proficiencies(Character& obj, Invoker* inv) {
	//const int not_available = 0;
	//const int assigned = 1;
	//const int selec_available = 2;

	//const int past_end_of_array = 37;

	const int species_mode = 1;
	const int class_mode = 2;
	const int bckg_mode = 3;

	static bool show_spec_tools = true;
	static bool show_clss_tools = false;
	static bool show_bckg_tools = false;
	static bool disable_tool_prof = false;

	

	const char* tool_display[] {

		"Alchemist's supplies", "Brewer's supplies", "Calligrapher's supplies", "Carpenter's tools", "Cartographer's tools",
		"Cobbler's tools", "Cook's utensils", "Glassblower's tools", "Jeweler's tools", "Leatherworker's tools",
		"Mason's tools", "Painter's supplies", "Potter's tools", "Smith's tools", "Tinker's tools", "Weaver's tools",
		"Woodcarver's tools", "Disguise kit", "Forgery kit", "Dice set", "Dragonchess set", "Playing card set",
		"Three-Dragon Ante set", "Herbalism kit", "Bagpipes", "Drum", "Dulcimer", "Flute", "Lute", "Lyre", "Horn",
		"Pan flute", "Shawm", "Viol", "Navigator's tools", "Poisoner's kit", "Thieves' tools"

	};
	
	ImGui::BeginDisabled(disable_tool_prof);
	if (show_spec_tools == true) {
		ImGui::Text("Species Tool Proficiencies");
		
		if (obj.tlprf_ceiling(species_mode)) {
			
			for (auto i : obj.retr_toolprof_inds(species_mode)) {
				const char* label = tool_display[i];
				//ImGui::BeginDisabled(i->first == false);
				ImGui::BeginDisabled(obj.hit_ceiling(i, species_mode));
				//ImGui::Checkbox(label, &i->first);
				ImGui::Checkbox(label, &obj.prof_toggle(i));
				obj.prof_assign(i, species_mode);
				ImGui::EndDisabled();
			}
		}
		else {

			for (auto j : obj.retr_toolprof_inds(species_mode)) {
				const char* label = tool_display[j];
				ImGui::BeginDisabled(obj.prof_collision_ctrl(j, species_mode));
				ImGui::Checkbox(label, &obj.prof_toggle(j));
				obj.prof_assign(j, species_mode);
				ImGui::EndDisabled();
			}
		}
		
		ImGui::BeginDisabled(true);
		ImGui::Button("<- BACK##4");
		ImGui::EndDisabled();
		ImGui::SameLine();
		if (ImGui::Button("Class Tool Profs ->")) {
			show_spec_tools = false;
			show_clss_tools = true;
		}
	}
	if (show_clss_tools == true) {
		ImGui::Text("Class Tool Proficiencies");

		if (obj.tlprf_ceiling(class_mode)) {

			for (auto i : obj.retr_toolprof_inds(class_mode)) {
				const char* label = tool_display[i];
				ImGui::BeginDisabled(obj.hit_ceiling(i, class_mode));
				ImGui::Checkbox(label, &obj.prof_toggle(i));
				obj.prof_assign(i, class_mode);
				ImGui::EndDisabled();
			}
		}
		else {

			for (auto j : obj.retr_toolprof_inds(class_mode)) {
				const char* label = tool_display[j];
				ImGui::BeginDisabled(obj.prof_collision_ctrl(j, class_mode));
				ImGui::Checkbox(label, &obj.prof_toggle(j));
				obj.prof_assign(j, class_mode);
				ImGui::EndDisabled();
			}
		}

		if (ImGui::Button("<- BACK##5")) {
			show_clss_tools = false;
			show_spec_tools = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Background Tool Profs ->")) {
			show_clss_tools = false;
			show_bckg_tools = true;
		}
	}
	if (show_bckg_tools == true) {
		ImGui::Text("Background Tool Proficiencies");

		if (obj.tlprf_ceiling(bckg_mode)) {

			for (auto i : obj.retr_toolprof_inds(bckg_mode)) {
				const char* label = tool_display[i];
				ImGui::BeginDisabled(obj.hit_ceiling(i, bckg_mode));
				ImGui::Checkbox(label, &obj.prof_toggle(i));
				obj.prof_assign(i, bckg_mode);
				ImGui::EndDisabled();
			}
		}
		else {
			for (auto j : obj.retr_toolprof_inds(bckg_mode)) {
				const char* label = tool_display[j];
				ImGui::BeginDisabled(obj.prof_collision_ctrl(j, bckg_mode));
				ImGui::Checkbox(label, &obj.prof_toggle(j));
				obj.prof_assign(j, bckg_mode);
				ImGui::EndDisabled();
			}
		}
		//ImGui::BeginDisabled(disable_tool_prof);
		if (ImGui::Button("<- BACK##6")) {
			show_bckg_tools = false;
			show_clss_tools = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("COMMIT TOOL PROF CHOICES")) {
			//obj.tool_prof_commit();
			disable_tool_prof = true;
			obj.assign_tool_profs();
			obj.print_tool_vecs();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL##tool_prof")) {
			disable_tool_prof = false;
		}
		//ImGui::EndDisabled();
	}
	ImGui::EndDisabled();
}

void ImGuiUtil::Skill_Proficiencies(Character& obj, Invoker* inv) {
	
	const int species_mode = 1;
	const int class_mode = 2;
	const int bckg_mode = 3;

	static bool show_spec_skill = true;
	static bool show_clss_skill = false;
	static bool show_bckg_skill = false;
	static bool disable_skill_prof = false;

	const char* skill_display[]{
		"Athletics", "Acrobatics", "Sleight of Hand", "Stealth", "Arcana", "History",
		"Investigation", "Nature", "Religion", "Animal Handling", "Insight", "Medicine",
		"Perception", "Survival", "Deception", "Intimidation", "Performance", "Persuasion"
	};

	ImGui::BeginDisabled(disable_skill_prof);
	if (show_spec_skill == true) {
		ImGui::Text("Species Skill Proficiencies");

		if (obj.skillprf_ceiling(species_mode)) {

			for (const auto& i : obj.retr_skillprof_inds(species_mode)) {
				const char* label = skill_display[i];
				//ImGui::BeginDisabled(i->first == false);
				ImGui::BeginDisabled(obj.skill_hit_ceiling(i, species_mode));
				//ImGui::Checkbox(label, &i->first);
				ImGui::Checkbox(label, &obj.skill_prof_toggle(i));
				obj.skill_prof_assign(i, species_mode);
				ImGui::EndDisabled();
			}
		}
		else {

			for (const auto& j : obj.retr_skillprof_inds(species_mode)) {
				const char* label = skill_display[j];
				ImGui::BeginDisabled(obj.skill_prof_collision_ctrl(j, species_mode));
				ImGui::Checkbox(label, &obj.skill_prof_toggle(j));
				obj.skill_prof_assign(j, species_mode);
				ImGui::EndDisabled();
			}
		}

		ImGui::BeginDisabled(true);
		ImGui::Button("<- BACK##1");
		ImGui::EndDisabled();
		ImGui::SameLine();
		if (ImGui::Button("Class Skill Profs ->")) {
			show_spec_skill = false;
			show_clss_skill = true;
		}
	}
	if (show_clss_skill == true) {
		ImGui::Text("Class Skill Proficiencies");

		if (obj.skillprf_ceiling(class_mode)) {

			for (auto i : obj.retr_skillprof_inds(class_mode)) {
				const char* label = skill_display[i];
				ImGui::BeginDisabled(obj.skill_hit_ceiling(i, class_mode));
				ImGui::Checkbox(label, &obj.skill_prof_toggle(i));
				obj.skill_prof_assign(i, class_mode);
				ImGui::EndDisabled();
			}
		}
		else {

			for (auto j : obj.retr_skillprof_inds(class_mode)) {
				const char* label = skill_display[j];
				ImGui::BeginDisabled(obj.skill_prof_collision_ctrl(j, class_mode));
				ImGui::Checkbox(label, &obj.skill_prof_toggle(j));
				obj.skill_prof_assign(j, class_mode);
				ImGui::EndDisabled();
			}
		}

		if (ImGui::Button("<- BACK##2")) {
			show_clss_skill = false;
			show_spec_skill = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Background Skill Profs ->")) {
			show_clss_skill = false;
			show_bckg_skill = true;
		}
	}
	if (show_bckg_skill == true) {
		ImGui::Text("Background Skill Proficiencies");

		if (obj.skillprf_ceiling(bckg_mode)) {

			for (auto i : obj.retr_skillprof_inds(bckg_mode)) {
				const char* label = skill_display[i];
				ImGui::BeginDisabled(obj.skill_hit_ceiling(i, bckg_mode));
				ImGui::Checkbox(label, &obj.skill_prof_toggle(i));
				obj.skill_prof_assign(i, bckg_mode);
				ImGui::EndDisabled();
			}
		}
		else {
			for (auto j : obj.retr_skillprof_inds(bckg_mode)) {
				const char* label = skill_display[j];
				ImGui::BeginDisabled(obj.skill_prof_collision_ctrl(j, bckg_mode));
				ImGui::Checkbox(label, &obj.skill_prof_toggle(j));
				obj.skill_prof_assign(j, bckg_mode);
				ImGui::EndDisabled();
			}
		}

		if (ImGui::Button("<- BACK##3")) {
			show_bckg_skill = false;
			show_clss_skill = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("COMMIT SKILLS PROF CHOICES")) {
			//obj.tool_prof_commit();
			disable_skill_prof = true;
			//obj.assign_tool_profs();
			//obj.print_tool_vecs();
			obj.assign_skill_profs();
			obj.print_skill_vecs();
		}
		ImGui::SameLine();
		if (ImGui::Button("CANCEL##skills_prof")) {
			disable_skill_prof = false;
		}
	}
	ImGui::EndDisabled();
}


void ImGuiUtil::BeyondFirstLevel(Character& obj, Invoker* cmt_inv) {
	
	ImGui::Begin("BEYOND FIRST LEVEL", nullptr, ImGuiWindowFlags_NoCollapse);
	ImGui::Columns(3);

	//ImGui::Text("Level Selection: ");

	ImGui::SameLine();

	//HelpMarker("You can click and drag to desired level, or double click to enter manually");

	LevelUp(obj, cmt_inv);

	ImGui::NewLine();

	Background(obj, cmt_inv);
	
	ImGui::NextColumn();

	Skill_Proficiencies(obj, cmt_inv);

	ImGui::NextColumn();

	Tool_Wpn_Proficiencies(obj, cmt_inv);

	ImGui::End();
}

void ImGuiUtil::SkillsProf(proficiency& prof_obj) {
	ImGui::Begin("PROFICIENCIES, EQUIPMENT, & ARMORY", nullptr, ImGuiWindowFlags_NoCollapse);
	ImGui::Columns(3);

	

	

	ImGui::NextColumn();

	ImGui::End();
}

void ImGuiUtil::ScoreDisplay(Character& obj)
{
	ImGui::NextColumn();
	ImGui::Text("Strength:      %d", obj.retr_absumm().str);
	ImGui::SameLine();
	ImGui::Text(" + (%d)", obj.retr_absumm().strabm);
	ImGui::Spacing();
	ImGui::Text("Dexterity:     %d", obj.retr_absumm().dex);
	ImGui::SameLine();
	ImGui::Text(" + (%d)", obj.retr_absumm().dexabm);
	ImGui::Spacing();
	ImGui::Text("Constitution:  %d", obj.retr_absumm().con);
	ImGui::SameLine();
	ImGui::Text(" + (%d)", obj.retr_absumm().conabm);
	ImGui::Spacing();
	ImGui::Text("Intelligence:  %d", obj.retr_absumm().intl);
	ImGui::SameLine();
	ImGui::Text(" + (%d)", obj.retr_absumm().intlabm);
	ImGui::Spacing();
	ImGui::Text("Wisdom:        %d", obj.retr_absumm().wis);
	ImGui::SameLine();
	ImGui::Text(" + (%d)", obj.retr_absumm().wisabm);
	ImGui::Spacing();
	ImGui::Text("Charisma:      %d", obj.retr_absumm().cha);
	ImGui::SameLine();
	ImGui::Text(" + (%d)", obj.retr_absumm().chaabm);
	ImGui::Spacing();
	ImGui::Text("Armor Class (AC): %d", obj.retr_absumm().armor_class);
	ImGui::SameLine();
}

void ImGuiUtil::Points_or_Roll() {
	ImGui::Begin("ABILITY SCORE CONSOLE", nullptr, ImGuiWindowFlags_NoCollapse);
	
	if (ImGui::Button("ROLL FOR SCORES")) {
		abroll = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("POINT PURCHASE SYSTEM")) {
		pointbuy = true;
	}

	ImGui::End();
}

void ImGuiUtil::AbilityScorePkg(Character& obj, RollComm& roll_bttn, MTwisterComm& roll_bttn_mt, CommitRollComm& cmt, Invoker* inv) {
	
	
	ImGui::Begin("ABILITY SCORE CONSOLE", nullptr, ImGuiWindowFlags_NoCollapse);
	//size of roll history vector determines roll count now
	if (obj.retr_roll_hist().size() >= 3) {
		three_rolls = true;
	}
	//==================================
	//this block enabled/disabled by rng_select boolean
	ImGui::BeginDisabled((species_picked == false && clss_picked == false) || (species_picked == true && clss_picked == false));

	ImGui::BeginDisabled(rng_select);

	ImGui::Text("RNG Type: ");
	ImGui::SameLine();
	ImGui::RadioButton("Basic", &srand_mersenne, 1);
	ImGui::SameLine();
	ImGui::RadioButton("Advanced", &srand_mersenne, 2);
	ImGui::SameLine();
	HelpMarker("Choose which RNG you wish to use. BASIC uses a simple pseudo-random number generator. ADVANCED utilizes a Mersenne Twister to emulate truly random number generation.  NOTE: using the BASIC RNG will give you more evenly distributed and higher scores, and is useful for newer players.");


	ImGui::EndDisabled();
	//EndDisabled() bookends rng_select boolean trigger
	//==========================================

	//++++++++++++++++++++++++++++++++++++++++++++++
	//this block enabled/disabled by disabled_marker boolean
	ImGui::BeginDisabled(disabled_marker);

	if (three_rolls == true)
	{
		disabled_marker = true;
	}
	if (three_rolls == false)
	{
		disabled_marker = false;
	}

	if (ImGui::Button("PRESS TO ROLL"))
	{
		press_to_roll = true;
		//three_rollctr++;
		//std::cout << "counter: " << three_rollctr << std::endl;
		if (srand_mersenne == 1 || srand_mersenne == 2) {
			if (press_to_roll == true) {
				rng_select = true;
			}
		}

	}
	ImGui::SameLine();
	HelpMarker("Press the 'PRESS TO ROLL' button to automatically generate a random spread of scores for your abilities.  You can roll up to three times.");

	if (press_to_roll == true)
	{
		if (srand_mersenne == 1) {
			inv->change_rec(&roll_bttn);
			inv->invoke();
		}
		if (srand_mersenne == 2) {
			inv->change_rec(&roll_bttn_mt);
			inv->invoke();
		}

		press_to_roll = false;
	}

	ImGui::EndDisabled();

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++

	ImGui::Text("Ability Scores");

	Histogram(obj);

	ImGui::BeginDisabled(is_commit_clicked);

	Avail_Rolls(obj);

	ImGui::Spacing();

	if (ImGui::Button("COMMIT SCORE ROLL"))
	{
		inv->change_rec(&cmt);
		inv->invoke();
		//cmt_inv.invoke();

		is_commit_clicked = true;
		swap_disabled = true;
		//show_window = false;
		abscore_complete = true;
	}
	ImGui::EndDisabled();

	ImGui::EndDisabled();

	ImGui::End();
}
/*
void ImGuiUtil::PointValidate(int counter, std::vector<int>& container, int index) {
	if (counter == 0) {
		container.at(index) = 8;
	}
	else if (counter == 1) {
		container.at(index) = 9;
	}
	else if (counter == 2) {
		container.at(index) = 10;
	}
	else if (counter == 3) {
		container.at(index) = 11;
	}
	else if (counter == 4) {
		container.at(index) = 12;
	}
	else if (counter == 5) {
		container.at(index) = 13;
	}
	//else if (counter == 6) {}
	else if (counter == 6 || counter == 7) {
		container.at(index) = 14;
	}
	//else if (counter == 8) {}
	else if (counter == 8 || counter == 9) {
		container.at(index) = 15;
	}
	else {
		std::cout << "PointValidate() bad data" << std::endl;
	}
}
*/

int& ImGuiUtil::Retr_PurchTotal(Character& obj) {
	return obj.fetch_point_buy_total();
}

int& ImGuiUtil::Retr_PurchSpent(Character& obj) {
	return obj.fetch_point_spent_total();
}

int ImGuiUtil::Retr_PurchMap_Cost(Character& obj, int key) {
	return obj.fetch_purchmap_cost(key);
}

void ImGuiUtil::PurchaseDecr(Character& obj, PointPurchButtonComm& prs, Invoker* inv, int button_id, int index) {
	const char descend = 'd';
	//bool disable_toggle = false;

	//ImGui::BeginDisabled(disable_toggle);
	ImGui::PushID(button_id);
	if (ImGui::Button(" - ", ImVec2(36.0f, 0.0f))) {
		//disable_toggle = obj.point_purchase(descend, index);
		//obj.point_purchase(descend, index);
		prs.Set_Params(descend, index);
		inv->change_rec(&prs);
		inv->invoke();
	};
	ImGui::PopID();
	//ImGui::EndDisabled();
}

void ImGuiUtil::PurchaseIncr(Character& obj, PointPurchButtonComm& prs, Invoker* inv, int button_id, int index) {
	const char ascend = 'u';
	//bool disable_toggle = false;

	//ImGui::BeginDisabled(disable_toggle);
	ImGui::PushID(button_id);
	if (ImGui::Button(" + ", ImVec2(36.0f, 0.0f))) {
		//disable_toggle = obj.point_purchase(ascend, index);
		//obj.point_purchase(ascend, index);
		prs.Set_Params(ascend, index);
		inv->change_rec(&prs);
		inv->invoke();
	}
	ImGui::PopID();
	///ImGui::EndDisabled();
}

void ImGuiUtil::PointPurchase(Character& obj, PointPurchButtonComm& prs, CommitPointBuyComm& pcmt, Invoker* inv) {
	ImGui::Begin("POINT PURCHASE CONSOLE", nullptr, ImGuiWindowFlags_NoCollapse);

	ImGui::Text("Points available: %d", Retr_PurchTotal(obj));
	ImGui::Text("Points spent: %d", Retr_PurchSpent(obj));

	float histogram_conv_pp[6]; //we need floats for the integer values to show up on an ImGui histogram, so we're gonna static cast as float below and shove into a raw array

	for (int a = 0; a < obj.retr_purchdisplay().size(); a++)
	{
		histogram_conv_pp[a] = obj.retr_purchdisplay().at(a);
	}

	ImGui::PlotHistogram("##Point purchase histo", histogram_conv_pp, IM_ARRAYSIZE(histogram_conv_pp), 0, NULL, 1.0, 20.0, ImVec2(520.0f, 200.0f));
	int ymarker = 0;
	for (auto y : obj.retr_skills()) {
		//int ymarker = 0;
		ImGui::PushID(ymarker);
		const char* sbuffer;
		sbuffer = y.c_str();
		ImGui::Button(sbuffer, ImVec2(80.0f, 60.0f));
		ImGui::PopID();
		ImGui::SameLine();
		ymarker++;
	}

	ImGui::Spacing();

	const char* ppdisplay_array[6]; //creating a swap array for drag and drop of const char*; will be filled with data from the init_scores vector

	//for (int v = 0; v < obj.retr_init_rolls().size(); v++)
	for (int z = 0; z < obj.retr_purchdisplay().size(); z++) {
		//long laborious process to meet the const char* label reqs for buttons and text --
		//use sprintf_s to gt the ints to chars and shunt each int-to-char to the Button
		char ppibuffer[50];
		int ppcti = 0;
		ppcti = obj.retr_purchdisplay().at(z); //we also need an explicit int to sort values
		sprintf_s(ppibuffer, "%d", ppcti);
		const char* ppsi = ppibuffer;
		ppdisplay_array[z] = ppsi;

		ImGui::PushID(z);

		ImGui::Button(ppsi, ImVec2(80.0f, 60.0f));

		ImGui::PopID();
		ImGui::SameLine();
	}

	ImGui::Spacing();
	ImGui::BeginDisabled(is_commit_clicked);
	ImGui::BeginDisabled(clss_picked == false);
	const int id_stack[12]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//const int key_stack[8]{ 8, 9, 10, 11, 12, 13, 14, 15 };
	//int index_marker = 0;
	const int index_stack[12]{ 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };
	for (int i = 0; i < 12; i++) {
		if (i%2 == 0) {
			if (i != 0) {
				ImGui::SameLine();
			}
			PurchaseDecr(obj, prs, inv, id_stack[i], index_stack[i]);
		}
		else {
			ImGui::SameLine();
			PurchaseIncr(obj, prs, inv, id_stack[i], index_stack[i]);
			//++index_marker;
		}
		//std::cout << "index_marker: " << index_stack[i] << "id_stack[" << i << "] = " << id_stack[i] << std::endl;
	}

	ImGui::Spacing();
	if (ImGui::Button("COMMIT")) {
		//obj.retr_init_rolls() = purchdisplay;
		//cmt.Set_Params(purchdisplay);
		inv->change_rec(&pcmt);
		inv->invoke();
		is_commit_clicked = true;
		swap_disabled = true;
		//show_window = false;
		abscore_complete = true;
	}
	ImGui::EndDisabled();
	ImGui::EndDisabled();
	ImGui::End();
}
/*
void ImGuiUtil::PointPurchase(Character& obj, CommitPointBuyComm& cmt, Invoker* inv) {
	//TO DO:
	// - Method returning boolean for BeginDisabled
	// - Method to grab all purchase variables from abilityscore, not from imgui_util
	ImGui::Begin("POINT PURCHASE CONSOLE", nullptr, ImGuiWindowFlags_NoCollapse);
	
	//ImGui::BeginDisabled((species_picked == false && clss_picked == false) || (species_picked == true && clss_picked == false));
	ImGui::BeginDisabled(clss_picked == false);
	//ImGui::Text("Points available: %d", purchtotal);
	ImGui::Text("Points available: %d", Retr_PurchTotal(obj));
	ImGui::Text("Points spent: %d", Retr_PurchSpent(obj));
		
	float histogram_conv_pp[6]; //we need floats for the integer values to show up on an ImGui histogram, so we're gonna static cast as float below and shove into a raw array
	
	for (int a = 0; a < purchdisplay.size(); a++)
	{
		histogram_conv_pp[a] = purchdisplay.at(a);
	}

	ImGui::PlotHistogram("##Point purchase histo", histogram_conv_pp, IM_ARRAYSIZE(histogram_conv_pp), 0, NULL, 1.0, 20.0, ImVec2(520.0f, 200.0f));
	int ymarker = 0;
	for (auto y : obj.retr_skills()) {
		//int ymarker = 0;
		ImGui::PushID(ymarker);
		const char* sbuffer;
		sbuffer = y.c_str();
		ImGui::Button(sbuffer, ImVec2(80.0f, 60.0f));
		ImGui::PopID();
		ImGui::SameLine();
		ymarker++;
	}

	ImGui::Spacing();
	
	const char* ppdisplay_array[6]; //creating a swap array for drag and drop of const char*; will be filled with data from the init_scores vector

	//for (int v = 0; v < obj.retr_init_rolls().size(); v++)
	for (int z = 0; z < purchdisplay.size(); z++) {
		//long laborious process to meet the const char* label reqs for buttons and text --
		//use sprintf_s to gt the ints to chars and shunt each int-to-char to the Button
		char ppibuffer[50];
		int ppcti = 0;
		ppcti = purchdisplay.at(z); //we also need an explicit int to sort values
		sprintf_s(ppibuffer, "%d", ppcti);
		const char* ppsi = ppibuffer;
		ppdisplay_array[z] = ppsi;

		ImGui::PushID(z);

		ImGui::Button(ppsi, ImVec2(80.0f, 60.0f));

		ImGui::PopID();
		ImGui::SameLine();
	}
	
	ImGui::Spacing();

	ImGui::BeginDisabled(is_commit_clicked);
	
	const int id_stack[12]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	const int key_stack[8]{ 8, 9, 10, 11, 12, 13, 14, 15 };

	strcutoff = ((Retr_PurchTotal(obj) - Retr_PurchMap_Cost(obj, strppm + 1)) < 0) ? true : false;
	ImGui::BeginDisabled(strppm <= 0);
	ImGui::PushID(id_stack[0]);
	if (ImGui::Button(" - ", ImVec2(36.0f, 0.0f))) {
		//Retr_PurchTotal(obj) += purchase_stairs[strppm].ppcost;
		Retr_PurchTotal(obj) += Retr_PurchMap_Cost(obj, strppm);
		//Retr_PurchSpent(obj) -= purchase_stairs[strppm].ppcost;
		Retr_PurchSpent(obj) -= Retr_PurchMap_Cost(obj, strppm);
		strppm--;
		std::cout << strppm << std::endl;
		purchdisplay.at(0) = purchase_stairs[strppm].ppscore;
		
	};
	ImGui::PopID();
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(strppm >= 7 || strcutoff);
	ImGui::PushID(id_stack[1]);
	if (ImGui::Button(" + ", ImVec2(36.0f, 0.0f))) {
		strppm++;
		std::cout << strppm << std::endl;
		purchdisplay.at(0) = purchase_stairs[strppm].ppscore;
		Retr_PurchTotal(obj) -= purchase_stairs[strppm].ppcost;
		Retr_PurchSpent(obj) += purchase_stairs[strppm].ppcost;
		
	};
	ImGui::PopID();
	ImGui::EndDisabled();
	
	ImGui::SameLine();
	dexcutoff = ((purchtotal - purchase_stairs[dexppm + 1].ppcost) < 0) ? true : false;
	ImGui::BeginDisabled(dexppm <= 0);
	ImGui::PushID(id_stack[2]);
	if (ImGui::Button(" - ", ImVec2(36.0f, 0.0f))) {
		purchtotal += purchase_stairs[dexppm].ppcost;
		purchspent -= purchase_stairs[dexppm].ppcost;
		dexppm--;
		std::cout << dexppm << std::endl;
		purchdisplay.at(1) = purchase_stairs[dexppm].ppscore;
	};
	ImGui::PopID();
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(dexppm >= 7 || dexcutoff);
	ImGui::PushID(id_stack[3]);
	if (ImGui::Button(" + ", ImVec2(36.0f, 0.0f))) {
		dexppm++;
		std::cout << dexppm << std::endl;
		purchdisplay.at(1) = purchase_stairs[dexppm].ppscore;
		purchtotal -= purchase_stairs[dexppm].ppcost;
		purchspent += purchase_stairs[dexppm].ppcost;
	};
	ImGui::PopID();
	ImGui::EndDisabled();

	ImGui::SameLine();
	concutoff = ((purchtotal - purchase_stairs[conppm + 1].ppcost) < 0) ? true : false;
	ImGui::BeginDisabled(conppm <= 0);
	ImGui::PushID(id_stack[4]);
	if (ImGui::Button(" - ", ImVec2(36.0f, 0.0f))) {
		purchtotal += purchase_stairs[conppm].ppcost;
		purchspent -= purchase_stairs[conppm].ppcost;
		conppm--;
		std::cout << conppm << std::endl;
		purchdisplay.at(2) = purchase_stairs[conppm].ppscore;
	};
	ImGui::PopID();
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(conppm >= 7 || concutoff);
	ImGui::PushID(id_stack[5]);
	if (ImGui::Button(" + ", ImVec2(36.0f, 0.0f))) {
		conppm++;
		purchdisplay.at(2) = purchase_stairs[conppm].ppscore;
		purchtotal -= purchase_stairs[conppm].ppcost;
		purchspent += purchase_stairs[conppm].ppcost;
	};
	ImGui::PopID();
	ImGui::EndDisabled();

	ImGui::SameLine();
	intlcutoff = ((purchtotal - purchase_stairs[intlppm + 1].ppcost) < 0) ? true : false;
	ImGui::BeginDisabled(intlppm <= 0);
	ImGui::PushID(id_stack[6]);
	if (ImGui::Button(" - ", ImVec2(36.0f, 0.0f))) {
		purchtotal += purchase_stairs[intlppm].ppcost;
		purchspent -= purchase_stairs[intlppm].ppcost;
		intlppm--;
		purchdisplay.at(3) = purchase_stairs[intlppm].ppscore;
	};
	ImGui::PopID();
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(intlppm >= 7 || intlcutoff);
	ImGui::PushID(id_stack[7]);
	if (ImGui::Button(" + ", ImVec2(36.0f, 0.0f))) {
		intlppm++;
		purchdisplay.at(3) = purchase_stairs[intlppm].ppscore;
		purchtotal -= purchase_stairs[intlppm].ppcost;
		purchspent += purchase_stairs[intlppm].ppcost;
	};
	ImGui::PopID();
	ImGui::EndDisabled();

	ImGui::SameLine();
	wiscutoff = ((purchtotal - purchase_stairs[wisppm + 1].ppcost) < 0) ? true : false;
	ImGui::BeginDisabled(wisppm <= 0);
	ImGui::PushID(id_stack[8]);
	if (ImGui::Button(" - ", ImVec2(36.0f, 0.0f))) {
		purchtotal += purchase_stairs[wisppm].ppcost;
		purchspent -= purchase_stairs[wisppm].ppcost;
		wisppm--;
		purchdisplay.at(4) = purchase_stairs[wisppm].ppscore;
	};
	ImGui::PopID();
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(wisppm >= 7 || wiscutoff);
	ImGui::PushID(id_stack[9]);
	if (ImGui::Button(" + ", ImVec2(36.0f, 0.0f))) {
		wisppm++;
		purchdisplay.at(4) = purchase_stairs[wisppm].ppscore;
		purchtotal -= purchase_stairs[wisppm].ppcost;
		purchspent += purchase_stairs[wisppm].ppcost;
	};
	ImGui::PopID();
	ImGui::EndDisabled();

	ImGui::SameLine();
	chacutoff = ((purchtotal - purchase_stairs[chappm + 1].ppcost) < 0) ? true : false;
	ImGui::BeginDisabled(chappm <= 0);
	ImGui::PushID(id_stack[10]);
	if (ImGui::Button(" - ", ImVec2(36.0f, 0.0f))) {
		purchtotal += purchase_stairs[chappm].ppcost;
		purchspent -= purchase_stairs[chappm].ppcost;
		chappm--;
		purchdisplay.at(5) = purchase_stairs[chappm].ppscore;
	};
	ImGui::PopID();
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(chappm >= 7 || chacutoff);
	ImGui::PushID(id_stack[11]);
	if (ImGui::Button(" + ", ImVec2(36.0f, 0.0f))) {
		chappm++;
		purchdisplay.at(5) = purchase_stairs[chappm].ppscore;
		purchtotal -= purchase_stairs[chappm].ppcost;
		purchspent += purchase_stairs[chappm].ppcost;
	};
	ImGui::PopID();
	ImGui::EndDisabled();

	ImGui::Spacing();
	if (ImGui::Button("COMMIT")) {
		//obj.retr_init_rolls() = purchdisplay;
		cmt.Set_Params(purchdisplay);
		inv->change_rec(&cmt);
		inv->invoke();
		is_commit_clicked = true;
		swap_disabled = true;
		//show_window = false;
		abscore_complete = true;
	}

	ImGui::EndDisabled();

	ImGui::EndDisabled();

	ImGui::End();
}
*/
void ImGuiUtil::SideBar(Character& obj) {
	ImGui::Begin("CHARACTER OVERVIEW", nullptr, ImGuiWindowFlags_NoDecoration);
	int display_str = obj.retr_absumm().str;
	int display_strabm = obj.retr_absumm().strabm;
	int display_dex = obj.retr_absumm().dex;
	int display_dexabm = obj.retr_absumm().dexabm;
	int display_con = obj.retr_absumm().con;
	int display_conabm = obj.retr_absumm().conabm;
	int display_intl = obj.retr_absumm().intl;
	int display_intlabm = obj.retr_absumm().intlabm;
	int display_wis = obj.retr_absumm().wis;
	int display_wisabm = obj.retr_absumm().wisabm;
	int display_cha = obj.retr_absumm().cha;
	int display_chaabm = obj.retr_absumm().chaabm;

	ImGui::Text("CHARACTER OVERVIEW");
	ImGui::Spacing();
	ImGui::Text("-- Ability Scores --");
	ImGui::Spacing();
	ImGui::Text("Strength:     %d", display_str);
	ImGui::SameLine();
	ImGui::Text(" ( %d )", display_strabm);
	ImGui::Text("Dexterity:    %d", display_dex);
	ImGui::SameLine();
	ImGui::Text(" ( %d )", display_dexabm);
	ImGui::Text("Constitution: %d", display_con);
	ImGui::SameLine();
	ImGui::Text(" ( %d )", display_conabm);
	ImGui::Text("Intelligence: %d", display_intl);
	ImGui::SameLine();
	ImGui::Text(" ( %d )", display_intlabm);
	ImGui::Text("Wisdom:       %d", display_wis);
	ImGui::SameLine();
	ImGui::Text(" ( %d )", display_wisabm);
	ImGui::Text("Charisma:     %d", display_cha);
	ImGui::SameLine();
	ImGui::Text(" ( %d )", display_chaabm);
	
	



	ImGui::End();
}

void ImGuiUtil::WindowPos(int mode) {
	//0 top left
	//1 bottom left
	//2 top right
	//3 bottom right

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
	ImVec2 work_size = viewport->WorkSize;
	ImVec2 window_pos, window_pos_pivot;

	if (mode == 0) {
		window_pos.x = work_pos.x;
		window_pos.y = work_pos.y;
		window_pos_pivot.x = 0.0f;
		window_pos_pivot.y = 0.0f;
	}
	else if (mode == 1) {
		const float spec_pos = 550.0f;
		window_pos.x = work_pos.x + spec_pos;
		window_pos.y = work_pos.y;
		window_pos_pivot.x = 0.0f;
		window_pos_pivot.y = 0.0f;
	}
	else if (mode == 2) {
		const float class_pos = 1100.0f;
		window_pos.x = work_pos.x + class_pos;
		window_pos.y = work_pos.y;
		window_pos_pivot.x = 0.0f;
		window_pos_pivot.y = 0.0f;
	}
	else if (mode == 3) {
		const float sidebar_pos = 1920.0f;
		window_pos.x = work_pos.x + sidebar_pos;
		window_pos.y = work_pos.y;
		window_pos_pivot.x = 1.0f;
		window_pos_pivot.y = 0.0f;
	}
	else if (mode == 4) {
		const float cons_pos = 550.0f;
		window_pos.x = work_pos.x;
		window_pos.y = work_pos.y + cons_pos;
		window_pos_pivot.x = 0.0f;
		window_pos_pivot.y = 0.0f;
	}
	else {
		std::cout << "bad mode value passed to WindowPos()" << std::endl;
	}
	
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
}

void ImGuiUtil::WindowSize(int mode) {
	if (mode == 0) {
		ImVec2 sz(550, 550);
		ImGui::SetNextWindowSize(sz);
	}
	else if (mode == 1) {
		ImVec2 sz(500, 550);
		ImGui::SetNextWindowSize(sz);
	}
	else if (mode == 2) {
		ImVec2 sz(270, 970);
		ImGui::SetNextWindowSize(sz);
	}
	else if (mode == 3) {
		ImVec2 sz(1650, 425);
		ImGui::SetNextWindowSize(sz);
	}
	else {
		std::cout << "improper mode parameter in WindowSize()" << std::endl;
	}
}

void ImGuiUtil::Update(bool mode, Character& obj, file_dialogue& handler) {

	RollComm roll_bttn(&obj);

	MTwisterComm roll_bttn_mt(&obj);
	
	PointPurchButtonComm prs(&obj);

	CommitRollComm cmt(&obj);

	CommitPointBuyComm pcmt(&obj);
	
	SaveComm save(&handler, &obj);
	
	OpenComm open(&handler, &obj);

	Invoker inv(&roll_bttn);


	if (mode == true) {
		ImGui::ShowDemoWindow();
	}
	
	


	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_MenuBar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	
	
	

	//ImGui::Begin("Character Builder Console", nullptr, window_flags);
	
	//ImGui::Columns(3);
	//ImGui::SetColumnOffset(1, 600);

	static bool filenew = false;
	static bool fileopen = false;
	static bool filesave = false;
	static bool fileexit = false;

	//static bool abroll = true;
	//static bool pointbuy = false;

	WindowPos(0);
	WindowSize(0);

	Species_Selection(obj, &inv);

	WindowPos(1);
	WindowSize(0);

	ClassSelection(obj, &inv);

	
	if (abroll == false && pointbuy == false) {
		WindowPos(2);
		WindowSize(0);
		Points_or_Roll();

	}
	if (abroll) {
		WindowPos(2);
		WindowSize(0);
		AbilityScorePkg(obj, roll_bttn, roll_bttn_mt, cmt, &inv); 
	}
	else if (pointbuy) {
		WindowPos(2);
		WindowSize(0);
		//PointPurchase(obj, pcmt, &inv);
		PointPurchase(obj, prs, pcmt, &inv);
	}
	else {

	}

	WindowPos(3);
	WindowSize(2);
	ImGui::SetNextWindowBgAlpha(0.75f);
	SideBar(obj);

	WindowPos(4);
	WindowSize(3);
	BeyondFirstLevel(obj, &inv);

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("FILE")) {

			ImGui::MenuItem("New", NULL, &filenew);
			ImGui::MenuItem("Open", NULL, &fileopen);
			ImGui::MenuItem("Save", NULL, &filesave);
			ImGui::MenuItem("Exit", NULL, &fileexit);
			
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("SETTINGS")) {

			ImGui::MenuItem("Roll for Scores", NULL, &abroll);
			ImGui::MenuItem("Point Purchase Scores", NULL, &pointbuy);

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("ABOUT")) {

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	
}

void ImGuiUtil::Render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiUtil::Shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}