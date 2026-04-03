#include "Rule.h"

Rule::Rule()
{
	m_Variable = '\0';
	m_Replacement = nullptr;
}

Rule::Rule(string variable, const char* replacement)
{
	m_Variable = variable;
	int size = strlen(replacement);
	m_Replacement = new char[size + 1];
	strcpy_s(m_Replacement, size + 1, replacement);
}

string Rule::getVar()
{
	return m_Variable;
}

const char* Rule::getReplacement()
{
	return m_Replacement;
}

bool Rule::isEmpty()
{
	if (m_Replacement == nullptr)
	{
		return true;
	}
	return false;
}

Rule::~Rule()
{
	//if (m_Replacement)
	//{
	//	delete[] m_Replacement;
	//}
}