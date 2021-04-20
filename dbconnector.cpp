#include "dbconnector.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QException>
#include <QSqlError>
#include <QDebug>

DBConnector::DBConnector() : QObject() {}

DBConnector::DBConnector(QString driver, QString dbName) : QObject() {
    db = QSqlDatabase::addDatabase(driver);
    db.setDatabaseName(dbName);
};

bool DBConnector::isConnected(){

    return db.open();
}


QList<PrjGroupAnswer> DBConnector::getPrjGroup(){

    if(!db.open()) throw db.lastError();

    QString queryText = "SELECT prj_group_id, name FROM prj_group";

    QList<PrjGroupAnswer> list = QList<PrjGroupAnswer>();

    QSqlQuery query = QSqlQuery(db);

    if (!query.exec(queryText)){ throw query.lastError(); }

    while(query.next()){
        list.append(PrjGroupAnswer(query.value(0).toInt(),query.value(1).toString()));
}
    return list;

}

QList<PrjGroupAddrbookAnswer>  DBConnector::getPrjGroupAddrbook(int id){

    if(!db.open()) throw db.lastError();

    QString queryText = ("SELECT prj_group_addrbook_id, family, first_name FROM prj_group_addrbook WHERE prj_group_id = ") + QString::number(id);

    QList<PrjGroupAddrbookAnswer> list = QList<PrjGroupAddrbookAnswer>();

    QSqlQuery query = QSqlQuery(db);

    if (!query.exec(queryText)){ throw query.lastError(); }

    while(query.next()){
        list.append(PrjGroupAddrbookAnswer(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString()));
}

    return list;

}

void DBConnector::deletePrjGroupAddrbook(int id){

        if(!db.open()) throw db.lastError();

        QString queryText = "delete from prj_group_addrbook where prj_group_addrbook_id='" + QString::number(id) + "';";

        QSqlQuery query = QSqlQuery(db);

        if (!query.exec(queryText)) throw query.lastError();
        else {
            emit callMessage("Запись с id " + QString::number(id) + " удалена");
        }

    }


void  DBConnector::addchangePrjGroupAddrbook(PrjGroupAddrbookAnswer a){

    if(!db.open()) throw db.lastError();

    QString queryText;
    QString messageText;

    if (a.prj_group_addrbook_id != -1){
        queryText="UPDATE prj_group_addrbook SET family='" + a.family + "', first_name='" + a.first_name + "' WHERE prj_group_addrbook_id = '" + QString::number(a.prj_group_addrbook_id) + "';";
        messageText = "Обновлена запись с id " + QString::number(a.prj_group_addrbook_id) + "\nНовые данные:\nfamily = " +  a.family + "\nfirst_name = " + a.first_name;
    }
    else{
        queryText="INSERT INTO `prj_group_addrbook` (prj_group_id, family, first_name, addrbook_type_id) "
                 "VALUES ('" + QString::number(a.prj_group_id) + "', '" + a.family + "', '" + a.first_name + "', 1);";
        messageText = "Добавлена запись в таблицу с id " + QString::number(a.prj_group_id) + "\nНовые данные:\nfamily = " +  a.family + "\nfirst_name = " + a.first_name;
    }

    QSqlQuery query(db);

    if (!query.exec(queryText)) throw query.lastError();
    else {
        emit callMessage(messageText);
    }

}
