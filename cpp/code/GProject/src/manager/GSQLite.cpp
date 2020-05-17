//===============================================
#include "GSQLite.h"
#include "GFile.h"
#include "GString.h"
#include "GShell.h"
#include "GDebug.h"
//================================================
#if defined(_GUSE_SQLITE_ON_)
//===============================================
GSQLite* GSQLite::m_instance = 0;
//===============================================
struct _sGParams {
    int flag;
    int id;
    int col;
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> datas;
};
//===============================================
GSQLite::GSQLite() {
    __CLASSNAME__ = __FUNCTION__;
}
//===============================================
GSQLite::~GSQLite() {

}
//===============================================
GSQLite* GSQLite::Instance() {
    if(m_instance == 0) {
        m_instance = new GSQLite;
    }
    return m_instance;
}
//===============================================
void GSQLite::test(int argc, char** argv) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    std::string lSqlite = "lSqlite";
    std::string lDatabaseFile = "data/sqlite/database.dat";
    std::string lQueryFile = "data/sqlite/query.sql";
    GSQLite::Instance()->createSQLite(lSqlite, lDatabaseFile, lQueryFile);
    GSQLite::Instance()->querySQLite(lSqlite); 
    GSQLite::Instance()->deleteSQLite(lSqlite);
}
//===============================================
void GSQLite::createSQLite(std::string sqliteId, std::string databaseFile, std::string queryFile) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    sqlite3* lSqlite;
    sGParams* lParams = new sGParams;
    int lRes = sqlite3_open(databaseFile.c_str(), &lSqlite);
    if(lRes != SQLITE_OK){std::cout << sqlite3_errmsg(lSqlite) << "\n"; exit(0);}
    funcSQLite(lSqlite, "md5", onMd5, 1);
    m_sqliteMap[sqliteId] = lSqlite;
    m_stringMap[sqliteId] = queryFile;
    m_paramsMap[sqliteId] = lParams;
}
//===============================================
void GSQLite::execSQLite(std::string sqliteId, std::string sqlQuery, GSQLITE_EXEC callback, void* params) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    sqlite3* lSqlite = m_sqliteMap[sqliteId];
    char* lError;
    int lRes = sqlite3_exec(lSqlite, sqlQuery.c_str(), callback, params, &lError);
    if(lRes != SQLITE_OK){std::cout << lError << "\n"; sqlite3_free(lError); exit(0);}
}
//===============================================
void GSQLite::funcSQLite(sqlite3* sqliteDb, std::string funcName, GSQLITE_FUNC funcPtr, int argc) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    sqlite3_create_function(sqliteDb, funcName.c_str(), argc, SQLITE_UTF8, NULL, funcPtr, NULL, NULL);
}
//===============================================
void GSQLite::querySQLite(std::string sqliteId) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    std::string lQueryFile = m_stringMap[sqliteId];
    sGParams* lParams = m_paramsMap[sqliteId];
    lParams->flag = 1;
    lParams->id = 5;
    lParams->col = 20;    
    GFile::Instance()->createIfstream(sqliteId, lQueryFile);
    std::string lSqlQuery = GFile::Instance()->getData(sqliteId);
    GFile::Instance()->deleteIfstream(sqliteId);
    execSQLite(sqliteId, lSqlQuery, onCallbackSQLite, lParams);
    showSQLite(sqliteId);
}
//===============================================
void GSQLite::showSQLite(std::string sqliteId) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    std::string lQueryFile = m_stringMap[sqliteId];
    sGParams* lParams = m_paramsMap[sqliteId];
    int lSize = lParams->headers.size();
    for(int i = 0; i < lSize; i++) {
        std::string lValue = lParams->headers.at(i);
        printf("|");
        if(i == 0) {printf("%*s", -lParams->id, lValue.c_str());}
        else {printf("%*s", -lParams->col, lValue.c_str());}
    }
    if(lSize != 0) {printf("|\n");}
    for(int i = 0; i < lSize; i++) {
        printf("|");
        if(i == 0) {for(int i = 0; i < lParams->id; i++) {printf("-");}}
        else {for(int i = 0; i < lParams->col; i++) {printf("-");}}
    }
    if(lSize != 0) {printf("|\n");}
    int lRows = lParams->datas.size();
    for(int j = 0; j < lRows; j++) {
        std::vector<std::string> lValueMap = lParams->datas.at(j);
        for(int i = 0; i < lSize; i++) {
            std::string lValue = lValueMap.at(i);
            printf("|");
            if(i == 0) {printf("%*s", -lParams->id, lValue.c_str());}
            else {printf("%*s", -lParams->col, lValue.c_str());}
        }
        printf("|\n");
    }
}
//===============================================
void GSQLite::deleteSQLite(std::string sqliteId) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    sqlite3* lSqlite = m_sqliteMap[sqliteId];
    sGParams* lParams = m_paramsMap[sqliteId];
    delete lParams;
    sqlite3_close(lSqlite);
    m_sqliteMap[sqliteId] = 0;
    m_paramsMap[sqliteId] = 0;
}
//===============================================
int GSQLite::onCallbackSQLite(void* params, int argc, char** argv, char** cols) {
    GDebug::Instance()->write("GSQLite", "::", __FUNCTION__, "()", _EOA_);    
    sGParams* lParams = (sGParams*)params;
    if(lParams->flag == 1) {
        for(int i = 0; i < argc; i++) {
            std::string lUpper = GString::Instance()->toUpper(cols[i]);
            lParams->headers.push_back(lUpper);
        }
    }
    lParams->flag = 0;
    std::vector<std::string> lValueMap;
    for(int i = 0; i < argc; i++) {
        std::string lValue = argv[i] ? argv[i] : "NULL";
        lValueMap.push_back(lValue);
    }
    lParams->datas.push_back(lValueMap);
    return 0;
}
//===============================================
void GSQLite::onMd5(sqlite3_context* context, int argc, sqlite3_value **argv) {
    GDebug::Instance()->write("GSQLite", "::", __FUNCTION__, "()", _EOA_);    
    if(argc == 1) {
        std::string lText = (char*)sqlite3_value_text(argv[0]);
        char lCommand[256];
        char lOuput[256];
        sprintf(lCommand, "echo %s | md5sum | awk '{print $1}'", lText.c_str());
        GShell::Instance()->run(lCommand, lOuput, 255, 1);
        sqlite3_result_text(context, lOuput, -1, SQLITE_TRANSIENT);
    }
}
//===============================================
#endif
//===============================================
