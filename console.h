/*
 * console.h
 *
 *  Created on: Jul 3, 2018
 *      Author: prest
 */

#include <string>
#include <algorithm>
#include <set>
#include <memory>
#include <iomanip>
#include "artists.h"
#include "bb_artists.h"
#include "own_artists.h"
#include "genres.h"
using namespace std;

#ifndef CONSOLE_H_
#define CONSOLE_H_

class EndGameException
{
};
class Console
{
	int score;
	int weeks;
	int myBal;
	int current_artist;
	vector <string> genre_v;
	vector <shared_ptr<OArtists>> artists_v;
	vector <shared_ptr<BBArtists>> bb_v;
	vector <shared_ptr<OArtists>> choices_v;
	vector <Songs> bb;
	unordered_map < string, bool > goals;
	string menu_c;
	Genres g;
	string ceiling_floor;
public:
	Console( int balance): score(0), weeks(0), myBal(balance), current_artist(0)
	{
		goals =
		{
				{"Unstoppable", false},
				{"Loyal", false},
				{"Golden Goose", false},
				{"Straight", false},
				{"Scrooge", false},
				{"Shiny III", false},
				{"Shiny II", false},
				{"Shiny I", false},
				{"Champion", false},
				{"Kanye West", false},
				{"Mr. Worldwide", false},
				{"Moneybags", false},
				{"Late Night", false},
				{"Bound 2", false},
				{"Trash", false},
				{"Hermit", false},
				{"Loss", false},
				{"Go Big or Go Home", false}
		};
		init_songs();
		genre_v = g.ret_genre_v();
		menu_c = "main_menu";
		ceiling_floor =  "______________________________________________\n";
	}
	string choose( int num )
	{
		if ( menu_c == "main_menu" )
		{
			return mm_choice(num);
		}
		else if ( menu_c == "art_list" )
		{
			return al_choice(num);
		}
		else if ( menu_c == "one_art")
		{
			return oa_choice(num);
		}
		else if ( menu_c == "event" )
		{
			return ev_choice(num);
		}
		else if ( menu_c == "c_artists")
		{
			return c_choice(num);
		}
		else if (menu_c == "billboards")
		{
			return b_choice(num);
		}
		else if ( menu_c == "upgrades" )
		{
			return up_choice(num);
		}
		return "";
	}
	string main_menu()
	{
		string title =	  		"|Main Menu\t";
		string balance =  		"Balance: "  + to_string(myBal) + "\t\t\n";
		string time = 			"|1.\tPlay Week\n";
		string week = 			"|\tCurrent Week: " + to_string(weeks) + "\n";
		string artists =  		"|2.\tArtists\n";
		string billboards=		"|3.\tBillboards\n";
		string upgrades = 		"|4.\tStudio Upgrades\n";
		string achievements = 	"|5.\tAchievements\n";
//		string high_scores =	"|7.\tHigh Scores\n";
		string quit_choice = 	"|6.\tQuit\n";

		return ceiling_floor + title + balance + time + week + artists + billboards
			    + upgrades + achievements + quit_choice + ceiling_floor;
	}
	string calc_score()
	{
		unordered_map <string, int> cert_map = calc_cert();
		string art_size     = "Number of Artists:    " + to_string( artists_v.size() ) + "\n";
		string gold 		= "Number of Golds:      " + to_string( cert_map["Gold"] ) + "\n";
		string plat 		= "Number of Platinums:  " + to_string( cert_map["Plat"] ) + "\n";
		string diamond 		= "Number of Diamonds:   " + to_string( cert_map["Diamond"] ) + "\n";
		string balance =  "Finishing Balance:\t" + to_string(myBal) + "\n";
		string awards =   "";

		int cert = ( cert_map["Gold"] * 100 ) + ( cert_map["Plat"] * 500 )
				+ ( cert_map["Diamond"] * 20000);
		score = artists_v.size() * 500 + myBal/100 + cert;
		string final_score = "Game Over\n\tYour final score is " + to_string(score) + "\n";
		return ceiling_floor + art_size + gold + plat + diamond + balance + awards + final_score + ceiling_floor;
	}
	int get_score()
	{
		return score;
	}
	~Console()
	{

	}

private:
	void init_songs()		//starts with 18 artists each with 3 songs
	{
		for ( int i = 0; i < 18 ; ++i )
		{
			b_sign();
		}
//		for( int i = 0; i < 4; ++i )
//		{
//			shared_ptr<OArtists> a( new OArtists );
//			oa_sign(a);
//		}
	}

