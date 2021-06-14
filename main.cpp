#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <time.h> 

using namespace std;

#define HEIGHT 6
#define WIDTH 7

void draw_board();
void player_movement(int player);
void ai_movement(int player);
bool check_for_winner(int x, int y, int player);
bool check_vertical(int x, int y, int player);

int board_info[HEIGHT][WIDTH] = {{0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0}};

int PrevMoveX, PrevMoveY;
int difficulty;  
int configuration;

int main(){ 
   int counter = 0;
   bool winner = false;
   string diff;
   string config;
   
   srand(time(NULL)); 
   while(1){
   cout << "Please select a difficulty: e - easy, m - medium, h - hard" << endl;
   cin >> diff;
   if (diff == "e"){
     difficulty = 0;
     break;
   }
   else if (diff == "h"){
     difficulty = 2;
     break;
   }
   else if (diff == "m"){
     difficulty = 1;
     break;
   }
   else{
     cout << "Try again" << endl;
     continue;
   } 
   }

   while(1){
   cout << "Who's playing: 1 - Human vs Human, 2 - Human vs AI, 3 - AI vs AI" << endl;
   cin >> config;
   if (config == "1"){
     configuration = 0;
     break;
   }
   else if (config == "2"){
     configuration = 1;
     break;
   }
   else if (config == "3"){
     configuration = 2;
     break;
   }
   else{
     cout << "Try again" << endl;
     continue;
   } 
   }
   if((configuration == 1) || (configuration == 2)){
   cout << "Please select a number from 1-7" << endl;
   cout << "| 1| 2| 3| 4| 5| 6| 7" << endl;
   cout << "---------------------";
   draw_board();
   }
   else{
   draw_board();
   }
   
   for (int i = 0; i < 21; i++){
     if((configuration == 0) || (configuration == 1)){
       player_movement(1);
     }
     else{
      ai_movement(1);
     }
      
      draw_board();
      winner = check_for_winner(PrevMoveX, PrevMoveY, 1);
      if (winner){
        if((configuration == 0) || (configuration == 1)){
       cout << "\nYou Win" << endl;
         break;
      }
      else{
       cout << "\nBot Wins" << endl;
         break;
      }
      }
   
      if(configuration == 0){
       player_movement(2);
     }
     else{
      ai_movement(2);
     }
      draw_board();
      winner = check_for_winner(PrevMoveX, PrevMoveY, 2);
      if (winner){
         if(configuration == 0){
       cout << "\nYou Win" << endl;
         break;
      }
      else{
       cout << "\nBot Wins" << endl;
         break;
      }
         break;
      }   
   }
   if (!winner){
         cout << "\nDraw" << endl;
      }
  
   return 0;
}

void draw_board(){
   cout << endl;   
   for (int y = 0; y < HEIGHT; y++){
      for (int x = 0; x < WIDTH; x++){
         cout << "| ";
         if (board_info[y][x] == 0) cout << " ";
         else if (board_info[y][x] == 1) cout << "X";
         else if (board_info[y][x] == 2) cout << "O";
      }
      cout << "\n---------------------" << endl;
   }
}

void player_movement(int player){
   int choice;
   cout << "\nPlayer" << player << ", please select a number from 1 - 7: ";
   cin >> choice;
   
   if (cin.fail()){
      cout << "Error";
      exit(1);
   }
   
   while (choice > WIDTH || choice <=0){
      cout << "\nTry again: ";
      cin >> choice;
   }
 
   int number = 0;
   while (board_info[(HEIGHT-1)-number][(choice-1)] != 0){
      number++;
      if (number > (HEIGHT-1)){
         cout << "\nTry again: ";
         cin >> choice;
         number = 0;  
      }
   };
   
   board_info[(HEIGHT-1)-number][choice-1] = player;
   PrevMoveY = (HEIGHT-1)-number;
   PrevMoveX = choice-1;
}

