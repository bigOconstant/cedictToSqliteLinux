
#include <iostream>
#include <vector>
class databasecreator
{
public:
	void createdatabase(std::vector<cedict*> input);
	
	void createDefinitionsTable();
	void createDatabaseFile();
	void insertcedict(cedict* input, int counter);
	void insertdefinitions(std::string input, int cedictid);

};

