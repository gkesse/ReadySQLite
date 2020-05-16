//================================================
#ifndef _GSQLite_
#define _GSQLite_
//================================================
#include "GInclude.h"
//================================================
#if defined(_GUSE_SQLITE_ON_)
//================================================
typedef int (*GSQLITE_CB)(void*,int,char**,char**);
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
    void querySQLite(std::string sqliteId);
    void showSQLite(std::string sqliteId);
    void execSQLite(std::string sqliteId, std::string sqlQuery, GSQLITE_CB callback = 0, void* params = 0);
    void deleteSQLite(std::string sqliteId);
    
private:
    static int onCallbackSQLite(void* params, int argc, char** argv, char** cols);

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
