

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <SQLiteCpp/SQLiteCpp.h>
#include "cedict.cpp"

#include "databasecreator.cpp"
#include <fstream>
#ifdef SQLITECPP_ENABLE_ASSERT_HANDLER
namespace SQLite
{
/// definition of the assertion handler enabled when SQLITECPP_ENABLE_ASSERT_HANDLER is defined in the project (CMakeList.txt)
void assertion_failed(const char* apFile, const long apLine, const char* apFunc, const char* apExpr, const char* apMsg)
{
    // Print a message to the standard error output stream, and abort the program.
    std::cerr << apFile << ":" << apLine << ":" << " error: assertion failed (" << apExpr << ") in " << apFunc << "() with message \"" << apMsg << "\"\n";
    std::abort();
}
}
#endif


cedict* parseLine(std::string input){
  cedict* value = new cedict();
  //std::string

// Get simplified and traditional characters
  std::string delimiter = " ";
  value->setTraditional(input.substr(0,input.find(delimiter)));
  input.erase(0, input.find(delimiter) + delimiter.length());
  //cout<<"traditional:"<<value->getTraditional()<<endl;
  value->setSimplified(input.substr(0,input.find(delimiter)));
  //cout<<"Simplified:"<<value->getSimplified()<<endl;
  input.erase(0, input.find(delimiter) + delimiter.length()+1);

// Get numbered pinyin
delimiter = "]";
value->setPinyinNumbered(input.substr(0,input.find(delimiter)));
input.erase(0, input.find(delimiter) + delimiter.length());
//cout<<"Numbered Pinyin:"<<value->getPinyinNumbered()<<endl;
value->setBasicPinyin();
//cout<<"basic pinyin:"+value->getBasicPinyin()<<endl;
input.erase(0, input.find("//") +std::string("//").length());

  value->setDefinitions(input);

  value->setPinyin(value->getPinyinNumbered());
  value->setBasicPinyin();
  //std::cout<<"Pinyin:"<<value->getPinyin()<<std::endl;;
  //value->printDefinitions();
  return value; 
}


int main ()
{
 	std::ifstream myfile;
	myfile.open("cedict_ts.u8");
	std::string line;
	auto d = new databasecreator();

	std::vector<cedict> parsedList;

	if (myfile.is_open())
	{
		std::vector<cedict*> definitions;
		std::cout << "begin parse" << std::endl;
		while (getline(myfile, line))
		{
			if (line.at(0) != '#') {
				// cout << line << '\n';
				definitions.push_back(parseLine(line));
			}
		}
		myfile.close();
		std::cout << "done parse. length:" << definitions.size() << " Start creating database"<<std::endl;
		
		
		databasecreator().createdatabase(definitions);
		std::cout << "Begin cleaning up data deleting everything added" << std::endl;
		for (auto p : definitions)
		{
			delete p;
		}
		definitions.clear();
		std::cout << "done clearing data" << std::endl;
	}
	else std::cout << "Unable to open file";


    return EXIT_SUCCESS;
}
