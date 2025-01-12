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
	string parseString(string str, int& start)
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
	UsersData(const UsersData& other)
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
	void readFromFile(ifstream& FileToRead)
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

// UsersProfiles class to manage profiles
class UsersProfiles
{
	vector<UsersData> users_profiles;

public:
	// default constructor that will read the data automatically from the file
	UsersProfiles()
	{
		ifstream FileToRead(profilesPath);

		if (!FileToRead.is_open())
		{
			cout << "Unable to open file" << endl;
			return;
		}

		UsersData obj;
		string line;

		getline(FileToRead, line);
		obj.readLine(line);
		this->users_profiles.push_back(obj);

		while (getline(FileToRead, line))
		{
			if (line == "" || line == "\n")
				continue;
			obj.readLine(line);
			this->users_profiles.push_back(obj);
		}
		FileToRead.close();

		// reading relationships file
		FileToRead.open(relationshipsPath);
		if (!FileToRead.is_open())
		{
			cout << "Unable to open file" << endl;
			return;
		}

		int user_id, friend_id;

		while (FileToRead >> user_id >> friend_id)
		{
			if (FileToRead.eof())
				break;
			this->users_profiles[user_id - 1].friends.push_back(friend_id);
		}
		FileToRead.close();
	}

	// copy constructor to copy the data
	UsersProfiles(const UsersProfiles& other)
	{
		this->users_profiles = other.users_profiles;
	}

	// function to display random user last login time and registration time
	void displayRandomUser(int userIndex)
	{
		this->users_profiles[userIndex].display();
	}

	// function to get number of profiles
	size_t getNumProfiles()
	{
		return this->users_profiles.size();
	}

	// function to check if proposition holds or not
	void proposition()
	{
		cout << "---------------------------------- Proposition ----------------------------------" << endl;
		int index1, index2;
		cout << "Enter pokec user 1: ";
		cin >> index1;
		cout << "Enter pokec user 2: ";
		cin >> index2;
		propositionHolder(users_profiles[index1 - 1], users_profiles[index2 - 1]);
		cout << endl;
	}

	// function to check quantifiers conditions
	void Quantifies()
	{
		cout << "---------------------------------- Quantifiers ----------------------------------" << endl;
		string region;
		int age, comp_percentage;
		cout << "Enter Region, Age and Completion Percentage for Condition 1 " << endl;
		cout << "Enter region: ";
		getline(cin, region);
		cout << "Enter age: ";
		cin >> age;
		cout << "Enter completion percentage: ";
		cin >> comp_percentage;
		cin.ignore();

		// built-in function to convert string to lowercase
		transform(region.begin(), region.end(), region.begin(), ::tolower);

		if (ExistentialQuantifier(region, age, comp_percentage))
		{
			cout << "There exists a user in " + region + " who is above " << age
				<< "and has a completion percentage above " << 70 << " % ." << endl;
		}
		else
			cout << "No user found" << endl;

		cout << "Enter Region, Age and Completion Percentage for Condition 2 " << endl;
		cout << "Enter region: ";
		getline(cin, region);
		cout << "Enter age: ";
		cin >> age;
		cout << "Enter completion percentage: ";
		cin >> comp_percentage;

		if (UniversalQuantifer(region, age, comp_percentage))
		{
			cout << "Every user in " + region << " above " << age << " has completed "
				<< comp_percentage << "% of their profiles." << endl;
		}
		else
			cout << "There is atleast one use in " + region << " above " << age << " who has not completed "
			<< comp_percentage << "% of his/her profile." << endl;
		cout << endl
			<< endl;
	}

