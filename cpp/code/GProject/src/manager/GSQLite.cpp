//===============================================
#include "GSQLite.h"
#include "GFile.h"
#include "GString.h"
#include "GDebug.h"
//================================================
#if defined(_GUSE_SQLITE_ON_)
//===============================================
GSQLite* GSQLite::m_instance = 0;
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
    createSQLite(lSqlite, lDatabaseFile, lQueryFile);
    querySQLite(lSqlite); 
    deleteSQLite(lSqlite);
}
//===============================================
void GSQLite::createSQLite(std::string sqliteId, std::string databaseFile, std::string queryFile) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    sqlite3* lSqlite;
    sGHeader* lHeader = new sGHeader;
    int lRes = sqlite3_open(databaseFile.c_str(), &lSqlite);
    if(lRes != SQLITE_OK){std::cout << sqlite3_errmsg(lSqlite) << "\n"; exit(0);}
    m_sqliteMap[sqliteId] = lSqlite;
    m_stringMap[sqliteId] = queryFile;
    m_headerMap[sqliteId] = lHeader;
}
//===============================================
void GSQLite::querySQLite(std::string sqliteId) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    std::string lQueryFile = m_stringMap[sqliteId];
    sGHeader* lHeader = m_headerMap[sqliteId];
    lHeader->flag = 1;
    lHeader->id = 5;
    lHeader->col = 20;    
    GFile::Instance()->createIfstream(sqliteId, lQueryFile);
    std::string lSqlQuery = GFile::Instance()->getData(sqliteId);
    GFile::Instance()->deleteIfstream(sqliteId);
    execSQLite(sqliteId, lSqlQuery, onCallbackSQLite, lHeader);
}
//===============================================
void GSQLite::execSQLite(std::string sqliteId, std::string sqlQuery, GSQLITE_CB callback, void* params) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    sqlite3* lSqlite = m_sqliteMap[sqliteId];
    char* lError;
    int lRes = sqlite3_exec(lSqlite, sqlQuery.c_str(), callback, params, &lError);
    if(lRes != SQLITE_OK){std::cout << lError << "\n"; sqlite3_free(lError); exit(0);}
}
//===============================================
void GSQLite::deleteSQLite(std::string sqliteId) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    sqlite3* lSqlite = m_sqliteMap[sqliteId];
    sGHeader* lHeader = m_headerMap[sqliteId];
    delete lHeader;
    sqlite3_close(lSqlite);
    m_sqliteMap[sqliteId] = 0;
    m_headerMap[sqliteId] = 0;
}
//===============================================
int GSQLite::onCallbackSQLite(void* params, int argc, char** argv, char** cols) {
    GDebug::Instance()->write("GSQLite", "::", __FUNCTION__, "()", _EOA_);    
    sGHeader* lHeader = (sGHeader*)params;
    if(lHeader->flag == 1) {
        for(int i = 0; i < argc; i++) {
            std::string lUpper = GString::Instance()->toUpper(cols[i]);
            printf("|");
            if(i == 0) {printf("%*s", -lHeader->id, lUpper.c_str());}
            else {printf("%*s", -lHeader->col, lUpper.c_str());}
        }
        printf("|\n"); 
        for(int i = 0; i < argc; i++) {
            printf("|");
            if(i == 0) {for(int i = 0; i < lHeader->id; i++) {printf("-");}}
            else {for(int i = 0; i < lHeader->col; i++) {printf("-");}}
        }
        printf("|\n");    
    }
    lHeader->flag = 0;
    for(int i = 0; i < argc; i++) {
        printf("|");
        if(i == 0) {printf("%*s", -lHeader->id, argv[i] ? argv[i] : "NULL");}
        else {printf("%*s", -lHeader->col, argv[i] ? argv[i] : "NULL");}
    }
    printf("|\n");    
    return 0;
}
//===============================================
#endif
//===============================================
