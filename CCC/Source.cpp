#include <fstream>
#include <string>
#include <map>
#include "Domain.h"

using std::string;

std::ifstream in("input.in");
std::ofstream out("result.out");

typedef bool(*CompareFunction)(int a, int b);
 
template <typename tmp>
tmp getMinim(tmp a, tmp b)
{
	return a<b ? a:b;
}

template <typename tmp>
tmp getMaxim(tmp a, tmp b)
{
	return a>b ? a:b;
}

void read_data(string& x, std::ifstream& in)
{
	char ch;
	x.clear();

	while (in >> ch)
	{
		if (isalpha(ch))
			x += ch;
		else
			return;
	}
}

void read_between_spaces(string& x,std::istream &in)
{
	char ch;
	x.clear();

	while (in >> ch)
	{
		if (ch!=',')
			x += ch;
		else
			return;
	}
}

Cordinate linear_interpolation(const Cordinate& x, const Cordinate& y,float time_to_travel) 
{
	float new_lat = y.get_latitude() + (time_to_travel - y.get_timeStamp()) * ((x.get_latitude() - y.get_latitude()) / (x.get_timeStamp() - y.get_timeStamp()));
	float new_lon = y.get_longitude() + (time_to_travel - y.get_timeStamp()) * ((x.get_longitude() - y.get_longitude()) / (x.get_timeStamp() - y.get_timeStamp()));
	float new_alt = y.get_altitude() + (time_to_travel - y.get_timeStamp()) * ((x.get_altitude() - y.get_altitude()) / (x.get_timeStamp() - y.get_timeStamp()));
	return Cordinate(1, new_lat, new_lon, new_alt);
}
int main()
{	
	int N = 0;
	int timeStamp = 0;
	float latitude = 0.0f;
	float longitude = 0.0f;
	float altitude = 0.0f;
	char separator = ' ';
	
/* Key=Flight, Type = TakeOff, Comparator(Flight x < Flight y) */
	std::map <Flight, TakeOff, Comparator> flights;
	string starting_point="";
	string ending_point="";
	int takeOff = 0;

	in >> N;
	/* Level1
	in >> timeStamp >> separator;
	in >> latitude >> separator;
	in >> longitude >> separator;
	in >> altitude>>separator;

	int minTimeStamp = timeStamp;
	int maxTimeStamp = timeStamp;
	float minLatitude = latitude;
	float maxLatitude = latitude;
	float minLongitude = longitude;
	float maxLongitude = longitude;
	float maxAltitude = altitude;
	*/

	int flightId = 0;
	int timeStampToLocate = 0;
	string from="";
	string to = "";
	int takeOffFlight = 0;
	int numberCordinates = 0;
	for (int i = 0; i < N; i++)
	{	
		in >> flightId >> timeStampToLocate;

		string locatie_file = "./usedFlights/" + std::to_string(flightId) + ".csv";
		std::ifstream handler(locatie_file);

		handler >> from;
		handler >> to;
		handler >> takeOffFlight;
		handler >> numberCordinates;

		int offset = 0;
		float latitude = 0;
		float longitude = 0;
		float altitudine = 0;
		Cordinate anterior_location{ takeOffFlight,0,0,0 };
		Cordinate curent_location{ takeOffFlight,0,0,0 };

		for (int iterator_line = 0; iterator_line < numberCordinates; iterator_line++)
		{
			handler >> offset >> separator;
			handler >> latitude >> separator;
			handler >> longitude >> separator;
			handler >> altitude;

			curent_location = Cordinate{ takeOffFlight + offset,latitude,longitude,altitude };

			if (curent_location.get_timeStamp() > timeStampToLocate)
				break;

			anterior_location = curent_location;
		}
		
		Cordinate result = linear_interpolation(curent_location,anterior_location, timeStampToLocate);
		out << result << '\n';
		/* Level 2
		in >> timeStamp >> separator;
		in >> latitude >> separator;
		in >> longitude >> separator;
		in >> altitude >> separator;

	// Construiesc zborul 
		read_data(starting_point);
		read_data(ending_point);
		in >> takeOff;
		Flight f(starting_point, ending_point);

		auto iterator = flights.find(f);// Caut zborul in map 
		if (iterator != flights.end())// am gasit zborul 
			iterator->second.append(takeOff);
		else
		{
			TakeOff x;
			x.append(takeOff);
			flights.insert({ f, x });
		}

		 Level1
		minTimeStamp = getMinim<int>(timeStamp, minTimeStamp);
		maxTimeStamp = getMaxim<int>(timeStamp, maxTimeStamp);
		minLongitude = getMinim<float>(longitude, minLongitude);
		maxLongitude = getMaxim<float>(longitude, maxLongitude);
		minLatitude = getMinim<float>(latitude, minLatitude);
		maxLatitude = getMaxim<float>(latitude, maxLatitude);
		maxAltitude = getMaxim<float>(altitude, maxAltitude);
		*/
	
	}
	/* Level 1
	out << minTimeStamp << " " << maxTimeStamp << '\n';
	out << minLatitude << " " << maxLatitude << '\n';
	out << minLongitude << " " << maxLongitude << '\n';
	out << maxAltitude;
	*/

	for (auto it : flights)
			out << it.first << " " << it.second.occurences() << '\n';
}