#include "game.h"
#include "start_menu.h"
#include<fstream>
#include<iostream>
#ifndef MENU_H_
#define MENU_H_
using namespace std;


bool save(const Game& object,string filename)
{
  ofstream savefile(filename, std::ios::binary);
  if (!savefile)
  {
	cout << "An error occurred while opening the file " << filename << '.' << endl;
    return false;
  }
  savefile.write((char*)&object, sizeof(Game));
  savefile.close();
  return true;
}

bool desave(Game& object,string filename)
{
  ifstream savefile(filename, std::ios::binary);
  if (!savefile)
  {
	cout << "An error occurred while opening the file " << filename << '.' << endl;
    return false;
  }
  savefile.read((char*)&object, sizeof(Game));
  savefile.close();
  return true;
}

class Menu
{

public:
	start_menu sm;
	Game g;
Menu()
{

}

void display_menu()
{
	sm.main_menu();
	if (this->sm.choice == 'E')
	{
     g.start_game();
	 save(g, "save_game.dat");
	}
	if (this->sm.choice == 'S')
	{
	 desave(g, "save_game.dat");
	 g.start_game();
	 save(g, "save_game.dat");
	}
	if (this->sm.choice == 'H')
	{
	 sm.scores_menu();
	}
	if (this->sm.choice == 'I')
	{
	 sm.instructions_menu();
	}
	if (this->sm.choice == 'R')
	{
	 sm.requirements_menu();
	}
}

~Menu()
{

}

};
#endif
