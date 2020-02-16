
#include <fstream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

#include <memory>
class TestData{
    public:
        void GenerateFavoritesData(){
            {
                try {
                    std::string dest = "cedict.db3";
                    SQLite::Database    db(dest, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
                    SQLite::Transaction transaction(db);
                    std::shared_ptr<SQLite::Statement>  query;
                    query.reset(new SQLite::Statement(db, "select id from cedict"));
                
                    while (query->executeStep())
                    {
                        std::string id = query->getColumn(0);
                        std::shared_ptr<SQLite::Statement>  queryinner;
                        queryinner.reset(new SQLite::Statement(db,"insert into favorites (cedictid,notes) values (?,'test data')"));
                        queryinner->bind(1,id);
                        while(queryinner->executeStep()){};
                    };

                    transaction.commit();
                }
                catch (std::exception & e) {
                    std::cout << "exception: " << e.what() << std::endl;
                }

            }
        }
};