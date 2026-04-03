#include "GrammarManager.h"
#include <iostream>
using namespace std;

GrammarManager::GrammarManager()
{

}

int GrammarManager::AddRule(int grammarId, string variable, const char* replacement)
{
	char* p = new char[strlen(replacement) + 1];
	*p = *replacement;
	m_Replacements.push_back(p);
	Rule rule(variable, replacement);
	return m_GrammarList[grammarId].AddRule(rule);
}

int GrammarManager::AddGrammar(string startVar)
{
	m_GrammarList.push_back(Grammar(m_GrammarList.size(), startVar));
	return m_GrammarList.size() - 1;
}

void GrammarManager::RemoveRule(int grammarId, int number)
{
	m_GrammarList[grammarId].removeRule(number) ;
}

int GrammarManager::Union(int grammarNum1, int grammarNum2)
{
	int grammarNum = AddGrammar("U"); 
	Grammar& grammar1 = m_GrammarList[grammarNum1];
	Grammar& grammar2 = m_GrammarList[grammarNum2];

	string as = grammar1.getStartVar();
	string bs = grammar2.getStartVar();
	const char* a = as.c_str();
	const char* b = bs.c_str();

	AddRule(grammarNum,"U", a);
	AddRule(grammarNum,"U", b);

	// andding the rules from grammar 1 and 2
	for (int i = 0; i < grammar1.getRuleCount(); i++)
	{
		AddRule(grammarNum, grammar1.getRule(i).getVar(), grammar1.getRule(i).getReplacement());
	}
	for (int i = 0; i < grammar2.getRuleCount(); i++)
	{
		AddRule(grammarNum, grammar2.getRule(i).getVar(), grammar2.getRule(i).getReplacement());
	}
	return grammarNum;
}

int GrammarManager::Concat(int grammarNum1, int grammarNum2)
{
	int grammarNum = AddGrammar("C");
	Grammar& grammar1 = m_GrammarList[grammarNum1];
	Grammar& grammar2 = m_GrammarList[grammarNum2];

	string newRule = grammar1.getStartVar() + grammar2.getStartVar();
	const char* a = newRule.c_str();

	AddRule(grammarNum, "C", a);
	
	// andding the rules from grammar 1 and 2
	for (int i = 0; i < grammar1.getRuleCount(); i++)
	{
		AddRule(grammarNum, grammar1.getRule(i).getVar(), grammar1.getRule(i).getReplacement());
	}
	for (int i = 0; i < grammar2.getRuleCount(); i++)
	{
		AddRule(grammarNum, grammar2.getRule(i).getVar(), grammar2.getRule(i).getReplacement());
	}
	return grammarNum;
}

int GrammarManager::Iter(int grammarNum1)
{
	int grammarNum = AddGrammar("I");
	Grammar& grammar1 = m_GrammarList[grammarNum1];

	string newRule = grammar1.getStartVar() + "I";

	const char* a = newRule.c_str();

	AddRule(grammarNum, "I", a);
	AddRule(grammarNum, "I", "");

	// andding the rules from grammar 1
	for (int i = 0; i < grammar1.getRuleCount(); i++)
	{
		AddRule(grammarNum, grammar1.getRule(i).getVar(), grammar1.getRule(i).getReplacement());
	}
	return grammarNum;
}

void GrammarManager::List()
{
	cout << "The list of grammars is:" << endl;
	for (int i = 0; i < m_GrammarList.size(); i++)
	{
		cout << m_GrammarList[i].getId() << endl;
	}
}

void GrammarManager::Print(int grammarId)
{
	cout << endl;
	cout << "Grammar N:   " << grammarId << endl;
	cout << "Starts with: " << m_GrammarList[grammarId].getStartVar() << endl;

	for (int j = 0; j < m_GrammarList[grammarId].getRuleCount(); j++)
	{
		cout << "Rule N:" << j << " is: " 
			 << m_GrammarList[grammarId].getRule(j).getVar() << "->"
			 << m_GrammarList[grammarId].getRule(j).getReplacement() << endl ;
	}
	cout << endl;
}

bool GrammarManager::Chomsky(int grammarId)
{
	bool isChomsky = false;
	int count = 0;
	for (int i = 0; i < m_GrammarList[grammarId].getRuleCount(); i++)
	{
		if (( strlen(getGrammarRuleReplacement(grammarId, i)) == 0) ||
			((strlen(getGrammarRuleReplacement(grammarId, i)) == 1 && (getGrammarRuleReplacement(grammarId, i)[0] >= 'a' && getGrammarRuleReplacement(grammarId, i)[0] <= 'z')) ||
			( strlen(getGrammarRuleReplacement(grammarId, i)) == 1 && (getGrammarRuleReplacement(grammarId, i)[0] >= '0' && getGrammarRuleReplacement(grammarId, i)[0] <= '9'))) ||
			( strlen(getGrammarRuleReplacement(grammarId, i)) == 2 && (getGrammarRuleReplacement(grammarId, i)[0] >= 'A' && getGrammarRuleReplacement(grammarId, i)[0] <= 'Z')) &&
			((strlen(getGrammarRuleReplacement(grammarId, i)) == 2 && (getGrammarRuleReplacement(grammarId, i)[1] >= 'A' && getGrammarRuleReplacement(grammarId, i)[1] <= 'Z'))))
		{
			count++;
		}
	}
	if (count == m_GrammarList[grammarId].getRuleCount())
	{
		isChomsky = true;
	}
	return isChomsky;
}

bool GrammarManager::CYK(int grammarId)
{
	Chomskify(grammarId);
	//CYK algorithm 
	return false;
}

bool GrammarManager::Empty(int grammarId)
{
	bool isEmpty = true;
	for (int i = 0; i < m_GrammarList[grammarId].getRuleCount(); i++)
	{
		if (m_GrammarList[grammarId].getRule(i).getReplacement() != nullptr)
		{
			isEmpty = false;
			break;
		}
	}
	return isEmpty;
}

int GrammarManager::Chomskify(int grammarId)
{
	if (Chomsky(grammarId) == true)
	{
		return grammarId;
	}
	//Chomskify

	return -1; 
}

GrammarManager::~GrammarManager()
{
}

int GrammarManager::getSize()
{
	return m_GrammarList.size();
}

string GrammarManager::getGrammarStartVar(int id)
{
	return m_GrammarList[id].getStartVar();
}

string GrammarManager::getGrammarRuleVar(int grammarId, int ruleId)
{
	return m_GrammarList[grammarId].getRuleVar(ruleId);
}

const char * GrammarManager::getGrammarRuleReplacement(int grammarId, int ruleId)
{
	return m_GrammarList[grammarId].getRuleReplacement(ruleId);
}

int GrammarManager::getGrammarRuleCount(int id)
{
	return m_GrammarList[id].getRuleCount();
}

void GrammarManager::Clear()
{
	for (int i = 0; i < m_GrammarList.size(); i++)
	{
		m_GrammarList[i].Clear();
	}
	for (int i = 0; i < m_Replacements.size(); i++)
	{
		delete[] m_Replacements[i];
	}
	m_Replacements.clear();
	m_GrammarList.clear();
}

