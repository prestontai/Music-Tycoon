/*
 * main.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: prest
 */
#include "console.h"
#include "highscores.h"

string an = "artists_names.txt";
vector <string> Artists::artists_names = init_vector(an);
string sn = "song_names.txt";
vector <string> Songs::songs_v = init_vector(sn);
unordered_map <string, int> Artists::bb_dom;
unordered_map <string, int> OArtists::genre_map;
int base = 4;
int OArtists::up_last = base;
int OArtists::up_pop = base;
int OArtists::up_energy = base;
int OArtists::up_size = base;
int BBArtists::up_last = 0;
int BBArtists::up_pop  = 0;


int main()
{
	Console manager(0);
	cout << "Welcome to Music Manager!"<< endl;

	int num;
	try{
		cout << manager.main_menu();
		while ( true )
		{
			cin >> num;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(999, '\n');
			}
			else
			{
//				for ( int i = 0 ; i < 19; ++i)
//				{
					cout << manager.choose(num);
//				}
			}
		}
	} catch ( EndGameException & e)
	{
		cout << manager.calc_score();
	}
	HighScores hs;
	string name;
	cout << "Enter your name: ";
	cin >> name;
	cout << hs.enter_score( name, manager.get_score());








	return 0;
}




