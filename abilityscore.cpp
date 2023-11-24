#include "abilityscore.h"
//#include <iostream>
//#include <string>
//#include <vector>
//#include <cstdlib>
#include <algorithm>
#include <random>

/*
TO DO:
- fix iterator issues with the vector.erase() for the skills list (low priority with GUI implementation)
*/

std::vector<std::vector<int>>& Abilityscore::retr_roll_hist() {
    
    return roll_hist;

}

int Abilityscore::diceRoll_d6T_mersenne_twister() {
    static std::random_device rd;
    static std::mt19937 rng{ rd() };
    
    //std::mt19937 mt(time(nullptr));
    std::uniform_int_distribution<int> dist(min_roll, max_roll);

    //return dist(mt);
    return dist(rng);
}

int Abilityscore::diceRoll_d6T()
{
    int result = 0;
    result = rand() % max_roll + min_roll;
    return result;
}

void Abilityscore::return_rolls_mersenne_twister() {
    roll_results.clear();
    int y = 0;
    for (int i = 0; i < 4; i++) {
        y = diceRoll_d6T_mersenne_twister();
        roll_results.push_back(y);
    }
}

void Abilityscore::return_rolls()
{
    //we have to clear the roll_results vector each time
    //to ensure that we don't keep pushing back new values
    roll_results.clear();
    int y = 0;
    for (int i = 0; i < 4; i++)
    {
        y = diceRoll_d6T();
        roll_results.push_back(y);
    }
}

int Abilityscore::sortnsum_rolls()
{
    int y = max_roll;
    int roll_sum = 0;

    for (auto i : roll_results)
    {
        if (i < y)
        {
            y = i;
        }
        else
        {
        }
    }

    for (auto j : roll_results)
    {
        roll_sum += j;
    }

    roll_sum -= y;

    return roll_sum;
}

int Abilityscore::ability_score_mersenne_twister() {
    int score;
    return_rolls_mersenne_twister();
    score = sortnsum_rolls();
    return score;
}

int Abilityscore::ability_score()
{
    int score;
    //return_rolls(results);
    return_rolls();
    score = sortnsum_rolls();
    return score;
}
/*
void Abilityscore::point_buy(std::vector<int> selec) {
    const int zero = 8;
    const int one = 9;
    const int two = 10;
    const int three = 11;
    const int four = 12;
    const int five = 13;
    const int seven = 14;
    const int nine = 15;
    int double_check_sum = 0;
    for (auto h : selec) {
        double_check_sum += h;
    }
    if (double_check_sum >= pb_ceiling) {
        std::cout << "pb_ceiling violated" << std::endl;
    }
    for (auto i : selec) {
        if (i == 0) {
            pb_array.push_back(zero);
        }
        else if (i == 1) {
            pb_array.push_back(one);
        }
        else if (i == 2) {
            pb_array.push_back(two);
        }
        else if (i == 3) {
            pb_array.push_back(three);
        }
        else if (i == 4) {
            pb_array.push_back(four);
        }
        else if (i == 5) {
            pb_array.push_back(five);
        }
        else if (i == 7) {
            pb_array.push_back(seven);
        }
        else if (i == 9) {
            pb_array.push_back(nine);
        }
        else {
            std::cout << "bad data for pb_array" << std::endl;
        }
    }

}
*/
int Abilityscore::ability_modifier(int x) {
    int y = 0;
    if (x < 2) {
        y = -5;
    }
    else if (x < 4) {
        y = -4;
    }
    else if (x < 6) {
        y = -3;
    }
    else if (x < 8) {
        y = -2;
    }
    else if (x < 10) {
        y = -1;
    }
    else if (x < 12) {
        y = 0;
    }
    else if (x < 14) {
        y = 1;
    }
    else if (x < 16) {
        y = 2;
    }
    else if (x < 18) {
       y = 3;
    }
    else if (x <= 20) {
       y = 4;
    }
    else {
        std::cout << "Abilityscore->ability_modifier error" << std::endl;
    }
    return y;
}

void Abilityscore::push_roll_hist(std::vector<int> roll)
{
    if (roll_hist.size() < 3) {
        
        roll_hist.push_back(roll);
    
    }
    else {
        std::cout << "roll_hist vector is full" << std::endl;
    }
}

void Abilityscore::sextuple_score_mersenne_twister() {
    init_scores.clear();
    int x = 0;
    for (int i = 0; i < 6; i++) {
        x = ability_score_mersenne_twister();
        init_scores.push_back(x);
    }
    std::sort(init_scores.rbegin(), init_scores.rend());
    push_roll_hist(init_scores);
}

void Abilityscore::sextuple_score()
{
    //clear init_scores after every button press in main()
    init_scores.clear();
    int x = 0;
    for (int i = 0; i < 6; i++)
    {
        x = ability_score();
        init_scores.push_back(x);
    }
    //added sort to this function
    std::sort(init_scores.rbegin(), init_scores.rend());
    push_roll_hist(init_scores);
}
/*
int Abilityscore::ac_assign()
{
    int abm_passoff = ability_summary.dexabm;
    return armor_class = abm_passoff + 10;
}
*/

