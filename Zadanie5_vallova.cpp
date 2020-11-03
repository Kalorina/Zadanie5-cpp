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
	DateTime(std::string date, std::string oddelovacDatum, std::string oddelovacMedzera, std::string oddelovacCas);
	
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
	bool operator<(const DateTime& dat);
	bool operator>(const DateTime& dat);

	int operator[](int X);
	friend std::ostream& operator<<(std::ostream& os, const DateTime& dat);
	int operator-(const DateTime& dat);
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

DateTime::DateTime(std::string date, std::string oddelovacDatum, std::string oddelovacMedzera, std::string oddelovacCas)
{
	size_t pos = 0;
	std::string token1,token2,token3;
	int dat[6] = { 0,0,0,0,0,0 };
	int counter = 0;
	while ((pos = date.find(oddelovacDatum)) != std::string::npos) {
		token1 = date.substr(0, pos);
		dat[counter] = std::stoi(token1);
		date.erase(0, pos + oddelovacDatum.length());
		counter++;
	}
	while ((pos = date.find(oddelovacMedzera)) != std::string::npos) {
		token1 = date.substr(0, pos);
		dat[counter] = std::stoi(token1);
		date.erase(0, pos + oddelovacMedzera.length());
		counter++;
	}
	while ((pos = date.find(oddelovacCas)) != std::string::npos) {
		token1 = date.substr(0, pos);
		dat[counter] = std::stoi(token1);
		date.erase(0, pos + oddelovacCas.length());
		counter++;
	}
	day = dat[0];
	month = dat[1];
	year = dat[2];
	hour = dat[4];
	minute = dat[5];
	second = std::stoi(date);
}

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

	second++;
	if (second == 60) {
		second = 0;
		minute++;
		if (minute == 60) {
			minute = 0;
			hour++;
			if (hour == 24) {
				hour = 0;
				day++;
				if (day == daysInMonth[month - 1] + 1) {
					day = 1;
					month++;
					if (month == 13) {
						month = 1;
						year++;
					}
				}
				if (day == 32 && month == 13) {
					day = 1;
					month = 1;
					year++;
				}
			}
		}
	}

	return *this;
}

DateTime DateTime::operator++(int)
{
	int y = year, m = month, d = day, h = hour, mt = minute, s = second;
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	second++;
	if (second == 60) {
		second = 0;
		minute++;
		if (minute == 60) {
			minute = 0;
			hour++;
			if (hour == 24) {
				hour = 0;
				day++;
				if (day == daysInMonth[month - 1] + 1) {
					day = 1;
					month++;
					if (month == 13) {
						month = 1;
						year++;
					}
				}
				if (day == 32 && month == 13) {
					day = 1;
					month = 1;
					year++;
				}
			}
		}
	}
	return DateTime(y,m,d,h,mt,s);
}

DateTime& DateTime::operator--()
{
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	
	second--;
	if (second == -1) {
		second = 59;
		minute--;
		if (minute == -1) {
			minute = 59;
			hour--;
			if (hour == -1) {
				hour = 23;
				day--;
				if (day == 0) {
					day = daysInMonth[month - 1];
					month--;
					if (month == 0) {
						month = 12;
						year--;
					}
					if (day == 1 && month == 1) {
						day = 31;
						month = 12;
						year--;
					}
				}
			}
		}
	}
	return *this;
}

DateTime DateTime::operator--(int)
{
	int y = year, m = month, d = day, h = hour, mt = minute, s = second;
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	second--;
	if (second == -1) {
		second = 59;
		minute--;
		if (minute == -1) {
			minute = 59;
			hour--;
			if (hour == -1) {
				hour = 23;
				day--;
				if (day == 0) {
					day = daysInMonth[month - 1] ;
					month--;
					if (month == 0) {
						month = 12;
						year--;
					}
					if (day == 1 && month == 1) {
						day = 31;
						month = 12;
						year--;
					}
				}
			}
		}
	}
	return DateTime(y, m, d, h, mt, s);
}