	// function to perform set operations
	void Sets()
	{
		cout << "---------------------------------- Sets ----------------------------------" << endl;
		vector<int> setA;
		vector<int> setB;
		vector<int> unionAB;
		vector<int> intersectionAB;
		vector<int> complementA;
		string region;
		int isPublic;

		cout << "For set A: Enter 1 for public profiles and 0 for private profiles: ";
		cin >> isPublic;
		cin.ignore();

		if (isPublic)
		{
			for (int i = 0; i < users_profiles.size(); i++)
			{
				if (users_profiles[i].getIsPublic())
				{
					setA.push_back(users_profiles[i].getUserId());
				}
			}
		}
		else
		{
			for (int i = 0; i < users_profiles.size(); i++)
			{
				if (!users_profiles[i].getIsPublic())
				{
					setA.push_back(users_profiles[i].getUserId());
				}
			}
		}

		cout << "For set B: Enter the region to check for users: ";
		getline(cin, region);

		// built-in function to convert string to lowercase
		transform(region.begin(), region.end(), region.begin(), ::tolower);

		for (int i = 0; i < users_profiles.size(); i++)
		{
			if (isRegionInString(users_profiles[i].getRegion(), region))
			{
				setB.push_back(users_profiles[i].getUserId());
			}
		}

		cout << "Set A: ";
		for (int i = 0; i < setA.size(); i++)
		{
			cout << setA[i] << " ";
		}
		cout << "\nSet B: ";
		for (int i = 0; i < setB.size(); i++)
		{
			cout << setB[i] << " ";
		}
		cout << endl;
		Set_Union(setA, setB, unionAB);
		cout << "Union of AB: ";
		for (int i = 0; i < unionAB.size(); i++)
		{
			cout << unionAB[i] << " ";
		}
		cout << endl;
		Set_Intersection(setA, setB, intersectionAB);
		cout << "Intersection of AB: ";
		for (int i = 0; i < intersectionAB.size(); i++)
		{
			cout << intersectionAB[i] << " ";
		}
		cout << endl;
		cout << "Complement of A: ";
		Set_complement(setA, complementA);
		for (int i = 0; i < complementA.size(); i++)
		{
			cout << complementA[i] << " ";
		}
		cout << endl
			<< endl;
	}

	// function to show the ven diagram of the users
	void VenDiagram()
	{
		cout << "---------------------------------- Ven Diagram ----------------------------------" << endl;
		vector<int> setA;
		vector<int> setB;
		vector<int> setC;
		vector<int> intersectionABC;
		int age;
		int isPublic;
		string region;

		cout << "For set A: Enter 1 for public profiles and 0 for private profiles: ";
		cin >> isPublic;
		cout << "For set B: Enter age to check: ";
		cin >> age;
		cin.ignore();
		cout << "For set C: Enter region to check: ";
		getline(cin, region);

		// built-in function to convert string to lowercase
		transform(region.begin(), region.end(), region.begin(), ::tolower);

		for (auto& user : users_profiles)
		{
			if (isPublic)
			{
				if (user.getIsPublic())
				{
					setA.push_back(user.getUserId());
				}
			}
			else
			{
				if (!user.getIsPublic())
				{
					setA.push_back(user.getUserId());
				}
			}

			if (user.getAge() > age)
			{
				setB.push_back(user.getUserId());
			}

			if (isRegionInString(user.getRegion(), region))
			{
				setC.push_back(user.getUserId());
			}
		}

		cout << "Set A: ";
		for (auto& user : setA)
		{
			cout << user << " ";
		}
		cout << endl
			<< "Set B: ";
		for (auto& user : setB)
		{
			cout << user << " ";
		}
		cout << endl
			<< "Set C: ";
		for (auto& user : setC)
		{
			cout << user << " ";
		}

		// intersection of A, B, C
		Set_Intersection(setA, setB, intersectionABC);
		Set_Intersection(intersectionABC, setC, intersectionABC);

		if (intersectionABC.empty())
		{
			cout << "\n\nA, B, C are disjoint sets " << endl;
		}
		else
		{
			bool isInA = false, isInB = false, isInC = false;
			cout << "\n\nIntersection of A, B, C: ";

			for (auto& userID : intersectionABC)
			{
				cout << userID << " ";
				if (isInArray(userID, setA))
					isInA = true;
				if (isInArray(userID, setB))
					isInB = true;
				if (isInArray(userID, setC))
					isInC = true;
			}

			if (isInA && isInB && isInC)
			{
				cout << "\nA, B, C are overlapping sets." << endl;
			}
			else if (isInA && isInB)
			{
				cout << "\nA, B are overlapping sets while C is disjoint." << endl;
			}
			else if (isInA && isInC)
			{
				cout << "\nA, C are overlapping sets and B is disjoint." << endl;
			}
			else if (isInB && isInC)
			{
				cout << "\nB, C are overlapping sets and A is disjoint." << endl;
			}
		}
		cout << endl
			<< endl;
	}

