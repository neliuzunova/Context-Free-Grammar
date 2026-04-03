#pragma once
#include <string>
using namespace std;
class Rule
{
public:
	Rule();
	Rule(string variable, const char* replacement);
	string getVar();
	const char* getReplacement();
	bool isEmpty();
	~Rule();
private:
	string m_Variable;
	char* m_Replacement;
};

