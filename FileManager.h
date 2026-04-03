#pragma once
#include "GrammarManager.h" 
class FileManager
{
public:
	FileManager();
	FileManager(GrammarManager* m_GrammarManager);
	~FileManager();
	void Open(string fileName);
	void Save();
	void SaveAs(string fileName);
	void Close();

private:
	GrammarManager * m_GrammarManager;
	string m_FileName;
};