void DateTime::operator+(int pocet)
{
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	setSecond(second += pocet);

	if (second == 60) {
		second = 0;
		minute++;
		if (minute == 60) {
			minute = 0;
			hour++;
			if (hour == 24) {
				hour = 0;
				day++;
				if (day == daysInMonth[month - 1] + 1) {
					day = 1;
					month++;
					if (month == 13) {
						month = 1;
						year++;
					}
				}
				if (day == 32 && month == 13) {
					day = 1;
					month = 1;
					year++;
				}
			}
		}
	}
}

void DateTime::operator-(int pocet)
{
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	setSecond(second -= pocet);

	if (second == -1) {
		second = 59;
		minute--;
		if (minute == -1) {
			minute = 59;
			hour--;
			if (hour == -1) {
				hour = 23;
				day--;
				if (day == 0) {
					day = daysInMonth[month - 1];
					month--;
					if (month == 0) {
						month = 12;
						year--;
					}
					if (day == 1 && month == 1) {
						day = 31;
						month = 12;
						year--;
					}
				}
			}
		}
	}
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

bool DateTime::operator>(const DateTime& dat)
{
	if (second > dat.second) {
		return false;
	}
	else if (minute > dat.minute) {
		return false;
	}
	else if (hour > dat.hour) {
		return false;
	}
	else if (day > dat.day) {
		return false;
	}
	else if (month > dat.month) {
		return false;
	}
	else if (year > dat.year) {
		return false;
	}
	else { return true; }
}

bool DateTime::operator<(const DateTime& dat)
{
	if (second > dat.second) {
		return true;
	}
	else if (minute > dat.minute) {
		return true;
	}
	else if (hour > dat.hour) {
		return true;
	}
	else if (day > dat.day) {
		return true;
	}
	else if (month > dat.month) {
		return true;
	}
	else if (year > dat.year) {
		return true;
	}
	else { return false; }
}

int DateTime::operator[](int X)
{
	if (X == 0) {
		return second;
	}
	else if (X == 1) {
		return minute;
	}
	else if (X == 2) {
		return hour;
	}
	else if (X == 3) {
		return day;
	}
	else if (X == 4) {
		return month;
	}
	else if (X == 5) {
		return year;
	}
	else { 
		std::cout << "Zly zadany index" << std::endl;
		return 0; }
}

std::ostream& operator<<(std::ostream& os, const DateTime& dat)
{
	os << dat.day << "." << dat.month << "." << dat.year << " " << dat.hour << ":" << dat.minute << ":" << dat.second;
	return os;
}

int DateTime::operator-(const DateTime& dat)
{
	int y=0, m=0, d=0, h=0, mt=0, s=0, total=0;
	y = year - dat.year;
	m = month - dat.month;
	d = day - dat.day;
	h = hour - dat.hour;
	mt = minute - dat.minute;
	s = second - dat.second;

	total = y * 31536000 + m * 2628003 + d * 86400 + h * 3600 + mt * 60 + s;
	return total;
}

int main() {

	DateTime pokusA(0, 0, 0, 0, 0, 0);;
	pokusA.setDate(4, 5, 3000, 5, 23, 6);
//	pokusA.print();
	DateTime pokusB(0, 0, 0, 0, 0, 0);
	pokusB.setDate(1, 1, 2000, 0, 0, 0);
	pokusB.print();

//	pokusA++;
//	++pokusA;
//	pokusA--;
//	--pokusA;
//	pokusA+(2);
//	pokusA-(2);
//	pokusA.print();

	bool A=true;
//	A=(pokusA == pokusB);
//	A = (pokusA != pokusB);
//	A = (pokusA > pokusB);
//	A = (pokusA < pokusB);
//	std::cout << A << std::endl;

/*	int x;
	x=pokusA[1];
	std::cout << x << std::endl;
*/
	std::cout << pokusA << std::endl;

/*
	int total = 0;
	total = pokusA - pokusB;
	std::cout << total << "seconds" << std::endl;
*/
	return 0;
}