	unordered_map <string, int> calc_cert()
	{
		unordered_map <string, int> cert_map;
		cert_map["Gold"] = cert_map["Plat"] = cert_map["Diamond"] = 0;
		for( vector <shared_ptr<OArtists>>::iterator ma = artists_v.begin(); ma!= artists_v.end(); ++ma)
		{
			for( auto ms: (**ma).get_discog() )
			{
				int num = ms.update_cert();
				if ( num == 1 )
				{
					cert_map["Gold"] += 1;
				}
				else if ( num != 0 && num < 20 && num % 2 == 0 )
				{
					cert_map["Plat"] += ( num/2 );
				}
				else if ( num > 20 )
				{
					cert_map["Diamond"] += num /20;
				}
			}
		}
		return cert_map;
	}

	string to_string_genre()
	{
		string builder = "";
		int num = 0;
		for( vector<string>::iterator i = genre_v.begin(); i!= genre_v.end(); ++i)
		{
			builder += to_string(++num) + ". " + *i + "\n";
		}
		return builder;
	}
	string stud_str( int num )
	{
		string builder = "";
		for ( int i = 0; i < num; ++i )
		{
			builder += "*";
		}
		return builder;
	}
	string converter( int num )
	{
		if ( num > 100000000)
		{
			return to_string( num/100000000) + "B ";
		}
		else if ( num > 100000)
		{
			return to_string( num/100000 ) + "M ";
		}
		return to_string(num * 10);
	}
	string pass_artist_time(int num)
	{
		for( vector<Songs>::iterator b = bb.begin(); b!= bb.end(); ++b )
		{
			(*b).age_song(num);
		}
		return update_songs(num) + helper_time( artists_v, num, true );
	}

	string update_songs(int num)
	{
		string builder = "";
		bb_domination();
		helper_time( bb_v, num, false );
		for( vector <shared_ptr<BBArtists>>::iterator i = bb_v.begin(); i!= bb_v.end(); ++i)
		{
			if ( (**i).get_energy() >= 36 * (Random::gen_num(10)/55.0))
			{
				try{
					bb.push_back( (**i).add_song( BBArtists::get_up_pop(), BBArtists::get_up_last()) );
				}catch(...)
				{
					cout << "Crash: BBUpdate\n";
				}
			}
		}
		for( vector <shared_ptr<OArtists>>::iterator i = artists_v.begin(); i!= artists_v.end(); ++i)
		{
			if ( ( 1 + OArtists::get_up_energy()/9.0) * (**i).get_energy() >=
					42 * (Random::gen_num(5)/55.0) )
			{
				Songs s = (**i).add_song( OArtists::get_up_pop(), OArtists::get_up_last());
				bb.push_back( s );
				if ( !goals["Trash"] && s.get_pop() < 30 )
				{
					goals["Trash"] = true;
					builder += "\n**Trash: Debut a song at < 30 popularity**\n";
				}
			}
		}

		if ( BBArtists::get_up_pop() < weeks/12 )
		{
			BBArtists::add_pop();
		}
		if ( BBArtists::get_up_last() < weeks/10 )
		{
			BBArtists::add_last();
		}
		return builder;
	}

	template < typename T >
	string helper_time(vector <shared_ptr<T>> & s, int & num, bool add_bal )
	{
		string builder = "";
		try{
			for( typename vector <shared_ptr<T>>::iterator i = s.begin(); i!= s.end(); ++i)
			{
				(**i).age_discog(num);
				if ( add_bal )
				{
					myBal += (**i).get_weekly_earned();
					if ( !goals["Golden Goose"] && (**i).get_earned() >= 500000 )
					{
						goals["Golden Goose"] = true;
						builder += "\n**Golden Goose: Have an artist earn you 500,000**\n";
					}
					if ( !goals["Loyal"]  && (**i).get_weeks() >= 50 )
					{
						goals["Loyal"] = true;
						builder += "\n**Loyal: Have an artist signed for 50 weeks**\n";
					}
				}
			}
		}
		catch (...){
			cout <<"Helpertimecrash\n";
		}
		return builder;
	}
	void b_sign()
	{
		shared_ptr<BBArtists> b( new BBArtists );
		for( int i = 0; i<3; ++i)
		{
			bb.push_back( (*b).add_song(BBArtists::get_up_pop(), BBArtists::get_up_last()) );
		}
		bb_v.push_back(b);
	}
	void oa_sign( shared_ptr<OArtists> a )
	{
		bb.push_back( (*a).add_song( OArtists::get_up_pop(), OArtists::get_up_last()) );
		artists_v.push_back(a);
		++OArtists::genre_map[(*a).get_genre()];
	}

