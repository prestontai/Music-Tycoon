/*
 * songs.h
 *
 *  Created on: Jul 3, 2018
 *      Author: prest
 */

#ifndef SONGS_H_
#define SONGS_H_
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <unordered_map>
#include <math.h>
#include "time.h"
#include "genres.h"

using namespace std;

class Songs
{
protected:
	static vector <string> songs_v;
	int cert;
	string name;
	string genre;
	string singer;
	int popularity;
	int weeks;
	long streams;
	bool mine;
	int lasting;
public:
	Songs()
	{
		cert = 0;
		popularity = Random::gen_num(10);
		weeks = 0;
		streams = 0;
		lasting = Random::gen_num(3);
		mine = false;
	}
	Songs( string gen, string sing, int creativ, int art_pop,
			int up_pop, int up_last, bool own):
		cert(0),genre(gen), singer(sing), weeks(0), streams(0), mine(own)
	{
		try{
			popularity = Random::gen_num(int(creativ/4)) *
					(.855 + art_pop/380.0) * (1.0 + up_pop/69.0);
			lasting = 10 + abs(Random::gen_num(25) * (1.0 + up_last/30.0));
			int num = Random::gen_uniform(songs_v.size());
			name = songs_v.at(num);
			songs_v.erase( songs_v.begin() + num );
			streams = 0;
		}
		catch( ...)
		{
			cout <<"Crash: Song construction";
		}
	}

	void update_pop( double base, double exp)
	{
		popularity = popularity * double( pow( base, exp ) );
	}
	string get_name()
	{
		return name;
	}
	int get_weeks()
	{
		return weeks;
	}
	int get_streams()
	{
		if ( weeks == 0 )
		{
			return 0;
		}
		return popularity * 1000 * double( pow(1.03, popularity));
	}
	long get_total_streams()
	{
		return streams;
	}
	string get_song_info()
	{
		string n = "\nName:       " + name + "\n";
		string g = "Genre:      " + genre + "\n";
		string p = "Popularity: " + to_string(popularity) + "\n";
		string d = "Weeks:\t    " +  to_string(weeks);

		return n + g + p + d;
	}
	string get_singer()
	{
		return singer;
	}
	int get_pop()
	{
		if ( popularity < 1)
		{
			popularity = 0;
		}
		return popularity;
	}
	string get_genre()
	{
		return genre;
	}

	int age_song(int num)
	{
		lasting = lasting/( 1 + weeks * 0.035);
		streams += 7800 * double( pow(1.086, popularity/1.3));
		update_pop( 0.996, num * 2 * (60.0/lasting) );
		++weeks;
		update_cert();
		return weeks;
	}
	int update_cert()
	{
		if ( streams > 10000000)
		{
			cert = 2 * int(( streams/10000000 ));
		}
		else
		{
			cert = 	  int(streams/ 5000000);
		}
		return cert;
	}
	string get_owner()
	{
		return mine ? "*" : "";
	}
	bool operator < ( const Songs & rhs ) const
	{
		return popularity > rhs.popularity;
	}
};






#endif /* SONGS_H_ */
