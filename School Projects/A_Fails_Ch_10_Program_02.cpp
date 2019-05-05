/*
Alex Fails
5/4/19
This program will create a file of a list of students with 3 grade scores and the sum of those scores
to exit program enter "ZZZ" 0 0 0
*/

#include <sys/stat.h> //used for gathering information from file
#include <iostream>
#include <string>
#include<fstream>

using namespace std;

//modules
void eraseFileLine(string, string);
void createFile(string, string, string, int, int, int, int);
void appendFile(string, string, string, int, int, int, int);
void readFile(string);
void searchFile(string, string);

//function to test for existing file (this code get "inserted" where ever "exists" is called)
inline bool exists(const string & fileName)
{
	struct stat buffer;
	return(stat (fileName.c_str(), &buffer) == 0);
}
/***************************MAIN********************************/
int main()
{
	//On/Off Switch
	bool run = true;
	
	do
	{
		//varibles
		string fileName = "";
		string studentName = "";
		string funct, fileOutput;
		string stopLine = "zzz 0 0 0 0"; //for appending files
		int t1, t2, t3, sum;
		ofstream studentFile;
		
		//Ask user what they would like to do
		cout << "Enter option: 1 (Write to File)  2 (Read File) 3 (Search File) 4 (exit program)\n";
		cin >> funct;
		
		
		if (funct != "4")
		{
			//Ask user what file they would like to open
			cout << "Enter File Name (include dot notations \".txt\"): ";
			cin >> fileName;
		}
		//append file or create new file.
		if (funct == "1")
		{
			//removes "zzz 0 0 0 0" frome file if it exits
			if (exists(fileName) == true)
			{
				eraseFileLine(fileName, stopLine);
				appendFile(fileName, studentName, fileOutput, t1, t2, t3, sum);
			}
			//create file, if one doesn't exists
			if (exists(fileName) != true)
			{
				createFile(fileName, studentName, fileOutput, t1, t2, t3, sum);
			}
		}
		if (funct == "2")
		{
			readFile(fileName);
		}
		if (funct == "3")
		{
			searchFile(fileName, studentName);
		}
		if (funct == "4")
		{
			run = false;
		}
	}while(run);
	return 0;
}
/******************Erase File Line*****************************************/
void eraseFileLine(string fileName, string stopLine)
{
	//varibles
	string line;
	ifstream fin; //input file and call it fin
	fin.open(fileName); //open file
	
	//create temp file to wrtie to
	ofstream temp;
	temp.open("temp.txt");
	
	//loop through all lines in file and delete stopLine
	while (getline(fin, line)) // get a line in file (fin) assign to var line
	{
		if (line != stopLine) //wrtie line to temp file
		{
			temp << line << endl;
		}
	}
	//close files
	temp.close();
	fin.close();
	//rename temp file to fin file (overwriting it)
	//create pointer to fileName
	const char *p = fileName.c_str(); //required convertion for remove and rename funct
	remove(p); //delete fileName file (original)
	rename("temp.txt", p); //rename temp file (new)
}

/*****************Create New File*****************************************/
void createFile(string fileName,string studentName, string fOut, int t1, int t2, int t3, int sum)
{
	//varibles
	int count = 1;
	//create file
	ofstream studentFile;
	studentFile.open(fileName);
	
	//infinite loop to enter students in
	while(true)
	{
		cout << "Please enter student #" << count << ": ";
		cin >> studentName;
		if (studentName == "zzz")
		{
			studentFile << "zzz 0 0 0 0";
			break;
		}
		cout << "Please enter test #1: ";
		cin >> t1;
		cout << "Please enter test #2: ";
		cin >> t2;
		cout << "Please enter test #3: ";
		cin >> t3;
		sum = t1 + t2 + t3;
		fOut = studentName + " " + to_string(t1) + " " + to_string(t2) + " " + to_string(t3) + " " + to_string(sum) + "\n";
		studentFile << fOut;

		count += 1;
	}
	studentFile.close();
}

/****************Append File (Add to)*******************************************/
void appendFile(string fileName, string studentName, string fOut, int t1, int t2, int t3, int sum)
{	
	//varibles
	int count = 1;
	//open file to write to
	ofstream studentFile;
	studentFile.open(fileName, ios::app);
	//infinite loop to enter students in
	while(true)
	{
		cout << "Please enter student #" << count << ": ";
		cin >> studentName;
			if (studentName == "zzz")
		{
			studentFile << "zzz 0 0 0 0";
			break;
		}
		cout << "Please enter test #1: ";
		cin >> t1;
		cout << "Please enter test #2: ";
		cin >> t2;
		cout << "Please enter test #3: ";
		cin >> t3;
		sum = t1 + t2 + t3;
		fOut = studentName + " " + to_string(t1) + " " + to_string(t2) + " " + to_string(t3) + " " + to_string(sum) + "\n";
		studentFile << fOut;
		cin.ignore(); //clear end line charater in buffer
		
		count += 1;	
	}
	studentFile.close();
}
/*************************Read File***********************************/
void readFile(string file)
{
	//varibles
	string line;
	//create varible stream called f for file
	ifstream f;
	f.open(file);
	
	//test file is open
	if (f.is_open() == true)
	{
		while (getline(f, line))
		{
			cout << line << endl;
		}
	}
	else
	{
		cout << "Couldn't find that file\n";
	}	
}
/************************Search File******************************/
void searchFile(string file, string student)
{
	//varibles
	string line; //holds line data from file
	string subStrg; //to hold temp values in string
	//open file that they want to search through
	ifstream f(file);
	
	cout << "please enter student name: ";
	cin >> student;
	
	if (f.is_open())
	{
		while (getline(f, line))
		{
			subStrg = line;
			for (int i = 0; i < 4; i++)
			{
				subStrg = subStrg.substr(0, subStrg.find_last_of(" ")); //look for last "space" and delete everything past that.
			}
			//once the string is deleted to the "student Name" varible test
			if (student == subStrg)
			{
				cout << line << endl;
			}
		}
	}
	f.close();
}
