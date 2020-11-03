#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

class DateTime {
private:
	int day, month, year, hour, minute, second;
public:
	DateTime(int dayx, int monthx, int yearx, int hourx, int minutex, int secondx);
/*	DateTime(std::string date, std::string oddelovacDatum, std::string oddelovatM, std::string oddelovacCas);*/
	
	void setDay(int dayx) { day = dayx; }
	int getDay() { return day; }
	void setMonth(int monthx) { month = monthx; }
	int getMonth() { return month; }
	void setYear(int yearx) { year = yearx; }
	int getYear() { return year; }
	void setHour(int hourx) { hour = hourx; }
	int getHour() { return hour; }
	void setMinute(int minutex) { minute = minutex; }
	int getMinute() { return minute; }
	void setSecond(int secondx) { second = secondx; }
	int getSecond() { return second; }
	void setDate(int dayx, int monthx, int yearx, int hourx, int minutex, int secondx);
	void print();

	DateTime& operator++(); //aj zmeni navratovy typ
	DateTime operator++(int); //vrati original
	DateTime& operator--(); //aj zmeni navratovy typ
	DateTime operator--(int); //vrati original

	void operator+(int pocet);
	void operator-(int pocet);
	bool operator==(const DateTime& dat);
	bool operator!=(const DateTime& dat);
};

DateTime::DateTime(int dayx, int monthx, int yearx, int hourx, int minutex, int secondx)
{
	day = dayx;
	month = monthx;
	year = yearx;
	hour = hourx;
	minute = minutex;
	second = secondx;
}
/*
DateTime::DateTime(std::string date, std::string oddelovacDatum, std::string oddelovatM, std::string oddelovacCas)
{
	 
}
*/
void DateTime::setDate(int dayx, int monthx, int yearx, int hourx, int minutex, int secondx)
{
	day = dayx;
	month = monthx;
	year = yearx;
	hour = hourx;
	minute = minutex;
	second = secondx;
}

void DateTime::print()
{
	std::cout << day << "/" << month << "/" << year << " " << hour << ":" << minute << ":" << second << std::endl;
}

DateTime& DateTime::operator++()
{
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	

	if (day == 31 && month == 12) {
		year++;
		month = 1;
		day = 1;
	}
	else if (day == daysInMonth[month - 1]) {
		month++;
		day = 1;
	}
	else if (hour == 23) {
		day++;
		hour = 0;
		minute = 0;
		second = 0;
	}
	else if (minute == 59) {
		hour++;
		minute = 0;
		second = 0;
	}
	else if (second == 59) {
		second = 0;
		minute++;
	}
	else { second++; }

	return *this;
}

DateTime DateTime::operator++(int)
{
	int y = year, m = month, d = day, h = hour, mt = minute, s = second;
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	if (day == 31 && month == 12) {
		year++;
		month = 1;
		day = 1;
	}
	else if (day == daysInMonth[month - 1]) {
		month++;
		day = 1;
	}
	else if (hour == 23) {
		day++;
		hour = 0;
		minute = 0;
		second = 0;
	}
	else if (minute == 59) {
		hour++;
		minute = 0;
		second = 0;
	}
	else if (second == 59) {
		second = 0;
		minute++;
	}
	else { second++; }

	return DateTime(y,m,d,h,mt,s);
}

DateTime& DateTime::operator--()
{
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (day == 1 && month == 1) {
		year--;
		month = 12;
		day = 31;
	}
	else if (day == daysInMonth[month - 1]) {
		month--;
		day = daysInMonth[month - 2];
	}
	else if (hour == 0) {
		day--;
		hour = 23;
	}
	else if (minute == 0) {
		hour--;
		minute = 59;
	}
	else if (second == 0) {
		minute--;
		second = 59;
	}
	else {
		second--;
	}
	return *this;
}
/*
DateTime DateTime::operator--(int)
{
	return DateTime();
}
*/

void DateTime::operator+(int pocet)
{
	setSecond(second + pocet);
}

void DateTime::operator-(int pocet)
{
	setSecond(second - pocet);
}

bool DateTime::operator==(const DateTime& dat)
{
	if (year == dat.year && month == dat.month && day == dat.day && hour==dat.hour && minute==dat.minute && second==dat.second) {
		return true;
	}
	else {
		return false;
	}

}

bool DateTime::operator!=(const DateTime& dat)
{
	if (year == dat.year && month == dat.month && day == dat.day && hour == dat.hour && minute == dat.minute && second == dat.second) {
		return false;
	}
	else {
		return true;
	}
}

int main() {

	DateTime pokus(0, 0, 0, 0, 0, 0);;
	pokus.setDate(31, 12, 1999, 23, 59, 59);
	pokus.print();
//	++pokus;
	pokus++;
	pokus.print();
	return 0;
}