void ai_movement(int player){
   int greedy_choice;

   int player2;
   if(player==1){
     player2 = 2;
   }
   else{
     player2 = 1;
   }

   vector <int> poss_choicesV2; 
   vector <int> poss_choicesX2; 


   vector <int> any_choice;

   int match1 = 0;
   int match2 = 0;
   int y = 0;
   int x = 0;
   int max_player1Val = 0;
   int max_player2Val = 0;
  
   int max_player1XLoc = 0;
   int max_player2XLoc = 0;

   while (x < WIDTH){
     while(y  < HEIGHT){
       if ((board_info[0][x] == 1) || (board_info[0][x] == 2)){
         break;
       }
       else if (board_info[y][x] == 0){  
         any_choice.push_back(x);
         y++;
         if(y == HEIGHT){
           if(poss_choicesV2.empty()){
             poss_choicesV2.push_back(0);
             poss_choicesX2.push_back(x);
           }
           else if(0 == poss_choicesV2.at(poss_choicesV2.size() - 1)){
             poss_choicesV2.push_back(0);
             poss_choicesX2.push_back(x);
           }
         }
       }
       else if((board_info[y][x] == player2) && (board_info[y-1][x] != player)){
         any_choice.push_back(x);
         y++;
         match1++;
         if(match1 > max_player1Val){
           max_player1Val = match1;
           max_player1XLoc = x;
         }
         if(poss_choicesV2.empty()){
             poss_choicesV2.push_back(0);
             poss_choicesX2.push_back(x);
           }
          else if(0 == poss_choicesV2.at(poss_choicesV2.size() - 1)){
             poss_choicesV2.push_back(0);
             poss_choicesX2.push_back(x);
           }
       }
       else if((board_info[y][x] == player) && (board_info[y-1][x] != player)){
         any_choice.push_back(x);
         y++;
         match2++;
        if(match2 > max_player2Val){
           max_player2Val = match2;
           max_player2XLoc = x;
           if(poss_choicesV2.empty()){
             poss_choicesV2.push_back(max_player2Val);
             poss_choicesX2.push_back(max_player2XLoc);
           }
           else if(max_player2Val > poss_choicesV2.at(poss_choicesV2.size() - 1)){
             poss_choicesV2.clear();
             poss_choicesX2.clear();
             poss_choicesV2.push_back(max_player2Val);
             poss_choicesX2.push_back(max_player2XLoc);
           }
           else if(max_player2Val == poss_choicesV2.at(poss_choicesV2.size() - 1)){
             poss_choicesV2.push_back(max_player2Val);
             poss_choicesX2.push_back(max_player2XLoc);
           }
         }
       }
       else{
         any_choice.push_back(x);
         break;
       }
     }
     x++;
     y = 0;
     match1 = 0;
     match2 = 0;
   }

  
   if(difficulty == 0){
     greedy_choice = any_choice.at(rand() % any_choice.size());
   }

   if(difficulty == 1){
     greedy_choice = poss_choicesX2.at(rand() % poss_choicesX2.size());
   }

   else if(difficulty == 2){
   if((max_player2Val != 3) && (max_player1Val == 3)){
     greedy_choice = max_player1XLoc;
   }

    else if(max_player2Val == 3){
     greedy_choice = max_player2XLoc;
   }
    
    else{
     greedy_choice = poss_choicesX2.at(rand() % poss_choicesX2.size());
    }
   }
  

   int number = 0;
   while (board_info[(HEIGHT-1)-number][(greedy_choice)] != 0){
      number++;
   };
   
   board_info[(HEIGHT-1)-number][greedy_choice] = player;
   PrevMoveY = (HEIGHT-1)-number;
   PrevMoveX = greedy_choice;
}

bool check_for_winner(int x, int y, int player){
   bool winner;

   if (check_vertical(x,y,player)) return true;
   else return false;
}



bool check_vertical(int x, int y, int player){
   int match = 1;
   int count = 1;
   
   while(y+count >= 0 && y+count < HEIGHT){
      if (board_info[y+count][x] == player){  
         match++;
         count++;
      }
      else break;  
   }
  
   if (match == 4) return true;
   else return false;
}

