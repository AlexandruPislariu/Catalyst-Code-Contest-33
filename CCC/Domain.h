#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

class TakeOff
{
private:
	std::vector<int>takeOffsFlight;
public:
	void append(const int& takeOff)
	{	
		if (uniqueFlight(takeOff))
			takeOffsFlight.push_back(takeOff);
	}
	bool uniqueFlight(const int& takeOff)
	{
		for (auto it : takeOffsFlight)
			if (it == takeOff)
				return false;

		return true;
	}
	int occurences()
	{
		return takeOffsFlight.size();
	}
};

struct Flight
{
	std::string from;
	std::string to;
	Flight(const std::string& A, const std::string& B) : from{ A }, to{ B }{};
	friend std::ostream& operator<<(std::ostream& os, const Flight& ob);/* Overload << operator */
	bool operator==(const Flight& x)/* Overload == operator*/
	{
		return (this->from == x.from && this->to == x.to);
	}
};

struct Comparator
{/* Overload comparation operator */
	bool operator()(const Flight& left, const Flight& right) const
	{
		if (left.from < right.from)
			return true;

		if (left.from == right.from && left.to < right.to)
			return true;

		return false;
	}
};

class Cordinate
{
private:
	int timeStamp;
	float latitude;
	float longitude;
	float altitude;

public:
	Cordinate(const int& t, const float& l, const float& lo, const float& a) : timeStamp{ t }, latitude{ l }, longitude{ lo }, altitude{ a }{};

	int get_timeStamp() const
	{
		return timeStamp;
	}
	float get_latitude() const
	{
		return latitude;
	}
	float get_longitude() const
	{
		return longitude;
	}
	float get_altitude() const
	{
		return altitude;
	}

	friend std::ostream& operator<<(std::ostream& os, const Cordinate& ob)
	{
		os << std::setprecision(5)<<ob.get_latitude() << " " << ob.get_longitude() <<" "<< ob.get_altitude();
		return os;
	}

};