	bool enough( int num )
	{
		if ( myBal >= num )
		{
			myBal -= num;
			return true;
		}
		return false;
	}

//Menu makers
	string artist_menu(int num)
	{
		Artists a = (*artists_v.at(num-1));
		string art_name =		"|Name: " +  a.get_name() + "\t";
		string genre = 			"Genre: " + a.get_genre() + "\n"; // add the genre it is
		string pop = 			"|Popularity:   " + to_string(a.get_pop()) + "  ";
		string creativity = 	"\tCreativity: " + to_string(a.get_creativity()) + "\n";
		string soc = 			"|Social Media: "+ to_string(a.get_soc_med()) + "  ";
		string energy = 		"\tEnergy:     "+ to_string(a.get_energy()) + "\n";
		string cut = 			"|Cut:\t       "+ to_string(a.get_cut()) + "% ";
		string earned = 		"\tEarned:     "  + to_string(a.get_earned()) + "\n";
		string age = 			"|Weeks Signed:  " + to_string(a.get_weeks()) + "\n";

		string back =  			"|0.\tBack\n";
		string disc =  			"|1.\tDiscography\n";
		//string add =  		"|2.\tAdd Song/Album\n";
		string events =  		"|2.\tEvents\n";
		string release =  		artists_v.size() > 1 ? "|3.\tRelease\n" : "";

		return ceiling_floor + art_name + genre + pop + creativity + soc + energy + cut + earned + age +
				back + disc + events + release + ceiling_floor;
	}

