#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include "structures.h"
#include <QList>
#include <QObject>
#include <QSqlDatabase>

class DBConnector : public QObject
{
    Q_OBJECT

public:
    DBConnector();
    DBConnector(QString driver, QString dbname);

    bool isConnected();

    QList<PrjGroupAnswer> getPrjGroup();
    QList<PrjGroupAddrbookAnswer> getPrjGroupAddrbook(int id);

    void addchangePrjGroupAddrbook(PrjGroupAddrbookAnswer prjGroupAddrbookAnswer);
    void deletePrjGroupAddrbook(int id);

private:
    QSqlDatabase db;


signals:
    void callMessage(QString text);
};

#endif // DBCONNECTOR_H