	// function to show the function properties
	void functions()
	{
		cout << "---------------------------------- Functions ----------------------------------" << endl;
		vector<pair<int, int>> mapping;
		int totalUsers;
		cout << "Enter the number of users to check for function properties: ";
		cin >> totalUsers;

		if (totalUsers > users_profiles.size())
		{
			cout << "Not enough users to check for function properties." << endl;
			return;
		}

		for (int i = 0; i < totalUsers; i++)
		{
			mapping.emplace_back(users_profiles[i].getUserId(), users_profiles[i].getCompletionPercentage());
		}
		cout << "Domain: ";
		for (int i = 0; i < mapping.size(); i++)
		{
			cout << mapping[i].first << " ";
		}
		cout << endl
			<< "Range: ";
		for (int i = 0; i < mapping.size(); i++)
		{
			cout << mapping[i].second << " ";
		}
		cout << endl;
		if (isInjective(mapping))
		{
			cout << "Function is one-to-one (injective)" << endl;
		}
		else
			cout << "Function is not one-to-one (injective)" << endl;
		if (isSurjective(mapping))
			cout << "Function is onto" << endl;
		else
			cout << "Function is not onto" << endl;
		cout << endl
			<< endl;
	}

	// function to show Relation property of the users
	void relations()
	{
		cout << "---------------------------------- Relations ----------------------------------" << endl;

		int user1, user2, user3;
		cout << "Enter user 1: ";
		cin >> user1;
		cout << "Enter user 2: ";
		cin >> user2;
		cout << "Enter user 3: ";
		cin >> user3;

		// checking for reflexive
		if (checkReflexive(users_profiles[user1 - 1]))
			cout << "\nUser " << user1 << "'s Relation is reflexive" << endl;
		else
			cout << "\nUser " << user1 << "'s Relation is not reflexive" << endl;

		// checking for symmetric
		if (checkSymmetrix(users_profiles[user1 - 1], users_profiles[user2 - 1]))
			cout << "User " << user1 << " and User " << user2 << "'s Relation is symmetric" << endl;
		else
			cout << "User " << user1 << " and User " << user2 << "'s Relation is not symmetric" << endl;

		// checking for transitive
		if (checkTransitive(users_profiles[user1 - 1], users_profiles[user2 - 1], users_profiles[user3 - 1]))
			cout << "User " << user1 << ", User " << user2 << " and User " << user3 << "'s Relation is transitive" << endl;
		else
			cout << "User " << user1 << ", User " << user2 << " and User " << user3 << "'s Relation is not transitive" << endl;
		cout << endl
			<< endl;
	}