	template < typename T >
	string artists_list( vector <shared_ptr<T>> & av)
	{
		int amount = artists_v.size() == 0 ? 0 : int(pow( 3, artists_v.size()) * 10000);
		string art_name =		"|Manage Artists\t\tBalance: "  + to_string(myBal) + "\n";
		int num = 2;
		string builder  = "";
		string back =  			"|0.\tBack\n";
		string sign =  			"|1.\tSign\t\tContract Price: "
				+ to_string( amount ) + "\n";
		string siz = 			"|\t" + to_string(artists_v.size()) + "/" + to_string(2 + OArtists::get_up_size()) + "\n";
		string bonus = 			"|2.\tGenre Bonus\n";
		for( typename vector <shared_ptr<T>>::iterator i = av.begin(); i!= av.end(); ++i)
		{
			builder += "|" + to_string(++num) + ".\t" + (**i).get_name() +
					"\n|\t\tGenre: " + (**i).get_genre() + "\n";
		}

		return ceiling_floor + art_name + back + sign + siz + bonus + builder + ceiling_floor;
	}
	string choose_artist()
	{
		string builder = "";
		int init_size = choices_v.size();
		for ( int i = 0; i < 3 - init_size; ++i )
		{
			shared_ptr<OArtists> a( new OArtists );
			choices_v.push_back( a );
		}
		for ( int i = 0; i < int(choices_v.size()); ++i )
		{
			builder += to_string(i+1) + ceiling_floor + (*choices_v.at(i)).ret_info();
		}
		builder += artists_v.size() > 0 ? "4" + ceiling_floor + "Reset choices\nCost: " +
				to_string( int(pow( 3, artists_v.size()) * 3000)) + "\n" : "";
		return builder;
	}
	string studio_upgrades()
	{
		string stud_up = 	"|Studio Upgrades\t\tBalance: "  + to_string(myBal) + "\n";
		string back =  		"|0.\tBack\n";
		string stud = 		"|1.\tUpgrade Studio       (SongLast )\t" + stud_str(OArtists::get_up_last()) + "\n|\tCost: ";
		string studc = 		 to_string( int(pow( 2, OArtists::get_up_last() + 1 )) * 10000);

		string prod =  		"\n|2.\tUpgrade Production   (SongPromo)\t" + stud_str(OArtists::get_up_pop()) + "\n|\tCost: ";
		string prodc = 		 to_string( int(pow( 2, OArtists::get_up_pop() + 1 )) * 10000);

		string gift =  		"\n|3.\tUpgrade Amenities    (Energy   )\t" + stud_str(OArtists::get_up_energy()) + "\n|\tCost: ";
		string giftc = 		 to_string( int(pow( 2, OArtists::get_up_energy() + 1 )) * 10000);

		string size =  		"\n|4.\tUpgrade Studio Size  (#Artists )\t" + stud_str(OArtists::get_up_size()) + "\n|\tCost: ";
		string sizec = 		 to_string( int(pow( 2, OArtists::get_up_size() + 1 )) * 10000) + "\n";

		return ceiling_floor + stud_up + back + stud + studc +
				prod + prodc + gift + giftc + size + sizec + ceiling_floor;
	}
//Everything billboards
	string bb_menu()
	{
		string back = 			"|0.\tBack\n";
		string billboards = 	"|1.\tBillboards\n";
		string all_songs = 		"|2.\tAll Songs\n";
		string smart_board =	"|3.\tOwn Songs\n";
		string billboard_dom = 	"|4.\tBillboard Domination\n";
		return ceiling_floor + back + billboards + all_songs + smart_board + billboard_dom + ceiling_floor;
	}
	string bb_domination()
	{
		Artists::bb_dom.clear();
		vector <Songs> top_f = top_fourty(bb);
		for ( vector<Songs>::iterator s = top_f.begin(); s!= top_f.end(); ++s)
		{
			++Artists::bb_dom[(*s).get_genre()];
		}
		string builder = "";
		for ( auto it: Artists::bb_dom )
		{
			it.second = 100 * it.second/top_f.size();
			builder += it.first + "\t" + to_string(it.second) + "%\n";
		}
		return builder;
	}
	vector <Songs> top_fourty( vector <Songs> & s)
	{
		sort( s.begin(), s.end() );
		vector <Songs>::const_iterator first = s.begin();
		vector <Songs>::const_iterator last  = s.begin() + ( s.size() >= 40 ? 40: s.size() );
		vector <Songs> ret_vec( first, last );
		return ret_vec;
	}
	string billboards()
	{
		vector <Songs> top_f = top_fourty(bb);
		string builder = "Rank\tPop\tWeeks\tWeekly Streams\n";
		int count = 0;
		for( vector<Songs>::iterator b = top_f.begin(); b!= top_f.end(); ++b)
		{
			if ( (*b).get_pop() > 20)
			{
				builder += to_string(++count) + "\t" + (*b).get_name() + "\t" + //(*b).get_singer() +
						 "\n" + (*b).get_owner() + "\t" + to_string((*b).get_pop()) +
						"\t" + to_string((*b).get_weeks()) + "\t" + to_string((*b).get_streams())  + "\n";

			}
		}
		return builder;
	}

	template < typename T >
	string smart_board(  vector <shared_ptr<T>>& av)
	{
		sort( av.begin(), av.end());
		string builder = "\tPop\tWeeks\t#Streams\tSong Name\n";
		for( typename vector <shared_ptr<T>>::iterator s = av.begin(); s!= av.end(); ++s)
		{
			builder += discog_info(*s);
		}
		if ( builder == "Pop\tWeeks\t#Streams\tSong Name\n")
		{
			builder = "Sign some artists first!!\n";
		}
		return builder;
	}
	template < typename T >
	string discog_info( shared_ptr<T> & some_art )
	{
		string builder = (*some_art).get_name() + "\n\t" + (*some_art).get_genre() + "\n";
		for ( auto d: (*some_art).get_discog() )
		{
			builder += "\t" + (d.get_pop() < 10 ? "" :to_string(d.get_pop())) + "\t"
					+ to_string(d.get_weeks()) + "\t" + converter(d.get_total_streams()) + "\t\t"
					+ d.get_name() + "\n";
		}
		return builder;
	}

