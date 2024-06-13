#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

namespace seneca
{
	class SpellChecker
	{
		std::string m_badWords[6]{};
		std::string m_goodWords[6]{};
		size_t m_numReplace[6] = { 0 };
	public:
		SpellChecker(const char* filename);
		void operator()(std::string& text);  //this operator searches text and replaces any misspelled word with the correct version.
		void showStatistics(std::ostream& out) const; //inserts into the parameter how many times each misspelled word has been replaced by the correct word using the current instance.
	};
}

#endif

