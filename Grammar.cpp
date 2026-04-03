#include "Grammar.h"

Grammar::Grammar()
{
	m_RuleList = new Rule[START_CAPACITY];
	m_MaxSize = START_CAPACITY;
	m_Capacity = 0;
}

Grammar::Grammar(int id, string startVar)
{
	m_Id = id;
	m_StartVar = startVar;
	m_Capacity = 0;
	m_MaxSize = START_CAPACITY;
	m_RuleList = new Rule[START_CAPACITY];
}

int Grammar::AddRule(Rule& rule)
{
	if (m_Capacity + 1> m_MaxSize)
	{
		m_MaxSize *= 2;
		Rule* temp = new Rule[m_MaxSize];
		for (int i = 0; i < m_Capacity; i++)
		{
			temp[i] = m_RuleList[i];
		}
		delete[] m_RuleList;
		m_RuleList = temp;
	}
	m_RuleList[m_Capacity] = rule;
	m_Capacity++;
	return m_Capacity - 1;
}

void Grammar::removeRule(int number)
{	
	m_RuleList[number] = Rule();
}

Rule& Grammar::getRule(int number)
{
	return m_RuleList[number];
}

int Grammar::getRuleCount()
{
	return m_Capacity;
}

int Grammar::getId()
{
	return m_Id;
}

string Grammar::getStartVar()
{
	return m_StartVar;
}


string Grammar::getRuleVar(int id)
{
	return m_RuleList[id].getVar();
}

const char * Grammar::getRuleReplacement(int id)
{
	return m_RuleList[id].getReplacement();
}

void Grammar::Clear()
{
	delete[] m_RuleList;
}

Grammar::~Grammar()
{
}