	string genre_bonus()
	{
		string builder = "|Genre Bonus\n";
		if ( OArtists::genre_map.size() > 0)
		{
			for ( auto it: OArtists::genre_map )
			{
				builder += "|\t" + it.first + ": " + to_string(it.second*10) + "\n";
			}
			return ceiling_floor + builder + ceiling_floor;
		}
		return "Sign some artists first!!\n";
	}
	string display_goals()
	{
		string builder = "Status  Name\n";
		for ( auto it: goals )
		{
			builder += (it.second ? "   *\t" : "   \t") + it.first + "\n";
		}
		return builder;
	}
//Event Requirements
	string inter_req()
	{
		string builder = "";
		if ( (*artists_v.at(current_artist-1)).get_weeks() < 10 )
		{
			builder += "|\tArtist is " + to_string((*artists_v.at(current_artist-1)).get_weeks()) +
					"/10 weeks old\n";
		}
		if ( (*artists_v.at(current_artist-1)).get_event_count() > 0 )
		{
			builder += "\tArtist has to wait " + to_string((*artists_v.at(current_artist-1)).get_event_count()) +
					" weeks until the next event\n";
		}
		if ( !goals["Trash"] )
		{
			builder += "|\tTrash needs to be unlocked\n";
		}
		if ( !goals["Hermit"] )
		{
			builder += "|\tHermit needs to be unlocked\n";
		}
		return builder.size() == 0 ? "|\tAll requirements fulfilled!\n" : builder;
	}
	string mv_req()
	{
		string builder = "";
		if ( (*artists_v.at(current_artist-1)).get_weeks() < 20 )
		{
			builder += "|\tArtist is " + to_string((*artists_v.at(current_artist-1)).get_weeks()) +
					"/20 weeks old\n";
		}
		if ( (*artists_v.at(current_artist-1)).get_pop() < 60 )
		{
			builder += "|\tArtist has " + to_string((*artists_v.at(current_artist-1)).get_pop()) +
					"/60 popularity\n";
		}
		if ( (*artists_v.at(current_artist-1)).get_event_count() > 0 )
		{
			builder += "\tArtist has to wait " + to_string((*artists_v.at(current_artist-1)).get_event_count()) +
					" weeks until the next event\n";
		}
		if ( !goals["Shiny I"] )
		{
			builder += "|\tShiny I needs to be unlocked\n";
		}
		if ( !goals["Scrooge"] )
		{
			builder += "|\tScrooge needs to be unlocked\n";
		}
		if ( !goals["Go Big or Go Home"] )
		{
			builder += "|\tGo Big or Go Home needs to be unlocked\n";
		}
		return builder.size() == 0 ? "|\tAll requirements fulfilled!\n" : builder;
	}
	string tour_req()
	{
		string builder = "";
		if ( (*artists_v.at(current_artist-1)).get_weeks() < 30 )
		{
			builder += "|\tArtist is " + to_string((*artists_v.at(current_artist-1)).get_weeks()) +
					"/30 weeks old\n";
		}
		if ( (*artists_v.at(current_artist-1)).get_soc_med() < 85 )
		{
			builder += "|\tArtist has " + to_string((*artists_v.at(current_artist-1)).get_soc_med()) +
					"/85 social media\n";
		}
		if ( (*artists_v.at(current_artist-1)).get_event_count() > 0 )
		{
			builder += "\tArtist has to wait " + to_string((*artists_v.at(current_artist-1)).get_event_count()) +
					" weeks until the next event\n";
		}
		if ( (*artists_v.at(current_artist-1)).get_earned() < 400000 )
		{
			builder += "|\tArtist has earned " + to_string((*artists_v.at(current_artist-1)).get_earned()) +
					"/400,000\n";
		}
		if ( !goals["Straight"] )
		{
			builder += "|\tStraight needs to be unlocked\n";
		}
		if ( !goals["Shiny II"] )
		{
			builder += "|\tShiny II needs to be unlocked\n";
		}
		if ( !goals["Bound 2"] )
		{
			builder += "|\tBound 2 needs to be unlocked\n";
		}
		return builder.size() == 0 ? "|\tAll requirements fulfilled!\n" : builder;
	}
	string a_events()
	{
		string title = "|Events\n";
		string back  = "|0.\tBack\n";
		string show  = "|1.\tInterview / Show\n";
		string mv	 = "|2.\tMusic Video\n";
		string tour  = "|3.\tTour\n";
		return ceiling_floor + title + back + show + inter_req() +
				mv + mv_req() + tour + tour_req() + ceiling_floor;
	}


//Choices
	string mm_choice(int num)
	{
		//Main menu
		switch (num)
		{
			case 1:
				return pass_time();
			case 2:
				menu_c = "art_list";
				return artists_list(artists_v);
			case 3:
				menu_c = "billboards";
				return bb_menu();
			case 4:
				menu_c= "upgrades";
				return studio_upgrades();
			case 5:
				return display_goals();
			case 6:
				//Throws an exception to end the game
				throw ( EndGameException() );
			default:
				return main_menu();
				break;
		}
		return main_menu();
	}
	string al_choice( int num )
	{
		//Artist list menu
		int siz = artists_v.size();
		int amount = artists_v.size() == 0 ? 0 : int(pow( 3, artists_v.size()) * 10000);
		if ( num == 1)
		{
			if ( int(artists_v.size())  + 1 <= 2 + OArtists::get_up_size()  && myBal >= amount )
			{
				menu_c = "c_artists";
				return choose_artist();
			}
		}
		else if ( num == 2)
		{
			return genre_bonus();
		}
		else if ( num == 0)
		{
			menu_c = "main_menu";
			return main_menu();
		}
		else if (num > 2 && num < siz + 3 )
		{
			menu_c = "one_art";
			current_artist = num - 2;
			return artist_menu( current_artist );
		}

		return artists_list(artists_v);
	}
	string c_choice( int num )
	{
		menu_c = "art_list";
		if ( num > 0 && num < int(choices_v.size() + 1) )
		{
			int amount = artists_v.size() == 0 ? 0 : int(pow( 3, artists_v.size()) * 10000);
			enough( amount );
			oa_sign( choices_v.at( num - 1));
			choices_v.erase( choices_v.begin() + num - 1 );
		}
		else if ( num == 4 && artists_v.size() > 0 && enough(int(pow( 3, artists_v.size()) * 3000)) )
		{
			choices_v.clear();
		}
		return artists_list(artists_v) + check_agoals();
	}
	string ev_choice ( int num )
	{
		string builder = "";
		switch( num )
		{
			case 0:
				menu_c = "one_art";
				return artist_menu(current_artist);
			case 1:
				if ( inter_req() != "|\tAll requirements fulfilled!\n")
				{
					return a_events();
				}
				menu_c = "one_art";
			    if ( !goals["Late Night"])
			    {
			    	goals["Late Night"] = true;
			    	builder += "\n**Late Night: Be on a talk show**\n";
			    }
				(*artists_v.at(current_artist - 1)).start_event( 3 );
				return artist_menu(current_artist) + "\n" +
						(*artists_v.at(current_artist - 1)).get_name() + " is a guest on a talk show\n" + builder;
			case 2:
				if ( mv_req() != "|\tAll requirements fulfilled!\n")
				{
					return a_events();
				}
				menu_c = "one_art";
			    if ( !goals["Bound 2"])
			    {
			    	goals["Bound 2"] = true;
			    	builder += "\n**Bound 2: Produce a music video**\n";
			    }
				return artist_menu(current_artist) + "\n" +
						(*artists_v.at(current_artist - 1)).get_name() + " is making a music video for " +
						(*artists_v.at(current_artist - 1)).start_event( 6 ) + "\n" + builder;
			case 3:
				if ( tour_req() != "|\tAll requirements fulfilled!\n")
				{
					return a_events();
				}
				menu_c = "one_art";
			    if ( !goals["Mr. Worldwide"])
			    {
			    	goals["Mr. Worldwide"] = true;
			    	builder += "\n**Mr. Worldwide: Complete a tour**\n";
			    }
				return artist_menu(current_artist) + "\n" +
						(*artists_v.at(current_artist - 1)).get_name() + " is going on a tour singing " +
						(*artists_v.at(current_artist - 1)).start_event( 10 ) + "\n" + builder;
			default:
				return a_events();
		}
	}
	bool in_bounds()
	{
		return artists_v.size() > 0;
	}
	string check_agoals()
	{

		string builder = "";
		if ( !goals["Straight"] && OArtists::genre_map.size() >= 5 )
		{
			goals["Straight"] = true;
			builder += "\n**Straight: Sign 5 artists of different genres**\n";
		}
		if ( !goals["Scrooge"] && in_bounds() &&
				(*artists_v.at( artists_v.size() - 1)).get_cut() >= 21)
		{
			goals["Scrooge"] = true;
			builder += "\n**Scrooge: Sign an artist taking a 21% cut**\n";
		}
		if ( !goals["Hermit"] && in_bounds() &&
				(*artists_v.at( artists_v.size() - 1)).get_soc_med() < 35 )
		{
			goals["Hermit"] = true;
			builder += "\n**Hermit: Sign an artist with less than 35 social media**\n";
		}
		if ( !goals["Go Big or Go Home"] && in_bounds() &&
				(*artists_v.at( artists_v.size() - 1)).get_creativity() > 64)
		{
			goals["Go Big or Go Home"] = true;
			builder += "\n**Go Big or Go Home: Sign an artist with 65 creativity**\n";
		}
		return builder;
	}
	string oa_choice(int num)
	{
		//Single artist menu
		string builder;
		string curgenre = (*artists_v.at(current_artist-1)).get_genre();
		switch(num)
		{
			case 0:
				menu_c = "art_list";
				return artists_list(artists_v);
			case 1:
				return "\tPop\tWeeks\t#Streams\tSong Name\n" + discog_info( artists_v.at( current_artist - 1) );
			case 2:
				menu_c = "event";
				return a_events();
			case 3:
				if ( artists_v.size() > 1 )
				{
					if ( --OArtists::genre_map[ curgenre ] == 0 )
						{
							OArtists::genre_map.erase( curgenre );
						}
						artists_v.erase( artists_v.begin() + current_artist-1);
						myBal += artists_v.size() <= 1 ? 0 : int(pow( 3, artists_v.size() - 1) * 10000);
						menu_c = "art_list";
				}
				return artists_list(artists_v);
			default:
				return artist_menu(current_artist);
		}
		return artist_menu(current_artist);
	}
	string b_choice( int num )
	{
		//Display Billboard
		switch(num)
		{
			case 0:
				menu_c = "main_menu";
				return main_menu();
			case 1:
				return billboards();
			case 2:
				return smart_board(bb_v);
			case 3:
				return smart_board(artists_v);
			case 4:
				return bb_domination();
			default:
				return "";
		}
		return "";
	}
	string up_choice( int num )
	{
		//Upgrade menu
		switch(num)
		{
			case 0:
				menu_c = "main_menu";
				return main_menu();
			case 1:
				if ( OArtists::get_up_last() <= 6 &&
						enough( pow( 2, OArtists::get_up_last() + 1 ) * 10000) )
				{
					OArtists::add_last();
				}
				return studio_upgrades();
			case 2:
				if ( OArtists::get_up_pop() <= 6  &&
						enough( pow( 2, OArtists::get_up_pop() + 1 ) * 10000) )
				{
					OArtists::add_pop();
				}
				return studio_upgrades();
			case 3:
				if ( OArtists::get_up_energy() <= 6  &&
						enough( pow( 2, OArtists::get_up_energy() + 1 ) * 10000 ) )
				{
					OArtists::add_energy();
				}
				return studio_upgrades();
			case 4:
				if ( OArtists::get_up_size() <= 6  &&
						enough( pow( 2, OArtists::get_up_size() + 1 ) * 10000 ) )
				{
					OArtists::add_size();
				}
				return studio_upgrades();
			case 5:
				menu_c = "main_menu";
				return main_menu();
			default:
				return "";
		}
		return "";
	}

