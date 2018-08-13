/*
 * highscores.h
 *
 *  Created on: Jul 19, 2018
 *      Author: prest
 */

#ifndef HIGHSCORES_H_
#define HIGHSCORES_H_
#include <iostream>
#include <fstream>
#include <string>
#include <map>


class HighScores
{
	multimap < int, string, greater <int> > hs_map;
public:
	HighScores()
	{
		read_file();
	}
	string enter_score( string s, int score)
	{
		if ( s.size() == 0 )
		{
			s = "aaa";
		}
		hs_map.insert( pair <int, string> ( score, s.substr( 0, 3 ) ) );

		string builder = "";
		string for_file = "";
		string temp = "";
		int rank = -1;
		for ( multimap < int, string >::iterator it = hs_map.begin();
				it != hs_map.end() && rank < 9; ++it )
		{
			temp = (*it).second + "\t" +
					to_string((*it).first) + "\n";
			for_file += temp;
			builder += to_string( ++rank ) + ". " + temp ;
		}
		ofstream myfile("highscores.txt");
		myfile << for_file;
		myfile.close();
		return "High Scores:\n" + builder;
	}
private:
	void read_file()
	{
		int score;
		string name;
		ifstream myfile("highscores.txt");
		if (myfile.is_open())
		{
			while( myfile >> name >> score )
			{
				hs_map.insert( pair <int, string> ( score, name ) );
			}
			myfile.close();
		}
	}
};




#endif /* HIGHSCORES_H_ */
