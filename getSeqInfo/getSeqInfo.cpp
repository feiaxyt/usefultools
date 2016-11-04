#include <iostream>
#include <opencv.hpp>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
using namespace cv;

struct SeqInfo
{
	string name;
	string path;
	string inName;
	string gtName;
	int startFrame;
	int endFrame;
	int nz;
	string ext;
	int init_rect[4];
};
SeqInfo* getSeq(string configName,int n)
{
	SeqInfo *seqInfo = new SeqInfo[n];
	ifstream confIn;
	confIn.open(configName, ios::in);
	if(confIn.fail())
	{
		cout << configName << endl;
		cout << "Error, fail to open " << configName << endl;
		return NULL;
	}
	string line;
	stringstream ss;
	int i = 0;
	while (!confIn.eof() && i < n)
	{
		getline(confIn, line);
		if (line[0] == '#' || line.empty() || line[0] == ' ')
			continue;
		ss << line;
		ss >> seqInfo[i].name;
		ss >> seqInfo[i].path;
		ss >> seqInfo[i].inName;
		ss >> seqInfo[i].gtName;
		ss >> seqInfo[i].startFrame;
		ss >> seqInfo[i].endFrame;
		ss >> seqInfo[i].nz;
		ss >> seqInfo[i].ext;
		ss.clear();
		i++;
	}
	confIn.close();
	ifstream rectIn;
	char c;
	for (i = 0; i < n; ++i)
	{
		rectIn.open(seqInfo[i].path + seqInfo[i].gtName, ios::in);
		if (rectIn.fail())
		{
			cout << "Error, fail to open " << seqInfo[i].path + seqInfo[i].gtName << endl;
			return NULL;
		}
		getline(rectIn, line);
		ss << line;
		for (int j = 0; j < 4; ++j)
		{
			ss >> seqInfo[i].init_rect[j];
			ss >> c;
		}
		ss.clear();
		rectIn.close();
	}
	return seqInfo;
}
int main()
{
	int seqNum = 51;
	string t = "configSeq.txt";
	SeqInfo *info = getSeq(t, seqNum);
	if (!info)
	{
		cout << "Error, fail to get seq info!" << endl;
		exit(1);
	}
	for (int i = 0; i < seqNum; ++i)
	{
		cout << info[i].name << " ";
		cout << info[i].path << " ";
		cout << info[i].inName << " ";
		cout << info[i].gtName << " ";
		cout << info[i].startFrame << " ";
		cout << info[i].endFrame << " ";
		cout << info[i].nz << " ";
		cout << info[i].ext << " ";
		cout << info[i].init_rect[0] << " ";
		cout << info[i].init_rect[1] << " ";
		cout << info[i].init_rect[2] << " ";
		cout << info[i].init_rect[3] << " ";
		cout << endl;
	}
	delete[] info;
	return 0;
}