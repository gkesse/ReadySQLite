//================================================
#ifndef _GSQLite_
#define _GSQLite_
//================================================
#include "GInclude.h"
//================================================
#if defined(_GUSE_SQLITE_ON_)
//================================================
typedef int (*GSQLITE_EXEC)(void*,int,char**,char**);
typedef void (*GSQLITE_FUNC)(sqlite3_context*,int,sqlite3_value**);
//================================================
typedef struct _sGParams sGParams;
//================================================
class GSQLite {
private:
    GSQLite();

public:
    ~GSQLite();
    static GSQLite* Instance();
    void test(int argc, char** argv);
    void createSQLite(std::string sqliteId, std::string databaseFile, std::string queryFile);
    void execSQLite(std::string sqliteId, std::string sqlQuery, GSQLITE_EXEC callback = 0, void* params = 0);
    void funcSQLite(sqlite3* sqliteDb, std::string funcName, GSQLITE_FUNC funcPtr, int argc);
    void querySQLite(std::string sqliteId);
    void showSQLite(std::string sqliteId);
    void deleteSQLite(std::string sqliteId);
    
private:
    static int onCallbackSQLite(void* params, int argc, char** argv, char** cols);
    static void onMd5(sqlite3_context* context, int argc, sqlite3_value** argv);

private:
    const char* __CLASSNAME__;
    static GSQLite* m_instance;
    std::map<std::string, sqlite3*> m_sqliteMap;
    std::map<std::string, std::string> m_stringMap;
    std::map<std::string, sGParams*> m_paramsMap; 
};
//===============================================
#endif
//===============================================
#endif
//================================================