	// function to perform combination and permutation
	void combinationPermutation(int r)
	{
		cout << "---------------------------------- Combination and Permutation ----------------------------------" << endl;
		int nCr, nPr;
		int age;
		string region;
		cout << "Enter the age to check for users: ";
		cin >> age;
		cin.ignore();
		cout << "Enter the region to check for users: ";
		getline(cin, region);

		// built-in function to convert string to lowercase
		transform(region.begin(), region.end(), region.begin(), ::tolower);

		int countUsers = 0;
		for (auto& users : users_profiles)
		{
			if (users.getAge() > age && isRegionInString(users.getRegion(), region))
			{
				countUsers++;
			}
		}

		cout << "Total users with age over " << age << " from " << region << ": " << countUsers << endl;
		if (countUsers >= r)
		{
			nCr = Combination(countUsers, r);
			cout << "Combination of users with age over " << age << "from " << region << "(choosing " << r << ") : " << nCr << endl;
		}
		else
		{
			cout << "Not enough users to form a " << r << " subgroups." << endl;
		}

		int comp_percentage;
		cout << "Enter the completion percentage to check for users: ";
		cin >> comp_percentage;

		int countCompletion = 0;
		for (auto& users : users_profiles)
		{
			if (users.getCompletionPercentage() > comp_percentage)
			{
				countCompletion++;
			}
		}

		cout << "Total users with completion percentage over 50: " << countCompletion << endl;
		if (countCompletion >= r)
		{
			nPr = Permutation(countCompletion, r);
			cout << "Permutation of users with completion percentage over " << comp_percentage << " (arranging " << r << ") : " << Permutation(countCompletion, r) << endl;
		}
		else
		{
			cout << "Not enough users to form a permutation of size " << r << "." << endl;
		}
		cout << endl
			<< endl;
	}

	// function to perform counting
	void counting()
	{
		cout << "---------------------------------- Counting ----------------------------------" << endl;
		// Total number of users who have completed their profile above certain percentage
		int comp_percentage;
		cout << "Enter the completion percentage limit to check for users: ";
		cin >> comp_percentage;

		int countAbove = 0;
		for (auto& users : users_profiles)
		{
			if (users.getCompletionPercentage() > comp_percentage)
			{
				countAbove++;
			}
		}
		cout << "Total number of users who have completed their profile above " << comp_percentage << " are: " << countAbove << endl;

		// Number of users in each region
		vector<pair<string, int>> regionCount;

		for (auto& users : users_profiles)
		{
			bool found = false;
			for (auto& region : regionCount)
			{
				if (region.first == users.getRegion())
				{
					region.second++;
					found = true;
					break;
				}
			}
			if (!found)
			{
				regionCount.push_back({ users.getRegion(), 1 });
			}
		}

		cout << "Number of users in each region: " << endl;
		for (auto& region : regionCount)
		{
			cout << region.first << ": " << region.second << endl;
		}

		// Generate a report on Count of public profiles
		int countPublic = 0;
		for (auto& user : users_profiles)
		{
			if (user.getIsPublic())
			{
				countPublic++;
			}
		}
		cout << "Total number of public profiles: " << countPublic << endl;
		cout << endl
			<< endl;
	}

	// representing the relationships using tree structure
	void relationshipsAsTree()
	{
		cout << "---------------------------------- Relationships Tree ----------------------------------" << endl;
		int user1;
		cout << "Enter user to represents it's relation as Tree: ";
		cin >> user1;
		cout << "User's ID: " << users_profiles[user1 - 1].getUserId() << ".\t Total Friends: " << users_profiles[user1 - 1].getNumFriends() << " friends." << endl;

		Tree tree;
		int val = users_profiles[user1 - 1].getUserId();
		tree.insert(val);

		for (auto& friendId : users_profiles[user1 - 1].friends)
		{
			if (friendId > users_profiles.size())
			{
				cout << "Friend ID " << friendId << " does not exist. Or data range is too short!" << endl;
				continue;
			}
			val = users_profiles[friendId - 1].getUserId();
			tree.insert(val);
		}

		// displaying the friends tree as inorder, postorder, and preorder traversal
		tree.Display();
		cout << endl
			<< endl;
	}

