/*
 * own_artists.h
 *
 *  Created on: Jul 13, 2018
 *      Author: prest
 */

#include "artists.h"
#ifndef OWN_ARTISTS_H_
#define OWN_ARTISTS_H_

struct OArtists:public Artists
{
	static unordered_map <string, int> genre_map;
	static int up_last;
	static int up_pop;
	static int up_energy;
	static int up_size;

	static int get_up_pop()
	{
		return up_pop;
	}
	static int get_up_last()
	{
		return up_last;
	}
	static int get_up_energy()
	{
		return up_energy;
	}
	static int get_up_size()
	{
		return up_size;
	}

	static int add_pop()
	{
		++up_pop;
		return up_pop * 100;
	}
	static int add_last()
	{
		++up_last;
		return up_last * 100;
	}
	static int add_energy()
	{
		++up_energy;
		return up_energy * 100;
	}
	static int add_size()
	{
		++up_size;
		return up_size * 100;
	}
	Songs add_song( int uppop, int uplast)
	{
		Songs s(genre, name, creativity, popularity *
				(1 + bb_dom[genre]/150.0) * (1 + genre_map[genre]/150.0),
				uppop, uplast, true);
		discog.push_back(s);
		popularity += s.get_pop()/14;
		energy -= 21;
		return s;
	}
	string ret_info()
	{

		string n = "Name:\t" + name + "\n";
		string g = "Genre:\t" + genre + "\tCurrent Bonus: " +
				to_string( genre_map.find(genre) == genre_map.end() ? 0:
						genre_map[genre] * 10) + "%\n";
		string p = "Popularity:\t" + to_string(popularity) + "\n";
		string c = "Creativity:\t" + to_string(creativity) + "\n";
		string sc = "Social Media:\t" + to_string(social_med) + "\n";
		string cu = "Cut:\t\t" + to_string(cut) + "\n";
//		string e = "Energy:    \t" + to_string(energy) + "\n";
//		string a = "Age:\t" + to_string(days) + "\n\n";

		return n + g + p + c + sc + cu;
	}



};



#endif /* OWN_ARTISTS_H_ */
