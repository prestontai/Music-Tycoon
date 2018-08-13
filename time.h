/*
 * time.h
 *
 *  Created on: Jul 6, 2018
 *      Author: prest
 */

#ifndef TIME_H_
#define TIME_H_

class Time
{
int day;
public:
	Time():day(0)
	{
	}
	int pass_day()
	{
		return ++day;
	}
	int pass_week()
	{
		day += 7;
		return day;
	}
	int pass_month()
	{
		day += 30;
		return day;
	}
	int pass_year()
	{
		day += 365;
		return day;
	}
	int get_day()
	{
		return day;
	}
};




#endif /* TIME_H_ */
