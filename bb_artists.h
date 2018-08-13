/*
 * bb_artists.h
 *
 *  Created on: Jul 13, 2018
 *      Author: prest
 */

#include "artists.h"
#ifndef BB_ARTISTS_H_
#define BB_ARTISTS_H_

struct BBArtists:public Artists
{
	static int up_last;
	static int up_pop;

	BBArtists(): Artists()
	{
	}
	static int get_up_pop()
	{
		return up_pop;
	}
	static int get_up_last()
	{
		return up_last;
	}
	static void add_pop()
	{
		if ( up_pop < 5 )
		{
			++up_pop;
		}
	}
	static void add_last()
	{
		if ( up_last < 5)
		{
			++up_last;
		}
	}
	~BBArtists()
	{
	}

};



#endif /* BB_ARTISTS_H_ */
