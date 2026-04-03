#pragma once
#include "Rule.h"

const int START_CAPACITY = 1;
class Grammar
{
public:

	Grammar();
	Grammar(int grammerId, string startVar);

	int AddRule(Rule& rule);
	void removeRule(int number);

	int getId();
	string getStartVar();
	Rule& getRule(int number);
	int getRuleCount();

	string getRuleVar(int id);
	const char* getRuleReplacement(int id);
	void Clear();

	~Grammar();

private:
	int m_Id;
	string m_StartVar;
	Rule* m_RuleList;
	int m_Capacity;
	int m_MaxSize;
};