int Abilityscore::ac_assign(int dexabm)
{
    int abm_passoff = dexabm;
    abm_passoff += 10;
    return abm_passoff;
}

std::vector<int>& Abilityscore::fetch_init_scores() {
    return init_scores;
}
/*
std::vector<int>& Abilityscore::fetch_pb_array() {
    return pb_array;
}
*/
void Abilityscore::resort_init_scores() {
    if (!init_scores.empty())
    {
        std::sort(init_scores.rbegin(), init_scores.rend());
    }
}

void Abilityscore::clear_init_scores() {
    
    init_scores.clear();
    //would it be safer to assign all values to 0 thru an iterator?
    //init_scores = { 0, 0, 0, 0, 0, 0 };
    for (auto x : init_scores) {
        x = 0;
    }
 
}
/*
void Abilityscore::pushback_init(int var) {
    init_scores.push_back(var);
}
*/
/*
void Abilityscore::clr_init() {
    init_scores.clear();
}
*/
int& Abilityscore::retr_pointbuy_total() {
    
    //return point_buy_total;
    return purchtotal;
}

int& Abilityscore::retr_pointspend_total() {
    return purchspent;
}

int Abilityscore::retr_purchmap_cost(int index) {
    if (purch_stairs.find(index) != purch_stairs.end()) {
        return purch_stairs.at(index);
    }
    else {
        return 0;
    }
    
}

std::vector<int>& Abilityscore::retr_purchdisplay() {
    return purchdisplay;
}

bool Abilityscore::climb_stairs(int index) {
    //checking if we can move to a higher score before committing to that option
    //int no_one_over = step_marker + 1;
    int not_one_over = purchdisplay.at(index) + 1;
    if (not_one_over <= purchmax) {
        //step_marker++;
        return true;
    }
    else {
        return false;
    }
}

bool Abilityscore::descend_stairs(int index) {
    //checking if we can move to a lower score before committing to that option
    //int not_one_under = step_marker - 1;
    int not_one_under = purchdisplay.at(index) - 1;
    if (not_one_under >= purchmin) {
        //step_marker--;
        return true;
    }
    else {
        return false;
    }
}

bool Abilityscore::up_or_down(char option, int index) {
    //return bools for ascend and descend
    if (option == 'd') {
        return descend_stairs(index);
    }
    else if (option == 'u') {
        return climb_stairs(index);
    }
    else {
        return false;
    }
}

void Abilityscore::refund_pts(int refund) {
    purchspent -= refund;
    purchtotal += refund;
}

void Abilityscore::spend_pts(int cost) {
    purchspent += cost;
    purchtotal -= cost;
}
//maybe return bool for the console so disable options can just directly call this function
//bool Abilityscore::point_purchase_console(char option, int index) {
//TO DO : step_marker is shared between everything which is fucking up values in the menu; you're on the money tho with everything else
void Abilityscore::point_purchase_console(char option, int index) {
    //purchdisplay: the display vector<int> of scores
    //purch_stairs: the unordered_map with Key of scores and Value of costs
    //purchspent: int tallying how many points have been spent
    //purchtotal: int tallying how many points are remaining to spend
    
    bool climb_verify = up_or_down(option, index);
    //climb_verify mods the step_markers and allows the rest of the function to continue.  if we can't ascend or descend based on the option, it simply stops here
    if (climb_verify) {
        if (option == 'd') {
            //descend and climb make sure we are not out of bounds with the scores.  the following bools check
            //bool no_below_zero = (purchspent - purch_stairs.at(step_marker - 1) < 0) ? false : true;
            int downstairs_key = purchdisplay.at(index) - 1;
            bool none_below_zero = (purchspent - purch_stairs.at(downstairs_key) < 0) ? false : true;
            //if (purchspent > 0) {
            if (none_below_zero) {
            
                int refund = purch_stairs.at(downstairs_key);
                purchdisplay.at(index) = downstairs_key;
                //purchspent -= refund;
                //purchtotal += refund;
                refund_pts(refund);
                //return false;
            }
            else {
                //return true;
            }
        }
        else if (option == 'u') {
            int upstairs_key = purchdisplay.at(index) + 1;
            bool none_above_max = (purchspent + purch_stairs.at(upstairs_key) > purchconstant) ? false : true;
            //if (purchtotal < purchconstant) {
            if (none_above_max) {
                //++step_marker;
                int cost = purch_stairs.at(upstairs_key);
                purchdisplay.at(index) = upstairs_key;
                //purchspent += cost;
                //purchtotal -= cost;
                spend_pts(cost);
                //return false;
            }
            else {
                //return true;
            }
        }

    }
    else {
        //return false;
    }
}

