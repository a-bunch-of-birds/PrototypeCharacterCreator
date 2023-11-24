#ifndef ABILITYSCORE_H
#define ABILITYSCORE_H
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <unordered_map>
//#include "character.h"


class Abilityscore {
private:
    const int min_roll = 1;
    const int max_roll = 6;
    
    std::vector<int> roll_results;
    std::vector<int> init_scores;
    std::vector<std::vector<int>> roll_hist;


    const int purchmin = 8;
    const int purchmax = 15;
    const int purchconstant = 27;
    //const int pb_ceiling = 28;

    //std::vector<int> pb_array{0, 0, 0, 0, 0, 0};
    std::vector<int> purchdisplay{ purchmin, purchmin, purchmin, purchmin, purchmin, purchmin };
    std::unordered_map<int, int> purch_stairs{
        {purchmin, 0},
        {9, 1},
        {10, 1},
        {11, 1},
        {12, 1},
        {13, 1},
        {14, 2},
        {purchmax, 2}
    };
    //int step_marker = purchmin;
    int purchtotal = 27;
    int purchspent = 0;
    //int point_buy_total = 27;
   
    
public:
    
    std::vector<std::string> skills{ "STR", "DEX", "CON", "INT", "WIS", "CHA" };
    Abilityscore() {};
    ~Abilityscore() {};
    std::vector<std::vector<int>>& retr_roll_hist();
    int diceRoll_d6T_mersenne_twister();
    int diceRoll_d6T();
    void return_rolls_mersenne_twister();
    void return_rolls();
    int sortnsum_rolls();
    int ability_score_mersenne_twister();
    int ability_score();
    int ability_modifier(int x);
    void push_roll_hist(std::vector<int> roll);
    void sextuple_score_mersenne_twister();
    void sextuple_score();
    //void point_buy(std::vector<int> selec);
    int ac_assign(int dexabm);
    std::vector<int>& fetch_init_scores();
    //std::vector<int>& fetch_pb_array();
    void resort_init_scores();
    void clear_init_scores();
   
    //void pushback_init(int var);
    //void clr_init();

    int& retr_pointbuy_total();
    int& retr_pointspend_total();
    int retr_purchmap_cost(int index);
    std::vector<int>& retr_purchdisplay();
    bool climb_stairs(int index);
    bool descend_stairs(int index);
    bool up_or_down(char option, int index);
    void refund_pts(int refund);
    void spend_pts(int cost);
    void point_purchase_console(char option, int index);
};
#endif ABILITYSCORE_H