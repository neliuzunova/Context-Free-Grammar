#pragma once
#include "Grammar.h"
#include <vector>


class GrammarManager
{
public:
	GrammarManager();
	int AddGrammar(string startVar); // returns grammar number
	int AddRule(int grammarId, string variable, const char* replacement); //returns rule number
	void RemoveRule(int grammarId, int number);

	int Union(int grammarNum1, int grammarNum2); // returns new grammar number
	int Concat(int grammarNum1, int grammarNum2); // returns new grammar number
	int Iter(int grammarNum1);  // returns new grammar number

	void List(); // list of grammars
	void Print(int grammarId);

	bool Chomsky(int grammarId);
	bool CYK(int grammarId); //not ready
	int Chomskify(int grammarId); //not ready
	bool Empty(int grammarId);
	~GrammarManager();

	int getSize();
	string getGrammarStartVar(int id);
	string getGrammarRuleVar(int grammarId, int ruleId);
	const char* getGrammarRuleReplacement(int grammarId, int ruleId);
	int getGrammarRuleCount(int id);

	void Clear();

private:
	vector<Grammar> m_GrammarList; //List
	vector<const char*> m_Replacements;
};

