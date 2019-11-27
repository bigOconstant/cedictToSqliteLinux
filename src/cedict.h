#include <iostream>
#include <vector>
class cedict {
public:
	cedict();
	cedict(std::string Traditional, std::string Simplified, std::string PinyinNumbered, std::string Pinyin);
	cedict(const cedict& c2);
	std::string getTraditional();
	std::string getSimplified();
	std::string getPinyinNumbered();
	std::string getPinyin();
	std::vector<std::string> getDefinitions();
	int getId();

	void setTraditional(std::string input);
	void setSimplified(std::string input);
	void setPinyinNumbered(std::string input);
	void setPinyin(std::string input);
	//void setDefinition(std::string input);
	void addDefinition(std::string input);
	void setDefinitions(std::string input);
	void setId(int input);
	void setBasicPinyin(std::string str);
	void printDefinitions();
	std::string getBasicPinyin();

	std::string convertToTones(std::string input);



private:
	std::string Traditional;
	std::string Simplified;
	std::string PinyinNumbered;
	std::string Pinyin;
	std::string BasicPinyin;
	std::vector<std::string> Definitions;
	int Id;



};