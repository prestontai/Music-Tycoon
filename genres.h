/*
 * genres.h
 *
 *  Created on: Jul 4, 2018
 *      Author: prest
 */

#ifndef GENRES_H_
#define GENRES_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Random
{
	static int gen_num( int variance )
	{
	    random_device rand_dev;
	    mt19937 generator(rand_dev());
		normal_distribution<double> dist(57, variance);
		int num = int(dist(generator));
		return num < 1 ? 1 : num;
	}
	static int gen_uniform(int max)
	{
	    random_device rand_dev;
	    mt19937 generator(rand_dev());
		uniform_int_distribution<int> dist(0, max - 1);
		return dist(generator);
	}

};
class Genres
{
	vector <string> genre_v;
public:
	Genres()
	{
		string line;
		ifstream myfile("genres.txt");
		if (myfile.is_open())
		{
			while( getline( myfile, line))
			{
				genre_v.push_back(line);
			}
			myfile.close();
		}
	}
	string ret_genre()
	{
		return genre_v.at(Random::gen_uniform(genre_v.size()));
	}
	vector <string> ret_genre_v()
	{
		return genre_v;
	}

};



#endif /* GENRES_H_ */
