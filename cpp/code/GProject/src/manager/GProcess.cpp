//===============================================
#include "GProcess.h"
#include "GSQLite.h"
#include "GDebug.h"
//===============================================
GProcess* GProcess::m_instance = 0;
//===============================================
GProcess::GProcess() {
    __CLASSNAME__ = __FUNCTION__;
}
//===============================================
GProcess::~GProcess() {

}
//===============================================
GProcess* GProcess::Instance() {
    if(m_instance == 0) {
        m_instance = new GProcess;
    }
    return m_instance;
}
//===============================================
void GProcess::process(int argc, char** argv) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    bool lRunFlag = 0;
    std::string lKey = "";
    for(int i = 1; i < argc;) {
    	std::string lKey = argv[i++];
        if(lKey == "test") {test(argc, argv); lRunFlag = 1; break;}
        if(lKey == "query") {query(argc, argv); lRunFlag = 1; break;}
        break;
    }
    if(lRunFlag == 0) help(argc, argv);
}
//===============================================
void GProcess::help(int argc, char** argv) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    const char* lModule = "gp_sqlite";
    printf("\n");
    printf("%s\n", "Description:");
    printf("\t%s\n", "Operations sur le module gp_opencv.");
    printf("\n");
    printf("%s\n", "Utilisation:");
    printf("\t\%s : %s\n", lModule, "afficher aide");
    printf("\t\%s %s : %s\n", lModule, "query", "executer fichier requete");
    printf("\n");
}
//===============================================
void GProcess::test(int argc, char** argv) {
    GDebug::Instance()->write(__CLASSNAME__, "::", __FUNCTION__, "()", _EOA_);
    GSQLite::Instance()->test(argc, argv);
}
//===============================================
void GProcess::query(int argc, char** argv) {
    std::string lSqlite = "lSqlite";
    std::string lDatabaseFile = "data/sqlite/database.dat";
    std::string lQueryFile = "data/sqlite/query.sql";
    GSQLite::Instance()->createSQLite(lSqlite, lDatabaseFile, lQueryFile);
    GSQLite::Instance()->querySQLite(lSqlite); 
    GSQLite::Instance()->deleteSQLite(lSqlite);
}
//===============================================