	// Graphs representing the relationships
	void BipartiteGraph()
	{
		cout << "---------------------------------- Bipartite Graph ----------------------------------" << endl;

		int n;
		cout << "Enter the number of users to check for a bipartite graph: ";
		cin >> n;
		cout << endl;
		Graph graph(n);
		int maxIndex = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < users_profiles[i].getNumFriends(); j++)
			{
				int index = users_profiles[i].friends[j] - 1;
				graph.addEdge(i, index);
				maxIndex = max(maxIndex, index);
			}
		}

		graph.resizeGraph(maxIndex + 1);

		//	graph.display();

		// Checking if the graph is bipartite
		if (graph.isBipartite())
		{
			cout << "Graph is Bipartite" << endl;
		}
		else
		{
			cout << "Graph is not Bipartite" << endl;
		}
		cout << endl
			<< endl;
	}

	// Graphs representation as MST
	void MST()
	{
		cout << "---------------------------------- Minimum Spanning Tree ----------------------------------" << endl;

		int n;
		cout << "Enter the number of users to check for a Minimum Spanning Tree: ";
		cin >> n;
		cout << endl;
		Graph graph(n);
		int maxIndex = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < users_profiles[i].getNumFriends(); j++)
			{
				int index = users_profiles[i].friends[j] - 1;
				graph.addEdge(i, index);
				maxIndex = max(maxIndex, index);
			}
		}

		graph.resizeGraph(maxIndex + 1);

		cout << "Minimum Spanning Tree: " << endl;
		graph.kruskalMST();

		cout << endl
			<< endl;
	}

	// proving induction
	void induction()
	{
		cout << "---------------------------------- Induction ----------------------------------" << endl;

		int threshold, X;
		cout << "Enter the threshold completion percentage: ";
		cin >> threshold;
		cout << "Enter the number of users which should be greater than " << threshold << " : ";
		cin >> X;

		if (this->proveInduction(threshold, X))
		{
			cout << "Induction proof complete: The number of users with a completion_percentage above " << threshold << " is greater than " << X << endl;
		}
		else
		{
			cout << "Induction Does not prove,less than " << X << " users have a completion_percentage above " << threshold << endl;
		}
	}

	// destructor
	~UsersProfiles() { this->users_profiles.clear(); }


	/*      All Helpers Functions that are used above */
