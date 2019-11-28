#include "databasecreator.h"
#include <fstream>

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>


void databasecreator::createDatabaseFile() {
	std::string tablename = "cedict";
	try {

		std::string dest = "cedict.db3";
		SQLite::Database    db(dest, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		SQLite::Transaction transaction(db);
		db.exec("DROP TABLE IF EXISTS cedict");
		db.exec("CREATE TABLE " + tablename + "(id INTEGER PRIMARY KEY, pinyin adLongVarWChar,pinyinnumbered adLongVarWChar,simplified adLongVarWChar ,traditional adLongVarWChar,basicpinyin Text)");
		std::cout << "Created cedict table and database" << std::endl;
		transaction.commit();
	}
	catch (std::exception & e) {
		std::cout << "exception: " << e.what() << std::endl;
	}
}
void databasecreator::createFavoritesTable() {
	try {
		std::cout << "Creating favorites table" << std::endl;
		std::string dest = "cedict.db3";
		std::string tablename = "favorites";
		SQLite::Database    db(dest, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		SQLite::Transaction transaction(db);
		db.exec("DROP TABLE IF EXISTS favorites");
		db.exec("CREATE TABLE " + tablename + "(id INTEGER PRIMARY KEY,notes TEXT,cedictid INTEGER, FOREIGN KEY(cedictid) REFERENCES cedict(id) )");
		std::cout << "Finished Creating favorites table "<< std::endl;
		transaction.commit();
	}
	catch (std::exception & e) {
		std::cout << "exception: " << e.what() << std::endl;
	}

}
void databasecreator::createtagnameTable(){
	try {
		std::cout << "Creating tagnames table" << std::endl;
		std::string dest = "cedict.db3";
		std::string tablename = "tagnames";
		SQLite::Database    db(dest, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		SQLite::Transaction transaction(db);
		db.exec("DROP TABLE IF EXISTS tagnames");
		db.exec("CREATE TABLE " + tablename + "(id INTEGER PRIMARY KEY,name TEXT)");
		std::cout << "Finished Creating tagnames table "<< std::endl;
		transaction.commit();
	}
	catch (std::exception & e) {
		std::cout << "exception: " << e.what() << std::endl;
	}
}
void databasecreator::createfavoritetagsTable(){
	try {
		std::cout << "Creating tagnames table" << std::endl;
		std::string dest = "cedict.db3";
		std::string tablename = "favoritetags";
		SQLite::Database    db(dest, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		SQLite::Transaction transaction(db);
		db.exec("DROP TABLE IF EXISTS "+tablename);
		db.exec("CREATE TABLE " + tablename + "(id INTEGER PRIMARY KEY,tagid INTEGER,favoriteid INTEGER,FOREIGN KEY(tagid) REFERENCES tagnames(id), FOREIGN KEY(favoriteid) REFERENCES favorites(id))");
		std::cout << "Finished Creating "+tablename+" table "<< std::endl;
		transaction.commit();
	}
	catch (std::exception & e) {
		std::cout << "exception: " << e.what() << std::endl;
	}
}


void databasecreator::createDefinitionsTable() {
	try {
		std::cout << "Creating Definitions table" << std::endl;
		std::string dest = "cedict.db3";
		std::string tablename = "definitions";
		SQLite::Database    db(dest, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		SQLite::Transaction transaction(db);
		db.exec("DROP TABLE IF EXISTS definitions");
		db.exec("CREATE TABLE " + tablename + "(id INTEGER PRIMARY KEY,definition adLongVarWChar,cedictid INTEGER, FOREIGN KEY(cedictid) REFERENCES cedict(id) )");
		std::cout << "Finished Creating favorites table " << std::endl;
		transaction.commit();
	}
	catch (std::exception & e) {
		std::cout << "exception: " << e.what() << std::endl;
	}

}

void databasecreator::createdatabase(std::vector<cedict*> bag) {

	std::string tablename = "cedict";

	
	
	std::cout << "Done setting bag" << std::endl;

	std::cout << "Begin database creation" << std::endl;

	createDatabaseFile();
	createFavoritesTable();
	createtagnameTable();
	createfavoritetagsTable();
	createDefinitionsTable();
	int counter = 1;
	std::cout << "Begin inserting all that into new table" << std::endl;
	try {




		std::string dest = "cedict.db3";
		SQLite::Database    db(dest, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		SQLite::Transaction transaction(db);





		for (auto it = bag.begin(); it < bag.end(); ++it) {
			std::shared_ptr<SQLite::Statement>  query;
			query.reset(new SQLite::Statement(db, "INSERT INTO cedict (id,pinyin,pinyinnumbered,simplified,traditional,basicpinyin) VALUES(?,?,?,?,?,?)"));

			query->bind(1, counter);
			query->bind(2, (*it)->getPinyin());
			query->bind(3, (*it)->getPinyinNumbered());
			query->bind(4, (*it)->getSimplified());
			query->bind(5, (*it)->getTraditional());
			query->bind(6, (*it)->getPinyinBasic());
			while (query->executeStep())
			{
			}
			//std::cout << "Done inserting cedict now lets do definition";
			auto defs = (*it)->getDefinitions();
			for (auto ji = defs.begin(); ji < defs.end(); ++ji) {
				//insertdefinitions(*ji, counter);
				if ((*ji) != "") {
					query.reset();
					query.reset(new SQLite::Statement(db, "INSERT INTO definitions (definition,cedictid) VALUES(?,?)"));
					query->bind(1, *ji);
					query->bind(2, counter);
					while (query->executeStep())
					{
					}
				}

			}
			++counter;

		}


		std::cout << "Finished inserting " << counter << " dictonary objects" << std::endl;
		transaction.commit();
		
	}

	catch (std::exception & e) {
		std::cout << "exception: " << e.what() << std::endl;


	}


}