	string pass_time()
	{
		string builder = "";
		++weeks;

		try{
			builder += pass_artist_time(1);
		} catch( ... )
		{
			cout << "Pass_artist_time crash";
		}
		if ( weeks >= 10000 )
		{
			throw( EndGameException() );
		}
	    if ( !goals["Moneybags"] && myBal >= 2500000 )
	    {
			goals["Moneybags"] = true;
	    	builder += "\n**Moneybags: Accumulate 2,500,0000**\n";
	    }
		unordered_map <string, int> cert_map = calc_cert();
	    if ( !goals["Shiny III"] && cert_map["Diamond"] > 0)
	    {
	    	goals["Shiny III"] = true;
	    	builder += "\n**Shiny III: Have a song be certified Diamond**\n";
	    }
	    if ( !goals["Shiny II"] && cert_map["Plat"] > 0)
	    {
	    	goals["Shiny II"] = true;
	    	builder += "\n**Shiny II: Have a song be certified Platinum**\n";
	    }
	    if( !goals["Shiny I"] && cert_map["Gold"] > 0)
	    {
	    	goals["Shiny I"] = true;
	    	builder += "\n**Shiny I: Have a song be certified Gold**\n";
	    }
	    return main_menu() + builder;
	}

};




#endif /* CONSOLE_H_ */