private:
	// function to check if the proposition holds

	// function to check for existential quantifiers
	bool ExistentialQuantifier(const string region, int age, int comp_percentage)
	{
		for (int i = 0; i < users_profiles.size(); i++)
		{
			if (isRegionInString(users_profiles[i].getRegion(), region) &&
				users_profiles[i].getAge() > age &&
				users_profiles[i].getCompletionPercentage() > comp_percentage)
				return true;
		}
		return false;
	}

	// function to check for universal quantifiers
	bool UniversalQuantifer(const string region, int age, int comp_percentage)
	{
		for (int i = 0; i < users_profiles.size(); i++)
		{
			if (isRegionInString(users_profiles[i].getRegion(), region))
			{
				if (users_profiles[i].getAge() > age)
				{
					if (users_profiles[i].getCompletionPercentage() < comp_percentage)
						return false;
				}
			}
		}
		return true;
	}

	// function to check if the proposition holds or not
	void propositionHolder(const UsersData user1, const UsersData user2)
	{
		int age;
		int comp_percentage;
		cout << "Enter the age for the proposition: ";
		cin >> age;
		cout << "Enter the completion percentage for the proposition: ";
		cin >> comp_percentage;
		time_t now = time(nullptr);
		tm lastYearTime;

		// Using localtime_s for thread safety and to avoid warnings
		if (localtime_s(&lastYearTime, &now) == 0)
		{
			// Subtract one year
			lastYearTime.tm_year -= 1;
		}
		else
			cout << "Error: Failed to get local time" << endl;

		// now we have last year stored in lastyeartime
		cout << "-------------------- User 1 ---------------------" << endl;
		user1.display();
		bool above30 = user1.getAge() > age;
		bool completion_percentage = user1.getCompletionPercentage() > comp_percentage;
		if (!above30 || completion_percentage)
			cout << "Implication holds" << endl;
		else
			cout << "Implication does not hold" << endl;

		bool lastyearlogin = (user1.getLastLogin().tm_year >= lastYearTime.tm_year);
		if (user1.getIsPublic() == lastyearlogin)
			cout << "Biconditional holds.." << endl;
		else
			cout << "Biconditional does not hold" << endl;
		cout << endl;

		// now checking for user 2
		cout << "-------------------- User 2 ---------------------" << endl;
		user2.display();
		above30 = user2.getAge() > age;
		completion_percentage = user2.getCompletionPercentage() > comp_percentage;
		if (!above30 || completion_percentage)
			cout << "Implication holds" << endl;
		else
			cout << "Implication does not hold" << endl;
		lastyearlogin = (user2.getLastLogin().tm_year >= lastYearTime.tm_year);
		if (user2.getIsPublic() == lastyearlogin)
			cout << "Biconditional holds.." << endl;
		else
			cout << "Biconditional does not hold" << endl;
		cout << endl;
	}

	bool isInArray(int val, const vector<int>& arr)
	{
		return std::find(arr.begin(), arr.end(), val) != arr.end();
	}

	// function to form unoin of A and B and then store in AB
	void Set_Union(const vector<int> setA, const vector<int> setB, vector<int>& setAB)
	{
		setAB = setA;
		for (int i = 0; i < setB.size(); i++)
		{
			if (!isInArray(setB[i], setA))
			{
				setAB.push_back(setB[i]);
			}
		}
	}

	// function to take intersection of A, B and store in AB
	void Set_Intersection(const vector<int> setA, const vector<int> setB, vector<int>& setAB)
	{
		for (int i = 0; i < setA.size(); i++)
		{
			if (isInArray(setA[i], setB))
			{
				setAB.push_back(setA[i]);
			}
		}
	}

	// function to take compliment of a given sent
	void Set_complement(vector<int> set, vector<int>& complement)
	{
		vector<int> universal;
		for (int i = 0; i < users_profiles.size(); i++)
		{
			universal.push_back(users_profiles[i].getUserId());
		}

		for (int i = 0; i < universal.size(); i++)
		{
			if (!isInArray(universal[i], set))
				complement.push_back(universal[i]);
		}
	}

	// function to check if injective property holds or not for certain conditions
	bool isInjective(const vector<pair<int, int>> map)
	{
		for (int i = 0; i < map.size() - 1; i++)
		{
			for (int j = i + 1; j < map.size(); j++)
			{
				if (map[i].second == map[j].second)
					return false;
			}
		}
		return true;
	}

	// function to check if surjective property holds or not for certain conditions
	bool isSurjective(const vector<pair<int, int>> map)
	{
		bool check = false;
		for (int i = 1; i <= 100; i++)
		{
			check = false;
			for (int j = 0; j < map.size(); j++)
			{
				if (i == map[j].second)
				{
					check = true;
					break;
				}
			}
			if (!check)
				return false;
		}
		return true;
	}

	// function to check if the subregion is in the region
	bool isRegionInString(const string& fullRegion, const string subRegion)
	{
		return fullRegion.find(subRegion) != string::npos;
	}

	// function to check if the relation is reflexive if (a,a) is in R
	bool checkReflexive(const UsersData& user1)
	{
		for (int i = 0; i < user1.getNumFriends(); i++)
		{
			int index = user1.friends[i] - 1;
			if (index > users_profiles.size())
				continue;
			if (user1.getUserId() == users_profiles[index].getUserId())
			{
				return true;
			}
		}
		return false;
	}

	// function to check if the relation is symmetric if (a,b) is in R then (b,a) should be in R
	bool checkSymmetrix(const UsersData& user1, const UsersData& user2)
	{
		for (int i = 0; i < user1.getNumFriends(); i++)
		{
			int index = user1.friends[i] - 1;
			if (index > users_profiles.size())
				continue;
			if (user2.getUserId() == users_profiles[index].getUserId())
			{
				for (int j = 0; j < user2.getNumFriends(); j++)
				{
					int index2 = user2.friends[j] - 1;
					if (index2 > users_profiles.size())
						continue;
					if (user1.getUserId() == users_profiles[index2].getUserId())
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	// function to check if the relation is transitive if (a,b) and (b,c) is in R then (a,c) should be in R
	bool checkTransitive(const UsersData& user1, const UsersData& user2, const UsersData& user3)
	{
		// Check if user2 is a friend of user1
		for (int i = 0; i < user1.getNumFriends(); i++)
		{
			int index1 = user1.friends[i] - 1;
			if (index1 > users_profiles.size())
				continue;
			if (user2.getUserId() == users_profiles[index1].getUserId())
			{
				// Check if user3 is a friend of user2
				for (int j = 0; j < user2.getNumFriends(); j++)
				{
					int index2 = user2.friends[j] - 1;
					if (index2 > users_profiles.size())
						continue;
					if (user3.getUserId() == users_profiles[index2].getUserId())
					{
						// Check if user3 is also a friend of user1
						for (int k = 0; k < user1.getNumFriends(); k++)
						{
							int index3 = user1.friends[k] - 1;
							if (index3 > users_profiles.size())
								continue;
							if (user3.getUserId() == users_profiles[index3].getUserId())
							{
								// If user3 is a friend of user1, the transitive property holds
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// function to prove induction
	bool proveInduction(int threshold, int X)
	{
		int count = 0;

		// Base case
		if (users_profiles[0].getCompletionPercentage() > threshold)
		{
			count++;
		}
		else
		{
			return false;
		}

		// Inductive case
		for (int k = 1; k < users_profiles.size(); k++)
		{
			if (users_profiles[k].getCompletionPercentage() > threshold)
			{
				count++;
			}

			// If at any point the count exceeds X, return true
			if (count > X)
			{
				return true;
			}
		}

		// Return based on the final count
		return count > X;
	}

	// function to calculate the Combination
	unsigned long long Combination(int n, int r)
	{
		if (r == 0 || r == n)
			return 1;
		else
			return Combination(n - 1, r - 1) + Combination(n - 1, r);
	}

	// function to calculate the permutation
	unsigned long long Permutation(int n, int r)
	{
		if (r == 0)
			return 1;
		else
			return n * Permutation(n - 1, r - 1);
	}

};

int main()
{
	UsersProfiles profilesObject;

	int choice;

	do
	{
		cout << "\nMenu:\n";
		cout << "1. Proposition\n";
		cout << "2. Quantifies\n";
		cout << "3. Sets\n";
		cout << "4. Venn Diagram\n";
		cout << "5. Functions\n";
		cout << "6. Relations\n";
		cout << "7. Induction\n";
		cout << "8. Combination/Permutation\n";
		cout << "9. Counting\n";
		cout << "10. Relationships as Tree\n";
		cout << "11. Bipartite Graph\n";
		cout << "12. Minimum Spanning Tree\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		cin.ignore();

		switch (choice)
		{
		case 1:
			profilesObject.proposition();
			break;

		case 2:
			profilesObject.Quantifies();
			break;

		case 3:
			profilesObject.Sets();
			break;

		case 4:
			profilesObject.VenDiagram();
			break;

		case 5:
			profilesObject.functions();
			break;

		case 6:
			profilesObject.relations();
			break;

		case 7:
			profilesObject.induction();
			break;

		case 8:
			int r;
			cout << "Enter r for Combination/Permutation: ";
			cin >> r;
			profilesObject.combinationPermutation(r);
			break;

		case 9:
			profilesObject.counting();
			break;

		case 10:
			profilesObject.relationshipsAsTree();
			break;

		case 11:
			profilesObject.BipartiteGraph();
			break;

		case 12:
			profilesObject.MST();
			break;

		case 0:
			cout << "Exiting program.\n";
			break;

		default:
			cout << "Invalid choice. Try again.\n";
			break;
		}

		system("pause");
		system("cls");
	} while (choice != 0);

	return 0;
}

///////////////////////////////////////////// THE END /////////////////////////////////////////////
