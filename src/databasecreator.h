
#include <iostream>
#include <vector>
class databasecreator
{
public:
	void createdatabase(std::vector<cedict*> input);
	
	void createDefinitionsTable();
	void createDatabaseFile();
	void insertcedict(cedict* input, int counter);
	void createFavoritesTable();
	void createtagnameTable();
	void createcolorsTable();
	void createfavoritetagsTable();
	void createSearchHistoryTable();

	void insertdefinitions(std::string input, int cedictid);

};

