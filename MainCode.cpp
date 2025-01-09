#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
#include "Utility.cpp"

using namespace std;


// path to the files 
/*
    You can change the path for the files based on you directory location.
    As Files are too large to read at a same time, so you can read them in chunks. 
    Change the name of the files if you have different names for the files.

    You can download the files from the link below (use ctrl + click to open):
    https://snap.stanford.edu/data/soc-Pokec.html
    
*/
const string profilesPath = "soc-pokec-profiles.txt";
const string relationshipsPath = "soc-pokec-relationships.txt";


// structure to represent each user (node)
class UsersData
{
	int user_id;
	bool is_public;
	int completion_percentage;
	string gender;
	string region;
	tm last_login;	 // time of last login
	tm registration; // time of registration
	int age;
	vector<int> friends;

	// function to pare the string
	string parseString(string str, int &start)
	{
		if (start >= str.size())
			return "";
		string temp = "";
		for (; start < str.size(); start++)
		{
			if (str[start] == '\t')
			{
				start++;
				break;
			}
			temp += str[start];
		}
		(temp == "null") ? temp = "0" : temp;
		return temp;
	}

public:
	// default constructor
	UsersData()
	{
		this->user_id = 0;
		this->is_public = false;
		this->completion_percentage = this->age = 0;
		this->gender = "";
		this->region = "";
		this->last_login = this->registration = {};
	}

	// copy constructor
	UsersData(const UsersData &other)
		: user_id(other.user_id), is_public(other.is_public),
		  completion_percentage(other.completion_percentage),
		  gender(other.gender), region(other.region),
		  last_login(other.last_login), registration(other.registration),
		  age(other.age), friends(other.friends)
	{
	}

	// constructor with parameters
	UsersData(int user_id, bool is_public, int completion_percentage, string gender,
			  string region, tm last_login, tm registration, int age, int numFriends, vector<int> friends)
	{
		this->user_id = user_id;
		this->is_public = is_public;
		this->completion_percentage = completion_percentage;
		this->age = age;
		this->gender = gender;
		this->region = region;
		this->last_login = last_login;
		this->registration = registration;
		this->friends = friends;
	}

	// function to read data from file
	void readLine(string line)
	{
		string subLine;
		int start = 0;

		this->user_id = stoi(parseString(line, start));
		this->is_public = stoi(parseString(line, start));
		this->completion_percentage = stoi(parseString(line, start));
		this->gender = (stoi(parseString(line, start))) ? "male" : "female";
		this->region = parseString(line, start);
		subLine = parseString(line, start);
		if (sscanf_s(subLine.c_str(), "%4d-%2d-%2d %2d:%2d:%2d",
					 &this->last_login.tm_year, &this->last_login.tm_mon, &this->last_login.tm_mday,
					 &this->last_login.tm_hour, &this->last_login.tm_min, &this->last_login.tm_sec) == 6)
		{
			this->last_login.tm_year -= 1900;
			this->last_login.tm_mon -= 1;

			time_t time = mktime(&this->last_login);
			if (time == -1)
			{
				cout << "Failed to convert time" << endl;
			}
		}
		subLine = parseString(line, start);
		if (sscanf_s(subLine.c_str(), "%4d-%2d-%2d %2d:%2d:%2d",
					 &this->registration.tm_year, &this->registration.tm_mon, &this->registration.tm_mday,
					 &this->registration.tm_hour, &this->registration.tm_min, &this->registration.tm_sec) == 6)
		{
			this->registration.tm_year -= 1900;
			this->registration.tm_mon -= 1;

			time_t time = mktime(&this->registration);
			if (time == -1)
			{
				cout << "Failed to convert time" << endl;
			}
		}
		this->age = stoi(parseString(line, start));

		// ignoring the remaining data from the line which is redundant
	}

	// function to read data from file
	void readFromFile(ifstream &FileToRead)
	{
		int num;
		string timestamp;

		FileToRead >> this->is_public >> this->completion_percentage >> num;
		this->gender = (num) ? "male" : "female";

		FileToRead.ignore(1, '\t');

		getline(FileToRead, this->region, '\t');
		getline(FileToRead, timestamp, '\t');
		if (sscanf_s(timestamp.c_str(), "%4d-%2d-%2d %2d:%2d:%2d",
					 &this->last_login.tm_year, &this->last_login.tm_mon, &this->last_login.tm_mday,
					 &this->last_login.tm_hour, &this->last_login.tm_min, &this->last_login.tm_sec) == 6)
		{
			this->last_login.tm_year -= 1900;
			this->last_login.tm_mon -= 1;

			time_t time = mktime(&this->last_login);
			if (time == -1)
			{
				cout << "Failed to convert time" << endl;
			}
		}

		getline(FileToRead, timestamp, '\t');
		if (sscanf_s(timestamp.c_str(), "%4d-%2d-%2d %2d:%2d:%2d",
					 &this->registration.tm_year, &this->registration.tm_mon, &this->registration.tm_mday,
					 &this->registration.tm_hour, &this->registration.tm_min, &this->registration.tm_sec) == 6)
		{
			this->registration.tm_year -= 1900;
			this->registration.tm_mon -= 1;

			time_t time = mktime(&this->registration);
			if (time == -1)
			{
				cout << "Failed to convert time" << endl;
			}
		}
		FileToRead >> this->age;
		FileToRead.ignore(1, '\n');

		// read the remaining data from the line ( which is not for use)
		getline(FileToRead, timestamp);
	}

	// function to display user data
	void display() const
	{
		cout << "User ID: " << this->user_id << endl;
		cout << "Is Public: " << this->is_public << endl;
		cout << "Completion Percentage: " << this->completion_percentage << endl;
		cout << "Gender: " << this->gender << endl;
		cout << "Region: " << this->region << endl;

		cout << "Last Login: " << this->last_login.tm_hour << ":" << this->last_login.tm_min << ":" << this->last_login.tm_sec << " on "
			 << this->last_login.tm_mday << "-" << this->last_login.tm_mon + 1 << "-" << this->last_login.tm_year + 1900 << endl;

		cout << "Registration: " << this->registration.tm_hour << ":" << this->registration.tm_min << ":" << this->registration.tm_sec << " on "
			 << this->registration.tm_mday << "-" << this->registration.tm_mon + 1 << "-" << this->registration.tm_year + 1900 << endl;

		cout << "Age: " << this->age << endl;
		cout << "Total Friends: " << this->friends.size() << endl;
	}

	// getter functions to get user data
	int getUserId() const { return this->user_id; }
	bool getIsPublic() const { return this->is_public; }
	int getCompletionPercentage() const { return this->completion_percentage; }
	string getGender() const { return this->gender; }
	string getRegion() const { return this->region; }
	tm getLastLogin() const { return this->last_login; }
	tm getRegistration() const { return this->registration; }
	int getRegistrationYear() const { return this->registration.tm_year + 1900; }
	int getLastLoginYear() const { return this->last_login.tm_year + 1900; }
	size_t getNumFriends() const { return this->friends.size(); }
	int getAge() const { return this->age; }

	// destructor
	~UsersData() { this->friends.clear(); }

	friend class UsersProfiles;
};

int main()
{
    return 0;
}
