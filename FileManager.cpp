#include "FileManager.h"
#include <fstream>



FileManager::FileManager()
{
}


FileManager::FileManager(GrammarManager * grammarManager)
{
	m_FileName = "defaultFile";
	m_GrammarManager = grammarManager;
}

FileManager::~FileManager()
{
}

void FileManager::Open(string fileName)
{
	Close();
	ifstream f(fileName + ".txt");
	int grammarsCount;
	int ruleNum = 0;
	f >> grammarsCount;
	for (int i = 0; i < grammarsCount; i++)
	{
		string start;
		f >> start;
		m_GrammarManager->AddGrammar(start);
		int rulesCount;
		f >> rulesCount;
		for (int j = 0; j < rulesCount; j++)
		{
			string ruleVar;
			char ruleReplacement[100];
			f >> ruleVar >> ruleReplacement;
			m_GrammarManager->AddRule(i, ruleVar, ruleReplacement);
		}
	}
	f.close();
}

void FileManager::Save()
{
	ofstream f(m_FileName + ".txt");
	int grammarsCount = m_GrammarManager->getSize() ;
	f << grammarsCount << endl;
	for (int i = 0; i < grammarsCount; i++)
	{
		string start = m_GrammarManager->getGrammarStartVar(i);
		f << start << endl;
		int rulesCount = m_GrammarManager->getGrammarRuleCount(i);
		f << rulesCount << endl;
		for (int j = 0; j < rulesCount; j++)
		{
			string ruleVar = m_GrammarManager->getGrammarRuleVar(i, j);
			const char* ruleReplacement = m_GrammarManager->getGrammarRuleReplacement(i, j);

			//if the rule was removed
			if (ruleReplacement == nullptr)
			{
				continue;
			}
			f << ruleVar << " " << ruleReplacement << endl;
		}
	}
	f.close();
}

void FileManager::SaveAs(string fileName)
{
	m_FileName = fileName;
	Save();
}

void FileManager::Close()
{
	m_GrammarManager->Clear();
}
