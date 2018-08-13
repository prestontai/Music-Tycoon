/*
 * artists.h
 *
 *  Created on: Jul 3, 2018
 *      Author: prest
 */

#include "songs.h"
#ifndef ARTISTS_H_
#define ARTISTS_H_


class Artists:public Songs
{
	static vector <string> artists_names;
	int w_earned;
	int event_count;
protected:
	vector <Songs> discog;
	int energy;
	int weeks;
	int earned;
	int cut;
	int creativity;
	int social_med;
	string genre;
public:
	static unordered_map <string, int> bb_dom;

	Artists(): w_earned(0), event_count(0), energy(30), weeks(0), earned(0)
	{
		Genres g;
		genre = g.ret_genre();
		genre.erase(genre.end()-1, genre.end());
		creativity = Random::gen_num(13);
		social_med = Random::gen_num(20);
		cut = Random::gen_num(8)/3;
		int num = Random::gen_uniform(artists_names.size());
		name = artists_names.at(num);
		artists_names.erase( artists_names.begin() + num );

	}

	Songs add_song( int uppop, int uplast)
	{
		Songs s(genre, name, creativity, popularity *
				(1 + bb_dom[genre]/120.0), uppop, uplast, false);
		discog.push_back(s);
		popularity += s.get_pop()/12;
		energy -= 16;
		return s;
	}
	vector <Songs> get_discog()
	{
		sort( discog.begin(), discog.end(), [] (  Songs & left,
				 Songs & right)
		{
			return left.get_total_streams() > right.get_total_streams();
		});
		return discog;
	}
	void age_discog(int & num)
	{
		//ages the artist
		weeks += num;
		energy += 7;
		if ( event_count > 0 )
		{
			event_count -= 1;
		}
		if ( energy >= 32 )
		{
			update_pop( 0.97, num);
		}

		//ages the discog
		w_earned = 0;
		for( vector<Songs>::iterator i = discog.begin();
				i!= discog.end(); ++i)
		{
			(*i).age_song(num);
			earned += (*i).get_streams() * cut * 0.0005;
			w_earned += (*i).get_streams() * cut * 0.0005;
		}
	}
	int get_creativity()
	{
		return creativity;
	}
	int get_soc_med()
	{
		return social_med;
	}
	int get_energy()
	{
		return energy;
	}
	int get_weekly_earned()
	{
		return w_earned;
	}
	int get_earned()
	{
		return earned;
	}
	int get_cut()
	{
		return cut;
	}
	string get_genre()
	{
		return genre;
	}
	int get_weeks()
	{
		return weeks;
	}
	int get_event_count()
	{
		return event_count;
	}
	string start_event( int num )
	{
		string builder = "\n";
		energy -= num * 7;
		event_count = num;
		switch( num )
		{
			case 3:
				energy -= num * 7;
				popularity += 8;
				social_med += 10;
				return "";
			case 6:
				sort( discog.begin(), discog.end() );
				discog.at(0).update_pop( 1.2, 1.5 );
				social_med += 10;
				return discog.at(0).get_name();
			case 10:
				sort( discog.begin(), discog.end() );
				int count = 0;
				for( vector<Songs>::iterator d = discog.begin();
						d!= discog.end() && count < 5; ++d)
				{
					++count;
					discog.at(count).update_pop( 1.15, 1.5);
					builder += discog.at(count).get_name() + "\n";
				}
				popularity += 10;
				return builder;
		}
		return "";
	}

	bool operator < ( const Artists & rhs ) const
	{
		int own_total = 0;
		int rhs_total = 0;
		for ( auto s: discog)
		{
			own_total += s.get_pop();
		}
		for ( auto s: rhs.discog )
		{
			rhs_total += s.get_pop();
		}
		return own_total > rhs_total;
	}

};

vector <string> init_vector(string filename)
{
	vector <string> sv;
	string line;
	ifstream myfile( filename );
	if (myfile.is_open())
	{
		while( getline( myfile, line))
		{
			line.erase(line.end()-1, line.end());
			sv.push_back(line);
		}
		myfile.close();
	}
	return sv;
}


#endif /* ARTISTS_H_ */
